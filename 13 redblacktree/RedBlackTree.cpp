#include "RedBlackTree.h"


RBT::RBT()
{
	NIL = new RBNode();
	NIL->color = RBcolor::BLACK;
	NIL->left_small = NIL;
	NIL->right_large = NIL;
	NIL->parent = NIL;
	NIL->key = -1000000000;
	ROOT = NIL;
}


RBT::RBT(int n)
{
	NIL = new RBNode();

	NIL->color = RBcolor::BLACK;
	NIL->left_small = NIL;
	NIL->right_large = NIL;
	NIL->parent = NIL;

	RBNode* _ROOT = new RBNode();
	_ROOT->key = n;
	_ROOT->left_small = NIL;
	_ROOT->right_large = NIL;
	_ROOT->parent = NIL;
	_ROOT->color =  RBcolor::BLACK;
	ROOT = _ROOT;
}

RBT::~RBT()
{
	delete NIL;
	delete_RBNode(ROOT);
}

void RBT::delete_RBNode(RBNode* _RBNode)
{

	if (_RBNode->left_small != NIL)
	{
		delete_RBNode(_RBNode->left_small);
	}

	if (_RBNode->right_large != NIL)
	{
		delete_RBNode(_RBNode->right_large);
	}

	if (_RBNode->left_small == NIL && _RBNode->right_large == NIL)
	{
		delete _RBNode;
	}
}



void RBT::insert(int n)
{

	RBNode* _RBNode = new RBNode();
	_RBNode->key = n;
	_RBNode->left_small = NIL;
	_RBNode->right_large = NIL;
	_RBNode->parent = NIL;
	RB_INSERT(_RBNode);
}


void RBT::preorder() //전위순회
{
	if (ROOT == NIL)
		return;
	preorder_procedure(ROOT);
	std::cout << '\n';
}


void RBT::Inorder() //중위순회
{
	if (ROOT == NIL)
		return;
	inorder_procedure(ROOT);
	std::cout << '\n';
}


void RBT::postorder()	//후위순회
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
void RBT::inorder_procedure(RBNode* _RBNode)
{
	if (_RBNode->left_small != NIL)
		inorder_procedure(_RBNode->left_small);
	std::cout << _RBNode->key;
	if (_RBNode->color == RBcolor::RED)
	{
		std::cout << "(R)";
	}
	else
	{
		std::cout << "(B)";
	}
	std::cout <<" ";
	if (_RBNode->right_large != NIL)
		inorder_procedure(_RBNode->right_large);
}

/*
1.노드를 방문한다.
2.왼쪽 서브 트리를 중위 순회한다.
3.오른쪽 서브 트리를 중위 순회한다.
*/
void RBT::preorder_procedure(RBNode* _RBNode)
{
	std::cout << _RBNode->key;
	if (_RBNode->color == RBcolor::RED)
	{
		std::cout << "(R)";
	}
	else
	{
		std::cout << "(B)";
	}
	std::cout << " ";
	if (_RBNode->left_small != NIL)
		preorder_procedure(_RBNode->left_small);
	if (_RBNode->right_large != NIL)
		preorder_procedure(_RBNode->right_large);
}

/*
왼쪽 서브 트리를 후위 순회한다.
오른쪽 서브 트리를 후위 순회한다.
노드를 방문한다.
*/
void RBT::postorder_procedure(RBNode* _RBNode)
{
	if (_RBNode->left_small != NIL)
		postorder_procedure(_RBNode->left_small);
	if (_RBNode->right_large != NIL)
		postorder_procedure(_RBNode->right_large);
	std::cout << _RBNode->key;
	if (_RBNode->color == RBcolor::RED)
	{
		std::cout << "(R)";
	}
	else
	{
		std::cout << "(B)";
	}
	std::cout << " ";

}//recursion -> while 





RBNode* RBT::TREE_MINIMUM(RBNode* x) // 서브트리의 최솟값 반환
{

	while (x->left_small != NIL)
	{
		x = x->left_small;
	}

	return x;
}

