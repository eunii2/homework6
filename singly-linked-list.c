/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

//���Ḯ��Ʈ�� ��� ����ü ����
typedef struct Node {
	int key;
	struct Node* link; //���� ��带 ����Ű�� ������
} listNode;

//���� ����Ʈ�� ��� ����ü ����
typedef struct Head {
	struct Node* first; //ù ��° ��带 ����Ű�� ������
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h); //���� ����Ʈ �ʱ�ȭ �Լ�
int freeList(headNode* h); //���� ����Ʈ �޸� ���� �Լ�

int insertFirst(headNode* h, int key); //����Ʈ ù ��忡 ���� �Լ�
int insertNode(headNode* h, int key); //���ο� ��带 ������ ��ġ�� �����ϴ� �Լ�
int insertLast(headNode* h, int key); //����Ʈ ������ ��忡 ���� �Լ�

int deleteFirst(headNode* h); //����Ʈ ù ��� ���� �Լ�
int deleteNode(headNode* h, int key); //�־��� key ���� ������ ��� ���� �Լ�
int deleteLast(headNode* h); //����Ʈ ������ ��� ���� �Լ�
int invertList(headNode* h); //����Ʈ�� �������� ������ �Լ�

void printList(headNode* h); //����Ʈ�� ����ϴ� �Լ�

int main()
{
	printf("[----- [�ְ���] [2022078054] -----]\n");

	char command;
	int key;
	headNode* headnode=NULL; //���Ḯ��Ʈ�� ��� ��� �ʱ�ȭ

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

		//����ڰ� �Է��� ��ɾ ���� ���Ḯ��Ʈ ���� �Լ� ȣ��
		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); //����Ʈ �ʱ�ȭ
			break;
		case 'p': case 'P':
			printList(headnode); //����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //�־��� key���� ������ ���ο� ��带 ������ ��ġ�� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //�־��� key ���� ������ ��带 ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //����Ʈ �������� ��带 ����
			break;
		case 'e': case 'E':
			deleteLast(headnode); //����Ʈ ������ ��带 ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //����Ʈ ù ��忡 ��带 �����ϴ� �Լ��� ȣ��
			break;
		case 't': case 'T':
			deleteFirst(headnode); //����Ʈ ù ��带 �����ϴ� �Լ��� ȣ��
			break;
		case 'r': case 'R':
			invertList(headnode); //����Ʈ�� �������� ������ �Լ��� ȣ��
			break;
		case 'q': case 'Q':
			freeList(headnode); //����Ʈ �޸𸮸� �����ϴ� �Լ��� ȣ��
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�߸��� ��ɾ� �Է½� ��� �޼����� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); //q �Ǵ� Q�� �Է��� ������ �ݺ����� ����, �׿� ���� ������ �Լ��� ȣ����

	return 1;
}

//����Ʈ�� ��� ��带 �ʱ�ȭ�ϴ� �Լ�
headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

//����Ʈ�� ��� ���� ��� ��鸣 �����ϴ� �Լ�
int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	//���ο� ��� ����
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) //����Ʈ�� ����ִ� ���
	{
		h->first = node; //���ο� ��带 ù ��° ���� ����
		return 0;
	}
	
	//����Ʈ�� Ž���Ͽ� ���� ��ġ�� ã��
	listNode* n = h->first;
	listNode* trail = h->first;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) { //���ο� ��带 ������ ��ġ�� ã�� ���
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { //ù ��° ��� �տ� �����ؾ� �ϴ� ���
				h->first = node;
				node->link = n;
			} else { /* �߰��̰ų� �������� ��� */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node;
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	//listNode �޸� �Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	//�Ҵ�� �޸𸮿� key�� ����
	node->key = key;
	node->link = NULL;

	//headNode�� ����ִٸ�, ù��° ���� �߰�
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}
	//����Ʈ ������ ������ �̵�
	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	//���ο� ��带 ������ ��� ������ �߰�
	n->link = node;
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	//listNode �޸� �Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	//�Ҵ�� �޸𸮿� key�� ����
	node->key = key;

	//���ο� ��带 headNode ������ �߰�
	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	//headNode�� ����ִ� ���
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				h->first = n->link;
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link;
			}
			//��� �޸� ����
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) { //���Ḯ��Ʈ���� ������ ��带 �����ϴ� �Լ�
	//headNode �����Ͱ� ����Ű�� ����Ʈ�� ����ִ� ���
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL;
	free(n);

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) { //���Ḯ��Ʈ���� ù��° ��带 �����ϴ� �Լ�
	//headNode �����Ͱ� ����Ű�� ����Ʈ�� ����ִ� ���
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;
	//first ��带 �����ϰ�, headNode�� first �����͸� ���� ���� ����
	h->first = n->link;
	free(n);

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	//����Ʈ�� ����ִٸ�, ������ ���� �����Ƿ�, �޼��� ��� �� ����
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	// n�� ���� ���, trail�� ���� ����� ���� ���, middle�� ���� ����� ���� ���
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	// ����Ʈ�� ������ ���� �� ��带 �Ųٷ� ����
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	// ������ ����Ʈ�� ù ��° ��带 ����Ʈ�� ù ��° ���� ����
	h->first = middle;

	return 0;
}

//����Ʈ�� ����ϴ� �Լ�
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	// ���� ����Ʈ�� ����ִٸ�, ����� ���� �����Ƿ� �޽����� ����ϰ� ����
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	// ����Ʈ�� �� ��带 ������� ���
	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	// ����Ʈ�� �� ��� ���� ���
	printf("  items = %d\n", i);
}