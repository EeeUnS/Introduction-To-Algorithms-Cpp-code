# All-Pairs Shortest Paths

```C++
{
	{},
	{0, 0, 3, 8, INF, -4},
	{ 0,INF,0,INF,1,7 },
	{ 0,INF ,4,0,INF ,INF },
	{0 , 2, INF ,-5, 0 ,INF },
	{ 0,INF ,INF ,INF ,6,0 }
};

```

```C++
const int NIL = 0;
const int INF = 100000000;

void PRINT_ALL_PAIRS_SHORTEST_PATH(std::vector<std::vector<int>> pi, int i, int j)
{
	if (i == j)
		std::cout << ' ' << i << ' ';
	else if (pi[i][j] == NIL)
	{
		std::cout << "no path from " << i << " to " << j << " exists" << std::endl;
	}
	else
	{
		PRINT_ALL_PAIRS_SHORTEST_PATH(pi, i, pi[i][j]);
		std::cout << ' ' << j << ' ';
	}
}
```

```C++
#include<iomanip>
void print_matrix(std::vector < std::vector<int>>& m)
{
	const int n = m.size();

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if(m[i][j] == INF)
				std::cout << "INF" << ' ';
			else
				std::cout <<std::setw(3)<< m[i][j] << ' ';
			
		}
		std::cout << '\n';
	}
	std::cout << '\n' << '\n';
}

```


# 25.1 Shortest paths and matrix multiplication

O(V^3)
```C++
std::vector<std::vector<int>> EXTEND_SHORTEST_PATHS(std::vector<std::vector<int>>& L, std::vector<std::vector<int>>& W)
{
	const int n = L.size();


	std::vector<std::vector<int>> L_prime;
	L_prime.assign(n, std::vector<int>(n, INF));
	for(int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{

			for (int k = 1; k < n; k++)
			{
				L_prime[i][j] = (L_prime[i][j] < L[i][k] + W[k][j] ?  L_prime[i][j] : L[i][k] + W[k][j]);
			}

		}
	}
	return L_prime;
}
```


총 O(V^4)
```C++
//nxn 1~n
std::vector<std::vector<int>>SLOW_ALL_PAIRS_SHORTEST_PATHS(std::vector<std::vector<int>>& W)
{
	const int n = W.size() - 1;

	std::vector<std::vector<std::vector<int>>> L;
	L.resize(n+1);
	for (int i = 0 ; i < n+1;i++)
	{
		L[i].resize(n+1);
		for (int j = 0; j < n + 1; j++)
		{
			L[i][j].resize(n + 1);
		}
	}
	L[1] = W;
	for (int m = 2; m < n; m++)
	{
		L[m] = EXTEND_SHORTEST_PATHS(L[m - 1], W);
	}
	return L[n-1];
}
```



총 O(V^3log(V))
```C++
std::vector<std::vector<int>>FASTER_ALL_PAIRS_SHORTEST_PATHS(std::vector<std::vector<int>>& W)
{
	const int n = W.size() - 1;

	std::vector<std::vector<std::vector<int>>> L;
	int a = 1;
	while (a < n)
	{
		a = a * 2;
	}


	L.resize(a+1);
	for (int i = 0; i <= a ; i++)
	{
		L[i].resize(n+1);
		for (int j = 0; j <= n ; j++)
		{
			L[i][j].resize(n + 1);
		}
	}
	L[1] = W;
	int m = 1;
	while(m < n -1)
	{
		L[2*m] = EXTEND_SHORTEST_PATHS(L[m], L[m]);
		m = m*2;
	}
	return  L[m];
}
```





//25.1-6
```C++
void set_pi(std::vector<std::vector<int>> &W, std::vector<std::vector<int >> &L, std::vector<std::vector<int>>& pi)
{
	const int n = L.size();
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n ;j++)
		{
			for (int k = 1; k < n; k++)
			{
				if ((L[i][j] - L[i][k]) == W[k][j])
				{
					if (W[k][j] != 0 && i!=j)
					{
						pi[i][j] = k;
					}
				}
			}
		}
	}
}
```

