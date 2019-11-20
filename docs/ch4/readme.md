# 4.1 The maximum-subarray problem


4.1-2 A brute-force solution
$\Theta(n^2)$
```C++
int FIND_MAX_CROSSING_SUBARRAY(int A[], int n)
{
	const int INF = 1000000;
	int maximum = -1000000;
	for (int i = 0; i < n; i++)
	{
		int sub_max = A[i];
		for (int j = i + 1; j < n; j++)
		{ 
			sub_max = sub_max + A[j];
			maximum =  std::max(maximum , sub_max) ;
		}
	}
	return maximum;
}
```


daq
Theta(nlg(n))
```C++

std::tuple<int, int, int> FIND_MAX_CROSSING_SUBARRAY(int A[], int low, int mid, int high)///std::tuple<int, int, int> low , high ,sum
{
	const int INF = 1000000;
	int left_sum = -INF;
	int sum = 0;
	int max_left = -1;

	for (int i = mid; i >= low; i--)
	{
		sum = sum + A[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
	int right_sum = -INF, max_right = -1;
	sum = 0;
	for (int j = mid+1; j <= high ; j++)
	{
		sum = sum + A[j];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = j;
		}
	}
	return(std::make_tuple(max_left,max_right,left_sum+right_sum));

}
```

4.1-5 


[Kadane’s Algorithm](https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm)

O(n)
```C++
std::tuple<int, int, int>KADANE(int A[], int n)///std::tuple<int, int, int> low , high ,sum
{
	std::tuple<int, int, int> current_sum (0,0,0) ;
	std::tuple<int, int, int> maximum ;
	for (int i = 0; i < n; i++)
	{
		if ( std::get<2>(current_sum) + A[i] > 0)
		{
			if (std::get<2>(current_sum) == 0)
				std::get<0>(current_sum) = i;
			std::get<2>(current_sum) = std::get<2>(current_sum) + A[i];
			std::get<1>(current_sum) = i;
			
		}
		else
		{
			std::get<2>(current_sum) = 0;
		}
		if (std::get<2>(maximum) < std::get<2>(current_sum))
		{
			std::get<0>(maximum) = std::get<0>(current_sum);
			std::get<1>(maximum) = std::get<1>(current_sum);
			std::get<2>(maximum) = std::get<2>(current_sum);
		}
		
	}
	return maximum;
}
```



# 4.2 Strassen's algorithms for matrix multiplication

일반
n^3
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
n = 2^t
n^3
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