/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

//연결리스트의 노드 구조체 정의
typedef struct Node {
	int key;
	struct Node* link; //다음 노드를 가리키는 포인터
} listNode;

//연결 리스트의 헤드 구조체 정의
typedef struct Head {
	struct Node* first; //첫 번째 노드를 가리키는 포인터
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //연결 리스트 초기화 함수
int freeList(headNode* h); //연결 리스트 메모리 해제 함수

int insertFirst(headNode* h, int key); //리스트 첫 노드에 삽입 함수
int insertNode(headNode* h, int key); //새로운 노드를 적절한 위치에 삽입하는 함수
int insertLast(headNode* h, int key); //리스트 마지막 노드에 삽입 함수

int deleteFirst(headNode* h); //리스트 첫 노드 삭제 함수
int deleteNode(headNode* h, int key); //주어진 key 값을 가지는 노드 삭제 함수
int deleteLast(headNode* h); //리스트 마지막 노드 삭제 함수
int invertList(headNode* h); //리스트를 역순으로 뒤집는 함수

void printList(headNode* h); //리스트를 출력하는 함수

int main()
{
	printf("[----- [최가은] [2022078054] -----]\n");

	char command;
	int key;
	headNode* headnode=NULL; //연결리스트의 헤드 노드 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		//사용자가 입력한 명령어에 따라 연결리스트 관련 함수 호출
		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); //리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode); //리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //주어진 key값을 가지는 새로운 노드를 적절한 위치에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //주어진 key 값을 가지는 노드를 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //리스트 마지막에 노드를 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); //리스트 마지막 노드를 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //리스트 첫 노드에 노드를 삽입하는 함수를 호출
			break;
		case 't': case 'T':
			deleteFirst(headnode); //리스트 첫 노드를 삭제하는 함수를 호출
			break;
		case 'r': case 'R':
			invertList(headnode); //리스트를 역순으로 뒤집는 함수를 호출
			break;
		case 'q': case 'Q':
			freeList(headnode); //리스트 메모리를 해제하는 함수를 호출
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못된 명령어 입력시 경고 메세지를 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //q 또는 Q를 입력할 때까지 반복문을 실행, 그에 따라 적절한 함수를 호출함

	return 1;
}

//리스트의 헤드 노드를 초기화하는 함수
headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

//리스트의 모든 노드와 헤드 노들르 해제하는 함수
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	//새로운 노드 생성
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) //리스트가 비어있는 경우
	{
		h->first = node; //새로운 노드를 첫 번째 노드로 설정
		return 0;
	}
	
	//리스트를 탐색하여 삽입 위치를 찾음
	listNode* n = h->first;
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) { //새로운 노드를 삽입할 위치를 찾은 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //첫 번째 노드 앞에 삽입해야 하는 경우
				h->first = node;
				node->link = n;
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	//listNode 메모리 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	//할당된 메모리에 key값 저장
	node->key = key;
	node->link = NULL;

	//headNode가 비어있다면, 첫번째 노드로 추가
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}
	//리스트 마지막 노드까지 이동
	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	//새로운 노드를 마지막 노드 다음에 추가
	n->link = node;
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	//listNode 메모리 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	//할당된 메모리에 key값 저장
	node->key = key;

	//새로운 노드를 headNode 다음에 추가
	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	//headNode가 비어있는 경우
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			//노드 메모리 해제
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { //연결리스트에서 마지막 노드를 삭제하는 함수
	//headNode 포인터가 가리키는 리스트가 비어있는 경우
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { //연결리스트에서 첫번째 노드를 삭제하는 함수
	//headNode 포인터가 가리키는 리스트가 비어있는 경우
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;
	//first 노드를 삭제하고, headNode의 first 포인터를 다음 노드로 변경
	h->first = n->link;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	//리스트가 비어있다면, 뒤집을 것이 없으므로, 메세지 출력 후 종료
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	// n은 현재 노드, trail은 현재 노드의 이전 노드, middle은 현재 노드의 다음 노드
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	// 리스트를 뒤집기 위해 각 노드를 거꾸로 연결
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	// 뒤집힌 리스트의 첫 번째 노드를 리스트의 첫 번째 노드로 설정
	h->first = middle;

	return 0;
}

//리스트를 출력하는 함수
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	// 만약 리스트가 비어있다면, 출력할 것이 없으므로 메시지를 출력하고 종료
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	// 리스트의 각 노드를 순서대로 출력
	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	// 리스트의 총 노드 수를 출력
	printf("  items = %d\n", i);
}