//25.7
전체 다시 짜기
```C++
//25.1-7
void EXTEND_SHORTEST_PATHS_pi(std::vector<std::vector<int>>& L, 
	std::vector<std::vector<int>>& W, std::vector<std::vector<int>>& pi,
	std::vector<std::vector<int>>* __L , std::vector<std::vector<int>> *___pi
)
{
	const int n = L.size();
	//std::vector<std::vector<int>> L_prime;
	//L_prime.assign(n, std::vector<int>(n, INF));
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{

			for (int k = 1; k < n; k++)
			{
				if ((*__L)[i][j] > L[i][k] + W[k][j])
				{
					(*__L)[i][j] = (L[i][k] + W[k][j]);
					(*___pi)[i][j] = k;
				}
			}

		}
	}
	//return L_prime;
}

//nxn 1~n
void SLOW_ALL_PAIRS_SHORTEST_PATHS_pi(std::vector<std::vector<int>>& W, 
	std::vector<std::vector<int>> *__pi, std::vector<std::vector<int>> *__L)
{
	const int n = W.size() - 1;

	std::vector<std::vector<std::vector<int>>> L;
	std::vector<std::vector<std::vector<int>>> pi;
	L.resize(n + 1);
	pi.resize(n + 1);
	for (int i = 0; i < n + 1; i++)
	{
		pi[i].assign(n + 1, std::vector<int>(n + 1, INF));
		L[i].assign(n + 1, std::vector<int>(n + 1, INF));
	}
	L[1] = W;
	for (int m = 2; m < n; m++)
	{
		EXTEND_SHORTEST_PATHS_pi(L[m - 1], W, pi[m - 1], &L[m], &pi[m]);
	}
	__L->swap(L[n - 1]);
	__pi->swap(pi[n - 1]);
}

```


25.1-8
space requirement Theta(n^2)
```C++
std::vector<std::vector<int>>FASTER_ALL_PAIRS_SHORTEST_PATHS(std::vector<std::vector<int>>& W)
{
	const int n = W.size() - 1;

	std::vector<std::vector<int>> A, B = W;
	A.resize(n + 1);

	for (int j = 0; j <= n; j++)
	{
		A[j].resize(n + 1);
	}

	int m = 1;

	while (m < n - 1)
	{
		A = EXTEND_SHORTEST_PATHS(B, B);
		m = m * 2;
		if (m >= n - 1)
		{
			return A;
		}

		B = EXTEND_SHORTEST_PATHS(A, A);
		m = m * 2;
	}
	return  B;
}

```

25.1-9  25.1-8에 이어서.
no consider overflow;

```C++
std::vector<std::vector<int>>FASTER_ALL_PAIRS_SHORTEST_PATHS(std::vector<std::vector<int>>& W)
{
	const int n = W.size() - 1;

	std::vector<std::vector<int>> A = W, B = W, C = W ,D = W;
	A.resize(n + 1);
	for (int j = 0; j <= n; j++)
	{
		A[j].resize(n + 1);
	}

	int m = 1;

	while (1)
	{
		A = EXTEND_SHORTEST_PATHS(B, B);
		m = m * 2;
		if (m > n - 1)
		{
			C = A;
			break;
		}

		B = EXTEND_SHORTEST_PATHS(A, A);
		m = m * 2;
		if (m > n - 1)
		{
			C = B;
			break;
		}
	}
	D = EXTEND_SHORTEST_PATHS(C, C);
	
	print_matrix(C);
	print_matrix(D);


	bool chk_nwc = 0;
	for (int i = 1; i <= n && !chk_nwc; i++)
	{
		for (int j = 1; j <= n && !chk_nwc; j++)
		{
			if (C[i][j] != D[i][j])
			{
				chk_nwc = true;
			}
		}
	}

	if (chk_nwc)
		std::cout << "the input graph contains a negative-weight cycle" << std::endl;

	return C;
}
```





# 25.2 The Floyd-Warshall algorithm



