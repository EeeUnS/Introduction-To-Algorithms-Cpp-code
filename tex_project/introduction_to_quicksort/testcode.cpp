
/*
1. HOARE VS LOMUTO 
중복값 x

최악 : 정렬된것 순정렬 역정렬.
평균 :랜덤


2. 
PARALLELIZATION
HYBRID SORT
insertion
3way partition

*/
#include<iostream>
#include<algorithm>
#include<fstream>
#include<random>
#include<time.h>
#include<thread>
#include<mutex>
#include<utility>
using namespace std;
const int MAX = 10000000; //1000000 100000000


int A[MAX];
int B[MAX];
int C[MAX];
int lomuto_partition(int A[], int start, int end);
void insertion_sort(int a[], int start, int end);//end를 포함한다.
int Hoare_partition(int arr[], int low, int high);
std::mt19937_64 rng;

void Print(int A[])
{
	for (int i = 0; i < MAX; i++)
	{
		std::cout << A[i] << '\n';
	}
}

void make_a()
{
	for (int i = 0; i < MAX; i++)
	{
		A[i] = i;
		B[i] = i;
	}
}
void make_ab()
{
	for (int i = 0; i < MAX; i++)
	{
		A[i] = MAX - i;
		B[i] = MAX - i;
	}
}


void i_quicksort(int A[], int start, int end);
// +insertion
void l_quicksort(int A[], int start, int end);
// lumoto
void h_quicksort(int A[], int start, int end);
// hoamo
void t_quicksort(int A[], int start, int end);
// thread
void ti_quicksort(int A[], int start, int end);
// thread insertion
void tw_quicksort(int A[], int start, int end);
// 3wp
void ittw_quicksort(int a[], int l, int r);
// insertion thread 3wp
void Quick3way(int a[], int lo, int hi);

void  RANDOMIZE_IN_PLACE(int A[])
{
	for (int i = 0; i < MAX; i++)
	{
		std::uniform_int_distribution<int>distribution(i, MAX - 1);
		std::swap(A[i], A[distribution(rng)]);
	}
}
//////************************************************************************************************************
int main()
{
	clock_t start, end;
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	std::uniform_int_distribution<int>distribution(0, 1000);
	make_a();
	rng.seed(std::random_device()());
	
	for (int i = 0; i < 10; i++)
	{
		for (int i = 0; i < MAX; i++)
		{
			B[i] = distribution(rng);
		}
		RANDOMIZE_IN_PLACE(A);
		/*for (int i = 0; i < MAX; i++)
		{
			B[i] = A[i];
		}*/

		for (int i = 0; i < MAX; i++)
		{
			C[i] = 0;
		}
		std::cout << i + 1 << "회" <<  " & " ;
		start = clock();
		Quick3way(A, 0, MAX - 1);
		//h_quicksort(A, 0, MAX - 1);
		//lomuto_partition(A, 0, MAX - 1);
		//Hoare_partition(A, 0, MAX - 1);
		//t_quicksort(A, 0, MAX - 1);
		std::sort(A,A + MAX);
		end = clock();
		//Print(A);
		std::cout << (long double)(end - start) / CLOCKS_PER_SEC << " & ";

		start = clock();
		//std::sort(B, B + MAX);
		Quick3way(B, 0, MAX - 1);
		//h_quicksort(B, 0, MAX - 1);
		//l_quicksort(B, 0, MAX - 1);
		//Hoare_partition(B, 0, MAX - 1);
		//lomuto_partition(B, 0, MAX - 1);
		//i_quicksort(B, 0, MAX - 1);
		//tw_quicksort(B, 0, MAX - 1);
		//std::sort(B, B + MAX);//12345678~
		end = clock();
		//Print(B);
		std::cout << (long double)(end - start) / CLOCKS_PER_SEC << " & "  ;


		start = clock();
		//std::sort(C, C + MAX);
		Quick3way(C, 0, MAX - 1);
		//Quick3way(B, 0, MAX - 1);
		//h_quicksort(B, 0, MAX - 1);
		//l_quicksort(B, 0, MAX - 1);
		//Hoare_partition(B, 0, MAX - 1);
		//lomuto_partition(B, 0, MAX - 1);
		//i_quicksort(B, 0, MAX - 1);
		//tw_quicksort(B, 0, MAX - 1);
		//std::sort(B, B + MAX);//12345678~
		end = clock();
		//Print(B);
		std::cout << (long double)(end - start) / CLOCKS_PER_SEC << " \\\\ \\hline  " << '\n';






	}
}
//////************************************************************************************************************
int lomuto_partition(int arr[], int start, int end)
{

	/*std::uniform_int_distribution<int>distribution(start, end);
	std::swap(arr[distribution(rng)], arr[end]);*/
	//std::swap(arr[start], arr[end]);
	int x = arr[(start + end)/2];
	int i = start - 1;
	for (int j = start; j < end; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[end]);
	return i + 1;
}

int Hoare_partition(int arr[], int start, int end)
{
	//std::uniform_int_distribution<int>distribution(start, end);
	//std::swap(arr[distribution(rng)], arr[end]);
	//std::swap(arr[start], arr[end]);
	int x = arr[end], i = start - 1, j = end + 1;
	while (1) {
		do  
			j--;
		while (arr[j] > x);
		do  
			i++;
		while (arr[i] < x);

		if (i < j)
			swap(arr[i], arr[j]);
		else
			return j;
	}
}

/*


	int i = low;
	int j = high;
	int pivot = arr[low + (low + high) / 2]; // pivot
	while (1)
	{
		while (arr[j] > pivot);
		{
			--j;
		}

		while (arr[i] < pivot);
		{
			++i;
		}

		if (i >= j)
		{
			return j;

		}
		std::swap(arr[i], arr[j]);
		++i;
		--j;
	}
	*/



