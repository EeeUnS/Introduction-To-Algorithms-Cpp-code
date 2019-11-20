# 16.1활동 선택 문제(activity selection problem)



1. f가 제일작은 f[0]을 선택한다. 이게 a0

2. 이 앞의 f[0]보다 큰 s[i]를 선택한다. a1

3. 반복


```C++
void RECURSIVE_ACTIVITY_SELECTOR(int s[], int f[], int k, int n, std::vector<int> &a)
{
	int m = k + 1;
	while (m < n && s[m] < f[k])
	{
		m = m + 1;
	}
	if (m < n)
	{
		a.push_back(m);
		RECURSIVE_ACTIVITY_SELECTOR(s,f,m,n,a);
	}
	return;
}

```

```C++
std::vector<int> GREEDY_ACTIVITY_SELECTOR(int s[], int f[],int n)
{
	std::vector<int> A;
	A.push_back(1);
	int k = 1;
	for (int m = 2; m <= n; m++)
	{
		if (s[m] >= f[k])
		{
			A.push_back(m);
			k = m;
		}
	}
	return A;
}
```

# 16.2 Elements of the greedy strategy

# 16.3 Huffman codes