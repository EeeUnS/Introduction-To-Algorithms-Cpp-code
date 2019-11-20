// https://www.acmicpc.net/problem/13913


#include<queue>
#include<iostream>
#include<stack>
using namespace std;
queue<int> Q;
const int MAX = 100000;
stack<int> S;

int predecessor_subgraph[100001];//직전원소 그래프 v.pi
void PRINT_PATH(int s, int v)
{
	if (v == s)
		;
	/*else if (predecessor_subgraph[v] == 0) //최단경로 v가 보장되어있고 start가 0일때는 해당 주석을 뗀다
	{
		return;
	}*/
	else
		PRINT_PATH(s, predecessor_subgraph[v]);
	cout << v << ' ';
}

int BFS(int stealer, int police)
{

	bool visit[MAX + 1] = { 0 };

	Q.push(stealer);
	int _time = -1;//단계별 police 추가 거리
	while (!Q.empty())
	{
		unsigned int number = Q.size();
		//police += _time += 1; //
		_time += 1;
		if (police < 0 || police > MAX)
		{
			return -1;
		}

		for (unsigned int i = 0; i < number; i++)
		{
			int _stealer = Q.front();
			if (_stealer == police)
			{
				return _time;
			}
			Q.pop();

			if (0 <= (_stealer + 1) && (_stealer + 1) <= MAX && visit[_stealer + 1] != true)
			{
				visit[_stealer + 1] = true;
				Q.push(_stealer + 1);
			}
			if ((0 <= (_stealer - 1) && (_stealer - 1) <= MAX) && visit[(_stealer - 1)] != true)
			{
				visit[(_stealer - 1)] = true;
				predecessor_subgraph[(_stealer - 1)] = _stealer;
				Q.push(_stealer - 1);
			}
			if (0 <= (_stealer * 2) && (_stealer * 2) <= MAX && visit[_stealer * 2] != true)
			{
				visit[_stealer * 2] = true;
				predecessor_subgraph[_stealer * 2] = _stealer;
				Q.push(_stealer * 2);
			}
		}
	}
	return -1;
}

int main()
{
	int x, y;
	cin >> x >> y;
	cout << BFS(x, y) << '\n';
	PRINT_PATH(x, y);


	return 0;
}