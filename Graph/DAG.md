
# topological sort
# Directed acyclic graph
```
ios_base::sync_with_stdio(false); cin.tie(NULL);

```
https://www.acmicpc.net/problem/2252

## 책안의 구조
 Cormen et al. (2001); Tarjan (1976)이 제안
```
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
constexpr int MAX = 320000;
stack<int> S; // 실제 정렬된값이 역순으로 들어가있다.

std::vector<std::vector<int>> Graph; // 인접 노드
bool visit[MAX+2] = { 0, };
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
## Kahn's algorithm




```

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
std::vector<std::vector<int>> Graph; // 인접 노드
std::vector<int> DAG; // 위상정렬
```


```

void topologicalsort(int v)
{
	std::vector<int> indegree;
	indegree.resize(v + 1);
	for (int i = 1; i <= v; i++)
	{
		int e = Graph[i].size();
		for (int j = 0; j < e; j++)
		{
			indegree[Graph[i][j]]++;
		}
	}
	for (int r = 1; r <= v; r++)
	{
		for (int i = 1; i <= v; i++) //n^2
		{
			if (indegree[i] == 0)
			{
				DAG.push_back(i);
				int e = Graph[i].size();
				--indegree[i];
				for (int j = 0; j < e; j++)
				{
					--indegree[Graph[i][j]];
				}

			}
		}
	}
}


```
정점v와 indegree를 넣은 minheap을 사용하면
n에 구현할수있다.

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
	topologicalsort(n);

	for (auto a: DAG)
	{
		std::cout << a << ' ';
	}
	
	return 0;
}
//앆
```