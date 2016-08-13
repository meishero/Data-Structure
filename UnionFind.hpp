#pragma once
#include<iostream>
using namespace std;

void Set(int people1, int people2, int*& UnionFind)
{
	while (UnionFind[people2] > 0)
	{
		people2 = UnionFind[people2];
	}
	while (UnionFind[people1] > 0)
		people1 = UnionFind[people1];
	//此时，people1指向一个根朋友圈；
	if (people1 != people2) //防止(2,3),(3,2)这种情况
	{
		UnionFind[people1] += UnionFind[people2];
		UnionFind[people2] = people1;
	}
}

int friends(int(*r)[2], int n, int m)
{
	int* UnionFind = new int[n + 1];
	int count = 0; //朋友圈个数
	for (int i = 0; i < n + 1; i++)
		UnionFind[i] = -1;
	for (int i = 0; i < m; i++)
	{
		int first = r[i][0];
		int second = r[i][1];
		Set(first, second, UnionFind);
	}
	for (int i = 1; i < n + 1; i++)
	{
		if (UnionFind[i] < 0)
			count++;
	}
	return count;
}
void test()
{
	int Array[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 3, 2 } };
	int count = friends(Array, 5, 4);
	cout << count << endl;
}

