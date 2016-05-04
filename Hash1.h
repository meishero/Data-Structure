#pragma once 

#include<iostream>
#include<string>

using namespace std;

enum Status
{
	EMPTY,
	EXITS,
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

template<class K, class HashFun = HashFuner<K>>
class HashTable
{
public:
	HashTable()
		:_table(NULL)
		, _capacity(0)
		, _size(0)
		, _stateTable(NULL)
	{}
	HashTable(size_t size)
		:_table(new K[size])
		, _size(0)
		, _capacity(size)
		, _stateTable(new Status[size])
	{
		for (int i = 0; i < size; i++)
		{
			_stateTable[i] = EMPTY;
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

	bool Insert(const K& key)
	{
		_CheckCapacity();
		int index = HashFunc(key);
		while (_stateTable[index] == EXITS)
		{
			if (_table[index] == key)
				return false;
			index++;
			if (index == _capacity)
				index = 0;
		}
		_table[index] = key;
		_stateTable[index] = EXITS;
		_size++;
		return true;
	}

	K& Find(const K& key)
	{
		int index = HashFunc(key);
		while (_stateTable[index] != EMPTY)
		{
			if (_stateTable[index] == EXITS && _table[index] == key)
				return _table[index];
			index++;
		}
		//return;  //?????
	}

	bool Remove(const K& key)
	{
		int index = HashFunc(key);
		while (_stateTable[index] != EMPTY)
		{
			if (_stateTable[index] == EXITS && _table[index] == key)
			{
				_stateTable[index] == DELETE;
				_size--;
				return true;
			}
			if (_stateTable[index] != EXITS)
			{
				index++;
				if (index == _capacity)
					index = 0;
			}
		}
		return false;
	}
	void Display()
	{
		for (int i = 0; i<_capacity; i++)
		{
			if (_stateTable[i] == EXITS)
				cout << _table[i] << "->";
			if (_stateTable[i] == DELETE)
				cout << "DELETE->";
			else if (_stateTable[i] == EMPTY)
				cout << "EMPTY->";
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
				if (_stateTable[i] == EXITS)
					newTable.Insert(_table[i]);
			}
			Swap(newTable);
		}
	}

	size_t HashFunc(const K& key)
	{
		HashFun keytype;
		return (keytype(key)) % _capacity;
	}

	void Swap(HashTable& newTable)
	{
		swap(_table, newTable._table);
		swap(_capacity, newTable._capacity);
		swap(_size, newTable._size);
		swap(_stateTable, newTable._stateTable);
	}
private:
	K* _table;
	size_t _capacity;
	size_t _size;
	Status* _stateTable;
};

void test1()
{
	HashTable<int> h1(10);
	h1.Insert(1);
	h1.Insert(2);
	h1.Insert(3);
	h1.Insert(4);
	h1.Insert(5);
	//h1.Insert(1);
	//h1.Insert(4);
	h1.Insert(6);
	h1.Insert(7);
	//h1.Insert(8);
	h1.Insert(9);
	h1.Display();
	h1.Insert(10);
	h1.Insert(11);
	h1.Insert(12);
	//h1.Insert(28);
	h1.Display();
	h1.Find(5);
	int i = h1.Find(13);
}
void test2()
{
	HashTable<string> h1(10);
	h1.Insert("a");
	h1.Insert("1");
	h1.Display();
}