/////////////////////finished/////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////


void moveOddItemsToBack(LinkedList *ll) //odd 홀수 // even 짝수
{
    ListNode *cur = ll->head;
	int originalSize = ll->size;
	int idx = 0,cnt = 0;
	while(cur != NULL && idx+cnt< originalSize){
		if(cur->item % 2 != 0){
			insertNode(ll,ll->size,cur->item);
			cur = cur -> next;
			removeNode(ll,idx);
			cnt++;
		}
		else{
		cur = cur -> next;
		idx++;
		}
	}
    

}



void moveOddItemsToBack_2(LinkedList *ll) //odd 홀수 // even 짝수
{
	
	ListNode *oddHead = NULL;
    ListNode *oddTail = NULL;
    ListNode *evenHead = NULL;
    ListNode *evenTail = NULL;
    ListNode *cur = ll->head;
    
    // 홀수와 짝수 값을 각각의 리스트에 분류
    while (cur != NULL) {
        if (cur->item % 2 == 0) {
            if (evenHead == NULL) {
                evenHead = cur;
                evenTail = cur;
            } else {
                evenTail->next = cur;
                evenTail = evenTail->next;
            }
        } else {
            if (oddHead == NULL) {
                oddHead = cur;
                oddTail = cur;
            } else {
                oddTail->next = cur;
                oddTail = oddTail->next;
            }
        }
        cur = cur->next;
    }
    
    // 짝수 리스트의 끝에 NULL을 추가.
    if (evenTail != NULL) {
        evenTail->next = NULL;
    }
    
    // 홀수 리스트를 짝수 리스트의 끝에 연결
    if (oddHead != NULL) {
        if (evenTail != NULL) {
            evenTail->next = oddHead;
        } else {
            ll->head = oddHead;
        }
    }

}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		printf("asdasdasdasdasdasd");
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}


// 홀수 항목 삭제 시 인덱스 처리 오류:

// 홀수 항목을 발견하면 해당 항목을 리스트의 끝에 추가한 후, 원래 위치에서 삭제합니다. 그러나 cur 포인터를 다음 노드로 이동시킨 후 removeNode 함수를 호출하면, 현재 위치(cur)가 이미 다음 노드로 이동했기 때문에 원하는 노드를 정확하게 삭제하지 못할 수 있습니다.
// 홀수 노드를 삭제할 때 idx를 증가시키지 않습니다. 이는 removeNode 호출 후에 idx가 가리키는 위치가 이미 다음 노드를 가리키고 있기 때문에, 삭제 연산 후에 idx를 증가시키지 않아도 되는 경우입니다. 그러나, 이는 cur 포인터를 다음 노드로 옮기기 전에 노드를 삭제해야만 올바르게 작동합니다.
// 무한 반복의 가능성:

// 홀수 항목을 리스트의 끝에 추가하면, 리스트를 순회하는 동안 새로 추가된 홀수 항목에 대해서도 검사를 하게 됩니다. 이는 새로 추가된 홀수 항목을 계속해서 끝으로 옮기려고 시도하면서 무한 반복에 빠질 위험이 있습니다.