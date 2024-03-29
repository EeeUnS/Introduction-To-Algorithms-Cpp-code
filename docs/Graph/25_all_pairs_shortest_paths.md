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

```
typedef std::vector<std::vector<int>>  Matrix;
// must NxN
```

```C++
const int NIL = 0;
const int INF = 100000000;

void PRINT_ALL_PAIRS_SHORTEST_PATH(Matrix pi, int i, int j)
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
void print_matrix(Matrix& m)
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

$O(V^3)$

```C++
Matrix EXTEND_SHORTEST_PATHS(Matrix& L, Matrix& W)
{
	const int n = L.size();

	Matrix L_prime(n, std::vector<int>(n, INF));
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


총 $O(V^4)$
```C++
//nxn 1~n
MatrixSLOW_ALL_PAIRS_SHORTEST_PATHS(Matrix& W)
{
	const int n = W.size();

	std::vector<Matrix> L(n, Matrix(n, std::vector<int>(n)));
	L[1] = W;
	for (int m = 2; m < n; m++)
	{
		L[m] = EXTEND_SHORTEST_PATHS(L[m - 1], W);
	}
	return L[n-1];
}
```



총 $O(V^3 \log (V))$

```C++
MatrixFASTER_ALL_PAIRS_SHORTEST_PATHS(Matrix& W)
{
	const int n = W.size() - 1;

	int a = 1;
	while (a < n)
	{
		a = a * 2;
	}
	std::vector<Matrix> L(a+1, Matrix(n, std::vector<int>(n)));
	L[1] = W;

	int m = 1;
	while(m < n - 1)
	{
		L[2*m] = EXTEND_SHORTEST_PATHS(L[m], L[m]);
		m = m*2;
	}
	return  L[m];
}
```





//25.1-6
```C++
void set_pi(Matrix &W, std::vector<std::vector<int >> &L, Matrix& pi)
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
void EXTEND_SHORTEST_PATHS_pi(Matrix& L, 
	Matrix& W, Matrix& pi,
	Matrix* __L , Matrix *___pi
)
{
	const int n = L.size();
	//Matrix L_prime;
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
void SLOW_ALL_PAIRS_SHORTEST_PATHS_pi(const Matrix& W, 
	Matrix *out_pi, Matrix *out_L)
{
	const int n = W.size() - 1;

	std::vector<Matrix> L(n + 1, Matrix(n + 1, std::vector<int>(n + 1, INF)));
	std::vector<Matrix> pi(n + 1, Matrix(n + 1, std::vector<int>(n + 1, INF)));

	L[1] = W;
	for (int m = 2; m < n; m++)
	{
		EXTEND_SHORTEST_PATHS_pi(L[m - 1], W, pi[m - 1], &L[m], &pi[m]);
	}
	out_L->swap(L[n - 1]);
	out_pi->swap(pi[n - 1]);
}
```


25.1-8
space requirement Theta(n^2)
```C++
Matrix FASTER_ALL_PAIRS_SHORTEST_PATHS(Matrix& W)
{
	const int n = W.size() - 1;

	Matrix A(n + 1, std::vector<int>(n + 1))
	Matrix B(W);

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
Matrix FASTER_ALL_PAIRS_SHORTEST_PATHS(const Matrix& W)
{
	const int n = W.size() - 1;

	Matrix A = W, B = W, C = W ,D = W;

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
MatrixFLOYD_WARSHALL(const Matrix& W)
{
    const int n = W.size();
    std::vector<Matrix> D(n, Matrix(n, std::vector<int>(n)));
	D[0] = W;
    for(int k = 1 ; k <= n  ;k++)
    {
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ;j++)
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
Matrix TRANSITIVE_CLOSURE(Matrix& G)
{
	const int n = G.size();
    std::vector<Matrix> T(n, Matrix(n, std::vector<int>(n)));

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
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
	for (int k = 1; k < n; k++)
	{
		for (int i = 1; i < n; i++)
		{
			for (int j = 1; j < n; j++)
			{
				T[k][i][j] = T[k - 1][i][j] | (T[k - 1][i][k] & T[k - 1][k][j]);
			}
		}
	}
	return  T[n - 1];
}
```



25.2-3 25.2-4에 이어서.

공간복잡도 $O(n^3)$
```C++
Matrix FLOYD_WARSHALL_apostrophe_pi(cosnt Matrix &W, Matrix & out_pi )
{
	const int n = W.size() - 1;
	Matrix D(W);
    std::vector<Matrix> pi_prime(n + 1, Matrix(n + 1, std::vector<int>(n + 1)));

	for (int k = 0; k <= n; k++)
	{
		for (int i = 0; i <= n; i++)
		{
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
	out_pi.swap(pi_prime[n]);
	return D;
}
```

공간복잡도 $O(n^2)$
```C++
Matrix FLOYD_WARSHALL_apostrophe_pi(const Matrix& W, Matrix& out_pi )
{
	const int n = W.size()-1;
	Matrix D = W;
	Matrix pi_prime(n + 1, std::vector<int>(n + 1));

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
	out_pi.swap(pi_prime);
	return  D;
}
```


25.2-4

```c++
Matrix FLOYD_WARSHALL_apostrophe(const Matrix& W)
{
	const int n = W.size();
	Matrix D(W);

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

```c++
void INITIALIZE_SINGLE_SOURCE(const Graph& Graph,
	std::vector<int>& Distance, int s)
{
	std::fill(Distance.begin(), Distance.begin() + Graph.size(), INF);
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
bool BELLMAN_FORD(const Graph& Graph, 
	const Matrix& W,
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph, Distance, s);
	const std::size_t n = Graph.size() - 1;

	for (std::size_t i = 1; i <= n; i++)// 간선 u v w = Graph[v][]
	{
		for (std::size_t u = 0; u <= n; u++)
		{
			for (int v : Graph[u])
			{
				int w = W[u][v];
				BF_RELAX(u, v, w, Distance);
			}
		}
	}

	for (std::size_t u = 1; u <= n ; u++)
	{
		for (int v : Graph[u])
		{
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
	std::priority_queue<
		std::pair<int, int>,
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

void DIJKSTRA(const Graph& Graph,
	Matrix& W,
	std::vector<int> &Distance, int s)
{
	INITIALIZE_SINGLE_SOURCE(Graph,Distance, s);
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > PQ; //정점의 거리, 정점
	for (std::size_t i = 1; i < Graph.size(); i++)
	{
		PQ.push(std::make_pair(Distance[i], i));
	}

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		PQ.pop();
		for (int v : Graph[u])
		{
			DIJK_RELAX(u, v, W[u][v], Distance,PQ);
		}
	}
}


Matrix JOHNSON(const Matrix& Graph,
	Matrix& W
)
{//
	Matrix D(n + 1, std::vector<int>(n + 1));
	Matrix G_apostrophe(Graph);
	const std::size_t n = Graph.size() - 1;
	
	for (std::size_t i = 1; i <= n; i++)
	{
		W[0].resize(n + 1);
		G_apostrophe[0].push_back(i);
	}
	
	std::vector<int > Distance(n + 1); // and h(x)

	if (BELLMAN_FORD(G_apostrophe,W ,Distance,0) == false)
	{
		std::cout << "the input graph contains a negative-weight cycle" << std::endl;
	}
	else
	{
		
		std::vector<int> h = Distance;
		Matrix W_het(W);		
		Matrix D_het(n + 1 std::vector<int>(n + 1));

		for (std::size_t u = 1; u <= n; u++)
		{
			for(int v : Graph[u])
			{
				W_het[u][v] += (h[u] - h[v]);
			}
		}
		for (std::size_t u = 1; u <= n; u++)
		{
			DIJKSTRA(Graph, W_het, D_het[u], u );
			
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


void DIJK_RELAX(int u, int v, int w, std::vector<int> &Distance, 
	std::priority_queue<
		std::pair<int, int>, 
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
Matrix JOHNSON(std::vector<std::vector<std::pair<int, int>>>& Graph
)
{//Matrix &W
	Matrix D(n + 1, std::vector<int>(n + 1));
	std::vector<std::vector<std::pair<int, int>>> G_apostrophe(Graph);
	const int n = Graph.size()-1;
	
	for (int i = 1; i <= n; i++)
	{
		G_apostrophe[0].push_back(std::make_pair(i, 0));
	}

	std::vector<int > Distance(n + 1); // and h(x)

	if (BELLMAN_FORD(G_apostrophe, Distance,0) == false)
	{
		std::cout << "the input graph contains a negative-weight cycle" << std::endl;
	}
	else
	{
		std::vector<int> h(Distance);
		std::vector<std::vector<std::pair<int, int>>> Graph_het = Graph;
		
		Matrix D_het(n + 1, std::vector<int>(n + 1));

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
```