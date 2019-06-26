# Strongly connected component

문제:
https://www.acmicpc.net/problem/2150

## 코사라주 

실제 책에 소개되는 알고리즘

참고 :
https://jason9319.tistory.com/98

O(V+E)
```
#include<cstring> //memset
#include<iostream>
#include<stack>
#include<algorithm>
#include<vector>
using namespace std;

constexpr int MAX = 10000;

std::vector<std::vector<int>> Graph; //G 인접 노드
std::vector<std::vector<int>> TGraph; //G^T 인접 노드 
bool visit[MAX+2] = { 0, };

std::vector<std::vector<int>> SSC;   //각각의 ssc가 들어간다
```

```
int STRONGLY_CONNECTED_COMPONENTS(int v)
{
	std::stack<int> DFSf; // DFS pop 순서대로 들어가있다.

	for (int i = 1; i <= v; i++) {
		if (visit[i] != true)
			DFS(i,DFSf); //DFS순회 순서를 S에 저장한다.
	}
	int SSC_n = 0; // SSC의 갯수
	memset(visit, 0, MAX + 2);

	for (int i = 0; i < v; i++)
	{
		if (visit[DFSf.top()] != true)
		{
			SSC.resize(SSC_n + 1);
			TDFS(DFSf.top(), SSC_n);
			SSC_n++;
		}
		DFSf.pop();
	}

	for (int i = 0; i < SSC_n; i++)
	{
		sort(SSC[i].begin(), SSC[i].end());
	}

	std::sort(SSC.begin(), SSC.begin() + SSC_n,
		[](const std::vector<int> & a, const std::vector<int> & b) -> bool
		{
			return a[0] < b[0];
		});

	return SSC_n;
}
```
모든 ssc를 구해서 2차 벡터 SSC에 넣고 정렬할후 SSC의 갯수를 리턴한다
일반화 시킬때는 리턴값을 SSC자체로 하게한다.

```
void DFS(int x,std::stack<int> &DFSf)
{
	visit[x] = true;

	std::stack<int> sub_s;
	sub_s.push(x);
	//std::cout << sub_s.top() << ' '; // 순회출력

	while (!sub_s.empty())
	{
		int y = sub_s.top();
		for (std::size_t i = 0; i < Graph[y].size(); i++)
		{
			int next = Graph[y][i];
			if (visit[next] != true)
			{
				visit[next] = true;
				sub_s.push(next);
				//std::cout << sub_s.top() << ' '; // 순회출력
				i = -1;
				y = sub_s.top();
			}

		}
		DFSf.push(sub_s.top());//기존 DFS와 차이 STACK에 종료 순서 저장
		sub_s.pop();
		
	}
}
```
```

void DFS(int x, std::stack<int>& DFSf)
{
	visit[x] = true;
	//std::cout << x << ' '; // 순회출력

	for (std::size_t i = 0; i < Graph[x].size(); i++)
	{
		int next = Graph[x][i];
		if (visit[next] != true)
		{
			DFS(next,DFSf);
		}
	}
	DFSf.push(x);//기존 DFS와 차이 STACK에 종료 순서 저장
}
```
기존 DFS와는 DFSf에 각 종료 부분을 저장한다(위상정렬과같다.)

```
void TDFS(int x, int n)//G^T탐색
{
	visit[x] = true;

	std::stack<int> sub_s;
	sub_s.push(x);
	//std::cout << sub_s.top() << ' '; // 순회출력

	while (!sub_s.empty())
	{
		int y = sub_s.top();
		for (std::size_t i = 0; i < TGraph[y].size(); i++)
		{
			int next = TGraph[y][i];
			if (visit[next] != true)
			{
				visit[next] = true;
				sub_s.push(next);
				//std::cout << sub_s.top() << ' '; // 순회출력
				i = -1;
				y = sub_s.top();
			}

		}
		SSC[n].push_back(sub_s.top());
		sub_s.pop();
		
	}
}
```
```

void TDFS(int x,int n)
{
	visit[x] = true;
	//std::cout << x << ' '; // 순회출력
	std::size_t x_size = TGraph[x].size()
	for (std::size_t i = 0; i < x_size ; i++)
	{
		int next = TGraph[x][i];
		if (visit[next] != true)
		{
			TDFS(next, n);
		}
	}
	SSC[n].push_back(x);
}

```


