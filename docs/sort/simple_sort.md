

swap함수는 있는걸 씁니다
swap 함수는 다음 라이브러리에 있습니다.
```
#include<utility>
```


### bubble 
모든 값은 비교해서 스왑한다.
```
template<typename T>
void buble_sort(T a[], int num)
{
	for (int i = 0; i < num -1; i++)
	{
		for (int j = 0; j < num - i -1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}

}
```

###  selection_sort
가장작은 값을 찾아서 맨밑으로 넣는다
```
template<typename T>
void selection_sort(T a[], int num)
{
	for (int i = 0; i < num - 1; i++)
	{
		int Minindex = i;
		for (int j =  i + 1 ; j < num ; j++)
		{
			if (a[j] < a[Minindex])
			{
				Minindex = j;
			}
		}
		swap(a[Minindex], a[i]);
	}
	return ;
}

```
### insertion_sort

삽입정렬, 뒤의 값을 밀어내고 값을 넣는다
```

template<typename T>
void insertion_sort(T a[], int num)
{
    for (int i = 1 ; i < num ; i++ )
    {
        T item = a[i];
        int j = i ;
        while (--j >= 0 && item < a[j])
        {
            a[j + 1] = a[j];
        }
        a[++j] = item;
    }

}

```
실제 삽입을 했을때,


```c++
template<typename T>
int sorting_insertion(T a[], int num, T item)
{
		int j = num;
		while (--j >= 0 && item < a[j])
		{
			a[j + 1] = a[j];
		}
		a[++j] = item;

	return num+1;
}

