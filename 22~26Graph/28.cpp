

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
    std::vector<std::vector<double>> L,U;

    L.resize(n+1);
    U.resize(n+1);
    for(int i = 1 ; i<= n ; i++)
    {
        L[i].resize(n+1);
        U[i].resize(n+1);
    }


    for(int k = 1; k <= n ; k++)
    {
        for(int i = k+1 ; i <= n ;i++)
        {
            L[i][k] = A[i][k]/U[k][k] ;
            U[k][i] = A[k][i];
        }

        for(int i = k+1 ; i <= n ;i++)
        {
            for(int j = k+1 ; j<=n;j++)
            {
                A[i][j] = A[i][j] - L[i][k]*U[k][j];
            }
            
        }

    }
    return L,U;
}

//미
void LUP_DECOMPOSITION(std::vector<std::vector<int>> &A)
{
    const int n = A.size() - 1;
    pi[]
    for(int i = 1 ; i <= n; i++)
    {
        pi[i] = i;
    }
    for(int k = 1 ; k<n ;k++)
    {
        int k_prime;
        int p = 0 ;
        for(int i = k ; i <= n ; i++)
        {
            if(A[i][k] > p)
            {
                p = A[i][k];
                k_prime = i;
            }
        }
        if(p==0)
        {
            std::cout << "singular matrix" << std::endl;
        }
        int sub = pi[k];
        pi[k] = pi[k_prime];
        pi[k_prime] = sub;
        for(int i = 1 ; i <= n ; i++)
        {
            int sub = 
        }
    }
}
