

void RADIX_SORT(int A[],int n)// int d는 모른다고 가정
{

	int *B = new int[n];
	int *C = new int[n];
	
	int d  = 1; 
	bool check = false; // 끝 자리에 도달했는지 체크
	while(1)
	{
		for(int i = 0 ; i < n ; i++)
		{
			if(A[i] >=d)
			{
				check = true;
			}
		}
		if(!check) //끝자리에 도달했음
		{
			break;
		}
		d *= 10;



		check = false;
	}


	return ;
}
