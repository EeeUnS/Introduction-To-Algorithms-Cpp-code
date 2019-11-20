#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef std::vector<std::vector<int>> Graph;
//std::vector<std::vector<int>> G; // 인접 노드
//std::vector<int> DAG; // 위상정렬

std::vector<int> topologicalsort(const Graph &G, int v)
{
	std::vector<int> indegree;
	indegree.resize(v + 1);
	std::queue<int> qu;
	std::vector<int > DAG;
	for (int i = 1; i <= v; i++)
	{
		int e = G[i].size();
		for (int j = 0; j < e; j++)
		{
			indegree[G[i][j]]++;
		}
	}

	for (int i = 1; i <= v; i++)
	{
		if (indegree[i] == 0)
		{
			qu.push(i);
		}
	}
	for (int i = 1; i <= v; i++)
	{
		if (qu.empty())
		{
			return DAG;
		}
		int x = qu.front();
		qu.pop();
		DAG.push_back(x);
		int x_size = G[x].size();
		for (int i = 0; i < x_size; i++)
		{
			int y = G[x][i];
			indegree[y]--;
			if (indegree[y] == 0)
			{
				qu.push(y);
			}
		}
	}
	return DAG;
}



int main()
{
	Graph G;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	G.resize(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
	}

	for (int i = 1; i <= n; i++)  // 리스트 넘버순 정렬
		std::sort(G[i].begin(), G[i].end());
	std::vector<int > DAG = topologicalsort(G, n);

	for (auto a : DAG)
	{
		std::cout << a << ' ';
	}

	return 0;
}