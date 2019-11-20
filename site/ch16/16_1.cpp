#include <iostream>
#include<algorithm>
#include<vector>
//the maximum-subarray

void RECURSIVE_ACTIVITY_SELECTOR(int s[], int f[], int k, int n, std::vector<int> &a)
{
	int m = k + 1;
	while (m < n && s[m] < f[k])
	{
		m = m + 1;
	}
	if (m < n)
	{
		a.push_back(m);
		RECURSIVE_ACTIVITY_SELECTOR(s,f,m,n,a);
	}
	return;
}


std::vector<int> GREEDY_ACTIVITY_SELECTOR(int s[], int f[],int n)
{
	std::vector<int> A;
	A.push_back(1);
	int k = 1;
	for (int m = 2; m <= n; m++)
	{
		if (s[m] >= f[k])
		{
			A.push_back(m);
			k = m;
		}
	}
	return A;
}

int s[] = {0, 1, 3, 0, 5, 3, 5 ,6 ,8, 8, 2, 12 };
int f[] = {0, 4, 5, 6, 7 ,9 ,9, 10, 11, 12, 14, 16 };
int main()
{
	int n = sizeof(s) / sizeof(int);
	std::vector<int> a = GREEDY_ACTIVITY_SELECTOR(s,f,n);


	//RECURSIVE_ACTIVITY_SELECTOR(s, f, 0, n, a);
	for (int i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << ' ';
	}



	return 0;
}
