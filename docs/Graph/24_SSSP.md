# Single Source Shortest Paths
기본 프로시저
```C++
const int NIL = 0;
const int INF = 100000000;

int predecessor_subgraph[MAX];//직전원소 그래프 v.pi

void PRINT_PATH(int s, int v)
{
	if (v == s)
		;
	/*else if (predecessor_subgraph[v] == 0) //최단경로 v가 보장되어있고 start가 0일때는 해당 주석을 뗀다
	{
		return;
	}*/
	else
		PRINT_PATH(s, predecessor_subgraph[v]);
	cout << v << ' ';
}
```

- 2차 vector G
- s 정점으로부터 출발
- distance는 정점 s로부터의 거리 

```C++
void INITIALIZE_SINGLE_SOURCE(const Graph& G,
	std::vector<int>& Distance, int s)
{
	for (std::size_t i = 1; i < G.size(); i++)
	{
		Distance[i] = INF;
	}
	Distance[s] = 0;
}
```


완화에서 다음 프로시저를 실행하고 하면된다. 
predecessor_subgraph[v] = u;

# 24.1 BELLMAN FORD

- u -> v : 가중치 w

```C++
void BF_RELAX(int u, int v, int w, std::vector<int>& Distance)
{
	if ((Distance[u] != INF) && Distance[v] > Distance[u] + w)
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
	}
}
```

```C++
bool BELLMAN_FORD(const Graph& G, 
	std::vector<std::vector<int>>& W,
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(G, Distance, s);
	const std::size_t n = G.size() - 1;

	for (std::size_t i = 1; i <= n; i++)// 간선 u v w = G[v][]
	{
		for (std::size_t u = 0; u <= n; u++)
		{
			for(int v : G[u])
			{
				int w = W[u][v];
				BF_RELAX(u, v, w, Distance);
			}
		}
	}

	for (std::size_t u = 1; u <= n ; u++)
	{
		for (int v : G[u])
		{
			if ((Distance[v] > Distance[u] + W[u][v]) && Distance[u] != INF)
			{
				Distance[v] = -1;
				return false;
			}
		}
	}
	return true;
}
```
# 24.2 Single-source shortest paths in directed acyclic graphs


```C++
	W[1][2] = 5;
	W[2][3] = 2;
	W[2][4] = 6;
	W[3][4] = 7;
	W[3][5] = 4;
	W[3][6] = 2;
	W[4][5] = -1;
	W[4][6] = 1;
	W[5][6] = -2;
```

$\Theta(V+E)$
```C++
void DFS_TS(const Graph& G, std::vector<bool> &visit, 
	stack<int> &S, int x)
{
	visit[x] = true;

	//std::cout << x << ' '; // 순회출력

	for (int next : G[x])
	{
		if (visit[next] != true)
		{
			DFS_TS(G,visit,S,next);
		}
	}
	S.push(x);
}

std::stack<int> topologicalsort(const Graph& G)
{
	const int n = G.size();
	std::vector<bool> visit;
	visit.resize(n);
	stack<int> S; // 실제 정렬된값이 역순으로 들어가있다.
	for (std::size_t i = 1; i < n; i++)
	{
		if (visit[i] != true)
		{
			DFS_TS(G,visit,S, i);
		}
	}
	return  S;
}

void INITIALIZE_SINGLE_SOURCE(const Graph& G,
	std::vector<int>& Distance, int s)
{
	std::fill(Distance.begin(), Distance.begin() + Graph.size(), INF);
	Distance[s] = 0;
}

void RELAX(int u, int v, int w, std::vector<int>& Distance)
{
	if (Distance[v] > Distance[u] + w)
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
	}
}


void DAG_SHORTEST_PATHS(const Graph& G,
	std::vector<std::vector<int>>& W,
	std::vector<int>& Distance, int s)
{
	std::stack<int> S = topologicalsort(G);
	INITIALIZE_SINGLE_SOURCE(G, Distance, s);

	while(!S.empty())
	{
		int u =S.top();
		S.pop();
		for (int v : G[u])
		{
			RELAX(u, v, W[u][v], Distance);
		}
	}
}
```


# 24.3 Dijkstra's algorithm

참고:
https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Running_time

우선순위큐 사용 $O(E\log V)$

PQ의 탑 디스턴스값을 갱신시켜야한다 따라서 뽑고 다시넣는다.
책의 의사코드에 치명적인 문제가 하나있는데
완화에서 Q.decrease_priority로 key 거리값을 갱신 시켜줘야한다.



```C++
void DIJK_RELAX(int u, int v, int w, std::vector<int >& Distance,
	std::priority_queue<
		std::pair<int, int>,	
		std::vector<std::pair<int, int>>,	
		std::greater<std::pair<int, int>>>& PQ)
{
	if ((Distance[u] != INF) && (Distance[v] > Distance[u] + w))
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
		PQ.push(std::make_pair(Distance[v], v));
	}
}
```

```C++
void DIJKSTRA(const Graph& G,
	std::vector<std::vector<int>>& W,
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(G,Distance, s );
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > PQ; //정점의 거리, 정점
	for (std::size_t i = 1; i < G.size(); i++)
	{
		PQ.push(std::make_pair(Distance[i], i));
	}

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		PQ.pop();
		for (int v : G[u])
		{
			DIJK_RELAX(u, v, W[u][v], Distance,PQ);
		}
	}
}
```

