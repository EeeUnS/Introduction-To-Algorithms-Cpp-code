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
기존 DFS와는 DFSf에 각 종료 부분을 저장한다

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

참고 :
https://blog.naver.com/PostView.nhn?blogId=ndb796&logNo=221236952158&parentCategoryNo=&categoryNo=128&viewDate=&isShowPopularPosts=false&from=postView


