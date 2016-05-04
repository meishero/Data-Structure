#pragma once
#include<assert.h>
using namespace std;

template<class K, class V>
struct BSTNode
{
	BSTNode(const K& key = 0, const V& value = 0)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
	
	K _key;
	V _value;
	BSTNode<K, V>* _left;
	BSTNode<K, V>* _right;
};

template<class K, class V>
class BinarySearchTree
{
	typedef BSTNode<K, V> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}
	BinarySearchTree(Node** array, size_t size)
		:_root(NULL)
	{
		assert(array);
		for (int i = 0; i < size; i++)
		{
			Insert_R(array[i]->_key, array[i]->_value);
		}
	}
	bool Insert(const K&key, const V& value)
	{
		if (!_root)
			_root = new Node(key, value);
		Node* cur = _root;
		Node* parent = cur;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key == key)
				return false;
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		if (key > parent->_key)
			parent->_right = new Node(key, value);
		if (key < parent->_key)
			parent->_left = new Node(key, value);
		return true;
	}
	bool Insert_R(const K& key, const V& value)
	{
		//Node*& root = _root;
		return _Insert_R(_root, key, value);
	}

	Node* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}
	Node* Find(const K& key)
	{
		if (!_root)
			return NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key == key)
				return cur;
			else
				cur = cur->_left;
		}
		return NULL;
	}
	bool Remove_R(const K&key)
	{
		Node* root = _root;
		_Remove_R(root, key);
	}
	bool Remove(const K&key)
	{
		if (!_root)
			return false;
		Node* cur = _root;
		Node* parent = cur;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//注意！先判断要删除的节点是不是根节点，不然下面会炸！
				if (cur == _root)
				{
					if (!cur->_left && !cur->_right)
					{
						delete cur;
						_root = NULL;
					}
					if (cur->_right)
						cur = cur->_right;
				}
				//当前节点左右有一个为空的情况，将不为空部分的链上去
				if (!cur->_left)
				{
					if (parent->_left == cur)
						parent->_left = cur->_right;
					if (parent->_right == cur)
						parent->_right = cur->_right;
					delete cur;
					return true;
				}
				else if (!cur->_right)
				{
					if (parent->_left == cur)
						parent->_left = cur->_left;
					if (parent->_right == cur)
						parent->_right = cur->_left;
					delete cur;
					return true;
				}
				//左右都有节点，找到节点第一个叶子结点
				else
				{
					Node* tmp = cur->_right;
					Node* prev = cur;
					while (tmp)
					{
						prev = tmp;
						tmp = tmp->_left;
					}
					//注意！这里判断cur的右孩子是不是为空，为空就没有叶子节点，拿cur右孩子顶替！

					swap(prev->_key, cur->_key);
					swap(prev->_value, cur->_value);
					if (prev == cur->_right)
					{
						cur->_right = prev->_right;
					}
					delete prev;
					return true;
				}
			}
		}
		return false;
	}
		
	
	void InOrder_R()
	{
		Node* cur = _root;
		_InOrder(cur);
	}
private:
	bool _Insert_R(Node*& root, const K& key, const V& value)
	{
		if (!root)
		{
			Node* newNode = new Node(key, value);
			root = newNode;
			return true;
		}
		if (key == root->_key)
			return false;
		if (key > root->_key)
			_Insert_R(root->_right, key, value);
		else 
			_Insert_R(root->_left, key, value);
	}
	Node* _Find_R(Node* cur, const K& key)
	{
		if (!cur)
			return NULL;
		if (cur->_key == key)
			return cur;
		else if (cur->_key > key)
			_Find_R(cur->_left, key);
		else
			_Find_R(cur->_right, key);
	}
	void _InOrder(Node* cur)
	{
		if (!cur)
		{
			return;
		}
		_InOrder(cur->_left);
		cout << cur->_value << "->";
		_InOrder(cur->_right);
	}

	bool _Remove_R(Node*& root, const K& key)
	{
		if (!root)
			return false;
		Node* cur = root;
		if (cur->_key > key)
		{
			_Remove_R(cur->_left, key);
		}
		else if (cur->_key < key)
		{
			_Remove_R(cur->_right, key);
		}
		else
		{
			if (!cur->_left)
			{
				//cur 是上一次左或右的别名！
				Node* del = cur;
				cur = cur->_right;
				//delete del;
				return true;
			}
			else if (!cur->_right)
			{
				Node* del = cur;
				cur = cur->_left;
				//delete del;
				return true;
			}
			else
			{
				Node* tmp = cur->_right;
				Node* prev = cur;
				while (tmp->_left)
				{
					prev = tmp;
					tmp = tmp->_left;
				}
				swap(cur->_key, tmp->_key);
				swap(cur->_value, tmp->_value);
				prev->_left = tmp->_right;
				delete tmp;
				return true;
			}
		}
	}
private:
	Node* _root;
};

void Test1()
{
	int array[] = { 6, 8, 3, 4, 8, 7, 1, 2, 1};
	BSTNode<int,int>* data[8];
	for (int i = 0; i < 8; i++)
	{
		data[i] = new BSTNode<int, int>(array[i], array[i]);
	}
	BinarySearchTree<int, int> t1(data, 8);
	t1.InOrder_R();
	t1.Insert_R(5, 5);
	t1.InOrder_R();
	BSTNode<int,int>* tmp = t1.Find_R(1);
	cout << tmp->_value << endl;
}
void Test2()
{
	BinarySearchTree<int, int> t2;
	t2.Insert(1, 1);
	t2.Insert(3, 3);
	t2.Insert(7, 7);
	t2.Insert(2, 2);
	t2.Insert(0, 0);
	t2.Insert(9, 9);
	t2.Insert(4, 4);
	t2.Insert(5, 5);
	t2.InOrder_R();
	BSTNode<int,int>* tmp = t2.Find(4);
	cout << tmp->_value << endl;
	tmp = t2.Find(8);
	cout << tmp->_value << endl;
}
void Test3()
{
	int array[] = { 6, 8, 3, 4, 8, 7, 1, 2, 9, 5 };
	BSTNode<int, int>* data[10];
	for (int i = 0; i < 10; i++)
	{
		data[i] = new BSTNode<int, int>(array[i], array[i]);
	}
	BinarySearchTree<int, int> t1(data, 10);
	//t1.Remove(2);
	//t1.InOrder_R();
	//t1.Remove(4);
	//t1.InOrder_R();
	t1.Remove(8);
	t1.InOrder_R();
	t1.Remove(6);
	//t1.InOrder_R();
}