## 활동 선택 문제(activity selection problem)


main함수
```
#include<iostream>
#include<queue>
#include<vector>
#include<utility>
// C[i,j] = max(C[i,k] + C[k,j] + 1)

void activity_selection(int s[], int f[]);

std::queue<std::pair<int, int>> Q;

int main()
{
	int n;
	std::cin >> n;
	int* s = new int[n + 1];
	int* f = new int[n + 1]; //f는 정렬되어있다고 가정 아니면 s와 함께 f기준으로 정렬해야한다.
	int a;
	for (int i = 1; i <= n; i++)
	{
		std::cin >> s[i];
	}
	for (int i = 1; i <= n; i++)
	{
		std::cin >> f[i];
	}
	activity_selection(s, f);

	while(Q.size())
	{
		auto a = Q.front();
		Q.pop();
		std::cout <<"start : " << a.first << " final : " << a.second << '\n';
	}
	
}
```


1. f가 제일작은 f[0]을 선택한다. 이게 a0
2. 이 앞의 f[0]보다 큰 s[i]를 선택한다. a1
3. 반복


구현

```
std::queue<std::pair<int, int>>& Q
void activity_selection(int s[], int f[])
{
	std::pair<int, int> q(s[0], f[0]);
	Q.push(q);
	int fref = f[0];
	for (std::size_t i = 1; i < s.size(); i++)
	{
		if( s[i] >= fref)
		{
			q.first = s[i];
			q.second = f[i];
			Q.push(q);
			fref = f[i];
		}
	}
	return;
}
```