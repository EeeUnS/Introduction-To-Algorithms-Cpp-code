# 27.1 The basics of dynamic multithreading

```c++
int P_FIB(int n)
{
	if (n <= 1)
		return n;
	else
	{
		std::future<int> ret = std::async(&P_FIB, n-1);
		int y = P_FIB(n - 2);
		int x = ret.get();
		return x + y;
	}
}
```


```c++
void sub_procesure(std::vector<int> &y, std::vector<int> &x, std::vector<std::vector<int>> &A, int i)
{
	for (int j = 0; j < A.size(); j++)
	{
		y[i] = y[i] + A[i][j] * x[j];
	}
}

std::vector<int> MAT_VEC(std::vector<std::vector<int>> &A , std::vector<int> &x)
{
	int n = A[0].size();
	std::vector<int> y(n);
	std::vector<std::thread> _thread;
	for (int i = 0; i < n; i++)
	{
		_thread.push_back(std::thread([]
		(std::vector<int>::iterator i) {
				*i = 0;
			}, y.begin() + i));
	}
	for (int i = 0; i < n; i++)
	{
		_thread[i].join();
	}
	_thread.clear();
	for (int i = 0; i < n; i++)
	{
		_thread.push_back(std::thread(sub_procesure, std::ref(y), std::ref(x), std::ref(A),i));

	}
	for (int i = 0; i < n; i++)
	{
		_thread[i].join();
	}
	return y;
}
```


# 27.2 Multithreaded matrix multiplication

https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm#Parallel_and_distributed_algorithms


# 27.3 Multithreaded merge sort

Not working



$S_1 = \Theta(n\log n)$
$S_INF = \Theta(n)$
$parallelism = \Theta(\log n)$
```
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
```
0~n-1
P_Merge's

$S_1 = \Theta(n)$
$S_INF = \Theta((\log n)^2)$
$parallelism = \Theta(n/(\log n)^2)$

https://nms.kcl.ac.uk/colin.cooper/teachingmaterial/PAL-PDA/lectures/6B-parallel-MergeSort.pdf
```


```