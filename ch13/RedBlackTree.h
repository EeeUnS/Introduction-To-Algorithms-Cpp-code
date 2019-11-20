#ifndef __REDBLACKTREE__
#define __REDBLACKTREE__
#include<cassert>
#include<iostream>

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



//트리 노드의 캡슐화가 보장되지않는다.
class RBT //Red Black tree
{
public:
	RBT();
	RBT(int n);
	~RBT();

	void insert(int n);
	void preorder();//12.1-4
	void Inorder();//12.1-3
	void postorder(); //12.1-4

	RBNode* TREE_MINIMUM(RBNode* x);
	RBNode* TREE_MAXIMUM(RBNode* x);
	RBNode* TREE_SUCCESSOR(RBNode* x);
	RBNode* TREE_PREDECESSOR(RBNode* x);

	void RB_INSERT(RBNode* z);
	void RB_DELETE(RBNode* z);

	void LEFT_ROTATE(RBNode* x);
	void RIGHT_ROTATE(RBNode* x);


	void INORDER_TREE_WALK(RBNode* x);
	RBNode* TREE_SEARCH(RBNode* x, int k);
	RBNode* ITERATIVE_TREE_SEARCH(RBNode* x, int k);


	RBNode* getter_ROOT() const;

private:
	RBNode* ROOT;
	RBNode* NIL;// = { NIL, 0 , NIL,NIL, BLACK };

	void inorder_procedure(RBNode* _RBNode);
	void preorder_procedure(RBNode* _RBNode);
	void postorder_procedure(RBNode* _RBNode);
	void delete_RBNode(RBNode* _RBNode);
	
	void RB_TRANSPLANT(RBNode* u, RBNode* v);
	void RB_INSERT_FIXUP(RBNode* z);
	void RB_DELETE_FIXUP(RBNode* x);
};


#endif