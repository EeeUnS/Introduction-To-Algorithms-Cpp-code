// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include<utility>

#include <cstdio>
using namespace std;

int b[] = { 12,10 ,43,43 ,23,123,56,45,123 ,56,56,98,45,123,56,98,41,90,24 ,45 };//,-78,45,
 /**
   * @data  정수 배열
   * @size  data의 정수들의 개수
   * @p  숫자의 최대 자리수
   * @k  기수(10진법을 사용한다면 10)

   */
void rxSort(int* data, int size, int p, int k) 
{
	int* counts, // 특정 자리에서 숫자들의 카운트
		* temp; // 정렬된 배열을 담을 임시 장소
	int index, pval, i, j, n;
	// 메모리 할당
	if ((counts = (int*)malloc(k * sizeof(int))) == NULL)
		return;
	if ((temp = (int*)malloc(size * sizeof(int))) == NULL)
		return;
	for (n = 0; n < p; n++) { // 1의 자리, 10의자리, 100의 자리 순으로 진행
		for (i = 0; i < k; i++)
			counts[i] = 0; // 초기화
		   // 위치값 계산.
		  // n:0 => 1,  1 => 10, 2 => 100
		pval = (int)pow((double)k, (double)n);
		// 각 숫자의 발생횟수를 센다.
		for (j = 0; j < size; j++) 
		{
			// 253이라는 숫자라면
			// n:0 => 3,  1 => 5, 2 => 2
			index = (int)(data[j] / pval) % k;
			counts[index] = counts[index] + 1;
		}
		// 카운트 누적합을 구한다. 계수정렬을 위해서.
		for (i = 1; i < k; i++) 
		{
			counts[i] = counts[i] + counts[i - 1];
		}
		// 카운트를 사용해 각 항목의 위치를 결정한다.
		// 계수정렬 방식
		for (j = size - 1; j >= 0; j--) 
		{ // 뒤에서부터 시작
			index = (int)(data[j] / pval) % k;
			temp[counts[index] - 1] = data[j];
			counts[index] = counts[index] - 1; // 해당 숫자 카운트를 1 감소
		}
		// 임시 데이터 복사
		memcpy(data, temp, size * sizeof(int));
	}
	free(counts);
	free(temp);
}


void COUNTING_SORT(int A[], int n ,int k)//A의 수 n , k : 숫자범위
{
	int* C = new int[k];
	int* B = new int[n];
	for (int i = 0; i < k; i++)
	{
		C[i] = 0;
	}
	for (int j = 0; j < n; j++)
	{
		C[A[j]] = C[A[j]] + 1;
	}
	for (int i = 1; i < k; i++)
	{
		C[i] = C[i] + C[i - 1];
	}

	for (int j = n-1; j >= 0; j--)
	{
		B[C[A[j]]-1] = A[j];
		C[A[j]] = C[A[j]] - 1;
	}

	for (int i = 0; i < n; i++)
	{
		A[i] = B[i];
	}
	delete[] C;
	delete[] B;
}

void print(int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << ' ';
	}
	cout << '\n';
}

int main()//­
{
	int num = sizeof(b) / sizeof(int);
	print(b, num);

	COUNTING_SORT(b, num, 150);

	print(b, num);
	return 0;
}

//else if (a * c < k)
	//cout << a + k << '\n';
//완성


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
