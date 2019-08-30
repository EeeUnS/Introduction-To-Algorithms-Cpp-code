# 15.1 ROD CUTING
```
#include<iostream>
#include<algorithm> // std::max
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

메모라이즈 방법 
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



버튼업 /상향식
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

입력
```
int main()
{
	int n;
	std::cin >> n;
	int* p = new int[n+1];
	p[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		std::cin >> p[i];
	}
	// function(p,n);
}
```