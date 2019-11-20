
#ifndef VECTOR__HPP
#define VECTOR__HPP
#include "stack.h"

namespace euns
{

template<typename T>
stack<T>::stack(): size_type(0), end(nullptr)
{}

//template<typename t> //해결못하겠음
//stack<t>::stack(const stack<t> &b) 
//{
//	size_type = 0;
//	if (!b.empty())
//	{
//		end = nullptr;
//	}
//	else//iterator필요함
//	{
//		T *a = new T[b.size()];
//		while
//
//		stack<t> c;
//
//		while()
//	}
//}


template<typename T>
stack<T>::stack(const T &item) : size_type(0) ,end(nullptr)
{
	push(item);
}

template<typename T>
stack<T>::~stack()
{
	while (end != nullptr)
	{
		pop();
	}
}


template<typename T>
void stack<T>::push(const T &item)
{
	Node<T>* _node = new Node<T>;
	if (end == nullptr)
	{
		_node->pre = nullptr;
	}
	else
	{
		_node->pre = end;
		end->next = _node;
	}
	_node->item = item;
	_node->next = nullptr;
	size_type++;
	end = _node;
	return;
}


template<typename T>
void stack<T>::pop()
{
	Node<T>* _node = end;
	if (end->pre == nullptr)
	{
		end = nullptr;
	}
	else
	{
		end = end->pre;
	}
	delete _node;
	size_type--;
	return;
}


template<typename T>
int stack<T>::size()
{
	return size_type;
}


template<typename T>
bool stack<T>::empty()
{
	if (size_type == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
T stack<T>::top()
{
	return end->item;
}



template<typename T>
void stack<T>::swap(stack<T>& b)
{
	Node c = b.end;
	b.end = this->end;
	this->end = c;

	int c_size = b.size_type;
	b.size_type = this->size_type;
	this->size_type = c_size;
}

//template<typename T> //iterator필요
//bool stack<T>::operator== (const stack<T>& rhs)
//{
//
//}
//template<typename T>//iterator필요
//bool stack<T>::operator!= (const stack<T>& rhs)
//{
//
//}

template<typename T>
bool stack<T>::operator< (const stack<T>& rhs)
{
	return this->size() < rhs.size();
}

template<typename T>
bool stack<T>::operator<= (const stack<T>& rhs)
{
	return this->size() <= rhs.size();
}

template<typename T>
bool stack<T>::operator> (const stack<T>& rhs)
{
	return this->size()> rhs.size();
}

template<typename T>
bool stack<T>::operator>= (const stack<T>& rhs)
{
	return this->size() >= rhs.size();
}

}
#endif // !1
