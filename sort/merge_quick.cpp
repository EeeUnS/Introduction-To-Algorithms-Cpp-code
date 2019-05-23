
#include "pch.h"
using namespace std;
int b[] = { 12,10 ,43,43 ,23,-78,123,56,45,123 ,56,56,98,45,123,56,98,41,90,24 ,45};//,-78,45,

void mergesort(int a[], int low, int high);

void quicksort(int A[],int start ,int end);

//int partition(int A[],int p,int r);

int main()
{
	
	int num = sizeof(b) / sizeof(int);


	quicksort(b, 0, num - 1);

	for (int i = 0; i < num; i++)
		cout << b[i] << " ";
	cout << endl;
	return 0;
}

void mergesort(int a[], int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = (low + high) / 2;
		mergesort(a, low, pivot);
		mergesort(a, pivot + 1, high);

		int i = low, j = pivot + 1;
		queue<int>arr;

		while ((i <= pivot) && (j <= high))
		{
			if (a[i] <= a[j])
			{
				arr.push(a[i]);
				i++;
			}
			else
			{
				arr.push(a[j]);
				j++;
			}
		}

		while (i <= pivot)
		{
			arr.push(a[i]);
			i++;
		}

		while (j <= high)
		{
			arr.push(a[j]);
			j++;
		}

		for (int i = low; i <= high; i++)
		{
			a[i] = arr.front();
			arr.pop();
		}
	}
}

void quicksort(int A[], int start, int end)
{
	if (start < end)
	{
		int x = A[end];
		int i = start - 1;

		for (int j = start; j < end - 1; j++)
		{
			if (A[j] <= x)
			{
				i++;
				swap(A[i], A[j]);
			}
		}
		swap(A[i + 1], A[end]);
		int q = i + 1;
		quicksort(A, start, q - 1);
		quicksort(A, q + 1, end);
	}
	return;
}

//int partition(int A[], int start, int end)
//{
//	int x = A[end];
//	int i =  start- 1;
//	for (int j = start; j < end - 1; j++)
//	{
//		if (A[j] <= x)
//		{
//			i++;
//			swap(A[i], A[j]);
//		}
//	}
//	swap(A[i + 1], A[end]);
//	return i + 1;
//}
