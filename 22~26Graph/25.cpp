

////////////////////////////////////////////////////////////////////////////////
//코드전체 미완성

#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>


const int NIL = 0;
const int INF = 100000000;


void print_matrix(std::vector < std::vector<int>>& m)
{
	const int n = m.size();

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (m[i][j] == INF)
				std::cout << "INF" << ' ';
			else
				std::cout << std::setw(3) << m[i][j] << ' ';

		}
		std::cout << '\n';
	}
	std::cout << '\n' << '\n';
}




//25.2-3 25.2-4에 이어서.
void RELAX(int u, int v, int w,int Distance[])//(Distance[u] != INF )&& 
{
	if ((Distance[u] != INF) && (Distance[v] > Distance[u] + w))
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
	}
}


void INITIALIZE_SINGLE_SOURCE(std::vector<std::vector<std::pair<int, int>>>& Graph, 
	int Distance[],	int s) //start std::vector<std::vector<int>> Graph ,int s
{
	for (std::size_t i = 1; i < Graph.size(); i++)
	{
		Distance[i] = INF;
	}
	Distance[s] = 0;
}


bool BELLMAN_FORD(std::vector<std::vector<std::pair<int, int>>>& Graph, int Distance[], int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph,Distance,s);
	for (std::size_t i = 1; i < Graph.size() - 1; i++)// 간선 u v w = Graph[v][]
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
			if ((Distance[v] > Distance[u] + Graph[u][j].second) && Distance[u] != INF) //출력초과가 나는 지점
			{
				Distance[v] = -1;
				return false;
			}
		}
	}
	return true;
}

void DUKSTRA(std::vector<std::vector<std::pair<int, int>>>& Graph, int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph,s);
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > PQ; //정점의 거리, 정점
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


std::vector<std::vector<int>> JOHNSON(std::vector<std::vector<std::pair<int, int>>>& Graph)
{
	std::vector<std::vector<int>> D;
	std::vector<std::vector<std::pair<int, int>>> G_apostrophe = Graph;
	int n = Graph.size();
	for (int i = 1; i < n; i++)
	{
		G_apostrophe[0].push_back(std::pair<int, int>(i, 0));
	}


	if (BELLMAN_FORD(G_apostrophe, 0, Distance) == false)
	{
		std::cout << "the input graph contains a negative-weight cycle" << std::endl;
	}
	else
	{
		//int h = Distance;

		int D_het[][] =
			for (int i = 0; i < n; i++)
			{

			}

		for (int i = 0; i < n; i++)
		{
			W_het[u][v] = W[u][v] + h[u] - h[v];
		}

		for (int u = 0; u < n; u++)
		{
			DUKSTRA(Graph, W_het, u, d_het);

			for (int v = 0; v < n; v++)
			{
				D[u][v] = d_het[u][v] + h[v] - h[u];
			}
		}
	}

	return D;
}