n = n+1
```C++
std::vector<std::vector<int>>FLOYD_WARSHALL(std::vector<std::vector<int>>& W)
{
    const int n = W.size();
    std::vector<std::vector<std::vector<int>>> D;
    D.resize(n);
    for (int i = 0; i < n ; i++)
	{
		D[i].resize(n);
		for (int j = 0; j < n ; j++)
		{
			D[i][j].resize(n);
		}
	}
	D[0] = W;
    for(int k = 1 ; k< n  ;k++)
    {
        for(int i = 1 ; i < n ; i++)
        {
            for(int j = 1 ; j < n ;j++)
            {
                D[k][i][j] = (D[k-1][i][j] < D[k-1][i][k] + D[k-1][k][j] ?  D[k-1][i][j] : D[k-1][i][k] + D[k-1][k][j]);
            }
        }
    }
	return  D[n-1];
}
```



Graph is nxn matrix
```C++
std::vector<std::vector<int>>TRANSITIVE_CLOSURE(std::vector<std::vector<int>>& G)
{
	const int n = G.size() - 1;
	std::vector<std::vector<std::vector<int>>> T;

	T.resize(n + 1);
	for (int i = 0; i <= n; i++)
	{
		T[i].resize(n + 1);
		for (int j = 0; j <= n; j++)
		{
			T[i][j].resize(n + 1);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((i == j) || (G[i][j] != 0))
			{
				T[0][i][j] = 1;

			}
			else
			{
				T[0][i][j] = 0;
			}
		}
	}
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				T[k][i][j] = T[k - 1][i][j] | (T[k - 1][i][k] & T[k - 1][k][j]);
			}
		}
	}
	return  T[n];
}
```



25.2-3 25.2-4에 이어서.

공간복잡도 O(n^3)
```C++
std::vector<std::vector<int>>FLOYD_WARSHALL_apostrophe_pi(std::vector<std::vector<int>>& W, std::vector<std::vector<int>>& pi )
{
	const int n = W.size()-1;
	std::vector<std::vector<int>> D = W;
	std::vector<std::vector<std::vector<int>>> pi_prime;

	pi_prime.resize(n + 1);


	for (int k = 0; k <= n; k++)
	{
		pi_prime[k].resize(n + 1);
		for (int i = 0; i <= n; i++)
		{
			pi_prime[k][i].resize(n + 1);
			for (int j = 0; j <= n; j++)
			{
				if ((i == j) || (pi_prime[k][i][j] == INF))
				{
					pi_prime[k][i][j] = NIL;
				}
				else
				{
					pi_prime[k][i][j] = k;
				}
			}
		}
	}


	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((D[i][j] != INF)&&(i != j))
			{
				pi_prime[0][i][j] = i;
			}
		}
	}
	print_matrix(pi_prime[0]);

	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (D[i][j] > D[i][k] + D[k][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					pi_prime[k][i][j] = pi_prime[k - 1][k][j];
				}
				else
				{
					pi_prime[k][i][j] = pi_prime[k - 1][i][j];
				}
			}
		}
	}
	pi.swap(pi_prime[n]);
	return  D;
}

```

공간복잡도 O(n^2)
```C++
std::vector<std::vector<int>>FLOYD_WARSHALL_apostrophe_pi(std::vector<std::vector<int>>& W, std::vector<std::vector<int>>& pi )
{
	const int n = W.size()-1;
	std::vector<std::vector<int>> D = W;
	std::vector<std::vector<int>> pi_prime;

	pi_prime.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		pi_prime[i].resize(n + 1);
	}


	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((W[i][j] != INF) && (i != j))
			{
				pi_prime[i][j] = i;
			}
		}
	}
	print_matrix(pi_prime);

	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (D[i][j] > D[i][k] + D[k][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					pi_prime[i][j] = pi_prime[k][j];
				}
			}
		}
	}
	pi.swap(pi_prime);
	return  D;
}
```






25.2-4
```C++
std::vector<std::vector<int>>FLOYD_WARSHALL_apostrophe(std::vector<std::vector<int>>& W)
{
	const int n = W.size();
	std::vector<std::vector<int>> D;
	D.resize(n);
	for (int i = 0; i < n; i++)
	{
		D[i].resize(n);
	}
	D = W;
	for (int k = 1; k < n; k++)
	{
		for (int i = 1; i < n; i++)
		{
			for (int j = 1; j < n; j++)
			{
				D[i][j] = (D[i][j] < D[i][k] + D[k][j] ? D[i][j] : D[i][k] + D[k][j]);
			}
		}
	}
	return  D;
}
```

