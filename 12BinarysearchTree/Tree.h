#ifndef __TREE_H__
#define __TREE_H__

#include<iostream>
//using namespace std;

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
	void insert(int n);

	void preorder();//12.1-4
	void Inorder();//12.1-3
	void postorder(); //12.1-4

	Node* TREE_MINIMUM(Node* x);
	Node* TREE_MAXIMUM(Node* x);

	Node* TREE_SUCCESSOR(Node* x);
	Node* TREE_PREDECESSOR(Node* x);

	void TREE_INSERT(Node* z);
	void TREE_DELETE(Node* z);

	void INORDER_TREE_WALK(Node* x);
	Node* TREE_SEARCH(Node* x, int k);
	Node* ITERATIVE_TREE_SEARCH(Node* x, int k);

private:
	Node* ROOT;
	Node* NIL;

	void inorder_procedure(Node* _node);
	void preorder_procedure(Node* _node);
	void postorder_procedure(Node* _node);
	void delete_node(Node* _node);
	void TRANSPLANT(Node* u, Node* v);
public: 
	const Node* getter_ROOT() const;
};

BST::BST()
{
	NIL = new Node();
	ROOT = NIL;
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
	
	Node* _node = new Node();
	_node->key = n;
	_node->left_small = NIL;
	_node->right_large = NIL;
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
	std::cout << '\n';
}


void BST::Inorder() //중위순회
{
	if (ROOT == NIL)
		return;
	inorder_procedure(ROOT);
	std::cout << '\n';
}


void BST::postorder()	//후위순회
{
	if (ROOT == NIL)
		return;
	postorder_procedure(ROOT);
	std::cout << '\n';
}

/*
왼쪽 서브 트리를 중위 순회한다.
노드를 방문한다.
오른쪽 서브 트리를 중위 순회한다.
*/
void BST::inorder_procedure(Node* _node)
{
	if (_node->left_small != NIL)
		inorder_procedure(_node->left_small);
	std::cout << _node->key << " ";
	if (_node->right_large != NIL)
		inorder_procedure(_node->right_large);
}

/*
1.노드를 방문한다.
2.왼쪽 서브 트리를 중위 순회한다.
3.오른쪽 서브 트리를 중위 순회한다.
*/
void BST::preorder_procedure(Node* _node)
{
	std::cout << _node->key << " ";
	if (_node->left_small != NIL)
		preorder_procedure(_node->left_small);
	if (_node->right_large != NIL)
		preorder_procedure(_node->right_large);
}

/*
왼쪽 서브 트리를 후위 순회한다.
오른쪽 서브 트리를 후위 순회한다.
노드를 방문한다.
*/
void BST::postorder_procedure(Node* _node)
{
	if (_node->left_small != NIL)
		postorder_procedure(_node->left_small);
	if (_node->right_large != NIL)
		postorder_procedure(_node->right_large);
	std::cout << _node->key << " ";

}//recursion -> while 





Node* BST::TREE_MINIMUM(Node* _node) // 서브트리의 최솟값 반환
{
	
	while (_node->left_small != NIL)
	{
		_node = _node->left_small;
	}

	return _node;
}

Node* BST::TREE_MAXIMUM(Node* x)// 서브트리의 최댓값 반환
{
	
	while (x->right_large != NIL)
	{
		x = x->right_large;
	}

	return x;
}


Node* BST::TREE_SUCCESSOR(Node* x) // 직후노드
{
	
	if (x->right_large != NIL)
	{
		return TREE_MINIMUM(x->right_large);
	}
	Node* y = x->parent;
	while (y != NIL && x == y->right_large) //루트가아니고 오른쪽노드이면
	{
		x = y;
		y = y->parent;
	}
	return y;
}


Node* BST::TREE_PREDECESSOR(Node* x) //직전노드
{
	
	if (x->left_small != NIL)
	{
		return TREE_MAXIMUM(x->left_small);
	}
	Node* y = x->parent;
	while (y != NIL && x == y->left_small) //루트가아니고 오른쪽노드이면
	{
		x = y;
		y = y->parent;
	}
	return y;
}


void BST::TREE_INSERT(Node* z)// 책에 나오는 삽입
{
	
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
void BST::TRANSPLANT(Node* u, Node* v)
{
	
	if (u->parent == NIL)
	{
		ROOT = v;
	}
	else if (u == u->parent->left_small)
	{
		u->parent->left_small = v;
	}
	else
	{
		u->parent->right_large = v;
	}
	if (v != NIL)
	{
		v->parent = u->parent;
	}
}


void BST::TREE_DELETE(Node* _node)
{
	
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
void BST::INORDER_TREE_WALK(Node* x)
{
	if (x != NIL)
	{
		INORDER_TREE_WALK(x->left_small);
		std::cout << x->key << ' ';
		INORDER_TREE_WALK(x->right_large);
	}
	
}


Node* BST::TREE_SEARCH(Node* x, int k)
{
	if (x == NIL || k == x->key)
	{
		return x;
	}
	if (k < x->key)
	{
		return TREE_SEARCH(x->left_small, k);
	}
	else
	{
		return TREE_SEARCH(x->right_large, k);
	}
}


Node* BST::ITERATIVE_TREE_SEARCH(Node* x, int k)
{
	while (x != NIL && k != x->key)
	{
		if (k < x->key)
		{
			x = x->left_small;
		}
		else x = x->right_large;
	}
	return x;
}

const Node* BST::getter_ROOT() const
{
	// TODO: 여기에 구현 코드 추가.
	return static_cast<const Node *>(ROOT);
}

#endif