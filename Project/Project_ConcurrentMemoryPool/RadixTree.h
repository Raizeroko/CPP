#pragma once

#include "Utils.h"

// 基数树优化PAGE_ID与Span的映射结构
// 主要优化：可以取消访问映射时的加锁


// BITS：系统可以申请的最多页数位
// 32位系统: 2^32 / 2^13 ==> BITS = 32-13 = 19
// 64位系统: 2^64 / 2^13 ==> BITS = 64-13 = 55

// 一层基数树
template <int BITS>
class RadixTreeLevel1 {
private:
    // LENGTH: 最多页数
    static const int LENGTH = 1 << BITS; 
    // _radixTree: 二级指针，基数树指针，指向映射关系空间地址
    void** _radixTree;
public:
    typedef uintptr_t Number;

    // 构造函数，申请空间并设置空间数据为0
    // explicit关键字：要求显示调用构造函数
    // _radixTree[_pageID] ==> SpanNode*
    // 开辟空间总大小 = 最多页数(LENGTH) * sizeof(void*) "sizeof(void*) == sizeof(SpanNode*)"
    explicit RadixTreeLevel1() {
        // 基数树空间总大小:2^BIS * 4 = 2^(BIS+2)
        size_t radixSize = LENGTH * sizeof(void*);
        // 内存大小对齐
        size_t alignRadixSize = Utils::AlignSize(radixSize);
        // 向系统申请页数: 2^(BIS+2) / 2^13 = 2^(BIS-11)
        _radixTree = (void**)Utils::SystemAllocate(alignRadixSize >> PAGE_SHIFT);
        // 初始化空间
        memset(_radixTree, 0, alignRadixSize);
    }

    // 建立映射(PAGE_ID ==> SpanNode)
    void set(Number key, void* value) {
        _radixTree[key] = value;
    }

    // 获取映射的SpanNode地址
    void* find(Number key) const {
        // 超出范围返回空
        if ((key >> BITS) > 0) {
            return NULL;
        }
        return _radixTree[key];
    }

};


// 两层基数树
template <int BITS>
class RadixTreeLevel2 {
private:
    // ROOT_LENGTH = 2^ROOT_BITS
    static const int ROOT_BITS = 5;
    static const int ROOT_LENGTH = 1 << ROOT_BITS;
    // LEAF_LENGTH = 2^(BITS - ROOTBITS)
    static const int LEAF_BITS = BITS - ROOT_BITS; 
    static const int LEAF_LENGTH = 1 << LEAF_BITS;
    // 两层基数树包含的全部叶节点个数：2^BITS = 2^(LEAF_BITS + ROOT_BITS)

    // 第二层结构
    struct Leaf {
        void* values[LEAF_LENGTH];
    };

    // 第一层结构
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
        // 申请内存并构建两层基数树，确保每一个所有映射都有空间。
        bool ret = Ensure(0, 1 << BITS);
        // assert在Release下会被优化，不能把Ensure直接放里。
        assert(ret);
    }

    bool Ensure(Number start, size_t n) {
        for (Number key = start; key <= start + n - 1;) {
            // 先确定第一层映射
            const Number level1 = key >> LEAF_BITS;

            // 超出范围
            if (level1 >= ROOT_LENGTH) return false;

            // 当前映射没有分配空间
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

// 三层基数树
// 与前两种基数树不同，为了应对64系统下页总数过长(e.g. PAGE_SHIFT = 13, BITS = 64 - 13 = 51)，最多可能有2^51页，所以页号最多有51位二进制。
// 将页号转为二进制位,并将该段二进制分为三段：高位，中位，地位（e.g. 高位[51, 35], 中位[34, 18], 低位[17,1])
// 第一层按输入页号的高位映射
// 第二层按输入页号的中位映射
// 第三层按输入页号的地位映射
template <int BITS>
class RadixTreeLevel3 {
private:
    // 高位与中位的映射位长
    // INTERIOR_LENGTH = 2^((BITS + 2) / 3)
    static const int INTERIOR_BITS = (BITS + 2) / 3; 
    static const int INTERIOR_LENGTH = 1 << INTERIOR_BITS;
    // 地位的映射位长
    // LEAF_LENGTH = 2^(BITS - 2 * INTERIOR_BITS)
    static const int LEAF_BITS = BITS - 2 * INTERIOR_BITS; 
    static const int LEAF_LENGTH = 1 << LEAF_BITS;

// 成员对象
private:
    // 三层结构
    struct Leaf {
        void* values[LEAF_LENGTH];
    };

    struct Node {
        Node* ptrs[INTERIOR_LENGTH];
    };
    // 一层结构
    Node* _root;

//成员函数
public:
    typedef uintptr_t Number;
    explicit RadixTreeLevel3() {
        _root = NewNode();
        PreallocateMoreMemory();
    }

    void PreallocateMoreMemory() {
        // 申请内存并构建三层基数树，确保每一个所有映射都有空间。
        bool ret = Ensure(0, 1 << BITS);
        // assert在Release下会被优化，不能把Ensure直接放里。
        assert(ret);
    }

    bool Ensure(Number start, size_t n) {
        for (Number key = start; key <= start + n - 1;) {
            // 获取key高位
            const Number high = key >> (LEAF_BITS + INTERIOR_BITS);
            // 获取key中位
            const Number mid = (key >> LEAF_BITS) & (INTERIOR_LENGTH - 1);
            // 保证hign,mid的值大于等于INTERIOR_LENGTH
            if (high >= INTERIOR_LENGTH || mid >= INTERIOR_LENGTH) return false;
            // 构建第二层结构
            if (_root->ptrs[high] == NULL) {
                Node* n = NewNode();
                if (n == NULL) return false;
                _root->ptrs[high] = n;
            }
            // 创建叶结点
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