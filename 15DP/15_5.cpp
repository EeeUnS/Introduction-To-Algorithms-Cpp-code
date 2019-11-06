

void OPTIMAL_BST(p,q,n)
{
    e,w,root

    for(int i = 1 ; i <= n+1 ; i++)
    {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }

    for(int l = 1 ; l <= n ; l++)
    {
        for(int i = 1 ;  i <= n-l+1 ; i++)
        {
            int j = i + l - 1; 
            e[i][j] = 0xFFFF;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for( int r = i ; r <= j ; r++)
            {
                t = e[i][r-1] + e[r+1][j] + w[i][j];
                if(t , e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    return e,root
}
