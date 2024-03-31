#pragma once

#include <iostream>
#include "RBT.h"

namespace zwr {
	template<class K>
	class Set {
		struct SetKeyOfT {
			const K& operator()(const K& key)
			{
				return key;
			}
		};

		typedef RBTree<K, K, SetKeyOfT> RBTree;
	public:
		typedef typename RBTree::const_iterator iterator;
		typedef typename RBTree::const_iterator const_iterator;

		const_iterator begin() const
		{
			return _set.begin();
		}

		const_iterator end() const
		{
			return _set.end();
		}

		std::pair<iterator, bool> Insert(const K& _data)
		{
			return _set.Insert(_data);
		}

		void InOrder()
		{
			_set.InOrder();
		}

		void Find(const K& key)
		{
			_set.Find(key);
		}
	private:
		RBTree _set;
	};
}