void insertion_sort(int arr[], int start, int end) //end를 포함한다.
{
	for (int i = start; i <= end; i++)
	{
		int item = arr[i];
		int j = i;
		while (--j >= 0 && item < arr[j])
		{
			arr[j + 1] = arr[j];
		}
		arr[++j] = item;
	}
}

//template<typename T>
void l_quicksort(int A[], int start, int end)
{
	if (start >= end)
		return;

	int q = lomuto_partition(A, start, end);
	l_quicksort(A, start, q - 1);
	l_quicksort(A, q + 1, end);
	
	return;
}


void h_quicksort(int A[], int start, int end)
{
	if (start < end)
	{
		int q = Hoare_partition(A, start, end);
		h_quicksort(A, start, q - 1);
		h_quicksort(A, q + 1, end);
	}
	return;
}



void i_quicksort(int A[], int start, int end)
{
	if (start > end)
	{
		return ;// error
	}

	if (end - start <= 10)
	{
		insertion_sort(A, start, end);
	}
	else 
	//if (start < end)
	{
		int q = lomuto_partition(A, start, end);
		i_quicksort(A, start, q - 1);
		i_quicksort(A, q + 1, end);
	}
	return;
}


void t_quicksort(int A[], int start, int end)
{
	if (start >= end)
		return;
	//std::mutex rock;
	//rock.lock();
	int q = lomuto_partition(A, start, end);
	//rock.unlock();
	std::thread t1 = std::thread( l_quicksort,A, start, q - 1);
	std::thread t2 = std::thread(l_quicksort, A,q+1, end);
	t1.join();
	t2.join();
	return;
}



void ti_quicksort(int A[], int start, int end)
{
	if (start > end)
	{
		return;// error
	}

	if (end - start <= 10)
	{
		insertion_sort(A, start, end);
	}

	int q = lomuto_partition(A, start, end);
	std::thread t1 = std::thread(l_quicksort, A, start, q - 1);
	std::thread t2 = std::thread(l_quicksort, A, q + 1, end);
	t1.join();
	t2.join();
	return;
}

void three_way_partition(int A[], int start, int end)
{
	int mid = A[start + (start + end) / 2];
	int i = 0;
	int j = 0;
	int n = end - start;
	while (j <= n)
	{
		if (A[j] < mid)
		{
			std::swap(A[i], A[j]);
			++i;
			++j;
		}
		else if (A[j] > mid)
		{
			std::swap(A[j], A[n]);
			--n;
		}
		else
			j++;
	}
}

//void tw_quicksort(int A[], int start, int end)
//{
//	if (start < end)
//	{
//		Hoare_partition(A, start, end);
//		int i, j;
//		three_way_partition(A, start, end);
//		h_quicksort(A, start, q - 1);
//		h_quicksort(A, q + 1, end);
//	}
//	return;
//}

void tw_quicksort(int a[], int l, int r)
{
	int i = l - 1, j = r, p = l - 1, q = r; int v = a[r];
	if (r <= l) return;
	for (;;)
	{
		while (a[++i] < v)
			;
		while (v < a[--j])
		{
			if (j == l)
				break;
		}
		if (i >= j) 
			break;
		std::swap(a[i], a[j]);
		if (a[i] == v) 
		{
			p++; 
			std::swap(a[p], a[i]); 
		}
		if (v == a[j])
		{ 
			q--; 
			std::swap(a[j], a[q]); 
		}
	}
	std::swap(a[i], a[r]); j = i - 1; i = i + 1;
	for (int k = l; k < p; k++, j--) std::swap(a[k], a[j]);
	for (int k = r - 1; k > q; k--, i++) std::swap(a[i], a[k]);
	tw_quicksort(a, l, j);
	tw_quicksort(a, i, r);
}


void ittw_quicksort(int a[], int l, int r)
{
	/*if (r - l <= 10)
		insertion_sort(a, l, r);*/
	//else
	{
		int i = l - 1, j = r, p = l - 1, q = r; int v = a[r];
		if (r <= l) return;
		for (;;)
		{
			while (a[++i] < v);
			while (v < a[--j]) if (j == l) break;
			if (i >= j) break;
			std::swap(a[i], a[j]);
			if (a[i] == v) { p++; std::swap(a[p], a[i]); }
			if (v == a[j]) { q--; std::swap(a[j], a[q]); }
		}
		std::swap(a[i], a[r]); j = i - 1; i = i + 1;
		for (int k = l; k < p; k++, j--) std::swap(a[k], a[j]);
		for (int k = r - 1; k > q; k--, i++) std::swap(a[i], a[k]);
		std::thread t1 = std::thread(ittw_quicksort, a, l, j);
		std::thread t2 = std::thread(ittw_quicksort, a, i, r);
		t1.join();
		t2.join();
	}
}

void Quick3way(int a[], int lo, int hi)
{
	if (hi - lo <= 10)
	{
		insertion_sort(a, lo, hi);
		return;
	}
	if (hi <= lo)
		return;
	int lt = lo, i = lo + 1, gt = hi;
	int v = a[lo];
	while (i <= gt)
	{
		if (a[i] < v)
		{
			std::swap(a[lt], a[i]);
			lt++, i++;
		}
		else if (a[i] > v)
		{
			std::swap(a[gt], a[i]);
			gt--;
		}
		else //a[i]==v
		{
			i++;
		}
	}
	Quick3way(a, lo, lt - 1);
	Quick3way(a, gt + 1, hi);
}
