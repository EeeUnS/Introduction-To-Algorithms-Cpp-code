```
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

```
```
	RBT();
	RBT(int n);
	~RBT();

	RBNode* TREE_MINIMUM(RBNode* _node);
	RBNode* TREE_MAXIMUM(RBNode* _node);
	RBNode* TREE_SUCCESSOR(RBNode* _node);
	RBNode* TREE_PREDECESSOR(RBNode* _node);

	void preorder();
	void Inorder();
	void postorder();
	
	void RB_INSERT(RBNode* z);
	void RB_DELETE(RBNode* z);

	void LEFT_ROTATE(RBNode* _node);
	void RIGHT_ROTATE(RBNode* _node);

	RBNode* ROOT;
	RBNode* NIL;
	
	void inorder_procedure(RBNode* _node);
	void preorder_procedure(RBNode* _node);
	void postorder_procedure(RBNode* _node);

	void delete_node(RBNode* _node);
	void RB_TRANSPLANT(RBNode* u, RBNode* v);
	
	void RB_INSERT_FIXUP(RBNode* z);
	void RB_DELETE_FIXUP(RBNode* x);
```

```
RBT(int n);
```
n을 키로가지는 루트로 트리를 생성

```
~RBT();
```
동적할당 해제
```

void RB_TRANSPLANT(RBNode* u, RBNode* v);
	

void RB_INSERT(RBNode* z);
void RB_DELETE(RBNode* z);


void RB_INSERT_FIXUP(RBNode* z);
void RB_DELETE_FIXUP(RBNode* x);
```
노드대체

삽입

삭제
, 색깔맞추는 내부 프로시져

