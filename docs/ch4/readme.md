# 4.1 The maximum-subarray problem

[boj](https://www.acmicpc.net/problem/1912)

4.1-2 A brute-force solution
$\Theta(n^2)$

daq
$\Theta(n\log n)$
```C++
struct subset
{
	long long low;
	long long high;
	long long sum;
};

subset FIND_MAX_CROSSING_SUBARRAY(long long A[], long long low, long long mid, long long high)
{
	long long left_sum = A[mid]-1;
	long long sum = 0;

	long long max_left = 0 ;
	long long max_right = 0;
	long long right_sum = 0;
	

	for (long long i = mid; i >= low; i--)
	{
		sum = sum + A[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	right_sum = A[mid + 1] -1;
	
	sum = 0;
	for (long long j = mid + 1; j <= high; j++)
	{
		sum = sum + A[j];
		if (sum > right_sum)
		{ 
			right_sum = sum;
			max_right = j;
		}
	}
	return { max_left, max_right, left_sum + right_sum };
 }

subset FIND_MAXIMUM_SUBARRAY(long long A[], long long low, long long high)
{
	if (high == low)
	{
		return { low, high, A[low] }; // base case: only one element
	}
	else
	{
		long long mid = (low + high) / 2;
		subset LEFT = FIND_MAXIMUM_SUBARRAY(A, low, mid);
		subset RIGHT = FIND_MAXIMUM_SUBARRAY(A, mid + 1, high);
		subset CROSS = FIND_MAX_CROSSING_SUBARRAY(A, low, mid, high);
		if (LEFT.sum >= RIGHT.sum && LEFT.sum >= CROSS.sum)
		{
			return LEFT;
		}
		else if( RIGHT.sum >= LEFT.sum && RIGHT.sum >= CROSS.sum)
		{ 
			return RIGHT;
		}
		else
		{
			return CROSS;
		}
	}
}
```

4.1-5 


[Kadane’s Algorithm](https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm)

$O(n)$
```C++

struct subset
{
	long long low;
	long long high;
	long long sum;
};

subset KADANE(int A[], int n)
{
	subset current_sum = { 0, 0, A[0] };
	subset maximum = { 0, 0, A[0] };
	for (int i = 1; i < n; i++)
	{
		if (current_sum.sum + A[i] > A[i])
		{
			if (current_sum.sum  == 0)
				current_sum.low = i;
			current_sum.sum  = current_sum.sum  + A[i];
			current_sum.high = i;
		}
		else
		{
			current_sum.sum  = A[i];
		}

		if (maximum.sum < current_sum.sum )
		{
			maximum.low = current_sum.low;
			maximum.high = current_sum.high;
			maximum.sum = current_sum.sum ;
		}
	}
	return maximum;
}
```



# 4.2 Strassen's algorithms for matrix multiplication

일반
$O(n^3)$
```C++
std::vector<std::vector<int>> SQUARE_MATRIX_MULTIPLY(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B)
{
	const int n = A.size();
	std::vector<std::vector<int>> C;
	C.assign(n, std::vector<int>(n, 0));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}

		}
	}
	return C;
}
```

divide and conquer
$n = 2^t$
$O(n^3)$
```C++
std::vector< std::vector<int>>SQUARE_MATRIX_MULTIPLY_RECURSIVE(
	std::vector< std::vector<int>>& A,
	std::vector< std::vector<int>>& B
);

void ADD_MATRIX(std::vector< std::vector<int>> &C,
	std::vector< std::vector<int>> A,
	std::vector< std::vector<int>> B)
{
	const std::size_t n = C.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

std::vector< std::vector<int>>SQUARE_MATRIX_MULTIPLY_RECURSIVE(
	std::vector< std::vector<int>> &A,
	std::vector< std::vector<int>> &B
	)
{
	const std::size_t n = A.size();
	std::vector< std::vector<int>> C(n,std::vector<int>(n,0));

	if (n == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
		return C;
	}
	int m = n / 2;
	std::vector< std::vector<int>> A11(m,std::vector<int>(m,0)), 
		A12(m, std::vector<int>(m, 0)), 
		A21(m, std::vector<int>(m, 0)), 
		A22(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> B11(m, std::vector<int>(m, 0)),
		B12(m, std::vector<int>(m, 0)),
		B21(m, std::vector<int>(m, 0)),
		B22(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> C11(m, std::vector<int>(m, 0)),
		C12(m, std::vector<int>(m, 0)),
		C21(m, std::vector<int>(m, 0)),
		C22(m, std::vector<int>(m, 0));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + m];
			A21[i][j] = A[i + m][j];
			A22[i][j] = A[i + m][j + m];

			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + m];
			B21[i][j] = B[i + m][j];
			B22[i][j] = B[i + m][j + m];
		}
	}

	ADD_MATRIX(C11,SQUARE_MATRIX_MULTIPLY_RECURSIVE(A11,B11),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(A12, B21));
	ADD_MATRIX(C12, SQUARE_MATRIX_MULTIPLY_RECURSIVE(A11, B12),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(A12, B22));
	ADD_MATRIX(C21, SQUARE_MATRIX_MULTIPLY_RECURSIVE(A21, B11),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(A22, B21));
	ADD_MATRIX(C22, SQUARE_MATRIX_MULTIPLY_RECURSIVE(A21, B12),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(A22, B22));

	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			C[i][j] = C11[i][j];
			C[i][j+m] = C12[i][j];
			C[i+m][j] = C21[i][j];
			C[i+m][j+m] = C22[i][j];
		}
	}

	return C;
}
```

C이외의 추가적인 공간을 사용하지않음 모두 인덱스로 처리
```C++
std::vector< std::vector<int>>SQUARE_MATRIX_MULTIPLY_RECURSIVE(
	int C_row_index, int C_col_index,
	std::vector< std::vector<int>> A,
	int A_row_index, int A_col_index,
	std::vector< std::vector<int>> B,
	int B_row_index, int B_col_index,
	int size
);

void ADD_MATRIX(std::vector< std::vector<int>> &C,
	int C_row_index,int C_col_index,
	std::vector< std::vector<int>> A,
	std::vector< std::vector<int>> B
	)
{
	const std::size_t n = A.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i+C_row_index][j+C_col_index] = A[i][j] + B[i][j];
		}
	}
}


std::vector< std::vector<int>>SQUARE_MATRIX_MULTIPLY_RECURSIVE(
	int C_row_index, int C_col_index,
	std::vector< std::vector<int>> A,
	int A_row_index, int A_col_index,
	std::vector< std::vector<int>> B,
	int B_row_index, int B_col_index,
	int size
)
{
	std::vector< std::vector<int>> C(size,std::vector<int>(size,0));

	if (size == 1)
	{
		C[0][0] = A[A_row_index][A_col_index] * B[B_row_index][B_col_index];
		return C;
	}
	int m = size / 2;

	ADD_MATRIX(C, C_row_index, C_col_index,
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index, C_col_index,
			A, A_row_index, A_col_index,
			B, B_row_index, B_col_index,m),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index, C_col_index,
			A, A_row_index, A_col_index + m,
			B, B_row_index + m, B_col_index,m)
	);
	ADD_MATRIX(C, C_row_index, C_col_index + m,
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index, C_col_index + m,
			A, A_row_index, A_col_index,
			B, B_row_index, B_col_index + m, m),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index, C_col_index + m,
			A, A_row_index, A_col_index + m,
			B, B_row_index + m, B_col_index + m, m)
	);
	ADD_MATRIX(C, C_row_index + m, C_col_index,
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index + m, C_col_index,
			A, A_row_index + m, A_col_index,
			B, B_row_index, B_col_index, m),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index + m, C_col_index,
			A, A_row_index + m, A_col_index + m ,
			B, B_row_index + m, B_col_index, m)
	);
	ADD_MATRIX(C, C_row_index + m, C_col_index + m,
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index + m, C_col_index + m,
			A, A_row_index + m, A_col_index,
			B, B_row_index, B_col_index + m, m),
		SQUARE_MATRIX_MULTIPLY_RECURSIVE(C_row_index + m, C_col_index + m,
			A, A_row_index + m, A_col_index + m,
			B, B_row_index + m, B_col_index + m, m)
	);
	   	return C;
}
```

```C++
SQUARE_MATRIX_MULTIPLY_RECURSIVE(0,0,A,0,0, B,0,0,2);
```C++

스트라센;
```C++
void ADD_MATRIX(std::vector< std::vector<int>>& C,
	std::vector< std::vector<int>>& A,
	std::vector< std::vector<int>>& B)
{
	const std::size_t n = C.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void SUB_MATRIX(std::vector< std::vector<int>>& C,
	std::vector< std::vector<int>>& A,
	std::vector< std::vector<int>>& B)
{
	const std::size_t n = C.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

std::vector< std::vector<int>> STRASSEN(
	std::vector< std::vector<int>>& A,
	std::vector< std::vector<int>>& B
)
{
	const std::size_t n = A.size();
	std::vector< std::vector<int>> C(n, std::vector<int>(n, 0));

	if (n == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
		return C;
	}
	int m = n / 2;
	std::vector< std::vector<int>> A11(m, std::vector<int>(m, 0)),
		A12(m, std::vector<int>(m, 0)),
		A21(m, std::vector<int>(m, 0)),
		A22(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> B11(m, std::vector<int>(m, 0)),
		B12(m, std::vector<int>(m, 0)),
		B21(m, std::vector<int>(m, 0)),
		B22(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> S1(m, std::vector<int>(m, 0)),
		S2(m, std::vector<int>(m, 0)),
		S3(m, std::vector<int>(m, 0)),
		S4(m, std::vector<int>(m, 0)),
		S5(m, std::vector<int>(m, 0)),
		S6(m, std::vector<int>(m, 0)),
		S7(m, std::vector<int>(m, 0)),
		S8(m, std::vector<int>(m, 0)),
		S9(m, std::vector<int>(m, 0)),
		S10(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> P1(m, std::vector<int>(m, 0)),
		P2(m, std::vector<int>(m, 0)),
		P3(m, std::vector<int>(m, 0)),
		P4(m, std::vector<int>(m, 0)),
		P5(m, std::vector<int>(m, 0)),
		P6(m, std::vector<int>(m, 0)),
		P7(m, std::vector<int>(m, 0));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + m];
			A21[i][j] = A[i + m][j];
			A22[i][j] = A[i + m][j + m];

			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + m];
			B21[i][j] = B[i + m][j];
			B22[i][j] = B[i + m][j + m];
		}
	}

	SUB_MATRIX(S1, B12, B22);
	ADD_MATRIX(S2, A11, A12);
	ADD_MATRIX(S3, A21, A22);

	SUB_MATRIX(S4, B21, B11);
	ADD_MATRIX(S5, A11, A22);
	ADD_MATRIX(S6, B11, B22);

	SUB_MATRIX(S7, A12, A22);
	ADD_MATRIX(S8, B21, B22);
	SUB_MATRIX(S9, A11, A21);
	ADD_MATRIX(S10, B11, B12);

	P1 = STRASSEN(A11, S1);
	P2 = STRASSEN(S2, B22);
	P3 = STRASSEN(S3, B11);
	P4 = STRASSEN(A22, S4);
	P5 = STRASSEN(S5, S6);
	P6 = STRASSEN(S7, S8);
	P7 = STRASSEN(S9, S10);

	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
			C[i][j + m] = P1[i][j] + P2[i][j];
			C[i + m][j] = P3[i][j] + P4[i][j];
			C[i + m][j + m] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
		}
	}

	return C;
}
```