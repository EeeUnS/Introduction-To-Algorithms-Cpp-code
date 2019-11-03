12.1 What is a binary search tree?



12.2 Querying a binary search tree



12.3 Insertion and deletion



```
NODE
{
    Node* right_large; // key >=
	int key;
	Node* left_small; // key < 
	Node* parent;
}
```
```
    BST();
	BST(int n);
	~BST();

	void preorder();
	void Inorder();
	void postorder();

	Node* TREE_MINIMUM(Node* _node);
	Node* TREE_MAXIMUM(Node* _node);
	Node* TREE_SUCCESSOR(Node* _node);
	Node* TREE_PREDECESSOR(Node* _node);
	void TREE_INSERT(Node* z);
	void TREE_DELETE(Node* _node);

	Node* ROOT;
	Node* NIL;

	void delete_node(Node* _node);
	void TRANSPLANT(Node* u, Node* v);

	void inorder_procedure(Node* _node);
	void preorder_procedure(Node* _node);
	void postorder_procedure(Node* _node);
```

```
BST(int n);
```
n을 키로가지는 루트로 트리를 생성

```
~BST();
```
동적할당 해제

```
void preorder();
void Inorder();
void postorder();

void inorder_procedure(Node* _node);
void preorder_procedure(Node* _node);
void postorder_procedure(Node* _node);
```
전위 중위 후위순회

_procedure각각의 순회에 쓰이는 내부 함수

```
Node* TREE_MINIMUM(Node* _node);
Node* TREE_MAXIMUM(Node* _node);
Node* TREE_SUCCESSOR(Node* _node);
Node* TREE_PREDECESSOR(Node* _node);

```
트리의 가장 작은 값 반환

가장 큰값 반환

직후노드 반환

직전노드 반환
```
void TREE_INSERT(Node* z);
void TREE_DELETE(Node* _node);
```

삽입

삭제




```
void insert(int n);
void delete_node(RBNode* _node);
```
직접만든 삽입 삭제구현