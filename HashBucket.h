#pragma once
#include<iostream>
#include<vector>

using namespace std;

static size_t BKDRHash(const char* str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

template<class K>
struct HashFuner
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct HashFuner<string>
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};
template<class K, class V>
struct HashBucketNode
{
	HashBucketNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
	K _key;
	V _value;
	HashBucketNode* _next;
};

template<class K, class V, class HashFun = HashFuner<string>>
class HashBucket
{
	typedef HashBucketNode<K,V>  KVNode;
public:
	HashBucket()
		:_size(0)
	{}
	HashBucket(size_t size)
		:_size(size)
	{
		_table.resize(size);
	}

	HashBucket(const HashBucket<K, V, HashFun>& ht)
	{
		this->_size = ht._size;
		this->_table.resize(ht._table.size());
		for (size_t i = 0; i < ht._table.size(); ++i)
		{
			KVNode* cur = ht._table[i];
			while (cur)
			{
				this->Insert(cur->_key, cur->_value);   // capacity为0，NO
				cur = cur->_next;
			}
		}
	}
	HashBucket<K, V>& operator = (const HashBucket<K, V, HashFun>& ht)
	{
		swap(ht._size, _size);
		swap(ht._table, _table);
		return *this;
	}

	~HashBucket()
	{
		for (int i = 0; i < _table.size(); i++)
		{
			KVNode* cur = _table[i];
			while (cur)
			{
				KVNode* del = cur;
				cur = cur->_next;
				delete cur;
			}
		}
		_size = 0;
	}

	bool Insert(const K& key, const V& value)
	{
		_CheckCapacity();  //只做了扩容 没有重新排列
		int index = HashFunc(key);
		KVNode* tmp = new KVNode(key, value);
		KVNode* prev = _table[index];
		KVNode* cur = prev;
		cur = cur->_next;
		if (prev->_value == value)
			return false;
		while (cur)
		{
			if (cur->_value == value)
				return false;
			cur = cur->_next;
			prev = prev->_next;
		}
		prev->_next = tmp;
		_size++;
		return true;
	}

	bool Remove(const K& key)
	{
		size_t index = _HashFunc(key);
		KVNode* cur = _table[index];
		KVNode* prev = Findprev();
		if (!prev)
			return false;
		KVNode* del = prev->_next;
		prev->_next = del->_next;
		delete del;
		size--;
		reuturn true;
	}

	V& Find(const K& key)
	{
		size_t index = _HashFunc(key);
		KVNode* cur = _table[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur->_value;
			}
			cur = cur->_next;
		}
		exit(-1);
	}

	
private:
	size_t HashFunc(const K& key)
	{
		HashFun keytype;
		return (keytype(key) % _table.size());
	}

	void _CheckCapacity()
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,

			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,

			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,

			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,

			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,

			1610612741ul, 3221225473ul, 4294967291ul
		};
		if (_size >= _table.size())
		{
			for (int i = 0; i < _PrimeSize; i++)
			{
				if (_table.size() < _PrimeList[i])
				{
					_table.resize(_PrimeList[i])
						break;
				}
			}

			/*for (int i = 0; i < _table.size(); i++)
			{
				KVNode* cur = _table[i];
				while (!cur && !cur._next)
				{
					cur = cur->_next;
				}
			}*/
		}
	}
	KVNode* Findprev(const K& key)
	{
		size_t index = _HashFunc(key);
		KVNode* cur = _table[index];
		KVNode* prev = cur;
		if (!cur)
		{
			return NULL;
		}
		cur = cur->_next;
		while (cur)
		{
			if (cur->_key == key)
			{
				return prev;
			}
			cur = cur->_next;
			prev = prev->_next;
		}
		if (prev->_key != key)
			return NULL;
		return prev;
	}
private:
	vector<KVNode*> _table;
	size_t _size;
};