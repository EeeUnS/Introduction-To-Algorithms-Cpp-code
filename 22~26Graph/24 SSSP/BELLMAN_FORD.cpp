

/* 
https://www.acmicpc.net/problem/11657

CLRS와 다르게 RELAX부분에 Distance[u]의 inf조건 검사를 한다. 꼭 해야한다.

*/

#include <iostream>
#include<vector>
#include<climits>
using namespace std;
//54퍼에서땡
const int MAX = 600;
constexpr int INF = INT32_MAX;
//bool visit[MAX] = { 0, };
std::vector<std::vector<std::pair<int, int>>> Graph; // [v] index에 u,w 을 저장.
int Distance[MAX]; //S로부터 index i까지의 거리.


void RELAX(int u, int v, int w)//(Distance[u] != INF )&& 
{
	if((Distance[u] != INF) && (Distance[v] > Distance[u] + w))
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
	}
}


void INITIALIZE_SINGLE_SOURCE(int s) //start std::vector<std::vector<int>> Graph ,int s
{
	for (std::size_t i = 1; i < Graph.size(); i++)
	{
		Distance[i] = INF;
	}
	Distance[s] = 0;
}


bool BELLMAN_FORD(int s)
{
	INITIALIZE_SINGLE_SOURCE(s);
	for (std::size_t i = 1; i < Graph.size()-1; i++)// 간선 u v w = Graph[v][]
	{
		for (std::size_t u = 1; u < Graph.size(); u++)
		{
			for (std::size_t j = 0; j < Graph[u].size(); j++)
			{
				int v = Graph[u][j].first;
				int w = Graph[u][j].second;
				RELAX(u, v, w);
			}
		}
	}

	for (std::size_t u = 1; u < Graph.size(); u++)
	{
		for (std::size_t j = 0; j < Graph[u].size(); j++)
		{
			int v = Graph[u][j].first;
			if ((Distance[v] > Distance[u] + Graph[u][j].second ) && Distance[u] != INF) //출력초과가 나는 지점
			{
				Distance[v] = -1;
				return false;
			}
		}
	}
	return true;
}



int main()
{

	cin.tie(0);
	ios::sync_with_stdio(false);
	int V, E, start;
	std::cin >> V >> E;

	Graph.resize(V + 1);
	for (int i = 0, _v, _u, _w; i < E; i++)
	{
		std::cin >> _v >> _u >> _w;
		Graph[_v].push_back(std::make_pair(_u, _w)); //간선 ,, 인접한정점 순으로 넣는다.
	}

	if (!BELLMAN_FORD(1))
	{
		cout << -1 <<'\n';
		return 0;
	}


	for (int i = 2; i <= V; i++)
	{
		if (Distance[i] >= (INF - 5000000))
		{
			std::cout << -1 << '\n';
		}
		else
		{
			std::cout << Distance[i] << '\n';
		}
	}
	return 0;
}