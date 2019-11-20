
#ifndef QUEUE__HPP
#define QUEUE__HPP
#include "queue.h"

namespace euns
{
template<typename T>
queue<T>::queue(): size_type(0), end(nullptr), start(nullptr)
{}

//template<typename t> //해결못하겠음
//queue<t>::queue(const queue<t> &b) 
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
//		queue<t> c;
//
//		while()
//	}
//}


template<typename T>
queue<T>::queue(const T &item) : size_type(0) ,end(nullptr), start(nullptr)
{
	push(item);
}

template<typename T>
queue<T>::~queue()
{
	while (end != nullptr)
	{
		pop();
	}
}


template<typename T>
void queue<T>::push(const T &item)
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
void queue<T>::pop()
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
int queue<T>::size()
{
	return size_type;
}


template<typename T>
bool queue<T>::empty()
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
void queue<T>::swap(queue<T>& b)
{
	Node c = b.end;
	b.end = this->end;
	this->end = c;

	int c_size = b.size_type;
	b.size_type = this->size_type;
	this->size_type = c_size;
}

//template<typename T> //iterator필요
//bool queue<T>::operator== (const queue<T>& rhs)
//{
//
//}
//template<typename T>//iterator필요
//bool queue<T>::operator!= (const queue<T>& rhs)
//{
//
//}

template<typename T>
bool queue<T>::operator< (const queue<T>& rhs)
{
	return this->size() < rhs.size();
}

template<typename T>
bool queue<T>::operator<= (const queue<T>& rhs)
{
	return this->size() <= rhs.size();
}

template<typename T>
bool queue<T>::operator> (const queue<T>& rhs)
{
	return this->size()> rhs.size();
}

template<typename T>
bool queue<T>::operator>= (const queue<T>& rhs)
{
	return this->size() >= rhs.size();
}

template<typename T>
T queue<T>::front()
{
	
	return start->item;
}

template<typename T>
T queue<T>::back()
{
	// TODO: 여기에 구현 코드 추가.
	return end->item;
}

 }
#endif // !1
