# 23 Minimum Spaning Tree

```C++
typedef std::vector<std::vector<int>> Graph;
typedef std::vector<std::vector<std::pair<int, int>>> Weight_Graph; // [u] (v,w)
```

# 23.1 Growing a minimum spanning tree


# 23.2 The algorithms of Kruskal and Prim

## Kruskal's algorithm 

need Ch 21 class UNION_FOUND
```C++
struct edge
{
	int u;
	int v;
	int w;

	bool operator <(edge& Edge)
	{
		return this->w < Edge.w;
	}
};

std::vector<edge> MST_KRUSKAL(const Graph& G,const  std::vector<edge>& W)
{
	std::vector<edge> A;
	
	const int n = G.size() - 1;
	UNION_FIND SET(n+1);
	for (int v = 1; v <= n; v++)
	{
		SET.MAKE_SET(v);
	}
	std::sort(W.begin(), W.end());
	const int m = W.size();
	for (int i = 0; i < m; i++)
	{
		if (SET.FIND_SET(W[i].u) != SET.FIND_SET(W[i].v))
		{
			A.push_back({ W[i].u,W[i].v,W[i].w });
			SET.UNION(W[i].u, W[i].v);
		}
	}
	return A;
}
```

## Prim's algorithm

```C++

Set MST_PRIM(const  &Graph, int r)
{
	std::priority_queue<std::pair<int, int>,
		std::vector<std::pair<int, int>>,
		std::greater<std::pair<int, int>> > PQ;
	std::size_t vertex_n = Graph.size();
	std::vector<int> pi(vertex_n,0);// 정점의 직전 원소 저장
	std::vector<int> key(vertex_n, INF);// 정점의 직전 원소와의 간선 가중치
	std::vector<bool> visited(vertex_n,false);

	key[r] = 0;
	visited[r] = true;

	const size_t r_size = Graph[r].size();
	for (std::size_t i = 0; i < r_size; i++)
	{
		int v = Graph[r][i].first;
		int w_uv = Graph[r][i].second;
		
		pi[v] = r;
		key[v] = w_uv;

		PQ.push(std::make_pair(w_uv, v));
	}

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		int _key = PQ.top().first;
		PQ.pop();

		if (visited[u])
		{
			continue;
		}
		visited[u] = true;
		size_t u_size = Graph[u].size();
		for (size_t i = 0; i < u_size; i++)
		{
			int v = Graph[u][i].first;
			int w_uv = Graph[u][i].second;
			if (!visited[v] && w_uv < key[v])
			{
				pi[v] = u;
				key[v] = w_uv;
				PQ.push(std::make_pair(w_uv, v));
			}
		}
	}
	return std::make_pair(pi, key);
}

```