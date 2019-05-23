#pragma once
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
	Node* right_large; // key >=
	int key;
	Node* left_small; // key < 
	Node* parent;
};

class BST //binary search tree
{
public:
	BST();
	BST(int n);
	~BST();
private:
	Node* ROOT;
	Node* NIL;
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
	void TRANSPLANT(Node* u, Node* v);
public:
	Node* TREE_MINIMUM(Node* _node);
	Node* TREE_MAXIMUM(Node* _node);
	Node* TREE_SUCCESSOR(Node* _node);
	Node* TREE_PREDECESSOR(Node* _node);
	void TREE_INSERT(Node* z);

	void TREE_DELETE(Node* _node);
};

BST::BST() : ROOT(nullptr)
{
	NIL = new Node();
}


BST::BST(int n)
{
	NIL = new Node();
	Node* _ROOT = new Node();
	_ROOT->key = n;
	_ROOT->left_small = NIL;
	_ROOT->right_large = NIL;
	ROOT = _ROOT;
}

BST::~BST()
{
	delete NIL;
	delete_node(ROOT);
}

void BST::delete_node(Node* _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->left_small != NIL)
	{
		delete_node(_node->left_small);
	}

	if (_node->right_large != NIL)
	{
		delete_node(_node->right_large);
	}

	if (_node->left_small == NIL && _node->right_large == NIL)
	{
		delete _node;
	}
}



void BST::insert(int n)
{
	// TODO: 여기에 구현 코드 추가.
	Node* _node = new Node();
	_node->key = n;
	if (ROOT == NIL)
	{
		ROOT = _node;
		return;
	}

	Node* pre_node = ROOT;
	while (1)
	{
		if (pre_node->key >= n && pre_node->left_small == NIL)
		{
			pre_node->left_small = _node;
			break;
		}
		else if (pre_node->key >= n) //&& pre_node->right_large != NIL)
		{
			pre_node = pre_node->left_small;
		}
		else if (pre_node->key < n && pre_node->right_large == NIL)
		{
			pre_node->right_large = _node;
			break;
		}
		else //if (pre_node->key < n && pre_node->right_large != NIL)
		{
			pre_node = pre_node->right_large;
		}
	}
}


void BST::preorder() //전위순회
{
	if (ROOT == NIL)
		return;
	preorder_procedure(ROOT);

}


void BST::Inorder() //중위순회
{
	if (ROOT == NIL)
		return;
	inorder_procedure(ROOT);
	// TODO: 여기에 구현 코드 추가.
}


void BST::postorder()	//후위순회
{
	if (ROOT == NIL)
		return;
	postorder_procedure(ROOT);
	// TODO: 여기에 구현 코드 추가.
}

/*
왼쪽 서브 트리를 중위 순회한다.
노드를 방문한다.
오른쪽 서브 트리를 중위 순회한다.
*/
void BST::inorder_procedure(Node * _node)
{

	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == NIL)
		inorder_procedure(_node->right_large);
	cout << _node->key << " ";
	if (_node->left_small == NIL)
		inorder_procedure(_node->left_small);

}

/*
1.노드를 방문한다.
2.왼쪽 서브 트리를 중위 순회한다.
3.오른쪽 서브 트리를 중위 순회한다.
*/
void BST::preorder_procedure(Node * _node)
{
	cout << _node->key << " ";
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == NIL)
		preorder_procedure(_node->right_large);
	if (_node->left_small == NIL)
		preorder_procedure(_node->left_small);
}

/*
왼쪽 서브 트리를 후위 순회한다.
오른쪽 서브 트리를 후위 순회한다.
노드를 방문한다.
*/
void BST::postorder_procedure(Node * _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == NIL)
		postorder_procedure(_node->right_large);
	if (_node->left_small == NIL)
		postorder_procedure(_node->left_small);
	cout << _node->key << " ";
}//recursion -> while 





