

### COUNTING SORT
persude code
```

COUNTING - SORT(A, B, k)
 
let C[0..k] be a new array
 for i = 0 to k
	C[i] = 0
 for j = 1 to A.length
	C[A[j]] = C[A[j]] + 1
 // C[i] now contains the number of elements equal to i .
 for i = 1 to k
	C[i] = C[i] + C[i-1]
 // C[i] now contains the number of elements less than or equal to i .
 for j = A.ength downto 1
	B[C[A[j]]] = A[j]
	 C[A[j]] = C[A[j]] -1
```

분포값이 양수인경우에만 적용
```

void COUNTING_SORT(int A[], int n ,int k)//A의 수 n , k : 숫자범위
{
	int* C = new int[k];
	int* B = new int[n];
	for (int i = 0; i < k; i++)
	{
		C[i] = 0;
	}
	for (int j = 0; j < n; j++)
	{
		C[A[j]] = C[A[j]] + 1;
	}
	for (int i = 1; i < k; i++)
	{
		C[i] = C[i] + C[i - 1];
	}

	for (int j = n-1; j >= 0; j--)
	{
		B[C[A[j]]-1] = A[j];
		C[A[j]] = C[A[j]] - 1;
	}

	for (int i = 0; i < n; i++)
	{
		A[i] = B[i];
	}
	delete[] C;
	delete[] B;
}

```
