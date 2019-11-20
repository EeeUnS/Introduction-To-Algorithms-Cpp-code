//https://www.acmicpc.net/problem/1197

#include<vector>
#include<iostream>
#include<algorithm>
typedef std::vector<std::vector<int>> Graph;
//with Disjoint-set forests
class UNION_FIND
{
public:
	UNION_FIND() : n(101)
	{
		rank = new int[101];
		parent = new int[101];
		
	}

	UNION_FIND(int n) : n(n)
	{
		rank = new int[n];
		parent = new int[n];
	}

	~UNION_FIND()
	{
		delete[] rank;
		delete[] parent;
	}

	void MAKE_SET(int x)
	{

		parent[x] = x;
		rank[x] = 0;
	}

	void UNION(int x, int y)
	{
		LINK(this->FIND_SET(x), this->FIND_SET(y));
	}

	int FIND_SET(int x)//path compression
	{
		if (x != parent[x])
		{
			parent[x] = this->FIND_SET(parent[x]);
		}
		return parent[x];
	}

	int capacity()
	{
		return n;
	}
private:
	int* rank;//Union by ran
	int* parent;
	int n;
	void LINK(int x, int y)
	{
		if (rank[x] > rank[y])
		{
			parent[y] = x;
		}
		else
		{
			parent[x] = y;
			if (rank[x] == rank[y])
			{
				rank[y] = rank[y] + 1;
			}
		}
	}
};

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

std::vector<edge> MST_KRUSKAL(Graph& G, std::vector<edge>& W)
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

/*
3 3
1 2 1
2 3 2
1 3 3
*/


int main()
{
	std::ios::sync_with_stdio(false);
	std::vector<edge> W;
	Graph Graph;
	int n, m;
	std::cin >> n >> m;
	Graph.resize(10001);
	W.resize(m);
	for (int i = 0; i < m; i++)
	{
		int u, v,w;
		std::cin >> u >> v >> w;
		Graph[u].push_back(v);
		//Graph[v].push_back(u);
		W[i].u = u;
		W[i].v = v;
		W[i].w = w;
 	}
	std::vector<edge> A = MST_KRUSKAL(Graph,W);
	std::int64_t sum = 0;
	std::size_t mst_size = A.size();
	for (int i = 0; i < mst_size; i++)
	{
		sum += A[i].w;
	}
	std::cout << sum;
}