Node* BST::TREE_MINIMUM(Node* _node) // 서브트리의 최솟값 반환
{
	// TODO: 여기에 구현 코드 추가.
	while (_node->left_small != NIL)
	{
		_node = _node->left_small;
	}

	return _node;
}



//#endif // !1


Node* BST::TREE_MAXIMUM(Node* _node)// 서브트리의 최댓값 반환
{
	// TODO: 여기에 구현 코드 추가.
	while (_node->right_large!= NIL)
	{
		_node = _node->right_large;
	}

	return _node;
}


Node* BST::TREE_SUCCESSOR(Node* _node) // 직후노드
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large != NIL)
	{
		return TREE_MINIMUM(_node->right_large);
	}
	Node* y = _node->parent;
	while ( y != NIL && _node == y->right_large) //루트가아니고 오른쪽노드이면
	{
		_node = y;
		y = y->parent;
	}
	return y;
}


Node* BST::TREE_PREDECESSOR(Node* _node) //직전노드
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->left_small != NIL)
	{
		return TREE_MAXIMUM(_node->left_small);
	}
	Node* y = _node->parent;
	while (y != NIL && _node == y->left_small) //루트가아니고 오른쪽노드이면
	{
		_node = y;
		y = y->parent;
	}
	return y;
}


void BST::TREE_INSERT(Node *z)// 책에 나오는 삽입
{
	// TODO: 여기에 구현 코드 추가.
	Node* y = NIL;
	Node* x = ROOT;
	while (x != NIL)
	{
		y = x;
		if (z->key < x->key)
		{
			x = x->left_small;
		}
		else
		{
			x = x->right_large;
		}
	}
	z->parent = y;
	if (y == NIL)
	{
		ROOT = z;
	}
	else if (z->key < y->key)
	{
		y->left_small = z;
	}
	else
	{
		y->right_large = z;
	}
}

// _node위치의 노드를 _node의 자식인 replace노드로 대체하고 _node를 버린다.

void BST::TRANSPLANT(Node* _node, Node* replace) 
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->parent == NIL)
	{
		ROOT = replace;
	}
	else if (_node == _node->parent->left_small)
	{
		_node->parent->left_small = replace;
	}
	else
	{
		_node->parent->right_large = replace;
	}
	if (replace != NIL)
	{
		replace->parent = _node->parent;
	}
}


void BST::TREE_DELETE(Node* _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->left_small == NIL)
	{
		TRANSPLANT(_node, _node->right_large);
	}
	else if (_node->right_large == NIL)
	{
		TRANSPLANT(_node, _node->left_small);
	}
	else
	{
		Node* snode = TREE_MINIMUM(_node->right_large);
		if (snode->parent != _node)
		{
			TRANSPLANT(snode, snode->right_large);
			snode->right_large = _node->right_large;
			snode->right_large->parent = snode;
		}
		TRANSPLANT(_node, snode);
		snode->left_small = _node->left_small;
		snode->left_small->parent = snode;
	}

}

/* ******************************************************************************************/
//Red Black Tree

/*
1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the
same number of black nodes.
*/

enum RBcolor
{
	red = 0,
	black = 1
};


struct RBNode
{
	RBNode* right_large; // key >=
	int key;
	RBNode* left_small; // key < 
	RBNode* parent;
	RBcolor color;
};


class RBT //binary search tree
{
public:
	RBT();
	RBT(int n);
	~RBT();
private:
	RBNode* ROOT;
	RBNode* NIL;
public:
	void insert(int n);
	void preorder();
	void Inorder();
	void postorder();
private:

	void inorder_procedure(RBNode* _node);
	void preorder_procedure(RBNode* _node);
	void postorder_procedure(RBNode* _node);
public:

private:
	void delete_node(RBNode* _node);
	void TRANSPLANT(RBNode* u, RBNode* v);
public:
	RBNode* TREE_MINIMUM(RBNode* _node);
	RBNode* TREE_MAXIMUM(RBNode* _node);
	RBNode* TREE_SUCCESSOR(RBNode* _node);
	RBNode* TREE_PREDECESSOR(RBNode* _node);
	void TREE_INSERT(RBNode* z);

