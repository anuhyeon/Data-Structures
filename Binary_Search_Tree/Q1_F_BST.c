
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode* root)
{
	if(root == NULL){
			return;
		}
		Queue q;
		BSTNode* node;
		q.head = NULL;
		q.tail = NULL;
		enqueue(&(q.head),&(q.tail),root);
		printf("%d      ", root -> item);
		while(!isEmpty(q.head)){
			node = dequeue(&(q.head),&(q.tail));
			printf("%d ",node -> item);
			// 자식 노드가 NULL이 아닐 때만 큐에 추가
			if(node->left != NULL){
				enqueue(&(q.head),&(q.tail),node->left);
			}
			if(node->right != NULL){
				enqueue(&(q.head),&(q.tail),node->right);
			}
		}
		printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

// //단일 포인터를 사용하면 어떻게 되는지 자세히
// void insertBSTNode(BSTNode *node, int value){
// 	if (node == NULL) 
// 	{
// 		node = malloc(sizeof(BSTNode)); 

// 		if (node != NULL) {  
// 			node->item = value;  
// 			node->left = NULL;
// 			node->right = NULL;
// 		}
// 	}
// 	else 
// 	{
// 		if (value < node->item) 
// 		{
// 			insertBSTNode(node->left, value);
// 		}
// 		else if (value > node->item)
// 		{
// 			insertBSTNode(node->right, value);
// 		}
// 		else
// 			return ;
// 	}
// }
// 제시된 코드는 이진 탐색 트리(BST)에 새로운 노드를 삽입하는 함수의 구현을 시도하지만,
// 중요한 문제를 포함하고 있습니다. 문제의 핵심은 함수에 노드 포인터를 직접 전달하면서 발생합니다.
// node 포인터에 대한 변경이 호출한 함수에 반영되지 않기 때문입니다.
// 이는 루트 노드가 NULL일 때 새로운 노드를 할당하려고 할 때 문제가 됩니다.

// 문제의 원인:
// node = malloc(sizeof(BSTNode));
// 이 코드는 node 포인터에 새로운 메모리 주소를 할당합니다. 즉 node 포인터에 메모리 주소 할당한 것이 root 포인터에는 반영이 되지 않음!!!!!!
// 그러나, 이 변경사항은 함수 insertBSTNode의 지역 사본에만 적용됩니다.
// 즉, 함수가 종료되면 이 변경사항은 사라지고, 호출하는 쪽에서는 root 포인터가 여전히 NULL을 가리키게 됩니다.
// 해결 방법:

// 이 문제를 해결하기 위해,
// 포인터의 포인터(BSTNode **node)를 사용하여 함수에 노드의 주소를 전달해야 합니다.
// 이 방법으로, 함수 내에서 노드 포인터 자체를 변경할 수 있으며, 이 변경사항이 함수 호출자에게 반영됩니다.
// 이렇게 변경하면, node 포인터의 주소를 함수에 전달하여, 함수 내에서 *node를 변경하면 호출자에게도 그 변경사항이 반영됩니다.
// 또한, 재귀 호출 시 &((*node)->left) 또는 &((*node)->right)를 사용하여 자식 노드의 주소를 전달함으로써,
// 자식 노드에 새로운 노드를 올바르게 추가할 수 있습니다.
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}