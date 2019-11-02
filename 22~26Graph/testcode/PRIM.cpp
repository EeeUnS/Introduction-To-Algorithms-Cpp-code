//https://www.acmicpc.net/problem/1197

#include<iostream>
#include<stack>
#include<algorithm>
#include<vector>
#include<array>
#include<queue>
#include<utility>
#include<stdio.h>

using namespace std;

constexpr int MAX = 10002;
constexpr int INF = 7000000;

std::vector<std::vector<std::pair<int, int>>> Graph; // 인접한 정점,가중치
std::priority_queue<std::pair<int, int>,
	std::vector<std::pair<int, int>>,
	std::greater<std::pair<int, int>> > PQ; //
int pi[MAX];// 정점의 직전 원소 저장
int key[MAX];// 정점의 직전 원소와의 간선 가중치
bool visited[MAX];

int V, E;//, start;


std::int64_t  answer = 0;

void MST_PRIM(int r)
{
	std::size_t vertex_n = Graph.size();
	for (size_t i = 1; i <= V; i++)
	{
		key[i] = INF;
		pi[i] = 0;
	}
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
		//answer += _key;

		visited[u] = true;
		size_t u_size = Graph[u].size();


		/*if (!visited[u] && _key < key[u])
		{
			pi[v] = u;
			key[v] = _key;
		}*/
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
}

/*
3 3
1 2 1
2 3 2
1 3 3
*/
int main()
{

	cin.tie(0);
	ios::sync_with_stdio(false);
	//std::ifstream in("in3.txt"); //std::cin
	//int V, E;//, start;
	//in >> V >> E ;
	//in >> start;
	std::cin >> V >> E;
	//std::cin >> start;

	Graph.resize(MAX);
	for (int i = 0, _v, _u, _w; i < E; i++)
	{
		//in >> _v >> _u >> _w;
		std::cin >> _v >> _u >> _w;
		Graph[_v].push_back(std::make_pair(_u, _w)); //정점 ,간선 가중치 순으로 넣는다.
		Graph[_u].push_back(std::make_pair(_v, _w)); //정점 ,간선 가중치 순으로 넣는다.
	}

	MST_PRIM(1);
	for (int i = 2; i <= V; i++)
	{
		answer += key[i];
	}
	cout << answer << "\n";


	return 0;
}