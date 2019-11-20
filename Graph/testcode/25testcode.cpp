//미완성

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




void INITIALIZE_SINGLE_SOURCE(std::vector<std::vector<int>>& Graph,
	std::vector<int>& Distance, int s)
{
	for (std::size_t i = 1; i < Graph.size(); i++)
	{
		Distance[i] = INF;
	}
	Distance[s] = 0;
}


void BF_RELAX(int u, int v, int w, std::vector<int>& Distance)
{
	if (Distance[v] > Distance[u] + w)
	{
		Distance[v] = Distance[u] + w;
	}
}

//for johnson's alg
bool BELLMAN_FORD(std::vector<std::vector<int>>& Graph, 
	std::vector<std::vector<int>>& W,
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph, Distance, s);
	const std::size_t n = Graph.size() - 1;

	for (std::size_t i = 1; i <= n; i++)// 간선 u v w = Graph[v][]
	{
		for (std::size_t u = 0; u <= n; u++)
		{
			const std::size_t sub_size = Graph[u].size();
			for (std::size_t j = 0; j < sub_size; j++)
			{
				int v = Graph[u][j];
				int w = W[u][v];
				BF_RELAX(u, v, w, Distance);
			}
		}
	}

	for (std::size_t u = 1; u <= n ; u++)
	{
		const std::size_t sub_size = Graph[u].size();
		for (std::size_t j = 0; j < sub_size; j++)
		{
			int v = Graph[u][j];
			if ((Distance[v] > Distance[u] + W[u][v]) && Distance[u] != INF)
			{
				Distance[v] = -1;
				return false;
			}
		}
	}
	return true;
}

void DIJK_RELAX(int u, int v, int w, std::vector<int >& Distance,
	std::priority_queue<std::pair<int, int>,
	std::vector<std::pair<int, int>>,
	std::greater<std::pair<int, int>> >& PQ)
{
	if ((Distance[u] != INF) && (Distance[v] > Distance[u] + w))
	{
		Distance[v] = Distance[u] + w;
		//predecessor_subgraph[v] = u;
		PQ.push(std::make_pair(Distance[v], v));
	}
}

void DIJKSTRA(std::vector<std::vector<int>>& Graph,
	std::vector<std::vector<int>>& W,
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph,Distance, s );
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > PQ; //정점의 거리, 정점
	for (std::size_t i = 1; i < Graph.size(); i++)
	{
		PQ.push(std::make_pair(Distance[i], i));
	}

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		PQ.pop();
		for (std::size_t i = 0; i < Graph[u].size(); i++)
		{
			int v = Graph[u][i];
			DIJK_RELAX(u, v, W[u][v], Distance,PQ);
		}
	}
}


std::vector<std::vector<int>> JOHNSON(std::vector<std::vector<int>>& Graph,
	std::vector<std::vector<int>>& W
)
{//
	std::vector<std::vector<int>> D;
	std::vector<std::vector<int>> G_apostrophe = Graph;
	const std::size_t n = Graph.size()-1;
	
	D.resize(n + 1);
	for (std::size_t i = 1; i <= n; i++)
	{
		W[0].resize(n + 1);
		G_apostrophe[0].push_back(i);
		D[i].resize(n + 1);
	}
	
	std::vector<int > Distance; // and h(x)
	Distance.resize(n + 1);

	if (BELLMAN_FORD(G_apostrophe,W ,Distance,0) == false)
	{
		std::cout << "the input graph contains a negative-weight cycle" << std::endl;
	}
	else
	{
		
		std::vector<int> h = Distance;
		std::vector < std::vector<int>> W_het = W;		
		std::vector < std::vector<int>> D_het;
		D_het.resize(n + 1);
		for (std::size_t i = 1; i <= n; i++)
		{
			D_het[i].resize(n + 1);
		}

		

		for (std::size_t u = 1; u <= n; u++)
		{
			const int sub_size = Graph[u].size();
			for (int j = 0; j < sub_size; j++)
			{
				int v = Graph[u][j];
				W_het[u][v] += (h[u] - h[v]);
			}
		}
		for (std::size_t u = 1; u <= n; u++)
		{
			DIJKSTRA(Graph, W_het, D_het[u], u );
			
			const int sub_size = Graph[u].size();
			for (std::size_t v = 1; v <= n; v++)
			{
				D[u][v] = D_het[u][v] + h[v] - h[u];
			}
		}
	}
	return D;
}



/*
0 3 8 1 4
1 0 1 1 7
1 4 0 1 1
2 1 5 0 1
1 1 1 6 0
*/

/*
0 1 3 2 4
3 0 4 1 1
7 4 0 5 3
2 1 5 0 2
8 5 1 6 0
*/

/*
NIL 3 4 5 1
4 NIL 4 2 1
4 3 NIL 2 1
4 3 4 NIL 1
4 3 4 5 NIL
*/

/*
-1 -1
-1 -1

*/

/*
{
{},
{0,1, 0, 0, 0},
{0,0, 1, 1, 1, },
{0,0, 1, 1, 0},
{0,1, 0, 1, 1}
}

*/

int main()
{
	const int n = 5;
	std::vector<std::vector<int>> W/*= 
	{
{},
{0,1, 0, 0, 0},
{0,0, 1, 1, 1 },
{0,0, 1, 1, 0},
{0,1, 0, 1, 1}
	}*/
	;/*=
	{ {},
	{0,-1,-1},
	{0,-1,-1}
	};*/
	//A.resize(n + 1);
	W.push_back({});
	W.push_back(std::vector<int>{0, 0, 3, 8, INF, -4});
	W.push_back(std::vector<int>{ 0,INF,0,INF,1,7 });
	W.push_back(std::vector<int>{ 0,INF ,4,0,INF ,INF });
	W.push_back(std::vector<int>{0 , 2, INF ,-5, 0 ,INF });
	W.push_back(std::vector<int>{ 0,INF ,INF ,INF ,6,0 });

	std::vector<std::vector<int>> Graph;
	Graph.resize(n + 1);



	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((W[i][j] != INF) && (W[i][j] != 0))
			{
				Graph[i].push_back(j);
			}
		}
	}


	std::vector< std::vector<int>> __L;
	std::vector< std::vector<int>> __PI;
	
	

	print_matrix(W);
	
	__L = JOHNSON(Graph,W);


	print_matrix(__L);
	//print_matrix(__PI);
	
/*
	std::vector< std::vector<int>> LLK = {{0},
	{1, 0, 1, 1, 7},
	{1 ,4 ,0, 1, 1},
	{	2 ,1, 5, 0, 1},
	{1 ,1, 1, 6, 0},
	};*/
}

/*

{
	{}
	{0, 0, 3, 8, INF, -4},
	{ 0,INF,0,INF,1,7 },
	{ 0,INF ,4,0,INF ,INF },
	{0 , 2, INF ,-5, 0 ,INF },
	{ 0,INF ,INF ,INF ,6,0 },
};

	*/