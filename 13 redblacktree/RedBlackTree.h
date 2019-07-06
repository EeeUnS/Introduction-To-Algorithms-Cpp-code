#ifndef __REDBLACKTREE__
#define __REDBLACKTREE__

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
	RED = 0,
	BLACK = 1
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

	RBNode* TREE_MINIMUM(RBNode* _node);
	RBNode* TREE_MAXIMUM(RBNode* _node);
	RBNode* TREE_SUCCESSOR(RBNode* _node);
	RBNode* TREE_PREDECESSOR(RBNode* _node);

	void insert(int n);
	void preorder();
	void Inorder();
	void postorder();
	
	void RB_INSERT(RBNode* z);
	void RB_DELETE(RBNode* z);

	void LEFT_ROTATE(RBNode* _node);
	void RIGHT_ROTATE(RBNode* _node);

private:
	RBNode* ROOT;
	RBNode* NIL;
	
	void inorder_procedure(RBNode* _node);
	void preorder_procedure(RBNode* _node);
	void postorder_procedure(RBNode* _node);

	void delete_node(RBNode* _node);
	void RB_TRANSPLANT(RBNode* u, RBNode* v);
	
	void RB_INSERT_FIXUP(RBNode* z);
	void RB_DELETE_FIXUP(RBNode* x);
};

RBT::RBT() : ROOT(nullptr)
{
	NIL = new RBNode();
	NIL->color = BLACK;
}


RBT::RBT(int n)
{
	NIL = new RBNode();
	NIL->color = BLACK;
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


void RBT::RB_INSERT(RBNode * z)// 책에 나오는 삽입
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
	z->left_small = NIL;
	z->right_large = NIL;
	RB_INSERT_FIXUP(z);
}

// _node위치의 노드를 _node의 자식인 replace노드로 대체하고 _node를 버린다.

void RBT::RB_TRANSPLANT(RBNode * _node, RBNode * replace)
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
	replace->parent = _node->parent;
	
}


void RBT::RB_DELETE(RBNode * z)
{
	RBNode* y = z;
	RBcolor y_original_color = y->color;
	RBNode* x;

	if (z->left_small == NIL)
	{
		x = z->right_large;
		RB_TRANSPLANT(z, z->right_large);
	}
	else if (z->right_large == NIL)
	{
		x = z->left_small;
		RB_TRANSPLANT(z, z->left_small);
	}
	else
	{
		y = TREE_MINIMUM(z->right_large); // 직후원소
		y_original_color = y->color;
		x = y->right_large;
		if (y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			RB_TRANSPLANT(y, y->right_large);
			y->right_large = z->right_large;
			y->right_large->parent = y;
		}
		RB_TRANSPLANT(z, y);
		y->left_small = z->left_small;
		y->left_small->parent = y;
		y->color = z->color;
	}
	if (y_original_color == BLACK)
	{
		RB_DELETE_FIXUP(x);
	}

}




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



void RBT::RB_INSERT_FIXUP(RBNode* z)
{
	// TODO: 여기에 구현 코드 추가.
	while (z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left_small) //z의 부모가 부모의 부모의 왼쪽자식일때
		{
			RBNode* y = z->parent->parent->right_large;
			if (y->color == RED) //case 1
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else if (z == z->parent->right_large) //case 2
			{
				z = z->parent;
				z->parent->parent->color = RED;
				LEFT_ROTATE(z->parent->parent);
			} //case 3
			z->parent->color = BLACK;
			z->parent->parent->color = RED;
			RIGHT_ROTATE(z->parent->parent);
		}
		else //z의 부모가 부모의 부모의 오른쪽자식일때
		{
			RBNode* y = z->parent->parent->left_small;
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else if (z == z->parent->left_small)
			{
				z = z->parent;
				z->parent->parent->color = RED;
				RIGHT_ROTATE(z->parent->parent);
			}
			z->parent->color = BLACK;
			z->parent->parent->color = RED;
			LEFT_ROTATE(z->parent->parent);
		}
	}
	ROOT->color = BLACK;
}
#endif

void RBT::RB_DELETE_FIXUP(RBNode* x)
{
	// TODO: 여기에 구현 코드 추가.
	while (x != ROOT && x->color == BLACK)
	{
		if (x == x->parent->right_large) // 오른쪽 자식
		{
			RBNode* w = x->parent->right_large;
			if (w->color == RED) // case 1
			{
				w->color = BLACK;
				x->parent->color = RED;
				LEFT_ROTATE(x->parent);
				w = x->parent->right_large;
			}
			if (w->left_small->color == BLACK && w->right_large->color == BLACK) //case 2
			{
				w->color = RED;
				x = x->parent;
			}
			else if (w->right_large->color == BLACK)
			{
				w->left_small->color = BLACK;
				w->color = RED;
				RIGHT_ROTATE(w);
				w = x->parent->right_large;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->right_large->color = BLACK;
			LEFT_ROTATE(x->parent);
			x = ROOT;
		}
		else//왼쪽자식
		{
			RBNode* w = x->parent->left_small;
			if (w->color == RED) // case 1
			{
				w->color = BLACK;
				x->parent->color = RED;
				RIGHT_ROTATE(x->parent);
				w = x->parent->left_small;
			}
			if (w->left_small->color == BLACK && w->right_large->color == BLACK) //case 2
			{
				w->color = RED;
				x = x->parent;
			}
			else if (w->left_small->color == BLACK)
			{
				w->right_large->color = BLACK;
				w->color = RED;
				LEFT_ROTATE(w);
				w = x->parent->left_small;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->left_small->color = BLACK;
			RIGHT_ROTATE(x->parent);
			x = ROOT;
		}
	}
	x->color = BLACK;
}


#endif