#include <iostream>
#include<vector>
#include<stack>
#include<thread>

void ADD_MATRIX(std::vector< std::vector<int>>& C,
	std::vector< std::vector<int>>& A,
	std::vector< std::vector<int>>& B)
{
	const std::size_t n = C.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void SUB_MATRIX(std::vector< std::vector<int>>& C,
	std::vector< std::vector<int>>& A,
	std::vector< std::vector<int>>& B)
{
	const std::size_t n = C.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

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
	int m = n / 2;
	std::vector< std::vector<int>> A11(m, std::vector<int>(m, 0)),
		A12(m, std::vector<int>(m, 0)),
		A21(m, std::vector<int>(m, 0)),
		A22(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> B11(m, std::vector<int>(m, 0)),
		B12(m, std::vector<int>(m, 0)),
		B21(m, std::vector<int>(m, 0)),
		B22(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> C11(m, std::vector<int>(m, 0)),
		C12(m, std::vector<int>(m, 0)),
		C21(m, std::vector<int>(m, 0)),
		C22(m, std::vector<int>(m, 0));
	std::vector< std::vector<int>> T11(m, std::vector<int>(m, 0)),
		T12(m, std::vector<int>(m, 0)),
		T21(m, std::vector<int>(m, 0)),
		T22(m, std::vector<int>(m, 0));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + m];
			A21[i][j] = A[i + m][j];
			A22[i][j] = A[i + m][j + m];

			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + m];
			B21[i][j] = B[i + m][j];
			B22[i][j] = B[i + m][j + m];
		}
	}



	std::vector<std::thread> _thread;
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C11), std::ref(A11), std::ref(B11)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C12), std::ref(A11), std::ref(B12)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C21), std::ref(A21), std::ref(B11)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(C22), std::ref(A21), std::ref(B12)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(T11), std::ref(A12), std::ref(B21)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(T12), std::ref(A12), std::ref(B22)));
	_thread.push_back(std::thread(P_MATRIX_MULTIPLY_RECURSIVE, std::ref(T21), std::ref(A22), std::ref(B21)));
	P_MATRIX_MULTIPLY_RECURSIVE(T22,A22,B22);
	for (int i = 0; i < 7; i++)
	{
		_thread[i].join();
	}



	//parallel for i = 1 to n
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			C[i][j] = C11[i][j] + T11[i][j];
			C[i][j + m] = C12[i][j] + T12[i][j];
			C[i+m][j] = C21[i][j] + T21[i][j];
			C[i+m][j+m] = C22[i][j] + T22[i][j];
		}
	}


 }
// void P_MATRIX_MULTIPLY_RECURSIVE_SUB_LOOP(int i, int i_ap)
// {
// 	if (i == i_ap)
// 	{
		
// 	}
// 	else
// 	{
// 		int mid = (i + i_ap) / 2;
// 		std::thread __thread = std::thread(P_MATRIX_MULTIPLY_RECURSIVE_MAIN_LOOP, i, mid);
// 		P_MATRIX_MULTIPLY_RECURSIVE_MAIN_LOOP(mid + 1, i_ap);
// 		__thread.join();
// 	}
// }



// void P_MATRIX_MULTIPLY_RECURSIVE_MAIN_LOOP(int i, int i_ap)
// {
// 	if (i == i_ap)
// 	{
// 		P_MATRIX_MULTIPLY_RECURSIVE_SUB_LOOP();
// 	}
// 	else
// 	{
// 		int mid = (i + i_ap) / 2;
// 		std::thread __thread = std::thread(P_MATRIX_MULTIPLY_RECURSIVE_MAIN_LOOP ,i, mid);
// 		P_MATRIX_MULTIPLY_RECURSIVE_MAIN_LOOP(mid+1,i_ap);
// 		__thread.join();
// 	}
// }



int main()
{
	std::vector<std::vector<int>> A =
	{
		{1,2},
		{3,4}
	};

	std::vector<std::vector<int>> B =
	{
		{5,6},
		{7,8}
	};
	std::vector<std::vector<int>>  C(2, std::vector<int>(2, 0));
	P_MATRIX_MULTIPLY_RECURSIVE(C,A,B);

	const int n = C.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << C[i][j] << ' ';
		}
	}


	return 0;
}