RBNode* RBT::TREE_MAXIMUM(RBNode* x)// 서브트리의 최댓값 반환
{

	while (x->right_large != NIL)
	{
		x = x->right_large;
	}

	return x;
}


RBNode* RBT::TREE_SUCCESSOR(RBNode* x) // 직후노드
{

	if (x->right_large != NIL)
	{
		return TREE_MINIMUM(x->right_large);
	}
	RBNode* y = x->parent;
	while (y != NIL && x == y->right_large) //루트가아니고 오른쪽노드이면
	{
		x = y;
		y = y->parent;
	}
	return y;
}


RBNode* RBT::TREE_PREDECESSOR(RBNode* x) //직전노드
{

	if (x->left_small != NIL)
	{
		return TREE_MAXIMUM(x->left_small);
	}
	RBNode* y = x->parent;
	while (y != NIL && x == y->left_small) //루트가아니고 오른쪽노드이면
	{
		x = y;
		y = y->parent;
	}
	return y;
}



void RBT::RB_INSERT(RBNode* z)// 책에 나오는 삽입
{
	
	RBNode* y = NIL;
	RBNode* x = ROOT;
	while (x != NIL)
	{
		//assert((NIL->color == BLACK));
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
	z->color = RED;
	RB_INSERT_FIXUP(z);
}

void RBT::RB_TRANSPLANT(RBNode* u, RBNode* v)
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
	v->parent = u->parent;

}


void RBT::RB_DELETE(RBNode* z)
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
	delete z;
}




void RBT::LEFT_ROTATE(RBNode* x)
{
	
	RBNode* snode = x->right_large;
	x->right_large = snode->left_small;
	if (snode->left_small != NIL)
	{
		snode->left_small->parent = x;
	}
	snode->parent = x->parent;
	if (x->parent == NIL)
	{
		ROOT = snode;
	}
	else if (x == x->parent->left_small)
	{
		x->parent->left_small = x;
	}
	else
	{
		x->parent->right_large = snode;
	}
	snode->left_small = x;
	x->parent = snode;
}


void RBT::RIGHT_ROTATE(RBNode* x)
{
	
	RBNode* snode = x->left_small;
	x->left_small = snode->right_large;
	if (snode->right_large != NIL)
	{
		snode->right_large->parent = x;
	}
	snode->parent = x->parent;
	if (x->parent == NIL)
	{
		ROOT = snode;
	}
	else if (x == x->parent->right_large)
	{
		x->parent->right_large = x;
	}
	else
	{
		x->parent->left_small = snode;
	}
	snode->right_large = x;
	x->parent = snode;
}



void RBT::RB_INSERT_FIXUP(RBNode* z)
{
	
	while (z->parent->color == RED)
	{
		assert((NIL->color == BLACK));
		if (z->parent == z->parent->parent->left_small) //z의 부모가 부모의 부모의 왼쪽자식일때
		{
			RBNode* y = z->parent->parent->right_large;
			if (y->color == RED) //case 1
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				if (z == NIL)
				{
					break;
				}
			}
			else if (z == z->parent->right_large) //case 2
			{
				z = z->parent;
				z->parent->parent->color = RED;// 몬다이
				LEFT_ROTATE(z->parent->parent);
			} //case 3
			z->parent->color = BLACK;
			z->parent->parent->color = RED; // 몬다이
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
				if (z == NIL)
				{
					break;
				}
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

void RBT::RB_DELETE_FIXUP(RBNode* x)
{
	
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





void RBT::INORDER_TREE_WALK(RBNode* x)
{
	if (x != NIL)
	{
		INORDER_TREE_WALK(x->left_small);
		std::cout << x->key << ' ';
		INORDER_TREE_WALK(x->right_large);
	}

}


RBNode* RBT::TREE_SEARCH(RBNode* x, int k)
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


RBNode* RBT::ITERATIVE_TREE_SEARCH(RBNode* x, int k)
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

RBNode* RBT::getter_ROOT() const
{
	
	return ROOT;
}