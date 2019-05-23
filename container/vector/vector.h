#ifndef STRING_HPP_
#define STRING_HPP_
#include<iostream>

template<typename T>
class vector
{
public:
	vector();
	~vector();
	T at(int i);
	T front();
	T back();
	bool empty();
	int size();
	int max_size();
//	int clear();
	void clear();
	void pop_back();
	void push_back();
};


/*value_type	T
allocator_type	Allocator
size_type	Unsigned integer type (usually std::size_t)
difference_type	Signed integer type (usually std::ptrdiff_t)
reference	 Allocator::reference	(until C++11)	value_type&	(since C++11) 
const_reference	 Allocator::const_reference	(until C++11)	const value_type&	(since C++11) 
pointer	 Allocator::pointer	(until C++11)	std::allocator_traits<Allocator>::pointer	(since C++11) 
const_pointer	 Allocator::const_pointer	(until C++11)	std::allocator_traits<Allocator>::const_pointer	(since C++11) 
iterator	LegacyRandomAccessIterator
const_iterator	Constant LegacyRandomAccessIterator
reverse_iterator	std::reverse_iterator<iterator>
const_reverse_iterator	std::reverse_iterator<const_iterator>
Member functions
(constructor)
 
constructs the vector 
(public member function)
(destructor)
 
destructs the vector 
(public member function)
operator=
 
assigns values to the container 
(public member function)
assign
 
assigns values to the container 
(public member function)
get_allocator
 
returns the associated allocator 
(public member function)
Element access
at
 
access specified element with bounds checking 
(public member function)
operator[]
 
access specified element 
(public member function)
front
 
access the first element 
(public member function)
back
 
access the last element 
(public member function)
data
  
(C++11)
 
direct access to the underlying array 
(public member function)
Iterators
begin
cbegin
  
 
returns an iterator to the beginning 
(public member function)
end
cend
  
 
returns an iterator to the end 
(public member function)
rbegin
crbegin
  
 
returns a reverse iterator to the beginning 
(public member function)
rend
crend
  
 
returns a reverse iterator to the end 
(public member function)
Capacity
empty
 
checks whether the container is empty 
(public member function)
size
 
returns the number of elements 
(public member function)
max_size
 
returns the maximum possible number of elements 
(public member function)
reserve
 
reserves storage 
(public member function)
capacity
 
returns the number of elements that can be held in currently allocated storage 
(public member function)
shrink_to_fit
  
(C++11)
 
reduces memory usage by freeing unused memory 
(public member function)
Modifiers
clear
 
clears the contents 
(public member function)
insert
 
inserts elements 
(public member function)
emplace
  
(C++11)
 
constructs element in-place 
(public member function)
erase
 
erases elements 
(public member function)
push_back
 
adds an element to the end 
(public member function)
emplace_back
  
(C++11)
 
constructs an element in-place at the end 
(public member function)
pop_back
 
removes the last element 
(public member function)
resize
 
changes the number of elements stored 
(public member function)
swap
 
swaps the contents 
(public member function)
Non-member functions
operator==
operator!=
operator<
operator<=
operator>
operator>=
 
lexicographically compares the values in the vector 
(function template)
std::swap(std::vector)
 
specializes the std::swap algorithm 
(function template)
erase(std::vector)
erase_if(std::vector)
  
(C++20)
 
Erases all elements satisfying specific criteria 
(function template)*/




#endif