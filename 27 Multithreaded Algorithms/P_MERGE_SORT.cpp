//미완성

#include<iostream>
#include<vector>
#include<thread>

int BINARY_SEARCH(int x, int T[], int p, int r)
{
	int low = p;
	int high = (p >= r + 1 ? p : r + 1);
	while (low < high)
	{
		int mid = (low + high) / 2;
		if (x <= T[mid])
			high = mid;
		else low = mid + 1;
	}
	return high;
}

void P_MERGE(int T[], int p1, int r1, int p2, int r2, int A[], int p3)
{
	int n1 = r1 - p1 + 1;
	int n2 = r2 - p2 + 1;
	if (n1 < n2)
	{

	}
	if (n1 == 0)
	{
		return;
	}
	else
	{
		int q1 = (p1 + r1) / 2;
		int q2 = BINARY_SEARCH(T[q1], T, p2, r2);
		int q3 = p3 + (q1 - p1) + (q2 - p2);
		A[q3] = T[q1];
		std::thread _thread = std::thread(P_MERGE, T, p1, q1 - 1, p2, q2 - 1, A, p3);
		P_MERGE(T, q1 + 1, r1, q2, r2, A, q3 + 1);
		_thread.join();
	}
}


void P_MERGE_SORT(int A[], int p, int r,int B[],int s)
{
	const int n = r - p + 1;
	if (n == 1)
	{
		B[s] = A[p];
	}
	else
	{
		int* T = new int[n];
		int q = (p + r) / 2;
		int q_prime = q - p + 1;
		std::thread _thread = std::thread(P_MERGE_SORT, A, p, q,T,1);
		P_MERGE_SORT(A, q + 1, r, T, q_prime + 1);
		_thread.join();
		P_MERGE(T, 1, q_prime, q_prime + 1, n, B, s);
	}
}






void MERGE(int A[], int p, int q, int r)
{
	int n_1 = q - p + 1;
	int n_2 = r - q;
	int* L = new int[n_1 + 2];
	int* R = new int[n_2 + 2];
	for (int i = 1; i <= n_1; i++)
	{
		L[i] = A[p + i - 1];
	}
	for (int j = 1; j <= n_2; j++)
	{
		R[j] = A[q + j];
	}
	L[n_1 + 1] = 10000000;
	R[n_2 + 1] = 10000000;
	int i = 1;
	int j = 1;
	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}
	delete[] L;
	delete[] R;
}


void MERGE_SORT_PRIME(int A[], int p, int r)
{
	if (p >= r)
	{
		return;
	}
	int q = (p + r) / 2;
	std::thread _thread = std::thread(MERGE_SORT_PRIME, A, p, q);
	MERGE_SORT_PRIME(A, q + 1, r);
	_thread.join();
	MERGE(A, p, q, r);
	return;
}

void print(int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << A[i] << ' ';
	}
	std::cout << '\n';
}



int b[] = { 12,10 ,43,43 ,23,123,56,45,123 ,56,56,98,45,123,56,98,41,90,24 ,45 };//,-78,45,
int a[30];
int main()
{

	

	int num = sizeof(b) / sizeof(int);
	print(b, num);

	P_MERGE_SORT(b,0 ,num-1,a,0);

	print(a, num);
	return 0;
}


