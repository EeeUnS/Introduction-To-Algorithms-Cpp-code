# 32.1 The naive string matching algorithm

m = T.length
n = P.length

$O((n-m+1)m)$
```C++
void NAIVE_STRING_MATCHER(char* T, int m , char* P, int n )
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

Preprocessing time : $O(m)$

Matching time $O((n-m+1)m)$
평균 O(m)

q = prime

$d = \Sigma ^{*}$

I'm setting d = 26 (only Letter case)

```C++
void RABIN_KARP_MATCHER(char T[], int n , char P[], int m, int d, int q)
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
					break;
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


Preprocessing time : $O(m^{3} |\Sigma|)$
뒤의 kmp를 응용해서 해당 복잡도를 $O(m|\Sigma|)$로 줄일 수 있다.

Matching time $O(n)$
```C++
void FINITE_AUTOMATON_MATCHER(char T[], int n , std::vector<std::vector<int>> equation, int m )
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

```C++
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



# 32.4 The Knuth-Morris-Pratt algorithm


Preprocessing time : $O(m)$

Matching time $O(n)$

```C++
void KMP_MATCHER(char T[], int n, char P[], int m)
{
	std::vector<int> pi = COMPUTE_PREFIX_FUNCTION(P, m);
	int q = -1;
	for (int i = 0; i < n; i++)
	{
		while (q >= 0 && P[q + 1] != T[i])
		{
			q = pi[q];
		}
		if (P[q + 1] == T[i])
		{
			q++;
		}
		if (q+1 == m)
		{
			std::cout << "Pattern occurs with shift" << i - m + 1 << '\n';
			q = pi[q];
		}
	}
}
```


```C++
std::vector<int> COMPUTE_PREFIX_FUNCTION(char P[], int m)
{
	std::vector<int> pi;
	pi.resize(m);
	pi[0] = -1;
	int k = -1; 
	for (int q = 1; q < m; q++)
	{
		while (k >= 0 && P[k+1] != P[q])
		{
			k = pi[k];
		}
		if (P[k + 1] == P[q])
		{
			k++;
		}
		pi[q] = k;
	}
	return pi;
}
```
