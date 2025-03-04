#pragma once

#include "Utils.h"

// �������Ż�PAGE_ID��Span��ӳ��ṹ
// ��Ҫ�Ż�������ȡ������ӳ��ʱ�ļ���


// BITS��ϵͳ������������ҳ��λ
// 32λϵͳ: 2^32 / 2^13 ==> BITS = 32-13 = 19
// 64λϵͳ: 2^64 / 2^13 ==> BITS = 64-13 = 55

// һ�������
template <int BITS>
class RadixTreeLevel1 {
private:
    // LENGTH: ���ҳ��
    static const int LENGTH = 1 << BITS; 
    // _radixTree: ����ָ�룬������ָ�룬ָ��ӳ���ϵ�ռ��ַ
    void** _radixTree;
public:
    typedef uintptr_t Number;

    // ���캯��������ռ䲢���ÿռ�����Ϊ0
    // explicit�ؼ��֣�Ҫ����ʾ���ù��캯��
    // _radixTree[_pageID] ==> SpanNode*
    // ���ٿռ��ܴ�С = ���ҳ��(LENGTH) * sizeof(void*) "sizeof(void*) == sizeof(SpanNode*)"
    explicit RadixTreeLevel1() {
        // �������ռ��ܴ�С:2^BIS * 4 = 2^(BIS+2)
        size_t radixSize = LENGTH * sizeof(void*);
        // �ڴ��С����
        size_t alignRadixSize = Utils::AlignSize(radixSize);
        // ��ϵͳ����ҳ��: 2^(BIS+2) / 2^13 = 2^(BIS-11)
        _radixTree = (void**)Utils::SystemAllocate(alignRadixSize >> PAGE_SHIFT);
        // ��ʼ���ռ�
        memset(_radixTree, 0, alignRadixSize);
    }

    // ����ӳ��(PAGE_ID ==> SpanNode)
    void set(Number key, void* value) {
        _radixTree[key] = value;
    }

    // ��ȡӳ���SpanNode��ַ
    void* find(Number key) const {
        // ������Χ���ؿ�
        if ((key >> BITS) > 0) {
            return NULL;
        }
        return _radixTree[key];
    }

};


// ���������
template <int BITS>
class RadixTreeLevel2 {
private:
    // ROOT_LENGTH = 2^ROOT_BITS
    static const int ROOT_BITS = 5;
    static const int ROOT_LENGTH = 1 << ROOT_BITS;
    // LEAF_LENGTH = 2^(BITS - ROOTBITS)
    static const int LEAF_BITS = BITS - ROOT_BITS; 
    static const int LEAF_LENGTH = 1 << LEAF_BITS;
    // ���������������ȫ��Ҷ�ڵ������2^BITS = 2^(LEAF_BITS + ROOT_BITS)

    // �ڶ���ṹ
    struct Leaf {
        void* values[LEAF_LENGTH];
    };

    // ��һ��ṹ
    Leaf* _root[ROOT_LENGTH];
    
public:
    typedef uintptr_t Number;
    explicit RadixTreeLevel2() {
        memset(_root, 0, sizeof(_root));
        PreallocateMoreMemory();
    }
    /*explicit TCMalloc_PageMap2(void* (*allocator)(size_t)) {
        allocator_ = allocator;
        memset(root_, 0, sizeof(root_));
    }*/

    void PreallocateMoreMemory() {
        // �����ڴ沢���������������ȷ��ÿһ������ӳ�䶼�пռ䡣
        bool ret = Ensure(0, 1 << BITS);
        // assert��Release�»ᱻ�Ż������ܰ�Ensureֱ�ӷ��
        assert(ret);
    }

    bool Ensure(Number start, size_t n) {
        for (Number key = start; key <= start + n - 1;) {
            // ��ȷ����һ��ӳ��
            const Number level1 = key >> LEAF_BITS;

            // ������Χ
            if (level1 >= ROOT_LENGTH) return false;

            // ��ǰӳ��û�з���ռ�
            if (_root[level1] == NULL) {
                size_t leafSize = LEAF_LENGTH * sizeof(void*);
                size_t alignLeafSize = Utils::AlignSize(leafSize);
                Leaf* leaf = (Leaf*)Utils::SystemAllocate(alignLeafSize >> PAGE_SHIFT);
                assert(sizeof(*leaf) == alignLeafSize);
                if (leaf == NULL) return false;
                memset(leaf, 0, sizeof(*leaf));
                _root[level1] = leaf;
            }
            key = ((key >> LEAF_BITS) + 1) << LEAF_BITS;
        }
        return true;
    }

    void* find(Number key) const {
        const Number level1 = key >> LEAF_BITS;
        const Number level2 = key & (LEAF_LENGTH - 1);
        if ((key >> BITS) > 0 || _root[level1] == nullptr) {
            return nullptr;
        }
        return _root[level1]->values[level2];
    }
    void set(Number key, void* value) {
        const Number level1 = key >> LEAF_BITS;
        const Number level2 = key & (LEAF_LENGTH - 1); 
        assert(level1 < ROOT_LENGTH); 
        _root[level1]->values[level2] = value;
    }
    
};

