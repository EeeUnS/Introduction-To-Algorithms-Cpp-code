
#include<iostream>
#include<stack>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

constexpr size_t MAX_M = 32000;
//std::vector<std::vector<int>> Graph; // 인접 노드

int n, m; // V, E갯수
bool visit[MAX_M + 2] = { 0, };

stack<int> S; // 실제 정렬된값이 역순으로 들어가있다.
struct edge
{
	int a;
	int b;
	bool operator< (const edge& other) const
	{
		return a == other.a ? b < other.b : a < other.a;
	}
};

std::vector<edge> edges;
void DFS_TS(int x)
{
	visit[x] = true;

	edge a{ x, n + 1 };
	edge b{ x , 0 };
	auto x_end = std::lower_bound(edges.begin(), edges.end(), a);
	for (auto x_first = std::upper_bound(edges.begin(), edges.end(), b); x_first < x_end; x_first++)
	{
		int next = x_first->b;
		if (visit[next] != true)
		{
			DFS_TS(next);

		}
	}
	S.push(x);
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//int n, m;
	std::cin >> n >> m;
	edges.reserve(m + 1);
	
	for (int i = 0; i < m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		edges.push_back(edge{ u,v });
	}
	std::sort(edges.begin(), edges.end());

	for (std::size_t i = 1; i <= n; i++)
	{
		if (visit[i] != true)
		{
			DFS_TS(i);
		}
	}
	while (!S.empty())
	{
		std::cout << S.top() << ' ';
		S.pop();
	}
	return 0;
}