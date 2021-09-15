# 26 Maximum Flow


# 26.1 Flow networks

# 26.2 The Ford-Fulkerson method

Edmonds Karp
$O(VE^2)$
```
constexpr long long INF = 0x7FFF'FFFF;// 'FFFF'FFFF;
constexpr int MAX_V = 1002;

vector<int> adj[MAX_V];
int c[MAX_V][MAX_V];
int f[MAX_V][MAX_V];
int p[MAX_V];

bool findAugmentingPathBFS(const int S, const int T)
{
	fill(p, p + MAX_V, -1);
	queue<int> Q;
	Q.push(S);
	while (!Q.empty() && p[T] == -1)
	{
		int curr = Q.front();
		Q.pop();
		if (curr == T)
			break;

		for (int next : adj[curr])
		{
			if (c[curr][next] - f[curr][next] > 0 && p[next] == -1)
			{
				Q.push(next);
				p[next] = curr;
			}
		}
	}

	return (p[T] != -1);
}

int Edmonds_Karp(const int S, const int T)
{
	int maxFlow = 0;
	while (findAugmentingPathBFS(S, T))
	{
		int c_f_p = INF;
		for (int i = T; i != S; i = p[i])
			c_f_p = min(c_f_p, c[p[i]][i] - f[p[i]][i]);

		for (int i = T; i != S; i = p[i]) {
			f[p[i]][i] += c_f_p;
			f[i][p[i]] -= c_f_p;
		}
		maxFlow += c_f_p;
	}
	return maxFlow;
}
```

# 26.3 Maximum bipartite matching

# 26.4 Push-relabel algorithms

# 26.5 The relabel-to-front algorithm