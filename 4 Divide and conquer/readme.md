
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