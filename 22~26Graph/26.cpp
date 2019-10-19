

//n = n+1
std::vector<std::vector<int>> LUP_SOLVE(std::vector<std::vector<double>> &L,
std::vector<std::vector<double>> &U, std::vector<int> &PI,std::vector<std::vector<int>> &b )
{
    const int n = L.size() - 1;
    std::vector<double> x;
    x.resize(n+1);

    std::vector<int> y;
    y.resize(n+1);

    for(int i = 1 ; i <= n ; i++)
    {
        int sum =0;
        for(int j = 1 ; j <= i-1;j++)
        {
            sum += L[i][j]*y[j];
        }
        y[i] = b[PI[i]]  - sum;
    }

    for(int i = n ; i >= 1 ;i--)
    {
        
        int sum =0;
        for(int j = i+1 ; j <= n; j++)
        {
            sum += L[i][j]*y[j];
        }
        x[i] = (y[i] - sum)/U[i][i]
    }
    return x;
}


//A is an n 	 n nonsingular matrix and P is absent (or, equivalently, P = In).

void LU_DECOMPOSITION(std::vector<std::vector<int>> &A)
{
    const int n = A.size() - 1;





    return 
}