#ifndef VECTOR__H
#define VECTOR__H

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
class stack
{
public:
	stack(const stack<T> &b); //iterator鞘夸 固备泅
	stack();
	stack(const T &item);
	~stack();
	void push(const T &item);
	void pop();
	int size();
	bool empty();
	T top();
private:
	size_t size_type;
	Node<T>* end;
public:
	void swap(stack<T>& b);
	bool operator== (const stack<T>& rhs); //iterator鞘夸 固备泅
	bool operator!= (const stack<T>& rhs);//iterator鞘夸 固备泅
	bool operator< (const stack<T>& rhs);
	bool operator<= (const stack<T>& rhs);
	bool operator> (const stack<T>& rhs);
	bool operator>= (const stack<T>& rhs);

};

//
//
//template <class T, class Container>
//bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
}

#endif // !1
