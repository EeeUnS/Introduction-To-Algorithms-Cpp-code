
#include<iostream>
#include<vector>
#include<thread>



void sub_sub_procedure(int i, int j, std::vector< std::vector<int>>& C,	std::vector< std::vector<int>>& A, std::vector< std::vector<int>>& B)
{
	int n = A[0].size();
	//C[i][j] = 0;
	for (int k = 0; k < n; k++)
	{
		C[i][j] = C[i][j] + A[i][k] * B[k][j];
	}
}

void sub_procedure(int i, std::vector< std::vector<int>> &C, 
	std::vector< std::vector<int>>& A, std::vector< std::vector<int>>& B)
{
	int n = A[0].size();
	std::vector<std::thread> _thread;
    //parallel for j = 1 to n
	for (int j = 0; j < n; j++)
	{
		_thread.push_back(std::thread(sub_sub_procedure, i, j, std::ref(C), std::ref(A), std::ref(B)));
	}
	for (int i = 0; i < n; i++)
	{
		_thread[i].join();
	}
}

std::vector< std::vector<int>> P_SQUARE_MATRIX_MULTIPLY(std::vector< std::vector<int>> &A,std::vector< std::vector<int>> &B)
{
	int n = A[0].size();
	std::vector< std::vector<int>> C;
	C.assign(n, std::vector<int>(n, 0));
	std::vector<std::thread> _thread;
    //parallel for i = 1 to n
	for (int i = 0; i < n; i++)
	{
		_thread.push_back(std::thread(sub_procedure,i,std::ref(C), std::ref(A), std::ref(B)));
	}
	for (int i = 0; i < n; i++)
	{
		_thread[i].join();
	}
	return C;
}



int main()
{
	std::vector< std::vector<int>> A;
	A.assign(4, std::vector<int>(4, 2));
	std::vector< std::vector<int>> B;
	B.assign(4, std::vector<int>(4, 1));
	std::vector< std::vector<int>> C = P_SQUARE_MATRIX_MULTIPLY(A, B);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << C[i][j] << ' ';
		}
		std::cout << '\n';
	}
	return 0;
}


