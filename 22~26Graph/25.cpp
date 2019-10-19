
//25.1-8 NOT TEST

space requirement Theta(n^2)

std::vector<std::vector<int>>FASTER_ALL_PAIRS_SHORTEST_PATHS(std::vector<std::vector<int>>& W)
{
	const int n = W.size() - 1;

	std::vector<std::vector<int>>> A,B=W;
    A.resize(n+1);

    for (int j = 0; j <= n ; j++)
    {
        A[j].resize(n + 1);
    }

	int m = 1;
    
    while(m < n -1)
	{
        A = EXTEND_SHORTEST_PATHS(B, B);
        m = m*2;
        if(m < n -1)
        {
            return A;
        }

		B = EXTEND_SHORTEST_PATHS(A, A);
		m = m*2;
	}
	return  B;
}




//25.1-9  25.1-8에 이어서.

no consider overflow;
std::vector<std::vector<int>>FASTER_ALL_PAIRS_SHORTEST_PATHS(std::vector<std::vector<int>>& W)
{
	const int n = W.size() - 1;

	std::vector<std::vector<int>>> A,B=W,C;
    A.resize(n+1);
    for (int j = 0; j <= n ; j++)
    {
        A[j].resize(n + 1);
    }

	int m = 1;
    
    while(m < n -1)
	{
        A = EXTEND_SHORTEST_PATHS(B, B);
        m = m*2;
        if(m < n -1)
        {
            C = A;
            break;
        }

		B = EXTEND_SHORTEST_PATHS(A, A);
		m = m*2;
        if(m < n -1)
        {
            C = B;
            break;
        }
	}
    D = EXTEND_SHORTEST_PATHS(C, C);  
    bool chk_nwc = 0 ;
    for(int i = 1; i < n && !chk_nwc;i++)
    {
        for(int j = 1 ; j < n  && !chk_nwc ;j++)
        {
            if(C[i][j] != D[i][j])
            {
                chk_nwc = true;
            }
        }
    }


    if(chk_nwc)
        std::cout << "the input graph contains a negative-weight cycle" <<std::endl;

    return C;
}


