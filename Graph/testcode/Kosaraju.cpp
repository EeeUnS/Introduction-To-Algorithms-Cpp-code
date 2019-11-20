

//https://www.acmicpc.net/problem/2150
#include<iostream>
#include<stack>
#include<algorithm>
#include<vector>
//using namespace std;

typedef std::vector<std::vector<int>> Graph ;
constexpr int MAX = 10000;
/*
Graph G; //G 인접 노드
Graph TG; //G^T 인접 노드 
bool visit[MAX + 2] = { 0, };
Graph SSC;   //각각의 ssc가 들어간다
*/

void TDFS(Graph& TG, int x, std::vector<int>& SSC, std::vector<bool>& visit);//G^T탐색
void DFS(const Graph& G, int x, std::stack<int>& DFSf, std::vector<bool>& visit);

Graph STRONGLY_CONNECTED_COMPONENTS(const Graph &G)
{
	const int v = G.size()-1;
	 
	Graph SSC;
	std::stack<int> DFSf; // DFS pop 순서대로 들어가있다.
	std::vector<bool> visit(v+2 ,false);
	for (int i = 1; i <= v; i++) {
		if (visit[i] != true)
			DFS(G, i, DFSf,visit); //DFS순회 순서를 S에 저장한다.
	}

	Graph TG(v + 1, (std::vector<int>()));//G^T
	for (int i = 1; i <= v; i++)
	{
		const int sub_size = G[i].size();
		for (int j = 0; j < sub_size; j++)
		{
			TG[G[i][j]].push_back(i);
		}
	}
	
	visit.assign(v+1,false);
	for (int i = 0; i < v; i++)
	{
		if (visit[DFSf.top()] != true)
		{
			SSC.push_back(std::vector<int>());
			TDFS(TG, DFSf.top(), SSC[SSC.size()-1],visit);
			///SSC_n++;
		}
		DFSf.pop();
	}

	const int n = SSC.size();
	for (int i = 0; i < n; i++)
	{
		sort(SSC[i].begin(), SSC[i].end());
	}

	std::sort(SSC.begin(), SSC.end(),
		[](const std::vector<int>& a, const std::vector<int>& b) -> bool
		{
			return a[0] < b[0];
		});

	return SSC;
}
//
//void DFS(const Graph &G, int x, std::stack<int>& DFSf , std::vector<bool> &visit)
//{
//	visit[x] = true;
//	std::stack<int> sub_s;
//	sub_s.push(x);
//	while (!sub_s.empty())
//	{
//		int y = sub_s.top();
//		for (std::size_t i = 0; i < G[y].size(); i++)
//		{
//			int next = G[y][i];
//			if (visit[next] != true)
//			{
//				visit[next] = true;
//				sub_s.push(next);
//				i = -1;
//				y = sub_s.top();
//			}
//		}
//		DFSf.push(sub_s.top());//기존 DFS와 차이 STACK에 종료 순서 저장
//		sub_s.pop();
//	}
//}


void DFS(const Graph& G, int x, std::stack<int>& DFSf, std::vector<bool>& visit)
{
	visit[x] = true;
	//std::cout << x << ' '; // 순회출력

	for (std::size_t i = 0; i < G[x].size(); i++)
	{
		int next = G[x][i];
		if (visit[next] != true)
		{
			DFS(G, next, DFSf,visit);
		}
	}
	DFSf.push(x);//기존 DFS와 차이 STACK에 종료 순서 저장
}

//
//void TDFS(Graph &TG, int x,std::vector<int> &SSC, std::vector<bool> &visit)//G^T탐색
//{
//	visit[x] = true;
//
//	std::stack<int> sub_s;
//	sub_s.push(x);
//	//std::cout << sub_s.top() << ' '; // 순회출력
//
//	while (!sub_s.empty())
//	{
//		int y = sub_s.top();
//		for (std::size_t i = 0; i < TG[y].size(); i++)
//		{
//			int next = TG[y][i];
//			if (visit[next] != true)
//			{
//				visit[next] = true;
//				sub_s.push(next);
//				//std::cout << sub_s.top() << ' '; // 순회출력
//				i = -1;
//				y = sub_s.top();
//			}
//
//		}
//		SSC.push_back(sub_s.top());
//
//		sub_s.pop();
//
//	}
//}


void TDFS(Graph& TG, int x, std::vector<int>& SSC, std::vector<bool>& visit)
{
	visit[x] = true;
	//std::cout << x << ' '; // 순회출력
	std::size_t x_size = TG[x].size();
		for (std::size_t i = 0; i < x_size; i++)
		{
			int next = TG[x][i];
			if (visit[next] != true)
			{
				TDFS(TG, next, SSC,visit);
			}
		}
	SSC.push_back(x);
}


int main()
{
	std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
	int v, e;
	Graph G, TG;
	std::cin >> v >> e;
	G.resize(v + 1);
	TG.resize(v + 1);
	for (int i = 0; i < e; i++)
	{
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
	}

	for (int i = 1; i <= v; i++)  // 리스트 넘버순 정렬
	{
		std::sort(G[i].begin(), G[i].end());
		std::sort(TG[i].begin(), TG[i].end());
	}
	Graph SSC = STRONGLY_CONNECTED_COMPONENTS(G);
	const int SSC_n = SSC.size();
	std::cout << SSC_n << '\n';
	for (int i = 0; i < SSC_n; i++)
	{
		int nn = SSC[i].size(); //각 ssc의 갯수
		for (int j = 0; j < nn; j++)
		{
			std::cout << SSC[i][j] << ' ';
		}
		std::cout << -1 << '\n';
	}

	return 0;
}