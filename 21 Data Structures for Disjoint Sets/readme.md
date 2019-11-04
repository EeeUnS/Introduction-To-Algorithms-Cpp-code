# 21.1 Disjoint-set operations


접근성을 위해서 실제 트리 대신 배열을 사용
```C++
UNION_FIND CONNECTED_COMPONENTS(std::vector< std::vector<int>> &G)
{
	const int n = G.size() -1;
	UNION_FIND set;
	for (int v = 1; v <= n; v++)
	{
		set.MAKE_SET(v);
	}
	for (int u = 1; u <= n; u++)
	{
		const int sub_n = G[u].size();
		for (int i = 0; i < sub_n; i++)
		{
            int v = G[u][i];
			if (set.FIND_SET(u) == set.FIND_SET(v))
			{
				set.UNION(u, v);
			}
		}
	}
	return set;
}

bool SAME_COMPONENT(UNION_FIND set ,int u, int v)
{
	if (set.FIND_SET(u) == set.FIND_SET(v))
	{
		return true;
	}
	else return false;
}
```



# 21.3 Disjoint-set forests

```C++
//with Disjoint-set forests
class UNION_FIND
{
public:
	UNION_FIND()
	{
		rank = new int(101);
		parent = new int(101);
		n = 101;
	}

	UNION_FIND(int n): n (n)
	{
		rank = new int(n);
		parent = new int(n);
	}

	void MAKE_SET(int x)
	{
		
		parent[x] = x;
		rank[x] = 0;
	}

	void UNION(int x, int y)
	{
		LINK(this->FIND_SET(x), this->FIND_SET(y));
	}

	int FIND_SET(int x)//path compression
	{
		if (x != parent[x])
		{
			parent[x] = this->FIND_SET[parent[x]];
		}
		return parent[x];
	}

	int capacity()
	{
		return n;
	}
private:
	int *rank;//Union by rank
	int *parent;
	int n;
	void LINK(int x, int y)
	{
		if (rank[x] > rank[y])
		{
			parent[y] = x;
		}
		else
		{
			parent[x] = y;
			if (rank[x] == rank[y])
			{
				rank[y] = rank[y] + 1;
			}
		}
	}
};

```