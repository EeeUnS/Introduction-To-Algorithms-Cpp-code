#include <iostream>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<windows.h>

#include<string.h>
enum class arrow
{
    left_up ,
    up ,
    left
};

typedef std::pair<std::vector<std::vector<int>>,std::vector<std::vector<arrow>>> Set;

Set LCS_LENGTH(const char* XX,const char* YY , const int m, const int n)
{
    const char * X = XX-1;
    const char * Y = YY-1;
    std::vector<std::vector<arrow>> b(m+1,std::vector<arrow>(n+1,arrow::left_up)) ;
    std::vector<std::vector<int>> c(m+1,std::vector<int>(n+1,0)) ;
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
            if(X[i] == Y[j])
            {
                c[i][j] = c[i-1][j-1] +1;
                b[i][j] = arrow::left_up;
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
    return std::make_pair(c,b);
}


void PRINT_LCS(const std::vector<std::vector<arrow>> b ,const char* XX, int i , int j)
{
    const char * X = XX-1;
    if( i == 0 || j == 0 )
    {
        return;
    }
    if( b[i][j] == arrow::left_up)
    {
        PRINT_LCS(b, X+1, i-1 , j-1);
        std::cout << X[i] <<' ';
    }
    else if(b[i][j] == arrow::up)
    {
        PRINT_LCS(b,X+1,i-1, j);
    }
    else
        PRINT_LCS(b,X+1,i, j-1);
}

const char *X = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
const char *Y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";

//const char *X = "ABCBDAB";
//const char *Y = "BDCABA";
char *Z = "GTCGTCGGAAGCCGGCCGAA";

int main()
{
    const int m = strlen(X);
    const int n = strlen(Y);
    Set cb = LCS_LENGTH(X,Y,m,n);

    for(int i = 0 ; i <= m ; i++)
    {
        for(int j = 0 ; j <= n ; j++)
        {
            std::cout <<cb.first[i][j] <<' ';
        }
        std::cout <<'\n';
    }
    PRINT_LCS(cb.second, X, m, n );
}
