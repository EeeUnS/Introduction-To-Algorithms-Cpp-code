

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include<stack>

typedef std::vector<std::vector<int>> Graph;

//bool visit[1010] = { 0, };
//std::vector<std::vector<int>> G;


//void DFS(const G& G, int s)
//{
//	std::vector<bool> visit(G.size(), false);
//
//	DFS_VISIT(G, s, visit);
//}
//
//
//void DFS_VISIT(G &G, int x, std::vector<bool> &visit)
//{
//	bool visit[1010] = { 0, };
//	visit[x] = true;
//	std::cout << x << ' '; // 순회출력
//
//	for (std::size_t i = 0; i < G[x].size(); i++)
//	{
//		int next = G[x][i];
//		if (visit[next] != true)
//			DFS_VISIT( G, next);
//	}
//}

void DFS(const Graph &G, int x)
{
	std::vector<bool> visit(G.size(), false);
	visit[x] = true;
	
	std::stack<int> sub_s;
	sub_s.push(x);
	//std::cout << sub_s.top() << ' '; // 순회출력

	while (!sub_s.empty())
	{
		int y = sub_s.top();
		std::size_t G_size = G[y].size();
		for (std::size_t i = 0; i < G_size; i++)
		{
			int next = G[y][i];
			if (visit[next] != true)
			{
				visit[next] = true;
				sub_s.push(next);
				//std::cout << sub_s.top() << ' '; // 순회출력
				i = -1;
				y = sub_s.top();
				G_size = G[y].size();
			}

		}
		sub_s.pop();
	}
}


void BFS(const Graph &G, int x)
{
	std::queue<int> Q;
	Q.push(x);
	std::vector<bool> visit(G.size(), false);
	visit[x] = true;

	while (!Q.empty())
	{
		int here = Q.front();
		Q.pop();
		std::cout << here << ' ';// 순회 출력
		std::size_t G_size = G[here].size();

		for (std::size_t i = 0; i < G_size; i++)
		{
			int next = G[here][i];
			if (visit[next] != true)
			{
				visit[next] = true;
				Q.push(next);
			}
		}
	}
}

int main()
{
	int n, m, s;
	std::cin >> n >> m >> s;
	Graph G;
	G.resize(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)  // 리스트 넘버순 정렬
		std::sort(G[i].begin(), G[i].end());
	DFS(G,s);
	puts("");
	
	BFS(G,s);
}