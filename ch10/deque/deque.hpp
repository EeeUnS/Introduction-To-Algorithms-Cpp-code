
#ifndef DEQUE__HPP
#define DEQUE__HPP
#include "deque.h"

namespace euns
{
template<typename T>
deque<T>::deque(): size_type(0), end(nullptr), start(nullptr)
{}

//template<typename t> //해결못하겠음
//deque<t>::deque(const deque<t> &b) 
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
//		deque<t> c;
//
//		while()
//	}
//}


template<typename T>
deque<T>::deque(const T &item) : size_type(0) ,end(nullptr), start(nullptr)
{
	push(item);
}

template<typename T>
deque<T>::~deque()
{
	while (end != nullptr)
	{
		pop();
	}
}


template<typename T>
void deque<T>::push_back(const T &item)
{
	Node<T>* _node = new Node<T>;
	if (start == nullptr)
	{
		_node->pre = nullptr;
		start = _node;
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
void deque<T>::pop_front()
{
	Node<T>* _node = start;
	if (start->next == nullptr)
	{
		end = nullptr;
		start = nullptr;
	}
	else
	{
		start = start->next;
	}
	delete _node;
	size_type--;
	return;
}

template<typename T>
void deque<T>::push_front(const T& item)
{
	Node<T>* _node = new Node<T>;
	if (start == nullptr)
	{
		_node->pre = nullptr;
		start = _node;
	}
	else
	{
		_node->end = start;
		start->pre = _node;
	}
	_node->item = item;
	_node->next = nullptr;
	size_type++;
	start = _node;
	return;
}


template<typename T>
void deque<T>::pop_back()
{
	Node<T>* _node = end;
	if (end->pre == nullptr)
	{
		end = nullptr;
		start = nullptr;
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
int deque<T>::size()
{
	return size_type;
}


template<typename T>
bool deque<T>::empty()
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
void deque<T>::swap(deque<T>& b)
{
	Node c = b.end;
	b.end = this->end;
	this->end = c;

	int c_size = b.size_type;
	b.size_type = this->size_type;
	this->size_type = c_size;
}

//template<typename T> //iterator필요
//bool deque<T>::operator== (const deque<T>& rhs)
//{
//
//}
//template<typename T>//iterator필요
//bool deque<T>::operator!= (const deque<T>& rhs)
//{
//
//}

template<typename T>
bool deque<T>::operator< (const deque<T>& rhs)
{
	return this->size() < rhs.size();
}

template<typename T>
bool deque<T>::operator<= (const deque<T>& rhs)
{
	return this->size() <= rhs.size();
}

template<typename T>
bool deque<T>::operator> (const deque<T>& rhs)
{
	return this->size()> rhs.size();
}

template<typename T>
bool deque<T>::operator>= (const deque<T>& rhs)
{
	return this->size() >= rhs.size();
}

template<typename T>
T deque<T>::front()
{
	
	return start->item;
}

template<typename T>
T deque<T>::back()
{
	// TODO: 여기에 구현 코드 추가.
	return end->item;
}

 }
#endif // !1
