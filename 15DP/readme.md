1. Characterize the structure of an optimal solution

2. Recursively define the value of an optimal solution

3. Compute the calue of an optimal solution, typically in a bottom-up fashion

4. Construct an optimal solution from computed information

# 15.1 ROD CUTING


```
int p[] ={ 0, 1,5,8,9,10,17,17,20,24,30 };
```


완전 탐색 $O(2^n)$//수식안되네..
```
int CUT_ROD(int p[], int n) // p는 index 1부터 저장되어있다.
{
	if (n == 0)
	{
		return 0;
	}
	int q = INT32_MIN;
	for (int i = 1; i <= n; i++)
	{
		q = std::max(q, p[i-1] + CUT_ROD(p, n - i));
	}
}
```

O(n)


메모이제이션 방법 (top-down with memoization)
```
int MEMOIZED_CUT_ROD(int p[], int n)
{
	int* r = new int [n + 1];
	for (int i = 0; i <= n; ++i)
	{
		r[i] = INT32_MIN;
	}
	int q = MEMOIZED_CUT_ROD_AUX(p, n, r);
	delete []r;
	return q;
}
```


```
int MEMOIZED_CUT_ROD_AUX(int p[], int n, int r[])
{
	int q;
	if (r[n] >= 0)
	{
		return r[n];
	}
	if (n == 0)
	{
		 q = 0;
	}
	else
	{
		q = INT32_MIN;
		for (int i = 1; i <= n; ++i)
		{
			q = std::max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p, n - i, r));
		}
	}
	r[n] = q;
	return q;
}
```



bottm-up method(버튼업 /상향식)
```
int BOTTOM_UP_CUT_ROD(int p[], int n)
{
	int* r = new int[n + 1];
	r[0] = 0;
	for (int j = 1; j <= n; j++)
	{
		int q = INT32_MIN;
		for (int i = 1; i <= j; i++)
		{
			q = std::max(q, p[i] + r[j - i]);
		}
		r[j] = q;
	}
	delete[]r;
	return r[n];
}
```

```

std::vector<std::vector<int>> EXTENDED_BOTTOM_UP_CUT_ROD(int p[], int n)
{
	const int INF = 10000000;
	std::vector<std::vector<int>>rs; // r, s
	rs.resize(2);
	rs[0].resize(n + 1);
	rs[1].resize(n + 1);
	rs[0][0] = 0;
	for (int j = 1; j <= n; j++)
	{
		int q = -INF;
		for (int i = 1; i <= j; i++)
		{
			if (q < p[i] + rs[0][j - i])
			{
				q = p[i] + rs[0][j - i];
				rs[1][j] = i;
			}
		}
		rs[0][j] = q;
	}
	return rs;
}

void PRINT_CUT_ROD_COLUTION(int p[], int n)
{
	std::vector<std::vector<int>> rs = EXTENDED_BOTTOM_UP_CUT_ROD(p, n);
	while (n > 0)
	{
		std::cout << rs[1][n] <<' ';
		n = n - rs[1][n];
	}
	std::cout << std::endl;
}

```

# 15.2 Matrix_chain_multiplication

```C++
typedef std::pair<std::vector<std::vector<int>>,std::vector<std::vector<int>>> Set;
```

O(n^3)
```C++
Set MATRIX_CHAIN_ORDER(std::vector<int> p)
{
	const int INF = 1000000000;
	const int n = p.size()-1;
	std::vector<std::vector<int>> m(n+1, std::vector<int>(n+1, 0));
	std::vector<std::vector<int>> s(n+1, std::vector<int>(n+1, 0));
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			m[i][j] = INF;
			for (int k = i; k <= j - 1; k++)
			{
				int  q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{

					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	return std::make_pair(m, s);
}
```

```C++
void PRINT_OPTIMAL_PARENS(std::vector<std::vector<int>> s, int i, int j)
{
	if (i == j)
	{
		std::cout << "A" << i;
	}
	else
	{
		std::cout << '(';
		PRINT_OPTIMAL_PARENS(s, i, s[i][j]);
		PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j);
		std::cout << ')';
	}
}
```
# 15.3 Elements of dynamic programming





# 15.4 Longest common subsequence