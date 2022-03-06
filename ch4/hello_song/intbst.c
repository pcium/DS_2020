#include <stdlib.h> // malloc, atoi, rand
#include <stdio.h>
#include <ctype.h> // isdigit
#include <assert.h> // assert
#include <time.h> // time

////////////////////////////////////////////////////////////////////////////////
// TREE type definition
typedef struct node
{
	int			data;
	struct node	*left;
	struct node	*right;
} NODE;

typedef struct
{
	NODE	*root;
} TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations
static NODE *_makeNode( int);
static void _traverse( NODE *);
static void _infix_print( NODE *, int);
NODE *_delete( NODE *, int , int *);
int *BST_Retrieve( TREE *, int );
NODE *_retrieve( NODE *, int);
static void _destroy( NODE *);

/* Allocates dynamic memory for a tree head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
TREE *BST_Create( void)
{
	TREE* tree;
	tree = (TREE*)malloc(sizeof(TREE));
	if (tree)
	{
		tree->root = NULL;
	}
	return tree;
}

/* Deletes all data in tree and recycles memory
	return	NULL head pointer
*/
TREE *BST_Destroy( TREE *pTree)
{
	if (pTree)
	{
		_destroy( pTree->root);
	}
		
	free(pTree);
	
	return NULL;		
}
static void _destroy( NODE *root)
{
	if(root)
	{
		_destroy(root->left);
		_destroy(root->right);
		free(root);
	}
	return;
}

/* Inserts new data into the tree
	return	1 success
			0 overflow
*/
int BST_Insert( TREE *pTree, int data) 
{
	NODE* pLoc;
	pLoc = pTree->root;
	NODE* newNodePtr = _makeNode(data);
	if(pTree->root == NULL)
	{
		pTree->root = newNodePtr;
		return 1;
	}
	while(1)
	{	
		if(newNodePtr->data < pLoc->data)
		{
			if(pLoc->left != NULL) //왼쪽에 데이터가 있으면 다시 또 비교하러 가
			{
				pLoc = pLoc->left;		
				continue;				
			}
			else //데이터가 없으면 그 위치에 삽입
			{
				pLoc->left = newNodePtr;
				return 1;
			}
		}
		else
		{
			if(pLoc->right != NULL) //왼쪽에 데이터가 있으면 다시 또 비교하러 가
			{
				pLoc = pLoc->right;		
				continue;				
			}
			else //데이터가 없으면 그 위치에 삽입
			{
				pLoc->right = newNodePtr;
				return 1;
			}
		}
	}
}

