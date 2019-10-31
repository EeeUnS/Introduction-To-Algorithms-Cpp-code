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