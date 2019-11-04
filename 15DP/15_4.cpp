#include <iostream>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<windows.h>

enum class arrow
{
    left_up ,
    up ,
    left
};

void LCS_LENGTH(const std::vector<int> &X,const std::vector<int> &Y )
{
    const int m = X.size();
    const int n = Y.size();
    std::vector<std::vector<int>> b(n+1,std::vector<int>(m+1,0)) ;
    std::vector<std::vector<int>> c(n+1,std::vector<int>(m+1,0)) ;
    for(int i = 1 ; i <= m ; i++)
    {
        c[i][0] = 0;
    }
    for(int j = 0 ; j <= n; j++)
    {
        c[0][j] = 0;
    }
    for(int i = 1 ; i <= m; i++)
    {

        for(int j = 1; j <= n;j++)
        {
            if(x[i] == Y[j])
            {
                c[i][j] = c[i-1][j-1] +1;
                b[i][j] =arrow::left_up;
            }else if(c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = arrow::up;
            }
            else
            {
                c[i][j] = c[i][j-1];
                b[i][j] = arrow::left;
            }
        }
    }
}


void PRINT_LCS(const std::vector<int> & b , const std::vector<int> &X, int i , int j)
{
    if( i == 0 || j == 0 )
    {
        return;
    }
    if( b[i][j] == arrow::left_up)
    {
        PRINT_LCS(b, X, i-1 , j-1);
        std::cout << x[i] <<' ';
    }
    else if(b[i][j] == arrow::up)
    {
        PRINT_LCS(b,X,i-1, j);
    }
    else
        PRINT_LCS(b,X,i, j-1);
}



