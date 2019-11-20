#ifndef DEQUE__H
#define DEQUE__H

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
class deque
{
public:
	deque(const deque<T> &b); //iterator필요 미구현
	deque();
	deque(const T &item);
	~deque();
	void push_back(const T &item);
	void pop_front();
	void push_front(const T& item);
	void pop_back();
	int size();
	bool empty();
	
private:
	size_t size_type;
	Node<T>* end;
	Node<T>* start;
public:
	void swap(deque<T>& b);
	bool operator== (const deque<T>& rhs); //iterator필요 미구현
	bool operator!= (const deque<T>& rhs);//iterator필요 미구현
	bool operator< (const deque<T>& rhs);
	bool operator<= (const deque<T>& rhs);
	bool operator> (const deque<T>& rhs);
	bool operator>= (const deque<T>& rhs);

	T front();
	T back();
};

//
//
//template <class T, class Container>
//bool operator== (const deque<T, Container>& lhs, const deque<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator!= (const deque<T, Container>& lhs, const deque<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator<  (const deque<T, Container>& lhs, const deque<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator<= (const deque<T, Container>& lhs, const deque<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator>  (const deque<T, Container>& lhs, const deque<T, Container>& rhs);
//
//template <class T, class Container>
//bool operator>= (const deque<T, Container>& lhs, const deque<T, Container>& rhs);
}


/*
deque vs vector

vector구현 -배열
deque구현 연결리스트


deque
member type	definition	notes
value_type	The first template parameter (T)
allocator_type	The second template parameter (Alloc)	defaults to: allocator<value_type>
reference	value_type&
const_reference	const value_type&
pointer	allocator_traits<allocator_type>::pointer	for the default allocator: value_type*
const_pointer	allocator_traits<allocator_type>::const_pointer	for the default allocator: const value_type*
iterator	a random access iterator to value_type	convertible to const_iterator
const_iterator	a random access iterator to const value_type
reverse_iterator	reverse_iterator<iterator>
const_reverse_iterator	reverse_iterator<const_iterator>
difference_type	a signed integral type, identical to:
iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
size_type	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

Member functions
(constructor)
Construct deque container (public member function )
(destructor)
Deque destructor (public member function )
operator=
Assign content (public member function )

Iterators:
begin
Return iterator to beginning (public member function )
end
Return iterator to end (public member function )
rbegin
Return reverse iterator to reverse beginning (public member function )
rend
Return reverse iterator to reverse end (public member function )
cbegin
Return const_iterator to beginning (public member function )
cend
Return const_iterator to end (public member function )
crbegin
Return const_reverse_iterator to reverse beginning (public member function )
crend
Return const_reverse_iterator to reverse end (public member function )

Capacity:
size
Return size (public member function )
max_size
Return maximum size (public member function )
resize
Change size (public member function )
empty
Test whether container is empty (public member function )
shrink_to_fit
Shrink to fit (public member function )

Element access:
operator[]
Access element (public member function )
at
Access element (public member function )
front
Access first element (public member function )
back
Access last element (public member function )

Modifiers:
assign
Assign container content (public member function )
push_back
Add element at the end (public member function )
push_front
Insert element at beginning (public member function )
pop_back
Delete last element (public member function )
pop_front
Delete first element (public member function )
insert
Insert elements (public member function )
erase
Erase elements (public member function )
swap
Swap content (public member function )
clear
Clear content (public member function )
emplace
Construct and insert element (public member function )
emplace_front
Construct and insert element at beginning (public member function )
emplace_back
Construct and insert element at the end (public member function )

Allocator:
get_allocator
Get allocator (public member function )

Non-member functions overloads
relational operators
Relational operators for deque (function )
swap


*/

#endif // !1