static NODE *_makeNode( int data)
{
	NODE* node;
	node = (NODE*)malloc(sizeof(NODE));
	if(node)
	{
		node->data = data;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

/* Deletes a node with dltKey from the tree
	return	1 success
			0 not found
*/
int BST_Delete( TREE *pTree, int dltKey)
{
	int success;
	NODE* newRoot;
	
	newRoot = _delete(pTree->root, dltKey, &success);
	if(success == 1)
	{
		pTree->root = newRoot;
	}
	return success;
}

/* internal function
	success is 1 if deleted; 0 if not
	return	pointer to root
			NULL dltKey not found
*/
NODE *_delete( NODE *root, int dltKey, int *success)
{
	NODE* dltPtr;
	NODE* newRoot;
	NODE* exchPtr;
	int hold;
	
	if(!root) //빈 트리이면
	{
		*success = 0;
		return NULL;
	}
	if(dltKey < root->data) //작으면 왼쪽으로
	{
		root->left = _delete(root->left, dltKey, success);
	}
	else if(dltKey > root->data) //크면 오른쪽으로
	{
		root->right = _delete(root->right, dltKey, success);
	}
	else //지우고자하는 거 찾음
	{
		dltPtr = root;
		if(!root->left) //왼쪽 subtree가 없다면
		{
			newRoot = root->right;
			free(dltPtr);
			*success = 1;
			return newRoot;
		}
		else
		{
			if(!root->right) //왼쪽 subtree는 있고 오른쪽 subtree가 없다면
			{
				newRoot = root->left;
				free(dltPtr);
				*success = 1;
				return newRoot;
			}
			else //자식이 둘다 있는 경우
			{
				exchPtr = root->right;
				while(exchPtr->left)
					exchPtr = exchPtr->left;
				hold = root->data;
				root->data = exchPtr->data;
				exchPtr->data = hold;
				root->right = _delete(root->right, exchPtr->data , success);
				*success = 1;
			}
		}
		return root;
	}
}

/* Retrieve tree for the node containing the requested key
	return	address of data of the node containing the key
			NULL not found
*/
int *BST_Retrieve( TREE *pTree, int key)
{
	NODE* found;
	int* dataLoc;
	found = _retrieve(pTree->root, key);
	if(found == NULL)
		return NULL;
	else
	{
		*dataLoc = found->data;
		return dataLoc;
	}
}

/* internal function
	Retrieve node containing the requested key
	return	address of the node containing the key
			NULL not found
*/
NODE *_retrieve( NODE *root, int key) 
{
	NODE* pLoc;
	pLoc = root;
	
	if(pLoc != NULL)
	{
		if(pLoc->data == key)
		{
			printf("data는 %d\n", pLoc->data);
			return pLoc;
		}
		else
		{
			if(key < pLoc->data)
				_retrieve(pLoc->left, key);
			else
				_retrieve(pLoc->right, key);
		}
	}
	return NULL;
}

/* prints tree using inorder traversal
*/
void BST_Traverse( TREE *pTree)
{
	_traverse(pTree->root);
	return;
}
static void _traverse( NODE *root)
{
	if(root)
	{
		_traverse(root->left);
		printf("%d ", root->data);
		_traverse(root->right);
	}
	return;
}

/* Print tree using inorder right-to-left traversal
*/
void printTree( TREE *pTree)
{
	_infix_print(pTree->root, -1);
	
	return;
}
/* internal traversal function
*/
static void _infix_print( NODE *root, int level)
{
	NODE* pLoc = root;
	if(pLoc != NULL)
	{
		level++;
		if((pLoc->left == NULL) && (pLoc->right == NULL)) //leaf 노드
		{
			for (int i = 0; i < level; i++)
				printf("\t");
			printf("%d\n", pLoc->data);
		}
		else
		{
			_infix_print(pLoc->right, level);
			for (int i = 0; i < level; i++)
				printf("\t");
			printf("%d\n", pLoc->data);
			_infix_print(pLoc->left, level);
		}
	}		
}


////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	TREE *tree;
	int data;
	
	// creates a null tree
	tree = BST_Create();
	
	if (!tree)
	{
		printf( "Cannot create tree\n");
		return 100;
	}

	fprintf( stdout, "Inserting: ");
	
	srand( time(NULL));
	for (int i = 1; i < 20; i++)
	{
		data = rand() % 100 + 1; // 1 ~ 100 random number
		
		fprintf( stdout, "%d ", data);
		
		// insert funtion call
		BST_Insert( tree, data);
 	}
	fprintf( stdout, "\n");
			
	// inorder traversal
	fprintf( stdout, "Inorder traversal: ");
	BST_Traverse( tree);
	fprintf( stdout, "\n");
	
	// print tree with right-to-left infix traversal
	fprintf( stdout, "Tree representation:\n");
	printTree(tree);
	
	int ret;
	do
	{
		fprintf( stdout, "Input a number to delete: "); 
		int num;
		ret = scanf( "%d", &num);
		if (ret != 1) break;
		
		ret = BST_Delete( tree, num);
		if (!ret) fprintf( stdout, "%d not found\n", num);
		
		// print tree with right-to-left infix traversal
		fprintf( stdout, "Tree representation:\n");
		printTree(tree);
		
	} while(1);
	
	BST_Destroy( tree);

	return 0;
}

