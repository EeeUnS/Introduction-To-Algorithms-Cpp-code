#pragma once

#ifndef __TREE_H__
#define __TREE_H__
// heap , 
//red-black-tree ,
// binary search tree
#include<iostream>
using namespace std;

struct Node
{
	Node* right_large; // item >=
	int item;
	Node* left_small; // item < 
};

class BTS //binary search tree
{
public:
	BTS();
	BTS(int n);
	~BTS();
private:
	Node* root;
public:
	void insert(int n);
	void preorder();
	void Inorder();
	void postorder();
private:

	void inorder_procedure(Node* _node);
	void preorder_procedure(Node* _node);
	void postorder_procedure(Node* _node);
public:

private:
	void delete_node(Node* _node);
};

BTS::BTS() : root(nullptr)
{}


BTS::BTS(int n)
{
	Node *_root = new Node();
	_root->item = n;
	_root->left_small = nullptr;
	_root->right_large= nullptr;
	root = _root;
}

BTS::~BTS()
{
	delete_node(root);
}

void BTS::delete_node(Node* _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->left_small != nullptr)
	{
		delete_node(_node->left_small);
	}
	
	if (_node->right_large != nullptr)
	{
		delete_node(_node->right_large);
	}

	if (_node->left_small == nullptr && _node->right_large == nullptr)
	{
		delete _node;
	}
}



void BTS::insert(int n)
{
	// TODO: 여기에 구현 코드 추가.
	Node* _node = new Node();
	_node->item = n;
	if (root == nullptr)
	{
		root = _node;
		return;
	}

	Node* pre_node = root;
	while (1)
	{
		if (pre_node->item >= n && pre_node->left_small == nullptr)
		{
			pre_node->left_small = _node;
			break;
		}
		else if (pre_node->item >= n) //&& pre_node->right_large != nullptr)
		{
			pre_node = pre_node->left_small;
		}
		else if (pre_node->item < n && pre_node->right_large == nullptr)
		{
			pre_node->right_large = _node;
			break;
		}
		else //if (pre_node->item < n && pre_node->right_large != nullptr)
		{
			pre_node = pre_node->right_large;
		}
	}
}


void BTS::preorder() //전위순회
{
	if (root == nullptr)
		return;
	preorder_procedure(root);

}


void BTS::Inorder() //중위순회
{
	if (root == nullptr)
		return;
	inorder_procedure(root);
	// TODO: 여기에 구현 코드 추가.
}


void BTS::postorder()	//후위순회
{
	if (root == nullptr)
		return;
	postorder_procedure(root);
	// TODO: 여기에 구현 코드 추가.
}

/*
왼쪽 서브 트리를 중위 순회한다.
노드를 방문한다.
오른쪽 서브 트리를 중위 순회한다.
*/
void BTS::inorder_procedure(Node * _node)
{
	
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == nullptr)
		inorder_procedure(_node->right_large);
	cout << _node->item << " ";
	if (_node->left_small == nullptr)
		inorder_procedure(_node->left_small);

}

/*
1.노드를 방문한다.
2.왼쪽 서브 트리를 중위 순회한다.
3.오른쪽 서브 트리를 중위 순회한다.
*/
void BTS::preorder_procedure(Node* _node)
{
	cout << _node->item << " ";
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == nullptr)
		preorder_procedure(_node->right_large);
	if (_node->left_small == nullptr)
		preorder_procedure(_node->left_small);
}

/*
왼쪽 서브 트리를 후위 순회한다.
오른쪽 서브 트리를 후위 순회한다.
노드를 방문한다.
*/
void BTS::postorder_procedure(Node* _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == nullptr)
		postorder_procedure(_node->right_large);
	if (_node->left_small == nullptr)
		postorder_procedure(_node->left_small);
	cout << _node->item << " ";
}//recursion -> while 



#endif // !1

