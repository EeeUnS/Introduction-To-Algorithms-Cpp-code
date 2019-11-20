#include"Tree.h"


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
	TREE_INSERT(_node);
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





Node* BST::TREE_MINIMUM(Node* x) // 서브트리의 최솟값 반환
{
	
	while (x->left_small != NIL)
	{
		x = x->left_small;
	}

	return x;
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


void BST::TREE_DELETE(Node* z)
{
	
	if (z->left_small == NIL)
	{
		TRANSPLANT(z, z->right_large);
	}
	else if (z->right_large == NIL)
	{
		TRANSPLANT(z, z->left_small);
	}
	else
	{
		Node* y = TREE_MINIMUM(z->right_large);
		if (y->parent != z)
		{
			TRANSPLANT(y, y->right_large);
			y->right_large = z->right_large;
			y->right_large->parent = y;
		}
		TRANSPLANT(z, y);
		y->left_small = z->left_small;
		y->left_small->parent = y;
	}
	delete z;
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

Node* BST::getter_ROOT() const
{
	// TODO: 여기에 구현 코드 추가.
	return ROOT;
}