

# 28 Matrix Operations

I'm setting Matrix index 0 ~ n-1
nxn mat

```C++
typedef std::vector<std::vector<double>>  Matrix;
typedef std::pair<std::vector< std::vector<double>>, std::vector< std::vector<double>>>  Set;
```
  
## 28.1 Solving systems of linear equations


$O(n^2)$
```C++
//n^2
std::vector<double>LUP_SOLVE(Matrix& L, Matrix& U, std::vector<int> &PI,
	std::vector<double>& b)
{
	const int n = L.size();
	std::vector<double> x(n, 0);
	std::vector<double> y(n,0);

	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int j = 0; j <= i - 1; j++)
		{
			sum += L[i][j] * y[j];
		}
		y[i] = b[PI[i]] - sum;
	}

	for (int i = n-1; i >= 0; i--)
	{
		double sum = 0;
		for (int j = i + 1  ; j < n; j++)
		{
			sum += U[i][j] * x[j];
		}
		x[i] = (y[i] - sum) / U[i][i];
	}
	return x;
}
```


```C++
// n^3
Set LU_DECOMPOSITION(Matrix& A)
{
	const int n = A.size();
	Matrix L(n, std::vector<double>(n, 0));
	Matrix U(n, std::vector<double>(n, 0));
	for (int i = 0; i < n; i++)
	{
		L[i][i] = 1;
	}
	for (int k = 0 ; k < n; k++)
	{
		U[k][k] = A[k][k];
		for (int i = k + 1; i < n; i++)
		{
			L[i][k] = A[i][k] / U[k][k];
			U[k][i] = A[k][i];
		}

		for (int i = k + 1; i < n; i++)
		{
			for (int j = k + 1; j < n; j++)
			{
				A[i][j] = A[i][j] - L[i][k] * U[k][j];
			}
		}
	}
	return std::make_pair(L, U);
}
```

figure28.2 ex is wrong ex

```C++
std::vector<int> LUP_DECOMPOSITION(Matrix& A)
{
	const int n = A.size();
	std::vector<int> pi(n , 0);
	for (int i = 0; i < n; i++)
	{
		pi[i] = i;
	}

	for (int k = 0; k < n - 1; k++)
	{
		int k_prime = -1;
		double p = 0;
		for (int i = k; i < n; i++)
		{
			if (A[i][k] > p)
			{
				p = A[i][k];
				k_prime = i;
			}
		}
		if (p == 0)
		{
			
			std::cout << "singular Matrix" << std::endl;
		}
		//swap
		int sub = pi[k];
		pi[k] = pi[k_prime];
		pi[k_prime] = sub;

		for (int i = 0; i < n; i++)
		{
			double sub = A[k][i];
			A[k][i] = A[k_prime][i];
			A[k_prime][i] = sub;
		}

		for (int i = k + 1; i < n; i++)
		{
			A[i][k] = A[i][k] / A[k][k];
			for (int j = k + 1; j < n; j++)
			{
				A[i][j] = A[i][j] - A[i][k] * A[k][j];
			}
		}
	}
	return pi;
}
```