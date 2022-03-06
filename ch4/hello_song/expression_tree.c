#include <stdlib.h> // malloc, atoi
#include <stdio.h>
#include <ctype.h> // isdigit
#include <assert.h> // assert

#define MAX_STACK_SIZE	50

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{
	char		data;
	struct node	*left;
	struct node	*right;
} NODE;

typedef struct
{
	NODE	*root;
} TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations
static NODE *_makeNode( char );
static void _traverse( NODE *);
static void _infix_print( NODE *, int );
static void _destroy( NODE *);
/* Allocates dynamic memory for a tree head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/

TREE *createTree( void)
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
TREE *destroyTree( TREE *pTree)
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
	if((root->left == NULL) && (root->right == NULL))
	{
		free(root);
		return;
	}
	_destroy(root->left);
	_destroy(root->right);
	free(root);

}

/*  Allocates dynamic memory for a node and returns its address to caller
	return	node pointer
			NULL if overflow
*/
static NODE *_makeNode( char ch)
{
	NODE* node;
	node = (NODE*)malloc(sizeof(NODE));
	if(node)
	{
		node->data = ch;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

NODE* pop(NODE* stack[], int top)
{
	if(stack[top] != NULL)
	{
		NODE* topNode;
		topNode = stack[top];
		stack[top] = NULL;
		return topNode;
	}
	
	return NULL;

}

void push(NODE* stack[], int top, NODE* newNodePtr)
{
	stack[top + 1] = newNodePtr;
}
/* converts postfix expression to binary tree
	return	1 success
			0 invalid postfix expression
*/
int postfix2tree( char *expr, TREE *pTree)
{
	NODE* stack[MAX_STACK_SIZE] = {NULL};
	int top = -1; 
	NODE* newNodePtr;
	NODE* op1;
	NODE* op2;
	
	int check;
	while(*expr)
	{
		check = isdigit(*expr);
		if(check > 0) //숫자이면
		{
			newNodePtr = _makeNode(*expr);
			push(stack, top, newNodePtr);
			top++;
		}
		else if(check == 0) //숫자가 아니면
		{
			if((*expr == '+') || (*expr == '-') || (*expr == '*') || (*expr == '/')) //기호이면
			{
				if(top >= 1)
				{
					newNodePtr = _makeNode(*expr);
					op1 = pop(stack, top);
					top--;
					op2 = pop(stack, top);
					top--;
					newNodePtr->right = op1;
					newNodePtr->left = op2;
					push(stack, top, newNodePtr);
					top++;
				}
				else //underflow
				{
					if(top == 0)
						free(stack[0]);
					free(pTree);
					return 0;
				}
			}
			else
			{
				free(pTree);
				return 0;
			}
		}
		expr++;
	}
	
	if(top == 0)
	{
		pTree->root = stack[top];
		return 1;
	}
	else
	{
		int i = 0;
		while(stack[i] != NULL)
		{
			_destroy(stack[i]);
			i++;
		}
		free(pTree);
		return 0;
	}
}

/* Print node in tree using inorder traversal
*/
void traverseTree(TREE *pTree)
{
	_traverse(pTree->root);
	return;
}

/* internal traversal function
	an implementation of ALGORITHM 6-6
*/
static void _traverse( NODE *root)
{
	NODE* pLoc;
	pLoc = root;
	if(pLoc != NULL)
	{
		if((pLoc->left == NULL) && (pLoc->right == NULL)) //leaf 노드
		{
			printf("%c", pLoc->data);
		}
		else
		{
			printf("(");
			_traverse(pLoc->left);
			printf("%c", pLoc->data);
			_traverse(pLoc->right);
			printf(")");
		}
	}
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
			printf("%c\n", pLoc->data);
		}
		else
		{
			_infix_print(pLoc->right, level);
			for (int i = 0; i < level; i++)
				printf("\t");
			printf("%c\n", pLoc->data);
			_infix_print(pLoc->left, level);
		}
	}	
}

/* evaluate postfix expression
	return	value of expression
*/
float evalPostfix(char *expr)
{
	float stack[MAX_STACK_SIZE];
	int top = -1;
	float op1;
	float op2;
	while(*expr)
	{
		if((*expr == '+') || (*expr == '-') || (*expr == '*') || (*expr == '/'))
		{
			op1 = stack[top];
			top--;
			op2 = stack[top];
			top--;
		}
		switch(*expr)
		{
			case '+':
				stack[top + 1] = op2 + op1;
				top++;
				break;
			case '-':
				stack[top + 1] = op2 - op1;
				top++;
				break;
			case '*':
				stack[top + 1] = op2 * op1;
				top++;
				break;
			case '/':
				stack[top + 1] = op2 / op1;
				top++;
				break;
			default:
				stack[top + 1] = *expr - '0';
				top++;

		}
		expr++;
	}
	return stack[top];
}


////////////////////////////////////////////////////////////////////////////////
/* TREE *destroyTree( TREE *pTree)
{
	if (pTree)
	{
		//_destroy( pTree->root);
	}
		
	free( pTree);
	
	return NULL;	
} */

////////////////////////////////////////////////////////////////////////////////
/* void printTree( TREE *pTree)
{
	//_infix_print(pTree->root, 0);
	
	return;
} */

////////////////////////////////////////////////////////////////////////////////
// void traverseTree( TREE *pTree)
// {
//	_traverse (pTree->root);
	
	// return;
// }

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	TREE *tree;
	char expr[1024];
	
	fprintf( stdout, "\nInput an expression (postfix): ");
	
	while (fscanf( stdin, "%s", expr) == 1)
	{
		// creates a null tree
		tree = createTree();
		
		if (!tree)
		{
			printf( "Cannot create tree\n");
			return 100;
		}
		
		//postfix expression -> expression tree
		int ret = postfix2tree( expr, tree);
		if (!ret)
		{
			fprintf( stdout, "invalid expression!\n");
			continue;
		}
		
		// expression tree -> infix expression
		fprintf( stdout, "\nInfix expression : ");
		traverseTree( tree);
		
		// print tree with right-to-left infix traversal
		fprintf( stdout, "\n\nTree representation:\n");
		printTree(tree);
		
		// evaluate postfix expression
		float val = evalPostfix( expr);
		fprintf( stdout, "\nValue = %f\n", val);
		
		// destroy tree
		destroyTree( tree);
		
		fprintf( stdout, "\nInput an expression (postfix): ");
	}
	return 0;
}
