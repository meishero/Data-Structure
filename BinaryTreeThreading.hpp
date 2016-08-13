#pragma once
#include<iostream>

enum PointTag
{
	THREAD,
	LINK
};
template<class K>
struct BinaryTreeThdNode
{
	K _key;
	BinaryTreeThdNode<K>* _left;
	BinaryTreeThdNode<K>* _right;
	PointTag _leftTag;
	PointTag _rightTag;
	BinaryTreeThdNode(const K& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};


template<class K>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<K> Node;
public:
	BinaryTreeThd()
		:_root(NULL)
	{}
	BinaryTreeThd(const K* array, size_t size)
	{
		size_t index = 0;
		_root = _CreateTree(array, size, index);
	}
	void InOrderThding()
	{
		Node* prev = NULL;
		_InOrderThding(_root, prev);
		//切记 最后一个节点没有后继  要补上
		prev->_rightTag = THREAD;
	}

	void PrevOrderThding()
	{
		Node* prev = NULL;
		_PrevOrderThding(_root, prev);
		//切记 最后一个节点没有后继  要补上
		prev->_rightTag = THREAD;
	}

	void PostOrderThding()
	{
		Node* prev = NULL;
		//切记 最后一个节点是根！ 不用补！
		_PostOrderThding(_root, prev);
	}
	
	void PrevOrderThd()
	{
		Node* cur = _root;
		while (cur)
		{
			cout << cur->_key;
			if (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			else //lefttag == THREAD   向左会死循环
			{
				//经过分析 不管rightTag是什么类型 都要向右（后继/右孩子）
				cur = cur->_right;
			}
		}
	}

	void InOrderThd()
	{
		Node* cur = _root;
		while (cur)
		{
			//找到最左节点打印
			while (cur && cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_key;

			//一直找后继即可
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_key << " ";
			}

			// 跳到右子树访问
			cur = cur->_right;
		}
		
		void PrevOrderThd()
		{
			BinaryTreeNodeThd<T>* cur = _root;
			while (cur)
			{
				while (cur && cur->_leftTag == LINK)
				{
					cout << cur->_data << " ";
					cur = cur->_left;
				}
				cout << cur->_data << " ";
				cur = cur->_right;
			}

			cout << endl;
		}
		
	}
private:
	Node* _CreateTree(const K* array, size_t size, size_t& index)
	{
		Node* newnode = NULL;
		if (index < size && array[index] != '#')
		{
			newnode = new Node(array[index]);
			newnode->_left = _CreateTree(array, size, ++index);
			newnode->_right = _CreateTree(array, size, ++index);
		}
		return newnode;
	}
	void _InOrderThding(Node* cur,Node*& prev)
	{
		if (!cur)
			return;
		_InOrderThding(cur->_left, prev);

		if (!cur->_left)  //对左空的情况链接prev
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)  //等过去后又拿prev链接右(cur)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		_InOrderThding(cur->_right, prev);
	}

	void _PrevOrderThding(Node* cur, Node*& prev)
	{
		if (!cur)
			return;
		if (!cur->_left)   //注意次序  画图！！！
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		
		if (prev && !prev->_right)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		if (cur->_leftTag == LINK)
			_PrevOrderThding(cur->_left, prev);
		if (cur->_rightTag == LINK)
			_PrevOrderThding(cur->_right,prev);
	}

	void _PostOrderThding(Node* cur, Node*& prev)
	{
		if (!cur)
			return; 

		if (cur->_leftTag == LINK)
		{
			_PostOrderThding(cur->_left, prev);
		}

		if (cur->_rightTag == LINK)
		{
			_PostOrderThding(cur->_right, prev);
		}

		if (!cur->_left)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		
		if (prev && !prev->_right)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

	}
private:
	Node* _root;
};

void test()
{
	char array[] = {'A', 'B', 'C', '#' ,'#', 'D', 'E', '#' ,'#', 'F', '#', '#', 'G','#', 'H'};
	BinaryTreeThd<char> b1(array, 15);
	//b1.PrevOrderThding();
	//b1.PrevOrderThd();
	//b1.PostOrderThding();
	b1.InOrderThding();
	b1.InOrderThd();
}