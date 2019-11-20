#ifndef QUEUE__H
#define QUEUE__H

namespace euns
{

template<typename T>
struct Node
{
	Node* pre;
	T item;
	Node* next;
};

template<typename T>
class queue
{
public:
	queue(const queue<T> &b); //iterator필요 미구현
	queue();
	queue(const T &item);
	~queue();
	void push(const T &item);
	void pop();
	int size();
	bool empty();
	
private:
	size_t size_type;
	Node<T>* end;
	Node<T>* start;
public:
	void swap(queue<T>& b);
	bool operator== (const queue<T>& rhs); //iterator필요 미구현
	bool operator!= (const queue<T>& rhs);//iterator필요 미구현
	bool operator< (const queue<T>& rhs);
	bool operator<= (const queue<T>& rhs);
	bool operator> (const queue<T>& rhs);
	bool operator>= (const queue<T>& rhs);

	T front();
	T back();
};

//
//
//template <class T, class Container>
//bool operator== (const queue<T, Container>& lhs, const queue<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator!= (const queue<T, Container>& lhs, const queue<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator<  (const queue<T, Container>& lhs, const queue<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator<= (const queue<T, Container>& lhs, const queue<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator>  (const queue<T, Container>& lhs, const queue<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator>= (const queue<T, Container>& lhs, const queue<T, Container>& rhs);
}

#endif // !1