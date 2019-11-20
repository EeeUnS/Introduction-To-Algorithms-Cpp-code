//미완
#include<iostream>
#include<vector>
#include<thread>



void sub_sub_procedure(int i, int j, std::vector< std::vector<int>>& C, std::vector< std::vector<int>>& A, std::vector< std::vector<int>>& B)
{
	int n = A[0].size();
	//C[i][j] = 0;
	for (int k = 0; k < n; k++)
	{
		C[i][j] = C[i][j] + A[i][k] * B[k][j];
	}
}

void sub_procedure(int i, std::vector< std::vector<int>>& C,
	std::vector< std::vector<int>>& A, std::vector< std::vector<int>>& B)
{
	int n = A[0].size();
	std::vector<std::thread> _thread;
	for (int j = 0; j < n; j++)
	{
		_thread.push_back(std::thread(sub_sub_procedure, i, j, std::ref(C), std::ref(A), std::ref(B)));
	}
	for (int i = 0; i < n; i++)
	{
		_thread[i].join();
	}
}



미작동
//divide and conquer
void P_MATRIX_MULTIPLY_RECURSIVE(std::vector< std::vector<int>>& C,
	std::vector< std::vector<int>>& A,
	std::vector< std::vector<int>>& B)
{
	const int n = A.size();
	if (n == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
		return;
	}
		 /*
		 else let T be a new nxn matrix
 partition A, B, C, and T into n=2 	 n=2 submatrices
A11;A12;A21;A22; B11;B12;B21;B22; C11;C12;C21;C22;
and T11; T12; T21; T22; respectively
*/
		
	std::vector<std::thread> _thread;
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C), std::ref(A), std::ref(B)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C), std::ref(A), std::ref(B)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C), std::ref(A), std::ref(B)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C), std::ref(A), std::ref(B)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C), std::ref(A), std::ref(B)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C), std::ref(A), std::ref(B)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C), std::ref(A), std::ref(B)));
	P_MATRIX_MULTIPLY_RECURSIVE();
	for (int i = 0; i < 7; i++)
	{
		_thread[i].join();
	}
	//parallel for i = 1 to n
}


int main()
{
	std::vector< std::vector<int>> A;
	A.assign(4, std::vector<int>(4, 2));
	std::vector< std::vector<int>> B;
	B.assign(4, std::vector<int>(4, 1));
	std::vector< std::vector<int>> C;
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


