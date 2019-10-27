# 4.1 The maximum-subarray problem






#4.2 Strassen's algorithms for matrix multiplication

n^3
```
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
```
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
```
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

```
SQUARE_MATRIX_MULTIPLY_RECURSIVE(0,0,A,0,0, B,0,0,2);
```

스트라센;