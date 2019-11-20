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


//트리 노드의 캡슐화가 보장되지않는다.
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

	Node* getter_ROOT() const;
private:
	Node* ROOT;
	Node* NIL;

	void inorder_procedure(Node* _node);
	void preorder_procedure(Node* _node);
	void postorder_procedure(Node* _node);
	void delete_node(Node* _node);
	void TRANSPLANT(Node* u, Node* v);

};


#endif