// ���������
// ��ǰ���ֻ�������ͬ��Ϊ��Ӧ��64ϵͳ��ҳ��������(e.g. PAGE_SHIFT = 13, BITS = 64 - 13 = 51)����������2^51ҳ������ҳ�������51λ�����ơ�
// ��ҳ��תΪ������λ,�����öζ����Ʒ�Ϊ���Σ���λ����λ����λ��e.g. ��λ[51, 35], ��λ[34, 18], ��λ[17,1])
// ��һ�㰴����ҳ�ŵĸ�λӳ��
// �ڶ��㰴����ҳ�ŵ���λӳ��
// �����㰴����ҳ�ŵĵ�λӳ��
template <int BITS>
class RadixTreeLevel3 {
private:
    // ��λ����λ��ӳ��λ��
    // INTERIOR_LENGTH = 2^((BITS + 2) / 3)
    static const int INTERIOR_BITS = (BITS + 2) / 3; 
    static const int INTERIOR_LENGTH = 1 << INTERIOR_BITS;
    // ��λ��ӳ��λ��
    // LEAF_LENGTH = 2^(BITS - 2 * INTERIOR_BITS)
    static const int LEAF_BITS = BITS - 2 * INTERIOR_BITS; 
    static const int LEAF_LENGTH = 1 << LEAF_BITS;

// ��Ա����
private:
    // ����ṹ
    struct Leaf {
        void* values[LEAF_LENGTH];
    };

    struct Node {
        Node* ptrs[INTERIOR_LENGTH];
    };
    // һ��ṹ
    Node* _root;

//��Ա����
public:
    typedef uintptr_t Number;
    explicit RadixTreeLevel3() {
        _root = NewNode();
        PreallocateMoreMemory();
    }

    void PreallocateMoreMemory() {
        // �����ڴ沢���������������ȷ��ÿһ������ӳ�䶼�пռ䡣
        bool ret = Ensure(0, 1 << BITS);
        // assert��Release�»ᱻ�Ż������ܰ�Ensureֱ�ӷ��
        assert(ret);
    }

    bool Ensure(Number start, size_t n) {
        for (Number key = start; key <= start + n - 1;) {
            // ��ȡkey��λ
            const Number high = key >> (LEAF_BITS + INTERIOR_BITS);
            // ��ȡkey��λ
            const Number mid = (key >> LEAF_BITS) & (INTERIOR_LENGTH - 1);
            // ��֤hign,mid��ֵ���ڵ���INTERIOR_LENGTH
            if (high >= INTERIOR_LENGTH || mid >= INTERIOR_LENGTH) return false;
            // �����ڶ���ṹ
            if (_root->ptrs[high] == NULL) {
                Node* n = NewNode();
                if (n == NULL) return false;
                _root->ptrs[high] = n;
            }
            // ����Ҷ���
            if (_root->ptrs[high]->ptrs[mid] == NULL) {
                size_t leafSize = LEAF_LENGTH * sizeof(void*);
                size_t alignLeafSize = Utils::AlignSize(leafSize);
                Leaf* leaf = (Leaf*)Utils::SystemAllocate(alignLeafSize >> PAGE_SHIFT);
                if (leaf == NULL) return false;
                memset(leaf, 0, sizeof(*leaf));
                _root->ptrs[high]->ptrs[mid] = (Node*)(leaf);
            }
            
            key = ((key >> LEAF_BITS) + 1) << LEAF_BITS;
        }
        return true;
    }

    void* find(Number key) const {
        const Number high = key >> (LEAF_BITS + INTERIOR_BITS);
        const Number mid = (key >> LEAF_BITS) & (INTERIOR_LENGTH - 1);
        const Number low = key & (LEAF_LENGTH - 1);
        if ((key >> BITS) > 0 ||
            _root->ptrs[high] == NULL || _root->ptrs[high]->ptrs[mid] == NULL) {
            return NULL;
        }
        return ((Leaf*)(_root->ptrs[high]->ptrs[mid]))->values[low];
    }
    void set(Number key, void* value) {
        assert(key >> BITS == 0);
        const Number high = key >> (LEAF_BITS + INTERIOR_BITS);
        const Number mid = (key >> LEAF_BITS) & (INTERIOR_LENGTH - 1); 
        const Number low = key & (LEAF_LENGTH - 1);
        if (((Leaf*)(_root->ptrs[high]->ptrs[mid]))->values[low] == nullptr) {
            int x;
        }
        ((Leaf*)(_root->ptrs[high]->ptrs[mid]))->values[low] = value;
    }
    

private:
    Node* NewNode() {
        size_t nodeSize = INTERIOR_LENGTH * sizeof(void*);
        size_t alignNodeSize = Utils::AlignSize(nodeSize);
        Node* result = (Node*)Utils::SystemAllocate(alignNodeSize >> PAGE_SHIFT);

        if (result != NULL) {
            int x = sizeof(*result);
            memset(result, 0, sizeof(*result));
        }
        
        return result;
    }

};