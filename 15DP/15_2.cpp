#include <iostream>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>


void MATRIX_CHAIN_ORDER(std::vector<int> p)
{
    const int INF = 1000000000;
    const int n = p.size() -1 ;
    std::vector<std::vector<int>> m (n,std::vector<int>(n,0));
    std::vector<std::vector<int>> s (n,std::vector<int>(n,0));
    for(int l = 1 ;l < n;l++)
    {
        for( int  i = 0 ; i < n-l +1 ;i++)
        {
            int j = i+l-1;
            m[i][j] = INF;
            for( int k = i ; k < j-1 ;k++)
            {
                int  q = m[i][k] + m [k+1][j] +p[i-1]*p[k]*p[j];
                if( q < m[i][j])
                {

                m[i][j] = q;
                s[i][j] = k;
                }
            }
        }
    }
    return m,s;

}

void PRINT_OPTIMAL_PARNS( std::vector<std::vector<int>> s , int i , int j)
{
    if(i==j)
    {
        std::cout <<"A" << i <<' ';
    }
    else
    {
        std::cout <<'(';
        PRINT_OPTIMAL_PARNS(s,i,s[i][j]);
        PRINT_OPTIMAL_PARNS(s,s[i][j]+1,j);
        std::cout <<')'
    }
}

void RECURSIVE_MATRIX_CHAIN(int p[],int i,int j)
{
      const int INF = 1000000000;
    //const int n = p.size() -1 ;
    std::vector<std::vector<int>> m (n,std::vector<int>(n,0));
    if(i==j)
    {
        return 0;
    }
    m[i][j] = INF;
    for(int k = i ; k < j-1 ; k++)
    {
        q = RECURSIVE_MATRIX_CHAIN(p,i,k)+
        RECURSIVE_MATRIX_CHAIN(p,k+1,j)+p[i-1]*p[k]*p[j];
        if(q < m[i][j])
        {
            m[i][j] = q;
        }
    }
    return m[i][j];
}

void  LOOKUP_CHAIN( m,p,i,j)
{

    if(m[i][j] < INF)
    {
        return m[i][j];
    }
    if (i==j)
    {
        m[i][j] = 0;
    }
    else for(int k = i < k <=j-1;k++)
    {
        q = LOOKUP_CHAIN(m,p,i,k)
        +LOOKUP_CHAIN(m,p,k+1,j) + p[i-1]*p[k]*p[j];
        if(q<m[i][j])
        {
            m[i][j] = q;
        }
    }
    return m[i][j];
}


void MEMORIZED_MATRIX_CHAIN(int p[],int n)
{
 const int INF = 1000000000;
     std::vector<std::vector<int>> m (n,std::vector<int>(n,0));
     for(int i = 1; i <= n ; i++)
     {

         for(int j = 1; j <= n ; j++)
         {
            m[i][j] = INF;
         }
     }
     return LOOKUP_CHAIN(m,p,1,n);
}

void



int main()
{
      return 0;
}
