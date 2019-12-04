// #include <cstdio>
// #include <vector>
// #include <stack>
// #include <algorithm>
// using namespace std;
// const int MAX = 10000;

// // SN: SCC 개수, sn[i]: i가 속한 SCC의 번호
// int V, E, cnt, dfsn[MAX], SN, sn[MAX];
// vector<int> adj[MAX];
// bool finished[MAX]; // SCC 분리가 끝난 정점만 true
// stack<int> S;
// vector<vector<int>> SCC;

// // 자신의 결과값을 리턴하는 DFS 함수
// int DFS(int curr) {
// 	dfsn[curr] = ++cnt; // dfsn 결정
// 	S.push(curr); // 스택에 자신을 push

// 	// 자신의 dfsn, 자식들의 결과나 dfsn 중 가장 작은 번호를 result에 저장
// 	int result = dfsn[curr];
// 	for (int next : adj[curr]) {
// 		// 아직 방문하지 않은 이웃
// 		if (dfsn[next] == 0) result = min(result, DFS(next));
// 		// 방문은 했으나 아직 SCC로 추출되지는 않은 이웃
// 		else if (!finished[next]) result = min(result, dfsn[next]);
// 	}

// 	// 자신, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
// 	if (result == dfsn[curr]) {
// 		vector<int> currSCC;
// 		// 스택에서 자신이 나올 때까지 pop
// 		while (1) {
// 			int t = S.top();
// 			S.pop();
// 			currSCC.push_back(t);
// 			finished[t] = true;
// 			sn[t] = SN;
// 			if (t == curr) break;
// 		}
// 		// 출력을 위해 원소 정렬
// 		sort(currSCC.begin(), currSCC.end());
// 		// SCC 추출
// 		SCC.push_back(currSCC);
// 		SN++;
// 	}
// 	return result;
// }

// int main() {
// 	// 그래프 정보 입력
// 	scanf("%d %d", &V, &E);
// 	for (int i = 0; i < E; i++) {
// 		int A, B;
// 		scanf("%d %d", &A, &B);
// 		adj[A - 1].push_back(B - 1);
// 	}

// 	// DFS를 하며 SCC 추출
// 	for (int i = 0; i < V; i++)
// 		if (dfsn[i] == 0) DFS(i);
// 	// 출력을 위해 SCC들을 정렬
// 	sort(SCC.begin(), SCC.end());

// 	// SCC 개수
// 	printf("%d\n", SN);
// 	// 각 SCC 출력
// 	for (auto& currSCC : SCC) {
// 		for (int curr : currSCC)
// 			printf("%d ", curr + 1);
// 		puts("-1");
// 	}
// }


//https://jason9319.tistory.com/98
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
#define MAX_V 10000
using namespace std;
int v, e, discover[MAX_V + 1], x, y, r, c, scc[MAX_V + 1];
stack<int> st;
vector<vector<int>> vt;
vector<vector<int>> res;
bool cmp(vector<int> a, vector<int> b) {
    return a[0] < b[0];
}
int dfs(int here) {
    discover[here] = c++;
    int ret = discover[here];
    st.push(here);
    for (int there : vt[here]) {
        if (discover[there] == -1)
            ret = min(ret, dfs(there));
        else if (scc[there] == -1)
            ret = min(ret, discover[there]);
    }
    if (ret == discover[here]) {
        vector<int> tmp;
        while (1) {
            int t = st.top();
            st.pop();
            scc[t] = r;
            tmp.push_back(t);
            if (t == here)break;
        }
        sort(tmp.begin(), tmp.end());
        res.push_back(tmp);
        r++;
    }
    return ret;
}
int main() {
    scanf("%d%d", &v, &e);
    vt.resize(v + 1);
    for (int i = 0; i < e; i++) {
        scanf("%d%d", &x, &y);
        vt[x].push_back(y);
    }
    memset(discover, -1, sizeof(discover));
    memset(scc, -1, sizeof(scc));
    for (int i = 1; i <= v; i++) {
        if (discover[i] == -1)
            dfs(i);
    }
    sort(res.begin(), res.end(), cmp);
    printf("%d\n", r);
    for (int i = 0; i < r; i++) {
        for (auto h : res[i]) 
            printf("%d ", h);
        printf("-1\n");
    }
    return 0;
}
