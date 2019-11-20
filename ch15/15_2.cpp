#include <iostream>
#include<vector>

typedef std::pair<std::vector<std::vector<int>>,std::vector<std::vector<int>>> Set;



Set MATRIX_CHAIN_ORDER(const std::vector<int> &p)
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


void PRINT_OPTIMAL_PARENS(const std::vector<std::vector<int>> &s, int i, int j)
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



int RECURSIVE_MATRIX_CHAIN(const std::vector<int> &p, int i, int j)
{
	const int INF = 1000000000;
	const int n = p.size() -1 ;
	std::vector<std::vector<int>> m(n+1, std::vector<int>(n+1, 0));
	if (i == j)
	{
		return 0;
	}
	m[i][j] = INF;
	for (int k = i; k <= j - 1; k++)
	{
		int q = RECURSIVE_MATRIX_CHAIN(p, i, k) +
			RECURSIVE_MATRIX_CHAIN(p, k + 1, j) + p[i - 1] * p[k] * p[j];
		
		if (q < m[i][j])
		{
			m[i][j] = q;
		}
	}
	return m[i][j];
}

int LOOKUP_CHAIN(std::vector<std::vector<int>> &m,const std::vector<int> &p,int i,int j)
{
	const int INF = 1000000000;

	if (m[i][j] < INF)
	{
		return m[i][j];
	}
	if (i == j)
	{
		m[i][j] = 0;
	}
	else for (int k = i ; k <= j - 1; k++)
	{
		int q = LOOKUP_CHAIN(m, p, i, k)
			+ LOOKUP_CHAIN(m, p, k + 1, j) + p[i - 1] * p[k] * p[j];
		if (q < m[i][j])
		{
			m[i][j] = q;
		}
	}
	return m[i][j];
}


int MEMORIZED_MATRIX_CHAIN(const std::vector<int> &p)
{
	const int INF = 1000000000;
	const int n = p.size() - 1;
	std::vector<std::vector<int>> m(n+1, std::vector<int>(n+1, 0));
	for (int i = 1; i <= n; i++)
	{

		for (int j = 1; j <= n; j++)
		{
			m[i][j] = INF;
		}
	}
	return LOOKUP_CHAIN(m, p, 1, n);
}

std::vector<int> p = {30,35,15,5,10,20,25};


int main()
{
	Set ms = MATRIX_CHAIN_ORDER(p);// m, s
	std::cout << RECURSIVE_MATRIX_CHAIN(p, 1, 6) << std::endl;
	std::cout <<  MEMORIZED_MATRIX_CHAIN(p) << std::endl;


	//PRINT_OPTIMAL_PARENS(ms.second, 1, 6);
	

	return 0;
}
