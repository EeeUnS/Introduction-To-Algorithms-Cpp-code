//https://www.acmicpc.net/problem/1753
#include<queue>
#include<iostream>
#include<stack>
#include<algorithm>
#include<utility>

using namespace std;
queue<int> Q;
const int MAX = 20002;
constexpr int INF = 7000000;
std::vector<std::vector<std::pair<int,int>>> Graph;
std::priority_queue<std::pair<int,int>,  std::vector<std::pair<int, int>>,std::greater<std::pair<int, int>> > PQ; //정점의 거리, 정점
int Distance[MAX];


void INITIALIZE_SINGLE_SOURCE(int s) //start std::vector<std::vector<int>> Graph ,int s
{
	for (int i = 1; i < Graph.size() ; i++)
	{
		Distance[i] = INF;
	}
	Distance[s] = 0;
}


void DUKSTRA( int s) 
{
	INITIALIZE_SINGLE_SOURCE(s);
	
	for (int i = 1; i < Graph.size(); i++)
	{
		PQ.push(std::make_pair(Distance[i], i));
	}

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		//S  = S+u
        PQ.pop();
		for (int v = 0; v < Graph[u].size(); v++)
		{
			RELAX(u, Graph[u][v].first, Graph[u][v].second); 
		}
	}
}



void RELAX(int u, int v, int w)
{
	if (Distance[v] > Distance[u] + w)
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
		PQ.push(std::make_pair(Distance[v], v));
	}
}


int main()
{
	
	cin.tie(0);
	ios::sync_with_stdio(false);
	//std::ifstream in("in3.txt"); //std::cin
	int V, E,  start;
	//in >> V >> E ;
	//in >> start;
	std::cin >> V >> E;
	std::cin >> start;

	Graph.resize(V + 1);
	for (int i = 0,_v,_u,_w; i < E; i++)
	{
		//in >> _v >> _u >> _w;
		std::cin>> _v >> _u >> _w;
		Graph[_v].push_back(std::make_pair(_u, _w)); //간선 ,, 인접한정점 순으로 넣는다.
	}
	DUKSTRA(start);
	for (int i = 1; i <= V; i++)
	{
		if (Distance[i] == INF)
		{
			std::cout << "INF" << '\n';
		}
		else
		{
			std::cout << Distance[i] << '\n';
		}
	}
}
```