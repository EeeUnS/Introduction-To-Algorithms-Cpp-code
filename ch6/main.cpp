#include <iostream>

using namespace std;



template<typename T>
class max_priority_queue
{
public:
	max_priority_queue()
	{
		A = new T[200];
		heap_size = 0;
		capacity = 200;

	}

	max_priority_queue(const T &item)
	{
		A = new T[200 + 1];
		A[1] = item;
		heap_size = 1;
		capacity = 200;
	}

	
	max_priority_queue(const T &item[],int begin ,int end)
	{

		heap_capacity = end - begin + 200;
		heap_size = end - begin;
		A = new T[heap_capacity + 1];
		for (int i = 1; i <= heap_size ; i++)
		{
			A[i] = item[begin+i-1];
		}
	}

	~max_priority_queue()
	{
		delete[]A;
	}

	T MAXIMUM()
	{
		return this.A[0];
	}

	T EXTRACT_MAX()
	{
		if (n < 1)
		{
			std::cout << "heap underflow" << std::endl;
			return -1;
		}
		T max = A[1];
		A[1] = A[heap_size];
		--heap_size;
		MAX_HEAPIFY(A, 1);
		return max;
	}

	void INCREASE_KEY(int i, int key)
	{
		if (key < A[i])
		{
			std::cout << "new key is smaller than current key" << std::endl;
			return;
		}
		A[i] = key;
		while ((i > 1) && (A[PARENT(i) < A[i]))
		{
			T a = A[i];
			A[i] = A[PARENT(i)];
			A[PARENT(i)] = a;
			i = PARENT(i);
		}
	}

	void INSERT(int key)
	{
		if (heap_size == heap_capacity)
		{
			resize(heap_capacity * 2);
		}

		++heap_size;
		A[heap_size] = -INF;
		INCREASE_KEY(heap_size, key);
	}


	void resize(int n)
	{

		T* B = new T[n + 1];
		heap_capacity = n;
		if (heap_capacity < heap_size)
		{
			std::cout << "heap overflow" << std::endl;
		}
		for (int i = 1; i < heap_size; i++)
		{
			B[i] = A[i];
		}
		delete[] A;
		A = B;
	}

	bool empty()
	{
		return heap_size == 0;
	}

private:
	const int INF = 100000000;
	T* A;
	std::size_t heap_size;  
	std::size_t heap_capacity; 


	int PARENT(int i)
	{
		return i / 2;
	}

	int LEFT(int i)
	{
		return 2 * i;
	}


	int RIGHT(int i)
	{
		return 2 * i + 1;
	}

	void MAX_HEAPIFY(int i, int heapsize)
	{
		int l = LEFT(i);
		int r = RIGHT(i);
		int largest;
		if (l <= heapsize && A[l] > A[i])
		{
			largest = l;
		}
		else
		{
			largest = i;
		}
		if (r <= heapsize && A[r] > A[largest])
		{
			largest = r;
		}
		if (largest != i)
		{
			swap(A[i], A[largest]);
			MAX_HEAPIFY(A, largest, heapsize);
		}
	}

	void BUILD_MAX_HEAP(int A[], int n)
	{
		int heapsize = n;
		for (int i = n / 2; i >= 1; i--)
		{
			MAX_HEAPIFY(i, heapsize);
		}
	}
};



int main()
{
	cout << "Hello world!" << endl;
	return 0;
}
