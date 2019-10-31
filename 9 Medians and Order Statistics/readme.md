# 9.1 Minimum and maximum

```C++
int MINIMUM(int A[], int n)
{
	int min = A[0];
	for (int i = 1; i < n; i++)
	{
		if (min > A[i])
		{
			min = A[i];
		}
	}
	return min;
}
```

```C++
int MAXIMUM(int A[], int n)
{
	int max = A[0];
	for (int i = 1; i < n; i++)
	{
		if (max < A[i])
		{
			max = A[i];
		}
	}
	return max;
}
```



```C++
int secone_MINIMUM(int A[], int n)
{
	int min = A[0];
	int sub_min = A[0];
	for (int i = 1; i < n; i++)
	{
		if (min > A[i])
		{
			sub_min = min;
			min = A[i];
		}
	}
	return sub_min;
}
```

# 9.2 Selection in expected linear time

```C++
int PARTITION(int A[], int p, int r)
{
	int x = A[r]; //pivot
	int i = p - 1;

	for (int j = p; j < r - 1; j++)
	{
		if (A[j] <= x)
		{
			i++;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[r]);
	return i + 1;
}

int RANDOMIZED_SELECT(int A[], int p, int r, int i)
{
	if (p == r)
		return A[p];
	int q = PARTITION(A, p, r);
	int k = q - p + 1;
	if (i-1 == k)
		return A[q];
	else if (i < k)
		return RANDOMIZED_SELECT(A, p, q - 1, i);
	else 
		return RANDOMIZED_SELECT(A, q + 1, r, i - k);
}
```

# 9.3 Selection in worst-case linear time

Median of medians
https://en.wikipedia.org/wiki/Median_of_medians

1. Divide the n elements of the input array into bn=5c groups of 5 elements each
and at most one group made up of the remaining n mod 5 elements.

2. Find the median of each of the dn=5e groups by first insertion-sorting the elements
of each group (of which there are at most 5) and then picking the median
from the sorted list of group elements.

3. Use SELECT recursively to find the median x of the dn=5e medians found in
step 2. (If there are an even number of medians, then by our convention, x is
the lower median.)

4. Partition the input array around the median-of-medians x using the modified
version of PARTITION. Let k be one more than the number of elements on the
low side of the partition, so that x is the kth smallest element and there are nk
elements on the high side of the partition.

5. If i D k, then return x. Otherwise, use SELECT recursively to find the i th
smallest element on the low side if i < k, or the .i  k/th smallest element on
the high side if i > k.

