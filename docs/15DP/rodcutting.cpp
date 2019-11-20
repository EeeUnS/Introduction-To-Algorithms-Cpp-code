
#include<iostream>
#include<algorithm> // std::max
#include<vector>

int CUT_ROD(int p[], int n) // p는 index 1부터 저장되어있다.
{
	if (n == 0)
	{
		return 0;
	}
	int q = INT32_MIN;
	for (int i = 1; i <= n; i++)
	{
		q = std::max(q, p[i - 1] + CUT_ROD(p, n - i));
	}
}



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

int MEMOIZED_CUT_ROD(int p[], int n)
{
	int* r = new int[n + 1];
	for (int i = 0; i <= n; ++i)
	{
		r[i] = INT32_MIN;
	}
	int q = MEMOIZED_CUT_ROD_AUX(p, n, r);
	delete[]r;
	return q;
}

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

int p[] ={ 0, 1,5,8,9,10,17,17,20,24,30 };

int main()
{
	int n = sizeof(p)/sizeof(int);
	
	PRINT_CUT_ROD_COLUTION(p, n-1);
}
