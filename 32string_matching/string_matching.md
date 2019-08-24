# 32.1 The naive string matching algorithm


O((n-m+1)m)
```
void NAIVE_STRING_MATCHER(char* T, char* P, int n, int m )
{
	for (int s = 0; s <= n - m; s++)
	{
		bool maching = true; // strcmp
		for (int i = 0; i < m; i++)
		{
			if (T[i+s] != P[i])
			{
				maching = false;
			}
		}
		if (maching)
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


```




# 32.3
https://www.acmicpc.net/problem/1786

