#pragma once 

#include<iostream>
#include<string>

using namespace std;

enum Status
{
	EMPTY,
	EXIST,
	DELETE,
};

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
struct KeyValueStatusNode
{
	K _key;
	V _value;
	Status _state;
	KeyValueStatusNode()
	{}
	KeyValueStatusNode(K key, V value)
		:_key(key)
		, _value(value)
		, _state(EXIST)
	{}
};

template<class K, class V, class HashFun = HashFuner<string>>
class HashTable
{
	typedef KeyValueStatusNode<K, V>  KVSNode;
public:
	HashTable(size_t capacity)
		:_table(new KVSNode[capacity])
		, _size(0)
		, _capacity(capacity)
	{
		for (int i = 0; i < _size; i++)
		{
			_table[i]._state = EMPTY;
		}
	}

	~HashTable()
	{
		if (_table)
		{
			delete[] _table;
			_table = NULL;
		}
	}

	bool Insert(const K& key, const V& value)
	{
		_CheckCapacity();
		int i = 1;   //i作为HashFunc1的参数提高效率
		int index = HashFunc0(key);
		while (_table[index]._state == EXIST)
		{
			if (_table[index]._value == value)
				return false;
			index = HashFunc1(index, i++);
			if (index >= _capacity)
				index -= _capacity ;
		}
		_table[index]._key = key;
		_table[index]._value = value;
		_table[index]._state = EXIST;
		_size++;
		return true;
	}
	
	V& Find(const K& key)
	{
		int index = HashFunc0(key);
		int count = 1;
		while (_table[index]._state != EMPTY)
		{
			if (_table[index]._state == EXIST && _table[index]._key == key)
				return _table[index]._value;
			index = HashFunc1(index, count++);
			//????????没找到什么时候跳出
			if (index >= _capacity)
				exit(-1);
		}
		return _table[index]._value;
	}

	bool Remove(const K& key)
	{
		int index = HashFunc0(key);
		while (_table[index] != EMPTY)
		{
			if (_table[index]._state == EXIST && _table[index]._key == key)
			{
				_table[index]._state = DELETE;
				size--;
				return true;
			}
			index = HashFunc1(index, count++);
			if (index > _capacity)
			{
				index -= _capacity;
			}
		}
		return flase;

	}
	void Display()
	{
		for (int i = 0; i < _capacity; i++)
		{
			if (_table[i]._state == EMPTY)
				cout << "empty-> ";
			if (_table[i]._state == DELETE)
				cout << "delete-> ";
			else
				cout << _table[i]._key<<"-"<< _table[i]._value<<"->";
		}
	}
private:
	void _CheckCapacity()
	{
		if (_size * 10 / _capacity >= 8)
		{
			HashTable newTable(_capacity * 2);
			for (int i = 0; i < _capacity; i++)
			{
				if (_table[i]._state == EXIST)
					newTable.Insert(_table[i]._key, _table[i]._value);
			}
			Swap(newTable);
		}
	}

	void Swap(HashTable& newTable)
	{
		swap(_table, newTable._table);
		swap(_capacity, newTable._capacity);
		swap(_size, newTable._size);
	}

	size_t HashFunc0(const K& key)
	{
		HashFun keytype;
		return (keytype(key)%_capacity);
	}
	size_t HashFunc1(const size_t & key, size_t i)
	{
		return( key + 2*i-1);
	}

private:
	size_t _capacity;
	size_t _size;
	KVSNode* _table;
};

void test2()
{
	HashTable<string,string> h1(10);
	h1.Insert("w", "王少");
	h1.Insert("矩阵", "maxtrix");
	string tmp = h1.Find("w");
	h1.Display();
}