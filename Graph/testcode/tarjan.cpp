#include <vector>
#include <stack>
#include <algorithm>
#include<iostream>
using namespace std;
//const int MAX = 10000;

// 자신의 결과값을 리턴하는 DFS 함수
int DFS(int curr, vector<vector<int>>& SCC,
	vector<bool>& finished, stack<int>& S, vector<vector<int>>& adj, vector<int>& dfsn, int &cnt)
{
	dfsn[curr] = ++cnt; // dfsn 결정
	S.push(curr);       // 스택에 자신을 push

	// 자신의 dfsn, 자식들의 결과나 dfsn 중 가장 작은 번호를 result에 저장
	int result = dfsn[curr];
	for (int next : adj[curr])
	{
		// 아직 방문하지 않은 이웃
		if (dfsn[next] == 0)
		{
			result = min(result, DFS(next, SCC, finished, S, adj, dfsn, cnt));
		}
		// 방문은 했으나 아직 SCC로 추출되지는 않은 이웃
		else if (!finished[next])
		{
			result = min(result, dfsn[next]);
		}
	}

	// 자신, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
	if (result == dfsn[curr])
	{
		vector<int> currSCC;
		// 스택에서 자신이 나올 때까지 pop
		while (1)
		{
			int t = S.top();
			S.pop();
			currSCC.push_back(t);
			finished[t] = true;
			//sn[t] = SN;
			if (t == curr)
			{
				break;
			}
		}
		// 출력을 위해 원소 정렬
		sort(currSCC.begin(), currSCC.end());
		// SCC 추출
		SCC.push_back(currSCC);
	}
	return result;
}

vector<vector<int>> TARJAN_ALG(vector<vector<int>>& adj)
{
	const int V = adj.size();

	vector<int>  dfsn;
	vector<vector<int>> SCC;
	stack<int> S;
	vector<bool> finished; // SCC 분리가 끝난 정점만 true
    int cnt = 0 ;

	dfsn.resize(V + 1);
	finished.resize(V + 1);
	for (int i = 0; i < V - 1 ; i++)
	{
		if (dfsn[i] == 0)
		{
			DFS(i, SCC, finished, S, adj, dfsn,cnt);
		}
	}
	return SCC;
}

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(NULL);
	// 그래프 정보 입력
	int V, E;

	std::cin >> V >> E;
	

	vector<vector<int>> adj;
	adj.resize(V + 1);

	for (int i = 0; i < E; i++)
	{
		int A, B;
		std::cin >> A >> B;
		//scanf("%d %d", &A, &B);
		adj[A - 1].push_back(B - 1);
	}
	vector<vector<int>> SCC = TARJAN_ALG(adj);
	// 출력을 위해 SCC들을 정렬
	sort(SCC.begin(), SCC.end());

	// SCC 개수
	cout << SCC.size() << '\n';
	// 각 SCC 출력
	for (auto& currSCC : SCC)
	{
		for (int curr : currSCC)
			cout << curr + 1 << ' ';
		cout << -1 << '\n';
	}
	return 0;
}
