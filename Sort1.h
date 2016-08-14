#pragma once 

//[]
void _MergeSection(int* a, int* tmp, int left1, int right1, int left2, int right2)
{
	int first1 = left1;
	int first2 = left2;
	int last1 = right1;
	int last2 = right2;

	int index = 0;
	while (first1 <= last1 && first2 <= last2)
	{
		if (a[first1] >= a[first2])
		{
			tmp[index++] = a[first2++];
		}
		else
			tmp[index++] = a[first1++];
	}
	while (first1 <= last1)
	{
		tmp[index++] = a[first1++];
	}
	while (first2 <= last2)
	{
		tmp[index++] = a[first2++];
	}

	for (int i = 0; i < index; ++i)
	{
		a[left1 + i] = tmp[i];
	}
}

void _MergeSort(int* a, int* tmp, int left, int right)
{
	assert(tmp);
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		_MergeSort(a, tmp, left, mid);
		_MergeSort(a, tmp, mid + 1, right);
		_MergeSection(a, tmp, left, mid, mid + 1, right);
	}
}

//[]
void MergeSort(int* a, size_t size)
{
	assert(a);
	int* tmp = new int[size];
	_MergeSort(a, tmp, 0, size - 1);
	delete tmp;
}

void TestMergeSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	MergeSort(array, 10);
	cout << "MergeSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//LSD-- Least Significant Digit first
void RadixSort(int* a, size_t size)
{
	//返回位数
	int max = 10;
	int digit = 1;
	int radix = 1;
	for (size_t i = 0; i < size; ++i)
	{
		while (a[i] >= max)
		{
			++digit;
			max *= 10;
		}
	}

	int* count = new int[10];
	int* start = new int[10];
	int* tmp = new int[size];
	while (digit)
	{
		memset(count, 0, sizeof(int)* 10);
		memset(start, 0, sizeof(int)* 10);
		memset(tmp, 0, sizeof(int)*size);
		//先分配到各自的位置
		for (int i = 0; i < size; ++i)
		{
			int tmp = a[i];
			int unit = (tmp / radix) % 10;
			++count[unit];
		}

		//计算出start，这次的起始位置加上之前的所有元素个数，就是该元素的相对位置
		start[0] = 0;
		for (size_t i = 1; i < 10; ++i)
		{
			start[i] = count[i - 1] + start[i - 1];
		}

		//排序
		for (size_t i = 0; i < size; ++i)
		{
			int index = (a[i] / radix) % 10;
			tmp[start[index]++] = a[i];
		}

		//赋回a
		for (int i = 0; i < size; ++i)
		{
			a[i] = tmp[i];
		}
		radix *= 10;
		--digit;
	}
	delete[] count;
	delete[] start;
	delete[] tmp;
}

void TestRadixSort()
{
	int array[] = { 287, 5089, 44, 9, 39, 6, 8, 7, 1, 0, 123 };
	RadixSort(array, sizeof(array) / sizeof(int));
	cout << "RadixSort:";
	for (int i = 0; i < sizeof(array) / sizeof(int); i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//选择排序
void SelectionSort(int* a, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		int MinIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (a[j] < a[MinIndex])
			{
				MinIndex = j;
			}
		}
		swap(a[i], a[MinIndex]);
	}
}

void TestSelectionSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	SelectionSort(array, 10);
	cout << "SelectionSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//直接选择排序优化版，一次选出最大值和最小值
void SelectSort(int* a, size_t size, int left, int right)
{
	assert(a);
	int Left = left, Right = right;
	if (left >= right)
	{
		return;
	}
	if (a[left] > a[right])
	{
		swap(a[left], a[right]);
	}
	while (Left < Right)
	{
		if (a[Left + 1] >= a[Right - 1])
		{
			if (a[right] < a[Left + 1])
			{
				swap(a[right], a[Left + 1]);
			}
			else
			{
				--Right;
			}
			if (a[left] > a[Right - 1])
			{
				swap(a[left], a[Right - 1]);
			}
			else
			{
				++Left;
			}
		}
		if (a[Left + 1] < a[Right - 1])
		{
			if (a[right] < a[Right - 1])
			{
				swap(a[right], a[Right - 1]);
			}
			else
			{
				--Right;
			}
			if (a[left] > a[Left + 1])
			{
				swap(a[left], a[Left + 1]);
			}
			else
			{
				++Left;
			}
		}
	}
	SelectSort(a, size, ++left, --right);
}

void TestSelectSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	SelectSort(array, 10, 0, 9);
	cout << "SelectSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//升序大堆
void AjustDown(int* a, size_t size, int root)
{
	assert(a);
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (a[child + 1] && a[child] < a[child + 1])
		{
			++child;
		}
		if (a[parent] < a[child])
		{
			swap(a[parent], a[child]);
			parent = child;
			child = child * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, size_t size)
{
	assert(a);
	for (int i = (size - 2) / 2; i >= 0; --i)
	{
		AjustDown(a, size, i);
	}
	for (int index = size - 1; index > 1; --index)
	{
		swap(a[index], a[0]);
		AjustDown(a, index - 1, 0);
	}
}

void TestHeapSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	HeapSort(array, 10);
	cout << "HeapSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}