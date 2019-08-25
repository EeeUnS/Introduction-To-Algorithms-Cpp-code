# 32.1 The naive string matching algorithm


O((n-m+1)m)
```
void NAIVE_STRING_MATCHER(char* T, char* P, int n, int m )
{
	for (int s = 0; s <= n - m; s++)
	{
		bool matching = true; // strcmp
		for (int i = 0; i < m; i++)
		{
			if (T[i+s] != P[i])
			{
				matching = false;
			}
		}
		if (matching)
		{
			std::cout << "Pattern occurs with shift" << s <<'\n';
		}
	}
}
```
# 32.2 The Rabin Karp algorighm

Preprocessing time : O(m)

Matching time O((n-m+1)m)
평균 O(m)
```

void RABIN_KARP_MATCHER(char T[], char* P, int m, int n, int d, int q)
{
	int h = MODULAR_EXPONENTIATION(d, n - 1, q);
	int p = 0;
	int t_0 = 0;
	for (int i = 0; i < n; i++) //전처리
	{
		p = (d * p + (P[i]-'A')) % q;
		t_0 = (d * t_0 + (T[i]-'A')) % q;
	}
	for (int s = 0; s <= m - n ; s++)
	{
		if (p == t_0)
		{
			bool matching = true; // strcmp
			for (int i = 0; i < n; i++)
			{
				if (T[i + s] != P[i])
				{
					matching = false;
				}
			}
			if (matching)
			{
				std::cout << "Pattern occurs with shift" << s << '\n';
			}
		}
		if (s < m - n)
		{
			t_0 = ((d * (t_0 - (T[s]-'A') * h) + (T[s + n]-'A')) % q + q)%q;//음수가 나올수있기때문에 음수처리를 한다.
		}
	}
}


```




# 32.3 String matching with finite automata

https://www.acmicpc.net/problem/1786

Preprocessing time : O(m^3 *sigma)

Matching time O(m)


```
void FINITE_AUTOMATON_MATCHER(char T[], std::vector<std::vector<int>> equation, int n, int m )
{
	int q = 0;
	for (int i = 0; i < n ; i++)
	{
		q = equation[q][T[i]-'A'];
		if (q == m)
		{
			std::cout << "Pattern occurs with shift" << i-m+1 << '\n';
		}
	}
}
```

```
std::vector<std::vector<int>> COMPUTE_TRANSITION_FUNCTION(char P[],int sigma, int m)//
{
	std::vector<std::vector<int>> transition_function;
	transition_function.resize(m+1);
	for (int i = 0; i <= m; i++)
	{
		transition_function[i].resize(sigma,0);
	}
	for (int q = 0; q <= m; q++)
	{
		for (char a = 0; a < sigma; a++)
		{
			int k = (m+1< q+2  ? m + 1: q+2);
			bool matching = true;
			do
			{
				k--;
				matching = true;
				if (k == 0)
				{
					break;
				}
				if (P[k-1] != a+'A') // 접미사 매칭
				{
					continue;
				}
				for(int i = 0; i < k ; i++)
				{
					if (k - 2 - i < 0 || q - i < 0)
					{
						matching = false;
						break;
					}
					if (P[k - 1 - i] != P[q-i])
					{
						break;
					}
				}
			} while (matching);
			transition_function[q][a] = k;
		}
	}
	return transition_function;
}
```