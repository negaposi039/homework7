/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { // 노드 구조체
	int key; // key 값
	struct Node* llink; // 이전 노드 주소 포인터
	struct Node* rlink; // 다음 노드 주소 포인터
} listNode;



typedef struct Head { // 헤드 노드 구조체
	struct Node* first; // 리스트의 첫번째 노드 포인터
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); // 동적 할당 해제 함수

int insertNode(headNode* h, int key); // 노드 할당 받아 key보다 큰 값 앞에 삽입 함수
int insertLast(headNode* h, int key); // 리스트 마지막 노드 삽입 함수
int insertFirst(headNode* h, int key); // 리스트 첫번째 노드 삽입 함수
int deleteNode(headNode* h, int key); // key 값에 해당하는 노드 찾아 삭제하는 함수
int deleteLast(headNode* h); // 리스트 마지막 노드 삭제 함수
int deleteFirst(headNode* h); // 리스트 첫번째 노드 삭제 함수
int invertList(headNode* h); // 리스트 역순 재배치 함수

void printList(headNode* h); // 리스트 출력 함수


int main()
{
	char command; // 명령어
	int key; // key 값
	headNode* headnode=NULL; // 헤드노드 NULL 초기화

	do{
		printf("\n[----- [Kim Hyeong Jin]  [2021041079] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': // 메뉴 z
			initialize(&headnode); // 초기화 함수
			break;
		case 'p': case 'P': // 메뉴 p
			printList(headnode); // 리스트 출력 함수
			break;
		case 'i': case 'I': // 메뉴 i
			printf("Your Key = ");
			scanf("%d", &key); // key 입력
			insertNode(headnode, key); // 노드 삽입 함수
			break;
		case 'd': case 'D': // 메뉴 d
			printf("Your Key = ");
			scanf("%d", &key); // key 입력
			deleteNode(headnode, key); // 노드 삭제 함수
			break;
		case 'n': case 'N': // 메뉴 n
			printf("Your Key = ");
			scanf("%d", &key); // key 입력
			insertLast(headnode, key); // 리스트 마지막 노드 삽입 함수
			break;
		case 'e': case 'E': // 메뉴 e
			deleteLast(headnode); // 리스트 마지막 노드 삭제 함수
			break;
		case 'f': case 'F': // 메뉴 f
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // 리스트 첫번째 노드 삽입 함수
			break;
		case 't': case 'T': // 메뉴 t
			deleteFirst(headnode); // 리스트 첫번째 노드 삭제 함수
			break;
		case 'r': case 'R': // 메뉴 r
			invertList(headnode); // 리스트 역순 재배치 함수
			break;
		case 'q': case 'Q': // 메뉴 q
			freeList(headnode); // 리스트 할당 해제 함수
			break;
		default: // 이외의 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 에러 메시지
			break;
		}

	}while(command != 'q' && command != 'Q'); // q 입력시 반복 중지

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) // h가 가리키는 곳의 값이 NULL이 아니면
		freeList(*h); // h가 가리키는 곳의 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); // headnode에 대한 메모리 할당
	(*h)->first = NULL; // NULL 값
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 현재 노드를 가리키는 포인터

	listNode* prev = NULL; // 이전 노드를 가리키는 포인터
	while(p != NULL) { // p가 NULL이 아니면 반복
		prev = p; // prev도 p가 가리키는 노드를 가리키도록 함
		p = p->rlink; // p가 다음 노드를 가리키도록 함
		free(prev); // prev가 가리키는 노드의 메모리 해제
	}
	free(h); // 헤드노드 메모리 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0; // 노드 개수 변수
	listNode* p; // 리스트 노드 포인터

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤드노드가 NULL 이면
		printf("Nothing to print....\n"); // 에러 메시지
		return;
	}

	p = h->first; // p에 첫번째 노드 주소 저장

	while(p != NULL) { // p가 NULL이 아니면 반복
		printf("[ [%d]=%d ] ", i, p->key); // 리스트 번호, key 값 출력
		p = p->rlink; // 다음 노드 이동
		i++; // i 증가
	}

	printf("  items = %d\n", i); // 총 노드 개수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 동적할당
	node->key = key; // node에 key 값 저장
	node->rlink = NULL; // NULL 초기화
	node->llink = NULL; // NULL 초기화

	if (h->first == NULL) // 첫번째 노드가 NULL 이면
	{
		h->first = node; // 리스트의 첫번째 노드를 node로 함
		return 0;
	}

	listNode* n = h->first; // 현재 노드를 가리키는 포인터에 헤드노드가 가리키는 노드 주소 저장
	while(n->rlink != NULL) { // n->rlink가 NULL이 아니면 반복
		n = n->rlink; // 다음 노드로 이동
	}
	n->rlink = node; // n이 가리키는 다음 노드가 node가 되도록함
	node->llink = n; // node의 이전 노드가 n이 가리키는 노드가 되도록 함
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // 헤드노드가 가리키는 노드가 NULL이면
	{
		printf("nothing to delete.\n"); // 에러 메시지
		return 0;
	}

	listNode* n = h->first; // 현재 노드를 가리키는 포인터가 리스트의 첫번째 노드를 가리키도록 함
	listNode* trail = NULL; // trail 포인터 NULL

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { // n->rlink가 NULL 이면
		h->first = NULL; // 헤드노드가 가리키는 노드 NULL
		free(n); // n 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { // n->rlink가 NULL이 아니면
		trail = n; // trail에 n 저장
		n = n->rlink; // n에 n->rlink 저장
	} // 반복하여 마지막 노드까지 이동

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; // n이 가리키는 노드의 rlink에 NULL 저장
	free(n); // n 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 동적 할당
	node->key = key; // node의 key에 key 값 저장
	node->rlink = node->llink = NULL; // node의 다음, 이전 노드 NULL 초기화

	if(h->first == NULL) // 헤드노드가 가리키는 첫번째 노드가 NULL이면
	{
		h->first = node; // h->first에 node 저장
		return 1;
	}

	node->rlink = h->first; // node의 다음 노드가 리스트의 첫번째 노드가 되도록 함
	node->llink = NULL; // node->llink에 NULL 저장

	listNode *p = h->first; // 포인터 p에 헤드노드가 가리키는 노드 저장
	p->llink = node; // p->llink에 node 저장
	h->first = node; // h->first에 node 저장

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // 헤드노드가 가리키는 노드가 NULL이면
	{
		printf("nothing to delete.\n"); // 에러 메시지
		return 0;
	}
	listNode* n = h->first; // 현재노드를 가리키는 포인터에 헤드노드가 가리키는 노드 저장
	h->first = n->rlink; // 헤드노드가 n의 다음 노드를 가리키도록 함

	free(n); // n이 가리키는 노드 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { // 헤드노드가 가리키는 노드가 NULL이면
		printf("nothing to invert...\n"); // 에러 메시지
		return 0;
	}
	listNode *n = h->first; // n이 리스트의 첫번째 노드를 가리키도록 함
	listNode *trail = NULL; // middle 뒤를 따르는 trail 포인터
	listNode *middle = NULL; // n 뒤를 따르는 middle 포인터

	while(n != NULL){ // n이 NULL이 아니면
		trail = middle; // trail에 middle 저장
		middle = n; // middle에 n 저장
		n = n->rlink; // n 다음 노드 이동
		middle->rlink = trail; // middle의 다음 노드에 trail 저장
		middle->llink = n; // middle의 이전 노드에 n 저장
	}

	h->first = middle; // 헤드 노드가 middle이 가리키는 노드를 가리키도록 함.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 할당
	node->key = key; // node의 key에 key 값 저장
	node->llink = node->rlink = NULL; // node 이전, 다음 노드 NULL 초기화

	if (h->first == NULL) // 헤드노드가 가리키는 노드가 NULL이면
	{
		h->first = node; // h->first에 node 저장
		return 0;
	}

	listNode* n = h->first; // 포인터 n에 헤드노드가 가리키는 노드 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { // n == h ->first인 경우
				insertFirst(h, key); // insertFirst 함수 호출
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; // node의 다음 노드가 n이 가리키는 노드가 되도록 함
				node->llink = n->llink; // node의 이전노드가 n의 이전 노드가 되도록 함
				n->llink->rlink = node; // n이 가리키는 노드의 이전노드의 다음 노드가 node가 되도록 함
			}
			return 0;
		}

		n = n->rlink; // n 다음노드 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); // insertLast 함수 호출
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // 헤드노드가 가리키는 노드가 NULL인 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; // 포인터 n에 헤드노드가 가리키는 노드 저장

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); // deleteFirst 함수 호출
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); // deleteLast 함수 호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; // n의 이전노드의 rlink가 n의 다음 노드를 가리키도록 함
				n->rlink->llink = n->llink; // n의 다음노드의 llink가 n의 이전 노드를 가리키도록 함
				free(n);
			}
			return 1;
		}

		n = n->rlink; // n 다음 노드 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); // 에러 메시지
	return 1;
}


