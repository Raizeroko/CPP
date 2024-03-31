#pragma once
#include <iostream>
#include "RBT.h"



namespace zwr {
	template<class K, class V>
	class Map {
		struct MapKeyOfT {
			//这里pair加了引用，返回处也要引用，这两个引用必须同时存在！！！
			const K& operator()(const std::pair<const K, V>& kv)
			{
				return kv.first;
			}
		};

		typedef RBTree<K, std::pair<K, V>, MapKeyOfT> RBTree;
	public:

		typedef typename RBTree::const_iterator iterator;
		typedef typename RBTree::const_iterator const_iterator;

		const_iterator begin() const
		{
			return _map.begin();
		}

		const_iterator end() const	
		{
			return _map.end();
		}

		/*V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
			return ret.first->second;
		}*/


		std::pair<iterator, bool> Insert(std::pair<K, V> _data)
		{
			return _map.Insert(_data);
		}


		/*void InOrder()
		{
			_map.InOrder();
		}*/

		void Find(const K& key)
		{
			_map.Find(key);
		}
		
	private:
		RBTree _map;
	};


}
