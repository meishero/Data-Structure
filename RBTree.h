#pragma once

#include<iostream>
using namespace std;


enum color
{
	RED,
	BLACK,
};
template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K, V>* _parent;
	K _key;
	V _value;
	color _color;

	RBTreeNode(K key, V value, color Color = RED)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _color(Color)
		, _parent(NULL)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	RBTree(K* array, size_t size)
	{
		for (int i = 0; i < size; i++)
		{
			Insert(array[i], array[i]);
		}
	}
	bool Insert(const K& key, const V& value)
	{
		if (!_root)
		{
			_root = new Node(key, value, BLACK);
			return true;
		}
		return _Insert(key, value);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
private:
	void _InOrder(Node* root)
	{
		if (!root)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool _Insert(const K& key, const V& value)
	{
		//Step1  插入节点
		Node* prev = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
				return false;
		}
		cur = new Node(key, value);
		if (key > prev->_key)
			prev->_right = cur;
		else
			prev->_left = cur;
		cur->_parent = prev;

		//Step2 调整
		Node* parent = prev;
		Node* grandpa = parent->_parent;
		Node* uncle = NULL;
		if (grandpa)
		{
			if (grandpa->_left == parent)
				uncle = grandpa->_right;
			else
				uncle = grandpa->_left;
		}

		while (cur != _root && parent->_color == RED)
		{
			if (cur->_color == RED && parent->_color == RED && grandpa
				&& grandpa->_color == BLACK && uncle && uncle->_color == RED)
				situation1(cur, grandpa, parent, uncle);
			else if(cur->_color == RED && parent->_color == RED && grandpa
				&& grandpa->_color == BLACK && (!uncle || uncle->_color == BLACK))
				situation2(cur, grandpa, parent, uncle);
				situation3(cur, grandpa, parent, uncle);
		}
		_root->_color = BLACK;
		return true;
	}

	void situation1(Node*& cur, Node*& grandpa, Node*& parent, Node*& uncle)
	{
		parent->_color = BLACK;
		uncle->_color = BLACK;
		grandpa->_color = RED;
		cur = grandpa;
	}
	void situation2(Node*& cur, Node*& grandpa, Node*& parent, Node*& uncle)
	{
		//右单旋
		if (parent == grandpa->_left && cur == parent->_left)
		{
			_RotateR(grandpa);

			_Link(parent);

			grandpa = parent->_right;//注意 别忘了grandpa
			parent->_color = BLACK;
			grandpa->_color = RED;
			return;
		}

		//左单旋
		else if (parent == grandpa->_right && cur == parent->_right)
		{
			_RotateL(grandpa);

			_Link(parent);

			grandpa = parent->_left;//注意 别忘了grandpa
			parent->_color = BLACK;
			grandpa->_color = RED;
			return;
		}
	}


	void situation3(Node*& cur, Node*& grandpa, Node*& parent, Node*& uncle)
	{
		if (parent->_left == cur && grandpa->_right == parent)
		{
			//对parent 右单旋转
			_RotateR(parent);
			_Link(parent);

			cur = parent->_right;

			//变成情况2了
			return;
		}
		else if (parent->_right == cur && grandpa->_left == parent)
		{
			//对parent 左单旋转
			_RotateL(parent);
			_Link(parent);

			cur = parent->_left;
			//变成情况2了
			return;
		}
	}

	//左单旋
	void _RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		parent = subR;
		
	}

	//右单旋
	void _RotateR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		parent = subL;
		
	}
	void _Link(Node* cur)
	{
		//连接左右单旋后连接问题
		if (cur->_parent == NULL)
		{
			_root = cur;
			return;
		}
		Node* parent = cur->_parent;
		if (parent->_key > cur->_key)
		{
			parent->_left = cur;
		}
		else if (parent->_key < cur->_key)
		{
			parent->_right = cur;
		}
	}
private:
	Node* _root;
};

void test()
{
	int array[] = {10, 40, 30, 60, 90, 70, 20, 50 ,80, 55, 65 };
	RBTree<int, int> rbt(array,11);
	rbt.InOrder();
}