	void TREE_DELETE(RBNode* _node);
	void LEFT_ROTATE(RBNode* _node);
	void RIGHT_ROTATE(RBNode* _node);
};

RBT::RBT() : ROOT(nullptr)
{
	NIL = new RBNode();
}


RBT::RBT(int n)
{
	NIL = new RBNode();
	RBNode* _ROOT = new RBNode();
	_ROOT->key = n;
	_ROOT->left_small = NIL;
	_ROOT->right_large = NIL;
	ROOT = _ROOT;
}

RBT::~RBT()
{
	delete NIL;
	delete_node(ROOT);
}

void RBT::delete_node(RBNode* _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->left_small != NIL)
	{
		delete_node(_node->left_small);
	}

	if (_node->right_large != NIL)
	{
		delete_node(_node->right_large);
	}

	if (_node->left_small == NIL && _node->right_large == NIL)
	{
		delete _node;
	}
}



void RBT::insert(int n)
{
	// TODO: 여기에 구현 코드 추가.
	RBNode* _node = new RBNode();
	_node->key = n;
	if (ROOT == NIL)
	{
		ROOT = _node;
		return;
	}

	RBNode* pre_node = ROOT;
	while (1)
	{
		if (pre_node->key >= n && pre_node->left_small == NIL)
		{
			pre_node->left_small = _node;
			break;
		}
		else if (pre_node->key >= n) //&& pre_node->right_large != NIL)
		{
			pre_node = pre_node->left_small;
		}
		else if (pre_node->key < n && pre_node->right_large == NIL)
		{
			pre_node->right_large = _node;
			break;
		}
		else //if (pre_node->key < n && pre_node->right_large != NIL)
		{
			pre_node = pre_node->right_large;
		}
	}
}


void RBT::preorder() //전위순회
{
	if (ROOT == NIL)
		return;
	preorder_procedure(ROOT);

}


void RBT::Inorder() //중위순회
{
	if (ROOT == NIL)
		return;
	inorder_procedure(ROOT);
	// TODO: 여기에 구현 코드 추가.
}


void RBT::postorder()	//후위순회
{
	if (ROOT == NIL)
		return;
	postorder_procedure(ROOT);
	// TODO: 여기에 구현 코드 추가.
}

/*
왼쪽 서브 트리를 중위 순회한다.
노드를 방문한다.
오른쪽 서브 트리를 중위 순회한다.
*/
void RBT::inorder_procedure(RBNode * _node)
{

	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == NIL)
		inorder_procedure(_node->right_large);
	cout << _node->key << " ";
	if (_node->left_small == NIL)
		inorder_procedure(_node->left_small);

}

/*
1.노드를 방문한다.
2.왼쪽 서브 트리를 중위 순회한다.
3.오른쪽 서브 트리를 중위 순회한다.
*/
void RBT::preorder_procedure(RBNode * _node)
{
	cout << _node->key << " ";
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == NIL)
		preorder_procedure(_node->right_large);
	if (_node->left_small == NIL)
		preorder_procedure(_node->left_small);
}

/*
왼쪽 서브 트리를 후위 순회한다.
오른쪽 서브 트리를 후위 순회한다.
노드를 방문한다.
*/
void RBT::postorder_procedure(RBNode * _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large == NIL)
		postorder_procedure(_node->right_large);
	if (_node->left_small == NIL)
		postorder_procedure(_node->left_small);
	cout << _node->key << " ";
}//recursion -> while 





RBNode * RBT::TREE_MINIMUM(RBNode * _node) // 서브트리의 최솟값 반환
{
	// TODO: 여기에 구현 코드 추가.
	while (_node->left_small != NIL)
	{
		_node = _node->left_small;
	}

	return _node;
}



//#endif // !1


RBNode* RBT::TREE_MAXIMUM(RBNode * _node)// 서브트리의 최댓값 반환
{
	// TODO: 여기에 구현 코드 추가.
	while (_node->right_large != NIL)
	{
		_node = _node->right_large;
	}

	return _node;
}


