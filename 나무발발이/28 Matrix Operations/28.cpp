#include<vector>
#include<iostream>
#include <assert.h> 

typedef std::vector<std::vector<double>>  matrix;
typedef std::pair<std::vector< std::vector<double>>, std::vector< std::vector<double>>>  Set;

template<typename T, typename D>
std::vector<std::vector<D>> SQUARE_MATRIX_MULTIPLY(std::vector<std::vector<T>>& A, std::vector<std::vector<D>>& B)
{
	const int n = A.size();
	std::vector<std::vector<D>> C;
	C.assign(n, std::vector<D>(n, 0));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}

		}
	}
	return C;
}


//n^2
std::vector<double>LUP_SOLVE(matrix& L, matrix& U, std::vector<int> &PI,
	std::vector<double>& b)
{
	const int n = L.size();
	std::vector<double> x(n, 0);
	std::vector<double> y(n,0);

	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int j = 0; j <= i - 1; j++)
		{
			sum += L[i][j] * y[j];
		}
		y[i] = b[PI[i]] - sum;
	}

	for (int i = n-1; i >= 0; i--)
	{
		double sum = 0;
		for (int j = i + 1  ; j < n; j++)
		{
			sum += U[i][j] * x[j];
		}
		x[i] = (y[i] - sum) / U[i][i];
	}
	return x;
}


//A is an n 	 n nonsingular matrix and P is absent (or, equivalently, P = In).
// n^3
Set LU_DECOMPOSITION(matrix& A)
{
	const int n = A.size();
	matrix L(n, std::vector<double>(n, 0));
	matrix U(n, std::vector<double>(n, 0));
	for (int i = 0; i < n; i++)
	{
		L[i][i] = 1;
	}
	for (int k = 0 ; k < n; k++)
	{
		U[k][k] = A[k][k];
		for (int i = k + 1; i < n; i++)
		{
			L[i][k] = A[i][k] / U[k][k];
			U[k][i] = A[k][i];
		}

		for (int i = k + 1; i < n; i++)
		{
			for (int j = k + 1; j < n; j++)
			{
				A[i][j] = A[i][j] - L[i][k] * U[k][j];
			}
		}
	}
	return std::make_pair(L, U);
}

//미
std::vector<int> LUP_DECOMPOSITION(matrix& A)
{
	const int n = A.size();
	std::vector<int> pi(n , 0);
	for (int i = 0; i < n; i++)
	{
		pi[i] = i;
	}

	for (int k = 0; k < n - 1; k++)
	{
		int k_prime = -1;
		double p = 0;
		for (int i = k; i < n; i++)
		{
			if (A[i][k] > p)
			{
				p = A[i][k];
				k_prime = i;
			}
		}
		assert(p != 0, " ");
		if (p == 0)
		{
			
			std::cout << "singular matrix" << std::endl;
		}
		//swap
		
		int sub = pi[k];
		pi[k] = pi[k_prime];
		pi[k_prime] = sub;

		for (int i = 0; i < n; i++)
		{
			double sub = A[k][i];
			A[k][i] = A[k_prime][i];
			A[k_prime][i] = sub;
		}

		for (int i = k + 1; i < n; i++)
		{
			A[i][k] = A[i][k] / A[k][k];
			for (int j = k + 1; j < n; j++)
			{
				A[i][j] = A[i][j] - A[i][k] * A[k][j];
			}
		}
	}
	return pi;
}

matrix A =
{ {1,2,0},
{3,4,4},
{5,6,3}
};

std::vector<double> b ={ 3,7,8 };

matrix L =
{
	{1,0,0},
{0.2 ,1,0},
{0.6,0.5,1}
};

matrix U =
{
	{5,6,3},
	{0,0.8,-0.6},
{0,0,2.5}
};

std::vector< std::vector<int>> P =
{
	{0,0,1},
{1,0,0},
{0,1,0}
};

std::vector<double> y = { 8,  1.4,   1.5 };

template<typename T>
void print_matrx(std::vector<std::vector<T>> &mat)
{
	int  n = mat.size();
	for (int i = 0; i < n; i++)
	{
		int nn = mat[i].size();
		for (int j = 0; j < nn; j++)
		{
			std::cout << mat[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "\n\n";
}

//figure 28.1
matrix AA = {
	{2,3,1,5},
{6,13,5,19},
{2,19,10,23},
{4,10,11,31}
};

matrix AAA =
{
{2,0,2,0.6},
{3,3,4,-2},
{5,5,4,2},
{-1,2,3.4,-1}
};

int main()
{
	/*std::vector<int> PI = {2,0,1};
	std::vector<double> yy = LUP_SOLVE(L ,U ,PI ,b);
	for (auto x : yy)
	{
		std::cout << x << ' ';
	}
	std::cout << "\n\n";
	Set LU = LU_DECOMPOSITION(AA);

	print_matrx(LU.first);
	print_matrx(LU.second);

*/


	/*std::cout << "---------------------------\n";
	auto C = SQUARE_MATRIX_MULTIPLY(P, A);
	auto CC = SQUARE_MATRIX_MULTIPLY(L, U);
	print_matrx(C);
	print_matrx(CC);*/

	std::cout << "A\n";
	print_matrx(A);

	std::vector<int> pi = LUP_DECOMPOSITION(A);
	const int n = A.size();
	matrix ll(n, std::vector<double>(n,0));
	matrix uu(n, std::vector<double>(n, 0));

	std::cout << "A\n";
	print_matrx(A);


	for (int i = 0; i < n; i++)
	{
		ll[i][i] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i <= j)
			{
				uu[i][j] = A[i][j];
			}
			else
			{
				ll[i][j] = A[i][j];
			}
		}
	}
	for (auto x : pi)
	{
		std::cout << x << ' ';
	}

	std::cout << "\n\n";
	std::cout << "L\n";
	print_matrx(ll);
	std::cout << "U\n";
	print_matrx(uu);

	
	return 0;
}
