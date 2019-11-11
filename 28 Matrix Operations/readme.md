

# 28 Matrix Operations

I'm setting matrix index 0 ~ n-1
nxn mat

  ```C++
  typedef std::vector<std::vector<double>>  matrix;
  ```
  
## 28.1 Solving systems of linear equations


```C++
std::vector<double>LUP_SOLVE(matrix& L,	matrix& U, std::vector<int>& PI, 
	std::vector<double> & b)
{
	const int n = L.size() - 1;
	std::vector<double> x;
	x.resize(n + 1);

	std::vector<double> y;
	y.resize(n + 1);

	for (int i = 1; i <= n; i++)
	{
		double sum = 0;
		for (int j = 1; j <= i - 1; j++)
		{
			sum += L[i][j] * y[j];
		}
		y[i] = b[PI[i]] - sum;
	}

	for (int i = n; i >= 1; i--)
	{
		int sum = 0;
		for (int j = i + 1; j <= n; j++)
		{
			sum += U[i][j] * x[j];
		}
		x[i] = (y[i] - sum) / U[i][i];
	}
	return x;
}
```

```C++

void LU_DECOMPOSITION(matrix& A)
{
	const int n = A.size() - 1;
	matrix L(n + 1, std::vector<double>(n + 1, 0));
	matrix U(n + 1, std::vector<double>(n + 1, 0));
	for (int i = 1; i <= n; i++)
	{
		L[i][i] = 1;
	}
	for (int k = 1; k <= n; k++)
	{
		U[k][k] = A[k][k];
		for (int i = k + 1; i <= n; i++)
		{
			L[i][k] = A[i][k] / U[k][k];
			U[k][i] = A[k][i];
		}

		for (int i = k + 1; i <= n; i++)
		{
			for (int j = k + 1; j <= n; j++)
			{
				A[i][j] = A[i][j] - L[i][k] * U[k][j];
			}

		}

	}
	return L, U;
}
```

```C++
//미
void LUP_DECOMPOSITION(matrix& A)
{
	const int n = A.size() - 1;
	std::vector<double> pi(n+1, 0);
		for (int i = 1; i <= n; i++)
		{
			pi[i] = i;
		}

	for (int k = 1; k < n; k++)
	{
		int k_prime;
		int p = 0;
		for (int i = k; i <= n; i++)
		{
			if (A[i][k] > p)
			{
				p = A[i][k];
				k_prime = i;
			}
		}
		if (p == 0)
		{
			std::cout << "singular matrix" << std::endl;
		}
		//swap
		int sub = pi[k];
		pi[k] = pi[k_prime];
		pi[k_prime] = sub;

		for (int i =  1; i <= n; i++)
		{
			int sub = A[k][i];
			A[k][i] = A[k_prime][i];
			A[k_prime][i] = sub;
		}
		for (int i = k + 1; i <= n; i++)
		{
			A[i][k] = A[i][k] / A[k][k];
			for (int j = k + 1; j <= n; j++)
			{
				A[i][j] = A[i][j] - A[i][k] * A[k][j];
			}
		}
	}
}
```