RBNode* RBT::TREE_SUCCESSOR(RBNode * _node) // 직후노드
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->right_large != NIL)
	{
		return TREE_MINIMUM(_node->right_large);
	}
	RBNode* y = _node->parent;
	while (y != NIL && _node == y->right_large) //루트가아니고 오른쪽노드이면
	{
		_node = y;
		y = y->parent;
	}
	return y;
}


RBNode* RBT::TREE_PREDECESSOR(RBNode * _node) //직전노드
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->left_small != NIL)
	{
		return TREE_MAXIMUM(_node->left_small);
	}
	RBNode* y = _node->parent;
	while (y != NIL && _node == y->left_small) //루트가아니고 오른쪽노드이면
	{
		_node = y;
		y = y->parent;
	}
	return y;
}


void RBT::TREE_INSERT(RBNode * z)// 책에 나오는 삽입
{
	// TODO: 여기에 구현 코드 추가.
	RBNode* y = NIL;
	RBNode* x = ROOT;
	while (x != NIL)
	{
		y = x;
		if (z->key < x->key)
		{
			x = x->left_small;
		}
		else
		{
			x = x->right_large;
		}
	}
	z->parent = y;
	if (y == NIL)
	{
		ROOT = z;
	}
	else if (z->key < y->key)
	{
		y->left_small = z;
	}
	else
	{
		y->right_large = z;
	}
}

// _node위치의 노드를 _node의 자식인 replace노드로 대체하고 _node를 버린다.

void RBT::TRANSPLANT(RBNode * _node, RBNode * replace)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->parent == NIL)
	{
		ROOT = replace;
	}
	else if (_node == _node->parent->left_small)
	{
		_node->parent->left_small = replace;
	}
	else
	{
		_node->parent->right_large = replace;
	}
	if (replace != NIL)
	{
		replace->parent = _node->parent;
	}
}


void RBT::TREE_DELETE(RBNode * _node)
{
	// TODO: 여기에 구현 코드 추가.
	if (_node->left_small == NIL)
	{
		TRANSPLANT(_node, _node->right_large);
	}
	else if (_node->right_large == NIL)
	{
		TRANSPLANT(_node, _node->left_small);
	}
	else
	{
		RBNode* snode = TREE_MINIMUM(_node->right_large);
		if (snode->parent != _node)
		{
			TRANSPLANT(snode, snode->right_large);
			snode->right_large = _node->right_large;
			snode->right_large->parent = snode;
		}
		TRANSPLANT(_node, snode);
		snode->left_small = _node->left_small;
		snode->left_small->parent = snode;
	}

}



#endif

void RBT::LEFT_ROTATE(RBNode* _node)
{
	// TODO: 여기에 구현 코드 추가.
	RBNode* snode = _node->right_large;
	_node->right_large = snode->left_small;
	if (snode->left_small != NIL)
	{
		snode->left_small->parent = _node;
	}
	snode->parent = _node->parent;
	if (_node->parent == NIL)
	{
		ROOT = snode;
	}
	else if (_node == _node->parent->left_small)
	{
		_node->parent->left_small = _node;
	}
	else
	{
		_node->parent->right_large = snode;
	}
	snode->left_small = _node;
	_node->parent = snode;
}


void RBT::RIGHT_ROTATE(RBNode* _node)
{
	// TODO: 여기에 구현 코드 추가.
	RBNode* snode = _node->left_small;
	_node->left_small = snode->right_large;
	if (snode->right_large != NIL)
	{
		snode->right_large->parent = _node;
	}
	snode->parent = _node->parent;
	if (_node->parent == NIL)
	{
		ROOT = snode;
	}
	else if (_node == _node->parent->right_large)
	{
		_node->parent->right_large = _node;
	}
	else
	{
		_node->parent->left_small = snode;
	}
	snode->right_large = _node;
	_node->parent = snode;
}