# 25.3 Johnson's algorithm for sparse graphs
인접리스트 Graph+W행렬과 인접리스트 가중치 그래프 각각으로 짜여져있다




O(VElgV)
```C++

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

```


pair(정점,가중치) 가중치 인접그래프,
```C++
void INITIALIZE_SINGLE_SOURCE(std::vector<std::vector<std::pair<int, int>>>& Graph,
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


bool BELLMAN_FORD(std::vector<std::vector<std::pair<int, int>>>& Graph, 
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph, Distance, s);
	const int n = Graph.size() - 1;

	for (std::size_t i = 1; i <= n; i++)// 간선 u v w = Graph[v][]
	{
		for (std::size_t u = 0; u <= n; u++)
		{
			const int sub_size = Graph[u].size();
			for (std::size_t j = 0; j < sub_size; j++)
			{
				int v = Graph[u][j].first;
				int w = Graph[u][j].second;
				BF_RELAX(u, v, w, Distance);
			}
		}
	}

	for (std::size_t u = 1; u <= n ; u++)
	{
		const int sub_size = Graph[u].size();
		for (std::size_t j = 0; j < sub_size; j++)
		{
			int v = Graph[u][j].first;
			if ((Distance[v] > Distance[u] + Graph[u][j].second) && Distance[u] != INF)
			{
				Distance[v] = -1;
				return false;
			}
		}
	}
	return true;
}


void DIJK_RELAX(int u, int v, int w, std::vector<int > &Distance, 
	std::priority_queue<std::pair<int, int>, 
	std::vector<std::pair<int, int>>, 
	std::greater<std::pair<int, int>> > &PQ)
{
	if ((Distance[u] != INF) && (Distance[v] > Distance[u] + w))
	{
		Distance[v] = Distance[u] + w;
		PQ.push(std::make_pair(Distance[v], v));
	}
}


void DIJKSTRA(std::vector<std::vector<std::pair<int, int>>>& Graph,
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph,Distance, s );
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > PQ; //정점의 거리, 정점
	for (int i = 1; i < Graph.size(); i++)
	{
		PQ.push(std::make_pair(Distance[i], i));
	}

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		PQ.pop();
		for (int v = 0; v < Graph[u].size(); v++)
		{
			DIJK_RELAX(u, Graph[u][v].first, Graph[u][v].second, Distance,PQ);
		}
	}
}


//graph pair(정점,가중치)
std::vector<std::vector<int>> JOHNSON(std::vector<std::vector<std::pair<int, int>>>& Graph
)
{//std::vector<std::vector<int>> &W
	std::vector<std::vector<int>> D;
	std::vector<std::vector<std::pair<int, int>>> G_apostrophe = Graph;
	int n = Graph.size()-1;
	
	D.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		G_apostrophe[0].push_back(std::make_pair(i, 0));
		D[i].resize(n + 1);
	}

	std::vector<int > Distance; // and h(x)
	Distance.resize(n + 1);

	if (BELLMAN_FORD(G_apostrophe, Distance,0) == false)
	{
		std::cout << "the input graph contains a negative-weight cycle" << std::endl;
	}
	else
	{
		std::vector<int> h = Distance;
		std::vector<std::vector<std::pair<int, int>>> Graph_het = Graph;
		
		std::vector < std::vector<int>> D_het;
		D_het.resize(n + 1);
		
		for (int i = 1; i <= n; i++)
		{
			D_het[i].resize(n + 1);
		}

		for (int i = 1; i <= n; i++)
		{
			const int sub_size = Graph_het[i].size();
			for (int j = 0; j < sub_size; j++)
			{
				Graph_het[i][j].second += (h[i] - h[Graph_het[i][j].first]);
			}
		}

		for (int u = 1; u <= n; u++)
		{
			DIJKSTRA(Graph_het, D_het[u], u );
			for (int v = 1; v <= n; v++)
			{
				D[u][v] = D_het[u][v] + h[v] - h[u];
			}
		}
	}

	return D;
}


