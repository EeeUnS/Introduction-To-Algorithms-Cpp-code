# Single Source Shortest Paths
기본 프로시저
```
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
완화에서 다음 프로시저를 실행하고 하면된다. predecessor_subgraph[v] = u;
```
void RELAX(int u, int v, int w)
{
	if (Distance[v] > Distance[u] + w)
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
	}
}
```
```
void INITIALIZE_SINGLE_SOURCE(int s) //start std::vector<std::vector<int>> Graph ,int s
{
	for (int i = 1; i < Graph.size() ; i++)
	{
		Distance[i] = INF;
	}
	Distance[s] = 0;
}
```

## Dijkstra's algorithm

https://www.acmicpc.net/problem/1753
참고:
https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Running_time

우선순위큐 사용 O(ElogV)
```
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
```


```
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
```

```

void RELAX(int u, int v, int w)
{
	if (Distance[v] > Distance[u] + w)
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
		PQ.push(std::make_pair(Distance[v], v));
	}
}
```
PQ의 탑 디스턴스값을 갱신시켜야한다 따라서 뽑고 다시넣는다.
책의 의사코드에 치명적인 문제가 하나있는데
완화에서 Q.decrease_priority로 key 거리값을 갱신 시켜줘야한다.

```
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

#BELLMAN FORD

https://www.acmicpc.net/problem/11657

CLRS와 다르게 RELAX부분에 Distance[u]의 inf조건 검사를 한다. 꼭 해야한다.


```
//

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
	//std::ifstream in("in3.txt"); //std::cin
	int V, E, start;
	//in >> V >> E ;
	//in >> start;
	std::cin >> V >> E;
//	std::cin >> start;

	Graph.resize(V + 1);
	for (int i = 0, _v, _u, _w; i < E; i++)
	{
		//in >> _v >> _u >> _w;
		std::cin >> _v >> _u >> _w;
		/*bool vec = true;
		for (int i = 0; i < Graph[_v].size(); i++)
		{
			if ((Graph[_v][i].first == _u) && (Graph[_v][i].second > _w))
			{
				Graph[_v][i].second = _w;
				vec = false;
				break;
			}
		}
		if (!vec)
		{
			continue;
		}*/
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
```