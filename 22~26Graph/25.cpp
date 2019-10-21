
//25.1-7


//25.1-8 NOT TEST




//25.1-9  25.1-8에 이어서.
no consider overflow;



n = n+1
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




Graph is nxn matrix
std::vector<std::vector<int>>TRANSITIVE_CLOSURE(std::vector<std::vector<int>>& Graph)
{
    const int n = Graph.size();
    std::vector<std::vector<std::vector<bool>>> T;
	
    T.resize(n+1);
    for (int i = 0; i <= n ; i++)
	{
		T[i].resize(n);
		for (int j = 0; j <= n ; j++)
		{
			T[i][j].resize(n + 1);
		}
	}

    for(int i = 1 ; i < n ; i++)
    {
        for(int j = 1 ; j < n ;j++)
        {
            if(i == j | G[i][j] != 0)
            {
                T[0][i][j] =1;
                
            }
            else
            {
                T[0][i][j] =0;
            }
        }
    }
    for(int k = 1 ; k< n  ;k++)
    {
        for(int i = 1 ; i < n ; i++)
        {
            for(int j = 1 ; j < n ;j++)
            {
                T[k][i][j] = T[k-1][i][j] | (T[k-1][i][k] & T[k-1][k][j]);
            }
        }
    }
	return  T[n-1];
}

//25.2-4
std::vector<std::vector<int>>FLOYD_WARSHALL_apostrophe(std::vector<std::vector<int>>& W)
{
    const int n = W.size();
    std::vector<std::vector<int>> D = W;
    for(int k = 1 ; k< n  ;k++)
    {
        for(int i = 1 ; i < n ; i++)
        {
            for(int j = 1 ; j < n ;j++)
            {
                D[i][j] = (D[i][j] < D[i][k] + D[k][j] ?  D[i][j] : D[i][k] + D[k][j]);
            }
        }
    }
	return  D;
}


//25.2-3 25.2-4에 이어서.
std::vector<std::vector<int>>FLOYD_WARSHALL_apostrophe_pi(std::vector<std::vector<int>>& W,std::vector<std::vector<int>>& pi,)
{
    const int n = W.size();
    std::vector<std::vector<int>> D = W;
    std::vector<std::vector<std::vector<bool>>> pi_prime;
	
    pi_prime.resize(n+1);
   
	
    for(int k = 1 ; k< n  ;k++)
    {
		pi_prime[k].resize(n);
        for(int i = 1 ; i < n ; i++)
        {
			pi_prime[k][i].resize(n + 1);
            for(int j = 1 ; j < n ;j++)
            {
                if(i == j | pi[k][i][j] == INF)
                {
                    pi[k][i][j] = NIL
                }
                else
                {
                    pi[k][i][j] = k
                }
            }
        }
    }

    for(int k = 1 ; k< n  ;k++)
    {
        for(int i = 1 ; i < n ; i++)
        {
            for(int j = 1 ; j < n ;j++)
            {
                if(D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j]);
                    pi[k][i][j] = pi[k-1][k][j]);
                }
            }
        }
    }
	return  D;
}

























////////////////////////////////////////////////////////////////////////////////
//코드전체 미완성
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


bool BELLMAN_FORD(std::vector<std::vector<std::pair<int, int>>> &Graph,  int s)
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


std::vector<std::vector<int>> JOHNSON(std::vector<std::vector<std::pair<int, int>>> &Graph)
{
    std::vector<std::vector<int>> D;
    std::vector<std::vector<std::pair<int, int>>> G_apostrophe = Graph;
    int n= Graph.size();
    for(int i = 1 ; i < n ; i++)
    {
        G_apostrophe[0].push_back(std::pair<int,int>(i,0));
    }


    if(BELLMAN_FORD(G_apostrophe,0,Distance) == false)
    {
        std::cout << "the input graph contains a negative-weight cycle" <<std::endl;
    }
    else 
    {
        //int h = Distance;

        int D_het[][] = 
        for(int i = 0 ; i < n ; i++)
        {

        }

        for(int i = 0 ; i < n ; i++)
        {
            W_het[u][v] = W[u][v] + h[u] - h[v];
        }

        for(int u = 0 ; u < n ; u++)
        {
            DUKSTRA(Graph,W_het, u,d_het);
            
            for(int v = 0 ; v < n ; v++)
            {
                D[u][v] = d_het[u][v] + h[v] - h[u];
            }
        }
    }

    return D;
}