```
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int v, e;
	std::cin >> v >> e;
	Graph.resize(v + 1);
	TGraph.resize(v + 1);
	for (int i = 0; i < e; i++)
	{
		int u, v;
		std::cin >> u >> v;
		Graph[u].push_back(v);
		TGraph[v].push_back(u); //역방향 간선추가
	}

	for (int i = 1; i <= v; i++)  // 리스트 넘버순 정렬
	{
		std::sort(Graph[i].begin(), Graph[i].end());
		std::sort(TGraph[i].begin(), TGraph[i].end());
	}



	int SSC_n = STRONGLY_CONNECTED_COMPONENTS(v);

	std::cout << SSC_n << '\n';
	for (int i = 0; i < SSC_n; i++)
	{
		int nn = SSC[i].size(); //각 ssc의 갯수
		for (int j = 0; j < nn; j++)
		{
			std::cout << SSC[i][j] << ' ';
		}
		std::cout << -1 << '\n';
	}

	return 0;
}
//앆
```


## 타잔

베낌 

참고 :
https://blog.naver.com/PostView.nhn?blogId=ndb796&logNo=221236952158&parentCategoryNo=&categoryNo=128&viewDate=&isShowPopularPosts=false&from=postView

https://kks227.blog.me/220802519976

```


#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
const int MAX = 10000;

// SN: SCC 개수, sn[i]: i가 속한 SCC의 번호
int V, E, cnt, dfsn[MAX], SN, sn[MAX];
vector<int> adj[MAX];
bool finished[MAX]; // SCC 분리가 끝난 정점만 true
stack<int> S;
vector<vector<int>> SCC;

// 자신의 결과값을 리턴하는 DFS 함수
int DFS(int curr) {
	dfsn[curr] = ++cnt; // dfsn 결정
	S.push(curr); // 스택에 자신을 push

	// 자신의 dfsn, 자식들의 결과나 dfsn 중 가장 작은 번호를 result에 저장
	int result = dfsn[curr];
	for (int next : adj[curr]) {
		// 아직 방문하지 않은 이웃
		if (dfsn[next] == 0) result = min(result, DFS(next));
		// 방문은 했으나 아직 SCC로 추출되지는 않은 이웃
		else if (!finished[next]) result = min(result, dfsn[next]);
	}

	// 자신, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
	if (result == dfsn[curr]) {
		vector<int> currSCC;
		// 스택에서 자신이 나올 때까지 pop
		while (1) {
			int t = S.top();
			S.pop();
			currSCC.push_back(t);
			finished[t] = true;
			sn[t] = SN;
			if (t == curr) break;
		}
		// 출력을 위해 원소 정렬
		sort(currSCC.begin(), currSCC.end());
		// SCC 추출
		SCC.push_back(currSCC);
		SN++;
	}
	return result;
}

int main() {
	// 그래프 정보 입력
	scanf("%d %d", &V, &E);
	for (int i = 0; i < E; i++) {
		int A, B;
		scanf("%d %d", &A, &B);
		adj[A - 1].push_back(B - 1);
	}

	// DFS를 하며 SCC 추출
	for (int i = 0; i < V; i++)
		if (dfsn[i] == 0) DFS(i);
	// 출력을 위해 SCC들을 정렬
	sort(SCC.begin(), SCC.end());

	// SCC 개수
	printf("%d\n", SN);
	// 각 SCC 출력
	for (auto& currSCC : SCC) {
		for (int curr : currSCC)
			printf("%d ", curr + 1);
		puts("-1");
	}
}

```