


```
#include<queue>
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
queue<int> Q;
const int MAX = 100000;
stack<int> S; // 실제 정렬된값이 역순으로 들어가있다.

std::vector<std::vector<int>> Graph; // 인접 노드
bool visit[32002] = { 0, };
```



```
void topologicalsort()
{
	for (std::size_t i = 1; i < Graph.size(); i++)
	{
		if (visit[i] != true)
		{
			DFS_TS(i);
		}
	}
}
```




```
void DFS_TS(int x)
{
	visit[x] = true;

	std::stack<int> sub_s;
	sub_s.push(x);
	//std::cout << sub_s.top() << ' '; // 순회출력

	while (!sub_s.empty())
	{
		int y = sub_s.top();
		for (std::size_t i = 0; i < Graph[y].size(); i++)
		{
			int next = Graph[y][i];
			if (visit[next] != true)
			{
				visit[next] = true;
				sub_s.push(next);
				//std::cout << sub_s.top() << ' '; // 순회출력
				i = -1;
				y = sub_s.top();
			}

		}
		S.push(sub_s.top());
		sub_s.pop();
		
	}
}
```
기존 DFS와 차이는 마지막 sub_s.pop()하기전에 
값을 S에 넣는 것이다.

```
int main()
{
	int n, m;
	std::cin >> n >> m;
	Graph.resize(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		Graph[u].push_back(v);
	}

	for (int i = 1; i <= n; i++)  // 리스트 넘버순 정렬
		std::sort(Graph[i].begin(), Graph[i].end());
	topologicalsort();

	while (!S.empty())
	{
		std::cout << S.top() << ' ';
		S.pop();
	}
	return 0;
}
//앆
```

