#include <iostream>
#include<algorithm>
#include<tuple>
//the maximum-subarray

int FIND_MAX_CROSSING_SUBARRAY(int A[], int n)
{
	const int INF = 1000000;
	int max = -1000000;
	for (int i = 0; i < n; i++)
	{
		int sub_max = A[i];
		for (int j = i + 1; j < n; j++)
		{
			sub_max = sub_max + A[j];
			max = max < sub_max ? sub_max : max;
		}
	}
	return max;
}

std::tuple<int, int, int> FIND_MAX_CROSSING_SUBARRAY(int A[], int low, int mid, int high)
{
	const int INF = 1000000;
	int left_sum = -INF;
	int sum = 0;
	int max_left = -1;

	for (int i = mid; i >= low; i--)
	{
		sum = sum + A[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
	int right_sum = -INF, max_right = -1;
	sum = 0;
	for (int j = mid + 1; j <= high; j++)
	{
		sum = sum + A[j];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = j;
		}
	}
	return(std::make_tuple(max_left, max_right, left_sum + right_sum));

}

//low,high, sum
std::tuple<int, int, int>FIND_MAXIMUM_SUBARRAY(int A[], int low, int high)
{
	if (high == low)
		return (std::make_tuple(low, high, A[low]));
	else
	{
		int mid = (low + high) / 2;
		std::tuple<int, int, int> left = FIND_MAXIMUM_SUBARRAY(A, low, mid);
		std::tuple<int, int, int> right = FIND_MAXIMUM_SUBARRAY(A, mid + 1, high);
		std::tuple<int, int, int> cross = FIND_MAX_CROSSING_SUBARRAY(A, low, mid, high);
		if ((std::get<2>(left) >= std::get<2>(right)) && (std::get<2>(left) >= std::get<2>(cross)))
		{
			return left;
		}
		else if ((std::get<2>(right) >= std::get<2>(left)) && (std::get<2>(right) >= std::get<2>(cross)))
		{
			return right;
		}
		else
			return cross;
	}
}


std::tuple<int, int, int>KADANE(int A[], int n)
{
	std::tuple<int, int, int> current_sum (0,0,0) ;
	std::tuple<int, int, int> max ;
	for (int i = 0; i < n; i++)
	{
		if ( std::get<2>(current_sum) + A[i] > 0)
		{
			if (std::get<2>(current_sum) == 0)
				std::get<0>(current_sum) = i;
			std::get<2>(current_sum) = std::get<2>(current_sum) + A[i];
			std::get<1>(current_sum) = i;
			
		}
		else
		{
			std::get<2>(current_sum) = 0;
		}
		if (std::get<2>(max) < std::get<2>(current_sum))
		{
			std::get<0>(max) = std::get<0>(current_sum);
			std::get<1>(max) = std::get<1>(current_sum);
			std::get<2>(max) = std::get<2>(current_sum);
		}
		
	}
	return max;
}



int A[] = { 13 ,-3, -25, 20 ,-3 , -16, -23 , 18, 20 , -7, 12 , -5, -22, 15,-4 , 7 };

int main()
{
	const int n = sizeof(A) / sizeof(int);
	auto tup = FIND_MAXIMUM_SUBARRAY(A, 0, n - 1);
	auto top = KADANE(A, n );
	std::cout << std::get<0>(top) << ' ' << std::get<1>(top) << ' ' << std::get<2>(top) <<'\n';
	std::cout << std::get<0>(tup) << ' ' << std::get<1>(tup) << ' ' << std::get<2>(tup);
	return 0;
}
