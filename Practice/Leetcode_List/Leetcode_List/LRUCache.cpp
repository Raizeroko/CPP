#include "List.h"

// MySolution
class LRUCache {
    unordered_map<int, list<pair<int, int>>::iterator> _harsh;
    list<pair<int, int>> _list;
    int _capacity;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }

    int get(int key) {
        if (!_harsh.count(key)) return -1;
        auto it = _harsh[key];
        _list.splice(_list.begin(), _list, it);
        return _list.front().second;
    }

    void put(int key, int value) {
        if (_harsh.count(key)) {
            // 已经存在
            auto it = _harsh[key];
            it->second = value;
            _list.splice(_list.begin(), _list, it);
        }
        else {
            // 不存在
            if (_list.size() == _capacity) {
                // LRU缓存已满
                pair<int, int> kv = _list.back();
                _list.pop_back();
                _harsh.erase(kv.first);
            }
            // 未满
            _list.push_front({ key, value });
            _harsh.insert({ key, _list.begin() });

        }
    }
};



// MySolution
class LRUCache {
private:
    list<pair<int, int>> _list; //key,value
    unordered_map<int, list<pair<int, int>>::iterator> _map; // key, list_ptr
    int _capacity;

public:
    LRUCache(int capacity)
        :_capacity(capacity)
    {
    }

    int get(int key) {
        // 不在缓存中
        if (!_map.count(key)) return -1;
        auto it = _map[key];
        // 更新位置
        _list.splice(_list.begin(), _list, it);
        return it->second;
    }

    void put(int key, int value) {
        if (_map.count(key)) {
            // 在缓存中
            auto it = _map[key];
            // 更新位置
            it->second = value;
            _list.splice(_list.begin(), _list, it);
        }
        else {
            // 不在缓存中
            if (_list.size() == _capacity) {
                int pop_key = _list.back().first;
                _map.erase(pop_key);
                _list.pop_back();

            }
            _list.push_front({ key, value });
            _map[key] = _list.begin();
        }

    }
};
