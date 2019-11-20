pdf :  https://github.com/EeeUnS/Introduction_to_quicksort/blob/master/quick_sort.pdf

download : https://github.com/EeeUnS/Introduction_to_quicksort/raw/master/quick_sort.pdf


http://www.cs.princeton.edu/courses/archive/fall12/cos226/lectures/23Quicksort-2x2.pdf
https://algs4.cs.princeton.edu/lectures/23DemoPartitioning.pdf

lomuto_partition
```
int lomuto_partition(int A[], int start, int end)
{
	int x = A[end];
	int i = start - 1;
	for (int j = start; j < end; j++)
	{
		if (A[j] <= x)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[end]);
	return i + 1;
}

```

```
void l_quicksort(int A[], int start, int end)
{
	if (start < end)
	{
		int q = lomuto_partition(A, start, end);
		l_quicksort(A, start, q - 1);
		l_quicksort(A, q + 1, end);
	}
	return;
}
```

Hoare_partition
```
int Hoare_partition(int arr[], int low, int high)
{
	int x = arr[low], i = low - 1, j = high + 1;
	while (1) {
		do  j--; while (arr[j] > x);
		do  i++; while (arr[i] < x);
		if (i < j)
			swap(arr[i], arr[j]);
		else
			return j;
	}
}

```

https://stackoverflow.com/questions/7198121/quicksort-and-hoare-partition

```
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
```



insertion sort
```
void i_quicksort(int A[], int start, int end)
{
	//int j, r;
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
```

```
void insertion_sort(int a[], int start, int end) //end를 포함한다.
{
	for (int i = start; i <= end; i++)
	{
		int item = a[i];
		int j = i;
		while (--j >= 0 && item < a[j])
		{
			a[j + 1] = a[j];
		}
		a[++j] = item;
	}
}
```


multi threading
```
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
```

multi threading + insertion sort
```
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

```
3way partition
```
void tw_quicksort(int a[], int l, int r)
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
	tw_quicksort(a, l, j);
	tw_quicksort(a, i, r);
}
```


```
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
```



전체 test 코드  https://github.com/EeeUnS/Introduction_to_quicksort/blob/master/testcode.cpp
pdf : https://github.com/EeeUnS/Introduction_to_quicksort/blob/master/quick_sort.pdf
