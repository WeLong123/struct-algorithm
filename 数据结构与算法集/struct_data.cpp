/*
目的：本文件目的是将所学初等数据结构复现一下，仅供参考
作者：鑨
时间：2026.4.5
介绍：本次数据结构均为手搓，没有涉及到相互封装，在实现过程中最好运用相互封装，本文件仅为“裸展示”因此去除掉了相互封装
学习资料：哔哩大学（最强双非）  船说系列—胡光老师   AI—阿里通义千问
*/
# define _CRT_SECURE_NO_WARNINGS
#include"struct_algorithm.h"
namespace Base_struct{
//-------------------------------------------顺序表
//初始化
Vector* initVector(int size) {
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	vector->data = (int*)malloc(sizeof(int) * size);
	vector->count = 0;
	vector->size = size;
	return vector;
}
//顺序表判满（1为满 0为不满）
int fullVector(Vector* vec) {
	return vec->count == vec->size;
}
//顺序表判空（1为空 0为不空）
int emptyVector(Vector* vec) {
	return vec->count == 0;
}
//顺序表获取大小
int sizeVector(Vector* vec) {
	return vec->count;
}
//顺序表插入
bool insertVector(Vector* vec, int pos, int val) {
	if (vec == NULL || pos<0 || pos>vec->count)return false;
	if (fullVector(vec)) {
		vec->data = (int*)realloc(vec->data, sizeof(int) * 2 * vec->size);
		vec->size *= 2;
	}
	for (int i = vec->count; i > pos; i--) {
		vec->data[i] = vec->data[i - 1];
	}
	vec->count += 1;
	vec->data[pos] = val;
	return true;
}
bool earseVector(Vector* vec, int pos) {
	if (vec == NULL || pos < 0 || pos >= vec->count)return false;
	vec->count--;
	for (int i = pos; i < vec->count; i++) {
		vec->data[i] = vec->data[i + 1];
	}
	return true;
}
//销毁操作
void clearVector(Vector* vec) {
	if (vec == NULL)return;
	free(vec->data);
	free(vec);
	return;
}
//打印顺序表
void PrintVector(Vector* vec) {
	for (int i = 0; i < vec->count; i++) {
		printf("%3d", i);
	}
	printf("\n");
	for (int i = 0; i < vec->count; i++) {
		printf("%3d", vec->data[i]);
	}
	printf("\n");
	return;
}
//查找操作（按照索引）返回值
int seek_PositionVector(Vector* vec, int pos) {
	if (pos < 0 || pos >= vec->count)return -1;
	return vec->data[pos];
}
//查找操作(成功返回下标 失败返回-1）
int seek_ValueVector(Vector* vec, int val) {
	if (vec == NULL)return -1;
	Vector* q = vec;
	for (int i = 0; i < q->count; i++) {
		if (val == q->data[i])return i;
	}
	return -1;
}
//--------------------------------------链表
//初始化链表
NodeList* initNodeList(int val) {
	NodeList* Node = (NodeList*)malloc(sizeof(NodeList));
	Node->val = val;
	Node->next = NULL;
	return Node;
}
//销毁链表
void clearNodeList(NodeList* head) {
	if (head == NULL)return;
	clearNodeList(head->next);
	free(head);
	return;
}
//插入节点
NodeList* insertNodeList(NodeList* head, int pos, int val) {
	if (head == NULL)return head;
	NodeList newhead, * p = &newhead, * q; newhead.next = head;
	for (int i = 0; i < pos; i++) {
		if (p->next == NULL) {
			printf("insert fail\n");
			return head;
		}
		p = p->next;
	}
	q = p->next;
	p->next = initNodeList(val);
	p->next->next = q;
	return newhead.next;
}
//尾插
NodeList* tail_insertNodeList(NodeList* head, int val) {
	NodeList* newnode = initNodeList(val);
	if (newnode == NULL) {
		printf("malloc fail\n");
		return head;
	}
	if (head == NULL)return newnode;
	NodeList* p = head;
	while (p->next != NULL)p = p->next;
	p->next = newnode;
	return head;
}
//头插
NodeList* head_insertNodeList(NodeList* head, int val) {
	NodeList* newnode = initNodeList(val);
	if (newnode == NULL) {
		printf("malloc fail\n");
		return head;
	}
	newnode->next = head;
	return newnode;
}
//删除链表节点
NodeList* earseNodeList(NodeList* head, int pos) {
	if (head == NULL)return head;
	NodeList newhead, * p = &newhead, * q; newhead.next = head;
	for (int i = 0; i < pos; i++) {
		if (p->next == NULL) {
			printf("earseNodeList fail\n");
			return head;
		}
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	free(q);
	return newhead.next;
}
//反转链表
NodeList* reserveNodeList_all(NodeList* head) {
	if (head == NULL || head->next == NULL)return head;
	NodeList* tail = head->next;
	NodeList* newhead = reserveNodeList_all(head->next);
	head->next = tail->next;
	tail->next = head;
	return newhead;
}
//相邻逆置链表（娱乐）
NodeList* reserveNodeList_2_2(NodeList* head) {
	if (head == NULL || head->next == NULL)return head;
	NodeList newhead, * i = &newhead, * j = head, * k = head->next; newhead.next = head;
	while (i->next && i->next->next) {
		j = i->next;
		k = j->next;
		j->next = k->next;
		k->next = j;
		i->next = k;
		i = k;
	}
	return newhead.next;
}
//区间反转链表 就地逆置法（科目一）
NodeList* reserveNodeList1(NodeList* head, int start, int end) {
	if (head == NULL || !(end > start))return head;
	NodeList newhead, * i = &newhead, * j = &newhead, * k = &newhead;
	newhead.next = head;
	for (int t = 0; t < end; t++) {
		k = k->next;
		if (k == NULL) {
			printf("reserveNodeList fail\n");
			return head;
		}
	}
	for (int t = 0; t < start; t++) i = i->next;
	j = i->next;
	i->next = k;
	k = j->next;
	j->next = i->next->next;
	for (int t = 0; t < end - start; t++) {
		i = j;
		j = k;
		k = k->next;
		j->next = i;
	}
	return newhead.next;
}
//反转链表 （头插法LeetCode常用）（科目二）
NodeList* reserveNodeList(NodeList* head, int start, int end) {
	if (head == NULL || !(end > start))return head;
	NodeList newhead, * pre_node, * start_node, * to_move_node; newhead.next = head;
	pre_node = start_node = to_move_node = &newhead;
	for (int i = 0; i < end; i++) {
		to_move_node = to_move_node->next;
		if (to_move_node == NULL) {
			printf("reserveNodeList fail\n");
			return head;
		}
	}
	for (int i = 0; i < start; i++) pre_node = pre_node->next;
	start_node = pre_node->next;
	to_move_node = start_node->next;
	for (int i = 0; i < end - start; i++) {
		start_node->next = to_move_node->next;
		to_move_node->next = start_node;
		pre_node->next = to_move_node;
		to_move_node = start_node->next;
	}
	return newhead.next;
}
//建立循环链表
NodeList* build_cycleNodeList(NodeList* head) {
	if (head == NULL || head->next == NULL)return head;
	NodeList* node = head;
	for (; node->next; node = node->next);
	node->next = head;
	return head;
}
//判断循环链表
bool check_cycleNodeList(NodeList* head) {
	if (head == NULL || head->next == NULL)return false;
	NodeList* slow = head, * fast = head;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)return true;
	}
	return false;
}
//给出循环链表环的大小
int size_cycleNodeList(NodeList* head) {
	if (head == NULL)return 0;
	if (head->next == NULL)return 1;
	NodeList* slow = head, * fast = head;
	int count=0; bool flag = true;
	while (1) {
		if (fast == NULL || fast->next == NULL) { flag = false; break; }
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)break;
	}
	if (flag) {
		do {
			slow = slow->next;
			count++;
		} while (slow != fast);
		return count;
	}
	else return -1;
}
//给出循环链表整个的大小(floyd算法）
int size_allcycleNodeList(NodeList* head) {
	if (head == NULL)return 0;
	if (head->next == NULL)return 1;
	NodeList* slow = head, * fast = head;
	int count = 0; bool flag = true;
	while (1) {
		if (fast == NULL || fast->next == NULL) {
			flag = false;
			break;
		}
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) break;
	}
	if (flag == false) {
		printf("size_allcycleNodeList fail\n");
		return -1;
	}
	slow = head;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
		count++;
	}
	do {
		slow = slow->next;
		count++;
	} while (slow != fast);
	return count;
}
//打印循环链表的全部
void print_cycleNodeList(NodeList* head) {
	if (head == NULL)return;
	if (head->next == NULL) {
		printf("%d", head->val);
		return;
	}
	NodeList* slow = head, * fast = head;
	while (1) {
		if (fast == NULL || fast->next == NULL) {
			printf("no cycleNodeList\n");
			return;
		}
		printf("%d", slow->val);
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)break;
	}
	do {
		slow = slow->next;
		printf("%d", slow->val);
	} while (slow->next != fast);
	return;
}
//打印链表
void PrintNodeList(NodeList* head) {
	if (head == NULL)return;
	int count = 0; NodeList* node = head;
	for (; node; node = node->next)++count;
	for (int i = 0; i < count; i++)printf("%3d  ", i);
	printf("\n");
	for (node = head; node; node = node->next) {
		printf("%3d", node->val);
		if (node->next)printf("->");
	}
	printf("\n");
	return;
}
//-----------------------------队列
//队列初始化
Queue* initQueue(int size) {
	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->count = que->head = que->tail = 0;
	que->size = size;
	que->data = (int*)malloc(sizeof(int) * size);
	return que;
}
//队列销毁
void clearQueue(Queue* que) {
	free(que->data);
	free(que);
	return;
}
//队列判空
int emptyQueue(Queue* que) {
	return que->count == 0;
}
//队列判满
int fullQueue(Queue* que) {
	return que->count == que->size;
}
//入队
bool pushQueue(Queue* que, int val) {
	if (que == NULL||fullQueue(que))return false;
	que->data[que->tail++] = val;
	que->count++;
	if (que->tail == que->size)que->tail = 0;
	return true;
}
//出队
bool popQueue(Queue* que) {
	if (que == NULL || emptyQueue(que))return false;
	que->head++;
	que->count--;
	if (que->head == que->size)que->head = 0;
	return true;
}
//队首元素
int frontQueue(Queue* que) {
	return que->data[que->head];
}
//队的大小
int sizeQueue(Queue* que) {
	return que->size;
}
//打印队列
void PrintQueue(Queue* que) {
	for (int i = 0; i < que->count; i++)printf("%3d", i);
	printf("\n");
	for (int i = 0; i < que->count; i++) {
		printf("%3d", que->data[(que->head + i) % que->size]);
	}
	printf("\n");
	return;
}
//-----------------------------栈
//初始化栈
Stack* initStack(int size) {
	Stack* s = (Stack*)malloc(sizeof(Stack) * (size));
	s->data = (int*)malloc(sizeof(int));
	s->top = -1;
	s->size = size;
	return s;
}
//入栈
Stack* pushStack(Stack* sta, int val) {
	if (sta == NULL)return sta;
	Stack* s = sta;
	if (s->top == s->size) {
		int* temp = (int*)realloc(s->data, sizeof(int) * (s->size) * 2);
		if (temp == NULL) {
			perror("开辟失败");
			exit(-1);
		}
		s->data = temp;
		s->size *= 2;
	}
	s->data[++s->top] = val;
	return s;
}
//出栈
bool popStack(Stack* sta) {
	if (sta == NULL || sta->top == -1)return false;
	sta->top--;
	return true;
}
//显示栈顶元素
int frontStack(Stack* sta) {
	if (sta == NULL || sta->top == -1)return -1;
	return sta->data[sta->top];
}
//销毁栈
void clearStack(Stack* sta) {
	if (sta == NULL)return;
	free(sta->data);
	free(sta);
	return;
}
//打印栈
void Prints(Stack* sta) {
	if (sta == NULL || sta->top == -1)return;
	int n = sta->top;
	for (int i = 0; i <= sta->top; i++) {
		printf("%3d", i);
	}
	printf("\n");
	for (size_t i = 0; i <= sta->top; i++) {
		printf("%3d", sta->data[i]);
	}
	printf("\n");
	return;
}
//------------------------------------------------二叉树
//树的生成
TreeNode* initTree(int val) {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->val = val;
	root->ltag = root->rtag = 0;
	root->left = root->right = NULL;
	return root;
}
//树的清除
void clearTree(TreeNode* root) {
	if (root == NULL)return;
	if (root->left)clearTree(root->left);
	if (root->right)clearTree(root->right);
	free(root);
	return;
}
//随机树的生成
TreeNode* randomTree(int count) {
	TreeNode* __randomTree(TreeNode*);
	TreeNode* root = NULL;
	for (int i = 0; i < count; i++) {
		root = __randomTree(root);
	}
	return root;
}
TreeNode* __randomTree(TreeNode* root) {
	if (root == NULL)return initTree(rand() % 1000);
	else {
		if (rand() % 2) root->left = __randomTree(root->left);
		else root->right = __randomTree(root->right);
	}
	return root;
}
//树的广度优先搜索（层序遍历）
void bfs(TreeNode* root, int count) {
	if (root == NULL)return;
	TreeNode** Queue = (TreeNode**)calloc(count + 1, sizeof(TreeNode*));//注意不要使用malloc，因为无法初始化为0
	int t = 0;//Queue的索引
	Queue[t++] = root;
	for (int i = 0; Queue[i]; i++) {
		root = Queue[i];
		printf("root->val=%d\n", root->val);
		if (root->left) {
			Queue[t++] = root->left;
			printf("\troot->left:%d\n", root->left->val);
		}
		else {
			printf("\troot->left:NULL\n");
		}
		if (root->right) {
			Queue[t++] = root->right;
			printf("\troot->right:%d\n", root->right->val);
		}
		else {
			printf("\troot->right:NULL\n");
		}
	}
	free(Queue);
	return;
}
//树的深度优先搜索
void dfs(TreeNode* root) {
	int tot = -1;
	__dfs(root, &tot);
	return;
}
void __dfs(TreeNode* root, int* tot) {
	if (root == NULL)return;
	int start, end;
	*tot += 1; start = *tot;
	if (root->left)__dfs(root->left, tot);
	if (root->right)__dfs(root->right, tot);
	*tot += 1; end = *tot;
	printf("Node:%d  [%d,%d]\n", root->val, start, end);
	return;
}
//树的前序遍历
void preOrder(TreeNode* root) {
	if (root == NULL) {
		printf("root is NULL\n");
		return;
	}
	printf("The result of preorder:");
	__preOrder(root);
	printf("\n");
	return;
}
void __preOrder(TreeNode* root) {
	if (root == NULL)return;
	printf("%d ", root->val);
	if (root->left)__preOrder(root->left);
	if (root->right)__preOrder(root->right);
	return;
}
//树的中序遍历
void inOrder(TreeNode* root) {
	if (root == NULL) {
		printf("root is NULL\n");
		return;
	}
	printf("The result of inorder:");
	__inOrder(root);
	printf("\n");
	return;
}
void __inOrder(TreeNode* root) {
	if (root == NULL)return;
	if (root->left)__inOrder(root->left);
	printf("%d ", root->val);
	if (root->right)__inOrder(root->right);
	return;
}
//树的后序遍历
void postOrder(TreeNode* root) {
	if (root == NULL) {
		printf("root is NULL\n");
		return;
	}
	printf("The result of postOrder:");
	__postOrder(root);
	printf("\n");
	return;
}
void __postOrder(TreeNode* root) {
	if (root == NULL)return;
	if (root->left)__postOrder(root->left);
	if (root->right)__postOrder(root->right);
	printf("%d ", root->val);
	return;
}
//树的线索化(中序遍历）
void tagTree(TreeNode* root) {
	if (root == NULL)return;
	TreeNode* preroot = NULL;
	__tagTree(root, &preroot);
	preroot->right = NULL;
	preroot->rtag = 1;
	return;
}
void __tagTree(TreeNode* root, TreeNode** preroot) {
	if (root == NULL)return;
	if (root->left)__tagTree(root->left, preroot);

	if (root->left == NULL) {
		root->ltag = 1;
		root->left = *preroot;
	}
	if (*preroot && (*preroot)->right == NULL) {
		(*preroot)->rtag = 1;
		(*preroot)->right = root;
	}
	*preroot = root;

	if (root->right)__tagTree(root->right, preroot);
	return;
}
//树的遍历（迭代）
void tagVerseTree(TreeNode* root) {
	void __tagVerseTree(TreeNode * root);
	while (root->ltag == 0)root = root->left;
	printf("The result of tag Verse:");
	__tagVerseTree(root);
	printf("\n");
	return;
}
void __tagVerseTree(TreeNode* root) {
	while (root) {
		if (root->rtag == 1) {
			printf("%d ", root->val);
			root = root->right;
			continue;
		}
		printf("%d ", root->val);
		root = root->right;
		while (root->ltag == 0)root = root->left;
	}
	return;
}
//树的清除（线索版）
void clearTagTree(TreeNode* root) {
	if (root == NULL)return;
	if (root->ltag == 0)clearTagTree(root->left);
	if (root->rtag == 0)clearTagTree(root->right);
	free(root);
}
//树的前中后序遍历（线索版）
void tagPreOrder(TreeNode* root) {
	void __tagPreOrder(TreeNode*);
	if (root == NULL) {
		printf("root is NULL\n");
		return;
	}
	printf("The result of tagPre:");
	__tagPreOrder(root);
	printf("\n");
	return;
}
void __tagPreOrder(TreeNode* root) {
	if (root == NULL)return;
	printf("%d ", root->val);
	if (root->ltag == 0)__tagPreOrder(root->left);
	if (root->rtag == 0)__tagPreOrder(root->right);
	return;
}
void tagInOrder(TreeNode* root) {
	void __tagInOrder(TreeNode*);
	if (root == NULL) {
		printf("root is NULL\n");
		return;
	}
	printf("The result of tagIn:");
	__tagInOrder(root);
	printf("\n");
	return;
}
void __tagInOrder(TreeNode* root) {
	if (root == NULL)return;
	if (root->ltag == 0)__tagInOrder(root->left);
	printf("%d ", root->val);
	if (root->rtag == 0)__tagInOrder(root->right);
	return;
}
void tagPostOrder(TreeNode* root) {
	void __tagPostOrder(TreeNode*);
	if (root == NULL) {
		printf("root is NULL\n");
		return;
	}
	printf("The result of tagIn:");
	__tagPostOrder(root);
	printf("\n");
	return;
}
void __tagPostOrder(TreeNode* root) {
	if (root == NULL)return;
	if (root->ltag == 0)__tagPostOrder(root->left);
	if (root->rtag == 0)__tagPostOrder(root->right);
	printf("%d ", root->val);
	return;
}
//广义表编码
char* GeneralCode(TreeNode* root, char destination[]) {
	if (root == NULL)return NULL;
	int len = 0;
	__GeneralCode(root, destination, &len);
	return destination;
}
void __GeneralCode(TreeNode* root, char buff[], int* len) {
	if (root == NULL)return;
	*len += sprintf(buff + *len, "%d", root->val);
	if (root->left == NULL && root->right == NULL)return;
	buff[(*len)++] = '(';
	if (root->left) {
		__GeneralCode(root->left, buff, len);
	}
	buff[(*len)++] = ',';
	if (root->right) {
		__GeneralCode(root->right, buff, len);
	}
	buff[(*len)++] = ')';
	return;
}
//广义表解码
/*
关键字 建立新节点,并建立其与根的关系
"(" 新节点进栈  子树标志转换为左
"," 子树标志转换为右
")" 出栈
*/
TreeNode* antiGeneralCode(char buff[], int count) {
	int len = 0, scode = 0, addResult = 0, flag = 0;//flag默认为0，0为左，1为右
	TreeNode* tempNode = NULL;
	TreeNode** stack = (TreeNode**)malloc(sizeof(TreeNode*) * (count + 1)); int top = -1;
	for (int i = 0; buff[i];) {
		switch (scode) {
		case 0:
			if (buff[i] <= '9' && buff[i] >= '0')scode = 1;
			else if (buff[i] == '(')scode = 2;
			else if (buff[i] == ',')scode = 3;
			else scode = 4;
			break;
		case 1:
			addResult = 0;
			while (buff[i] <= '9' && buff[i] >= '0') {
				addResult = addResult * 10 + buff[i] - '0';
				i += 1;
			}
			tempNode = initTree(addResult);
			if (flag && top >= 0)stack[top]->right = tempNode;
			else if (top >= 0)stack[top]->left = tempNode;
			scode = 0;
			break;
		case 2:
			stack[++top] = tempNode;
			flag = 0;
			i++; scode = 0;
			break;
		case 3:
			flag = 1;
			i++; scode = 0;
			break;
		case 4:
			top--; flag = 0; i++;
			scode = 0;
			break;
		}
	}
	return stack[0];
}
//哈夫曼编码
HaffTree* initHaffTree(int fre, char character) {
	HaffTree* root = (HaffTree*)malloc(sizeof(HaffTree));
	root->character = character;
	root->fre = fre;
	root->left = root->right = NULL;
	return root;
}
HaffTree* haffmanCode(char Data[][100], int count, char Result[][100]) {
	void anti_HaffmanCode(HaffTree * root, int count, char Result[128][100], char buff[100], int k);
	if (Data == NULL || count == 0)return NULL;
	HaffTree** Queue = (HaffTree**)malloc(sizeof(HaffTree*) * (count + 1));
	for (int i = 0; i < count; i++) {
		Queue[i] = (HaffTree*)malloc(sizeof(HaffTree));
		Queue[i] = initHaffTree(strtol(Data[i] + 1, NULL, 10), Data[i][0]);
	}
	for (int i = 0; i < count - 1; i++) {
		HaffTree* temp = NULL; int min = 0;
		for (int j = 0; j < (count - i); j++) {
			if (Queue[min]->fre > Queue[j]->fre)min = j;
		}
		temp = Queue[min];
		Queue[min] = Queue[count - 1 - i];
		Queue[count - 1 - i] = temp;
		min = 0;
		for (int j = 0; j < (count - i - 1); j++) {
			if (Queue[min]->fre > Queue[j]->fre)min = j;
		}
		temp = Queue[min];
		Queue[min] = Queue[count - i - 2];
		Queue[count - i - 2] = temp;
		HaffTree* Node = initHaffTree(Queue[count - 1 - i]->fre + Queue[count - i - 2]->fre, NULL);
		Node->left = Queue[count - i - 1];
		Node->right = Queue[count - i - 2];
		Queue[count - i - 2] = Node;
	}
	char buff[100] = { 0 };
	anti_HaffmanCode(Queue[0], count, Result, buff, 0);
	return Queue[0];
}
void anti_HaffmanCode(HaffTree* root, int count, char Result[128][100], char buff[100], int k) {
	if (root == NULL)return;
	if (isgraph(root->character)) {
		Result[root->character][0] = root->character;
		for (int i = 0; i < k; i++)Result[root->character][i + 1] = buff[i];
		return;
	}
	buff[k] = '0';
	anti_HaffmanCode(root->left, count, Result, buff, k + 1);
	buff[k] = '1';
	anti_HaffmanCode(root->right, count, Result, buff, k + 1);
	return;
}
void PrintHaffman(char Result[128][100]) {
	printf("\n\n");
	for (int i = 0; i < 128; i++) {
		if (*Result[i])printf("%c:%s\n", Result[i][0], Result[i] + 1);
	}
	return;
}
//反转二叉树
void reserveTree(TreeNode* root) {
	if (root == NULL)return;
	if (root->left)reserveTree(root->left);
	if (root->right)reserveTree(root->right);
	TreeNode* temp = root->left;
	root->left = root->right;
	root->right = temp;
	return;
}
//判断子树是否是主树的子结构
bool match_one_node(TreeNode* Tree, TreeNode* subTree) {
	if (subTree == NULL)return true;
	if (Tree == NULL)return false;
	if (Tree->val != subTree->val)return false;
	return match_one_node(Tree->left, subTree->left) && match_one_node(Tree->right, subTree->right);
}
bool compareTreeAndSubTree(TreeNode* Tree, TreeNode* subTree) {
	if (Tree == NULL || subTree == NULL)return false;
	if (Tree->val == subTree->val && match_one_node(Tree, subTree))return true;
	if (compareTreeAndSubTree(Tree->left, subTree))return true;
	if (compareTreeAndSubTree(Tree->right, subTree))return true;
	return false;
}
//------------------------------------堆
Heap* initHeap(int size) {
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->__data = (int*)malloc(sizeof(int) * (size + 1));
	h->data = h->__data - 1;
	h->count = 0;
	h->size = size;
	return h;
}
void clearHeap(Heap* h) {
	free(h->__data);
	free(h);
	return;
}
void swap_arr(int* arr, int index1, int index2) {
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
	return;
}
void up_update_small(int* data, int index) {
	while (FATHER(index) >= 1 && data[index] < data[FATHER(index)]) {
		swap_arr(data, index, FATHER(index));
		index = FATHER(index);
	}
	return;
}
void down_update_small(int* data, int index, int len) {
	while (LEFT(index) <= len) {
		int ind = index, l = LEFT(index), r = RIGHT(index);
		if (data[ind] > data[LEFT(ind)])ind = l;
		if (r <= len && data[ind] > data[RIGHT(ind)])ind = r;
		if (ind == index)break;
		swap_arr(data, index, ind);
		index = ind;
	}
	return;
}
void up_update_large(int* data, int index) {
	while (FATHER(index) >= 1 && data[index] > data[FATHER(index)]) {
		swap_arr(data, index, FATHER(index));
		index = FATHER(index);
	}
	return;
}
void down_update_large(int* data, int index, int len) {
	while (LEFT(index) <= len) {
		int ind = index, l = LEFT(index), r = RIGHT(index);
		if (data[ind] < data[LEFT(ind)])ind = l;
		if (r <= len && data[ind] < data[RIGHT(ind)])ind = r;
		if (ind == index)break;
		swap_arr(data, index, ind);
		index = ind;
	}
	return;
}
int fullHeap(Heap* heap) {
	return heap->count == heap->size;
}
int emptyHeap(Heap* heap) {
	return heap->count == 0;
}
void pushHeap_small(Heap* heap, int val) {
	if (fullHeap(heap)) {
		heap->__data = (int*)realloc(heap->__data, heap->size * 2 * sizeof(int));
		heap->size *= 2;
		heap->data = heap->__data - 1;
	}
	heap->data[++heap->count] = val;
	up_update_small(heap->data, heap->count);
	return;
}
void pushHeap_large(Heap* heap, int val) {
	if (fullHeap(heap)) {
		heap->__data = (int*)realloc(heap->__data, heap->size * 2 * sizeof(int));
		heap->size *= 2;
		heap->data = heap->__data - 1;
	}
	heap->data[++heap->count] = val;
	up_update_large(heap->data, heap->count);
	return;
}
void popHeap_small(Heap* heap) {
	if (emptyHeap(heap)) {
		printf("popHeap_small fail\n");
		return;
	}
	heap->data[1] = heap->data[heap->count--];
	down_update_small(heap->data, 1, heap->count);
	return;
}
void popHeap_large(Heap* heap) {
	if (emptyHeap(heap)) {
		printf("popHeap_large fail\n");
		return;
	}
	heap->data[1] = heap->data[heap->count--];
	down_update_large(heap->data, 1, heap->count);
	return;
}
int frontHeap(Heap* heap) {
	if (emptyHeap(heap))return -1;
	return heap->data[1];
}
void linearHeap_small(int* arr, int len) {
	for (int i = len / 2; i >= 1; i--) {
		down_update_small(arr, i, len);
	}
	return;
}
void linearHeap_large(int* arr, int len) {
	for (int i = len / 2; i >= 1; i--) {
		down_update_large(arr, i, len);
	}
	return;
}
void PrintHeap(Heap* heap) {
	printf("Heap:");
	for (int i = 1; i <= heap->count; i++) {
		printf("%3d", heap->data[i]);
	}
	printf("\n");
	return;
}
/*
//------------哈夫曼编码(改进版）
typedef struct HeapTree {
	struct HeapTree* left, * right;
	int fre;
	char ch;
}HeapTree;
typedef struct Heap {
	HeapTree** __data, ** data;
	int size, count;
};
HeapTree* initHeapTree(int fre, char ch) {
	HeapTree* root = (HeapTree*)malloc(sizeof(HeapTree));
	root->left = root->right = NULL;
	root->fre = fre;
	root->ch = ch;
	return root;
}
void clearHeapTree(HeapTree* root) {
	if (root == NULL)return;
	clearHeapTree(root->left);
	clearHeapTree(root->right);
	free(root);
	return;
}
Heap* initHeap(int size) {
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->__data = (HeapTree**)malloc(sizeof(HeapTree*)*size);
	h->data = h->__data - 1;
	h->count = 0;
	h->size = size;
	return h;
}
int emptyHeap(Heap* h) {
	return h->count == 0;
}
int fullHeap(Heap* h) {
	return h->size == h->count;
}
HeapTree* frontHeap(Heap* h) {
	if (!emptyHeap(h))return h->data[1];
}
void swapHeap(Heap* h, int index1,int index2) {
	HeapTree* temp = h->data[index1];
	h->data[index1] = h->data[index2];
	h->data[index2] = temp;
	return;
}
void up_updatehaff(Heap* h, int index) {
	while (FATHER(index) >= 1&&h->data[index]->fre>h->data[FATHER(index)]->fre) {
		swapHeap(h, index, FATHER(index));
		index = FATHER(index);
	}
	return;
}
void down_updatehaff(Heap* h,int index) {
	while (LEFT(index) <= h->count) {
		int ind = index, l = LEFT(index), r = RIGHT(index);
		if (h->data[ind]->fre > h->data[l]->fre)ind = l;
		if (r <= h->count && h->data[ind]->fre > h->data[r]->fre)ind = r;
		if (index == ind)break;
		swapHeap(h, ind, index);
		index = ind;
	}
	return;
}
int popHeap(Heap* h) {
	if (emptyHeap(h))return 0;
	h->data[1] = h->data[h->count--];
	down_updatehaff(h, 1);
	return 1;
}
int pushHeap(Heap* h,HeapTree*root) {
	if (fullHeap(h))return 0;
	h->data[++h->count] = root;
	up_updatehaff(h, h->count);
	return 1;
}
HeapTree* haffmanTree_build(Heap*h) {
	int count = h->count;
	for (int i = 1; i < count; i++) {
		HeapTree* node1 = frontHeap(h);
		popHeap(h);
		HeapTree* node2 = frontHeap(h);
		popHeap(h);
		HeapTree* node3 = initHeapTree(node1->fre + node2->fre, NULL);
		node3->left = node1; node3->right = node2;
		pushHeap(h, node3);
	}
	return frontHeap(h);
}
void __antiHaffmanCode(HeapTree* root, char buff[128][100],char result[], int k) {
	if (root == NULL)return;
	if (isalpha(root->ch)) {
		buff[root->ch][0] = root->ch;
		buff[root->ch][1] = 32;
		strcat(buff[root->ch], result);
		return;
	}
	result[k] = '1';
	__antiHaffmanCode(root->left, buff,result, k + 1);
	result[k] = '0';
	__antiHaffmanCode(root->right, buff,result, k + 1);
	return;
}
void antiHaffmanCode(HeapTree* root,char buff[128][100]) {
	if (root == NULL)return;
	char result[100] = { 0 };
	__antiHaffmanCode(root, buff, result, 0);
}*/
}
namespace SkipList_ {
	//------------------------跳跃表
	//构造函数编写
	Node::Node(int val, int level) :val(val), level(level) {
		up = down = next = NULL;
	}
	//析构函数编写
	Node::~Node() {}
	//获得随机数
	int SkipList::getRandomLevel() {
#define DESIDE 1.0/2.0
		int ret = 1;
		while (1) {
			if (ret < MAX_LEVEL && getRandomDouble() >= DESIDE)ret++;
			else break;
		}
		return ret;
#undef DESIDE
	}
	double SkipList::getRandomDouble() {
		return (rand() % 10000 * 1.0) / 10000;
	}
	void SkipList::getMaxLevel()
	{
		Node* temp = head;
		while (temp) {
			if (temp->next->val != tail->val) { Node_max_level = temp->next->level; return; }
			else temp = temp->down;
		}
		return;
	}
	//编写构造函数
	SkipList::SkipList() {
		Node_max_level = 0;
		max_level = MAX_LEVEL;
		std::vector<Node*>arr_head(max_level);
		std::vector<Node*>arr_tail(max_level);
		for (int i = 0; i < max_level; i++) {
			arr_head[i] = new Node(INT32_MIN, i + 1);
			arr_tail[i] = new Node(INT32_MAX, i + 1);
		}
		for (int i = 0; i < max_level; i++) {
			if (i) {
				arr_head[i]->down = arr_head[i - 1];
				arr_tail[i]->down = arr_tail[i - 1];
			}
			else {
				arr_head[i]->down = NULL;
				arr_tail[i]->down = NULL;
			}
			if (i != max_level - 1) {
				arr_head[i]->up = arr_head[i + 1];
				arr_tail[i]->up = arr_tail[i + 1];
			}
			else {
				arr_head[i]->up = NULL;
				arr_tail[i]->up = NULL;
			}
			arr_head[i]->next = arr_tail[i];
		}
		head = arr_head[max_level - 1];
		tail = arr_tail[max_level - 1];
	}
	//编写析构函数
	SkipList::~SkipList() {
		Node* p = head, * q;
		for (int i = 0; i < max_level; i++) {
			q = p;
			p = p->down;
			while (q) {
				Node* temp = q->next;
				delete q;
				q = temp;
			}
		}
	}
	//编写查找函数
	Node* SkipList::find(int val) {
		Node* temp = head;
		while (temp) {
			if (temp->next->val == val)return temp->next;
			else if (temp->next->val < val)temp = temp->next;
			else temp = temp->down;
		}
		return NULL;
	}
	//插入
	bool SkipList::insert(int val) {
		Node* temp = head;
		int newLevel = getRandomLevel();
		Node* newNode = NULL, * p;
		std::vector<Node*>arr(newLevel);
		for (int i = 0; i < newLevel; i++) {
			arr[i] = new Node(val, i + 1);
		}
		for (int i = 0; i < newLevel; i++) {
			if (i)arr[i]->down = arr[i - 1];
			else arr[i]->down = NULL;
			if (i != newLevel - 1)arr[i]->up = arr[i + 1];
			else arr[i]->up = NULL;
		}
		newNode = arr[newLevel - 1];
		p = newNode;
		for (; temp->level != newNode->level; temp = temp->down);
		while (temp) {
			if (temp->next->val == p->val)return false;
			else if (temp->next->val > p->val) {
				p->next = temp->next;
				temp->next = p;
				p = p->down;
				temp = temp->down;
			}
			else {
				temp = temp->next;
			}
		}
		if (newLevel > Node_max_level)Node_max_level = newLevel;
		return true;
	}
	//输出
	void SkipList::output() {
		int len = 0;
		Node* p = head;
		for (; p->down; p = p->down);
		for (int i = 0; i < Node_max_level; i++) {
			len += printf("%4d", i + 1);
		}
		std::cout << '\n';
		for (int i = 0; i < len; i++) {
			printf("-");
		}
		std::cout << '\n';
		p = p->next;
		for (; p->val != INT32_MAX; p = p->next) {
			Node* temp = p;
			while (temp) {
				printf("%4d", temp->val);
				temp = temp->up;
			}
			std::cout << std::endl;
		}
	}
	//删除
	void SkipList::erase(int val)
	{
		int delete_level = 0;
		Node* temp_head = head;
		while (temp_head) {
			if (temp_head->next->val > val)temp_head = temp_head->down;
			else if (temp_head->next->val < val)temp_head = temp_head->next;
			else {
				if (!delete_level)delete_level = temp_head->next->level;
				Node* to_delete_node = temp_head->next;
				temp_head->next = temp_head->next->next;
				delete to_delete_node;
				temp_head = temp_head->down;
			}
		}
		if (delete_level == Node_max_level)getMaxLevel();
	}
}
//--------------------------------哈希表
namespace HashList_ {
	//初始化哈希节点
	Node* initNode(char* string ) {
		Node* p = (Node*)malloc(sizeof(Node));
		p->next = NULL;
		p->str = _strdup(string);
		return p;
	}
	//初始化哈希表
	HashList* initHashList(int size) {
		HashList* h = (HashList*)malloc(sizeof(HashList));
		h->arr = (Node*)malloc(sizeof(Node) * size);
		for (int i = 0; i < size; i++) {
			h->arr[i].next = NULL;
			h->arr[i].str = NULL;
		}
		h->count = 0;
		h->size = size;
		return h;
	}
	//销毁节点
	void clearNode(Node* node) {
		Node* to_delete;
		while (node) {
			to_delete = node->next;
			free(node);
			node = to_delete;
		}
	}
	//销毁哈希表
	void clearHashList(HashList* h) {
		for (int i = 0; i < h->size; i++) {
			Node* to_delete = h->arr[i].next;
			if (to_delete)clearNode(to_delete);
		}
		free(h->arr);
	}
	//哈希函数
	int Hash_function(char* str) {
		int seed = 131, h = 0;
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			h = h * seed + str[i];
		}
		return h & 0x7fffffff;
	}
	//插入
	bool insertHashList(HashList* h, char* des) {
		if (h->count * 2 >= h->size)expandHashList(h);
		int index = Hash_function(des) % h->size;
		Node* p = initNode(des);
		Node* temp = h->arr[index].next;
		while (temp) {
			Node* p = temp->next;
			int len1 = strlen(des), len2 = strlen(temp->str);
			if (len1 != len2)goto loop;
			for (int i = 0; i < len1; i++) {
				if (des[i] != temp->str[i])goto loop;
			}
			return false;
		loop:temp = p;
		}
		p->next = h->arr[index].next;
		h->arr[index].next = p;
		h->count++;
		return true;
	}
	//查找
	bool findHashList(HashList* h, char* des) {
		int index = Hash_function(des) % h->size;
		Node* to_find = h->arr[index].next;
		if (to_find == NULL)return false;
		while (to_find) {
			Node* p = to_find->next;
			int len1 = strlen(to_find->str), len2 = strlen(des);
			if (len1 != len2)goto loop;
			for (int i = 0; i < len1; i++) {
				if (des[i] != to_find->str[i])goto loop;
			}
			return true;
		loop:to_find = p;
		}
		return false;
	}
	//扩容
	void expandHashList(HashList* h) {
		Node* temp_arr = (Node*)malloc(sizeof(Node) * h->size * 2);
		for (int i = 0; i < h->size * 2; i++) {
			temp_arr[i].next = NULL;
			temp_arr[i].str = 0;
		}
		for (int i = 0; i < h->size; i++) {
			Node* op = h->arr[i].next;
			while (op) {
				Node* p = op->next;
				int index = Hash_function(op->str) % (h->size * 2);
				Node* temp = initNode(op->str);
				temp->next = temp_arr[index].next;
				temp_arr[index].next = temp;
				op = p;
			}
		}
		free(h->arr);
		h->arr = temp_arr;
		h->size *= 2;
		return;
	}
	//删除
	void eraseHashList(HashList* h, char* des)
	{
		int index = Hash_function(des) % h->size;
		Node* to_find = &(h->arr[index]);
		while (to_find->next) {
			if (strcmp(to_find->next->str, des) == 0) {
				Node* to_delete = to_find->next;
				to_find->next = to_find->next->next;
				free(to_delete);
				h->count--;
				return;
			}
			to_find = to_find->next;
		}
		return;
	}
	//输出
	void outputHashList(HashList* h) {
		int flag = 0;
		for (int i = 0; i < h->size; i++) {
			Node* to_op = h->arr[i].next;
			if (to_op)printf("%d:", i);
			while (to_op) {
				Node* p = to_op->next;
				printf("%s->", to_op->str);
				to_op = p;
				flag = 1;
			}
			if (flag) {
				putchar('\n'); flag = 0;
			}
		}
	}
}
//int main() {
//	using namespace HashList_;
//	HashList* h = initHashList(2);
//	char p[100];
//	while (scanf("%s", p)) {
//		if (strcmp(p, "end") == 0)break;
//		insertHashList(h, p);
//		outputHashList(h);
//	}
//	while (scanf("%s", p)) {
//		if (strcmp(p, "end") == 0)break;
//		if (findHashList(h, p))printf("yes!\n");
//		else printf("no find\n");
//	}
//	return 0;
//}
//-------------------------二叉排序树
namespace SortTree {
	//结点构造函数
		Node::Node(int val) {
			key = val;
			lchild = rchild = nullptr;
		}
		//结点析构函数
		Node::~Node() {}
		void SortTree::clear(Node* root) {
			if (root == nullptr)return;
			if (root->lchild)clear(root->lchild);
			if (root->rchild)clear(root->rchild);
			delete root;
			return;
		}
		//插入内部函数
		Node* SortTree::__insert(Node* root, int val) {
			if (root == nullptr) {
				Node* temp = new Node(val);
				root = temp;
				return root;
			}
			if (root->key == val)return root;
			if (val < root->key)root->lchild = __insert(root->lchild, val);
			else if (val > root->key)root->rchild = __insert(root->rchild, val);
			return root;
		}
		//删除内部函数
		Node* SortTree::__earse(Node* root, int val) {
			if (root == nullptr)return root;
			if (val < root->key)root->lchild = __earse(root->lchild, val);
			else if (val > root->key)root->rchild = __earse(root->rchild, val);
			else {
				if (root->lchild == nullptr && root->rchild == nullptr) {
					delete root;
					return nullptr;
				}
				else if (root->lchild == nullptr || root->rchild == nullptr) {
					Node* temp = root->lchild ? root->lchild : root->rchild;
					delete root;
					return temp;
				}
				else {
					Node* pre_node = root->lchild;
					while (pre_node->rchild != nullptr)pre_node = pre_node->rchild;
					root->key = pre_node->key;
					root->lchild = __earse(root->lchild, root->key);
					return root;
				}
			}
			return root;
		}
		//前序输出内部函数
		void SortTree:: __pre_output(Node* root) {
			if (root == nullptr)return;
			std::cout << root->key << ":" << "\nLeft:" << KEY(root->lchild) << "\nRight:" << KEY(root->rchild) << std::endl;
			if (root->lchild)__pre_output(root->lchild);
			if (root->rchild)__pre_output(root->rchild);
			return;
		}
		//中序输出内部函数
		void SortTree::__in_output(Node* root) {
			if (root == nullptr)return;
			if (root->lchild)__in_output(root->lchild);
			std::cout << root->key << ' ';
			if (root->rchild)__in_output(root->rchild);
			return;
		}
		//类构造
		SortTree::SortTree() {}
		//类析构
		SortTree::~SortTree() {
			clear(root);
			root = nullptr;
		}
		//插入
		void SortTree::insert(int val) {
			root = __insert(root, val);
			return;
		}
		//删除
		void SortTree::earse(int val) {
			root = __earse(root, val);
			return;
		}
		//前序输出
		void SortTree::pre_output() {
			__pre_output(root);
		}
		//中序输出
		void SortTree::in_output() {
			__in_output(root);
		}
};
//--------------------------------测试
//int main() {
//	srand(time(0));
//	SortTree::SortTree st;
//	int temp;
//	for (int i = 0; i < 10; i++) {
//		st.insert(rand() % 50);
//	}
//	st.pre_output();
//	std::cout << std::endl;
//	st.in_output();
//
//	while(scanf("%d",&temp)){
//		if (temp == -1)break;
//		st.earse(temp);
//		st.in_output();
//		std::cout << std::endl;
//	}
//	return 0;
//}
//----------------------------AVL树
//Node结点构造函数
AVLTree::Node::Node(int val, int high, Node* left, Node* right) :val(val), high(high), left(left), right(right){}
//Node结点构造函数重载
AVLTree::Node::Node(int val) {
	this->val = val;
	this->high = 1;
	this->right = this->left = NIL;
}
//Node结点析构函数
AVLTree::Node::~Node(){}
//静态类全局变量定义
AVLTree::Node AVLTree::__NIL{ -1,0,NIL,NIL };
//左旋函数
AVLTree::Node* AVLTree::leftRorate(Node* root) {
	Node* newroot = root->right;
	root->right = newroot->left;
	newroot->left = root;
	updateHigh(root);
	updateHigh(newroot);
	return newroot;
}
//右旋函数
AVLTree::Node* AVLTree::rightRorate(Node* root) {
	Node* newroot = root->left;
	root->left = newroot->right;
	newroot->right = root;
	updateHigh(root);
	updateHigh(newroot);
	return newroot;
}
//更新高度
void AVLTree::updateHigh(Node* root) {
	root->high = Max(root->left->high, root->right->high) + 1;
	return;
}
//保持平衡
AVLTree::Node* AVLTree::maintainBalance(Node* root) {
	if (abs(root->left->high - root->right->high) < 2)return root;
	if (root->left->high > root->right->high) {
		if (root->left->left->high < root->left->right->high)root->left = leftRorate(root->left);
		root = rightRorate(root);
	}
	else {
		if (root->right->right->high < root->right->left->high)root->right = rightRorate(root->right);
		root = leftRorate(root);
	}
	return root;
}
//插入内部函数
AVLTree::Node* AVLTree::__insert(Node* root, int val) {
	if (root == NIL)return new Node(val);
	if (root->val > val)root->left = __insert(root->left, val);
	else if (root->val < val)root->right = __insert(root->right, val);
	else return root;
	updateHigh(root);
	return maintainBalance(root);
}
//删除内部函数
AVLTree::Node* AVLTree::__erase(Node* root, int val) {
	if (root == NIL)return root;
	if (val > root->val)root->right = __erase(root->right, val);
	else if (val < root->val)root->left = __erase(root->left, val);
	else {
		if (root->left == NIL || root->right == NIL) {
			Node* ret = root->left == NIL ? root->left : root->right;
			delete root;
			return ret;
		}
		else {
			Node* pre_node = root->left;
			while (pre_node->right != NIL)pre_node = pre_node->right;
			root->val = pre_node->val;
			root->left = __erase(root->left, root->val);
		}
	}
	updateHigh(root);
	return maintainBalance(root);
}
//查找内部函数
bool AVLTree:: __find(Node* root, int val) {
	Node* temp = root;
	while (temp) {
		if (val > temp->val)temp = temp->right;
		else if (val < temp->val)temp = temp->left;
		else return true;
	}
	return false;
}
//输出内部函数
void AVLTree::__output(Node* root) {
	if (root == NIL)return;
	std::cout << root->val << ' ' << '[' << root->left->val << ',' << root->right->val << ']' << std::endl;
	if (root->left)__output(root->left);
	if (root->right)__output(root->right);
	return;
}
//插入
void AVLTree::insert(int val) {
	root = __insert(root, val);
	return;
}
//删除
void AVLTree::erase(int val) {
	root = __erase(root, val);
	return;
}
//查找
bool AVLTree::find(int val) {
	return __find(root, val);
}
//输出
void AVLTree::output() {
	__output(root);
}
//构造函数
AVLTree::AVLTree() :root(NIL) {}
//析构函数
AVLTree::~AVLTree() {}
//-----------------测试
//int main() {
//	int temp;
//	AVLTree t;
//	while (scanf("%d", &temp)) {
//		if (temp == -1)break;
//		t.insert(temp);
//		t.output();
//	}
//	while (scanf("%d", &temp)) {
//		if (temp == -1)break;
//		t.erase(temp);
//		t.output();
//	}
//	return 0;
//}
//-----------------------------------------红黑树
//结点初始化
RedBlackTree::Node::Node(int val) :val(val) {
	this->color = 0;
	this->left = this->right = NIL;
}
//结点初始化重载
RedBlackTree::Node::Node(int val, int color, Node* left, Node* right) :val(val), color(color), left(left), right(right) {}
//结点析构
RedBlackTree::Node::~Node(){}
//清除函数
void RedBlackTree::clear(Node* root) {
	if (root == NIL)return;
	if (root->left)clear(root->left);
	if (root->right)clear(root->right);
	delete root;
	return;
}
//左旋
RedBlackTree::Node* RedBlackTree::LeftRorate(Node* root)
{
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	return newRoot;
}
//右旋
RedBlackTree::Node* RedBlackTree::RightRorate(Node* root) {
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	return newRoot;
}
//判断是否有红色结点
bool RedBlackTree::isHaveRedNode(Node* root) {
	return root->left->color == 0 || root->right->color == 0;
}
//判断是否有双重黑结点
bool RedBlackTree::isHaveDoubleBlackNode(Node* root) {
	return root->left->color == 2 || root->right->color == 2;
}
//插入调整
RedBlackTree::Node* RedBlackTree::insertMaintain(Node* root) {
	if (!isHaveRedNode(root))return root;
	int flag = 0;
	if (root->left->color == 0 && isHaveRedNode(root->left))flag = 1;
	else if (root->right->color == 0 && isHaveRedNode(root->right))flag = 2;
	if (flag == 0)return root;
	if (root->left->color == 0 && root->right->color == 0)goto loop;
	if (flag == 1) {
		if (root->left->right->color == 0) {
			root->left = LeftRorate(root->left);
		}
		root = RightRorate(root);
	}
	else {
		if (root->right->left->color == 0) {
			root->right = RightRorate(root->right);
		}
		root = LeftRorate(root);
	}
loop:root->color = 0;
	root->left->color = root->right->color = 1;
	return root;
}
//删除调整
RedBlackTree::Node* RedBlackTree::eraseMaintain(Node* root) {
	if (!isHaveDoubleBlackNode(root))return root;
	if (isHaveRedNode(root)) {
		root->color = 0;
		if (root->left->color == 0) {
			root = RightRorate(root);
			root->right = eraseMaintain(root->right);
		}
		else {
			root = LeftRorate(root);
			root->left = eraseMaintain(root->left);
		}
		root->color = 1;
		return root;
	}
	if ((root->left->color == 2 && !isHaveRedNode(root->right)) ||
		(root->right->color == 2 && !isHaveRedNode(root->left))) {
		root->color += 1;
		root->left->color -= 1;
		root->right->color -= 1;
		return root;
	}
	if (root->left->color == 2) {
		root->left->color = 1;
		if (root->right->right->color != 0) {
			root->right = RightRorate(root->right);
		}
		root->right->color = root->color;
		root = LeftRorate(root);
	}
	else {
		root->right->color = 1;
		if (root->left->left->color != 0) {
			root->left = LeftRorate(root->left);
		}
		root->left->color = root->color;
		root = RightRorate(root);
	}
	root->left->color = root->right->color = 1;
	return root;
}
//插入内部函数
RedBlackTree::Node* RedBlackTree::__insert(Node* root, int val) {
	if (root == NIL)return new Node(val);
	if (root->val == val)return root;
	if (val > root->val)root->right = __insert(root->right, val);
	else root->left = __insert(root->left, val);
	return insertMaintain(root);
}
RedBlackTree::Node* RedBlackTree::__erase(Node* root, int val) {
	if (root == NIL)return root;
	if (val > root->val)root->right = __erase(root->right, val);
	else if (val < root->val)root->left = __erase(root->left, val);
	else {
		if (root->left == NIL || root->right == NIL) {
			Node* next_root = root->left == NIL ? root->right : root->left;
			next_root->color += root->color;
			delete root;
			return next_root;
		}
		else {
			Node* to_delete = root->left;
			while (to_delete->right != NIL)to_delete = to_delete->right;
			root->val = to_delete->val;
			root->left = __erase(root->left, root->val);
		}
	}
	return eraseMaintain(root);
}
//查找内部函数
RedBlackTree::Node* RedBlackTree::__find(Node* root, int val) {
	if (root == NIL)return root;
	if (root->val == val)return root;
	else if (val > root->val)__find(root->right, val);
	else __find(root->left, val);
}
//输出函数
void RedBlackTree::__output(Node* root) {
	if (root == NIL)return;
	printf("([%d],[%d:%d,%d]\n", root->color, root->val, root->left->val, root->right->val);
	if (root->left)__output(root->left);
	if (root->right)__output(root->right);
	return;
}
//红黑树初始化
RedBlackTree::RedBlackTree() {
	root = NIL;
}
//红黑树析构
RedBlackTree::~RedBlackTree() {
	clear(root);
}
//插入接口
void RedBlackTree::insert(int val) {
	root = __insert(root, val);
	root->color = 1;
}
//删除接口
void  RedBlackTree::erase(int val) {
	root = __erase(root, val);
	root->color = 1;
}
//查找接口
RedBlackTree::Node* RedBlackTree::find(int val) {
	Node* ret = __find(root, val);
	return ret == NIL ? nullptr : ret;
}
//输出接口
void RedBlackTree::output() {
	__output(root);
}
RedBlackTree::Node RedBlackTree::__NIL{ -1,1,NIL,NIL };
//------------测试
//int main() {
//	int temp;
//	RBTree t;
//	while (std::cin >> temp) {
//		if (temp == -1)break;
//		t.insert(temp);
//		t.output();
//	}
//	while (std::cin >> temp) {
//		if (temp == -1)break;
//		t.erase(temp);
//		t.output();
//	}
//	while (std::cin >> temp) {
//		if (temp == -1)break;
//		if (t.find(temp))std::cout << "find out\n";
//		else std::cout << "no find\n";
//	}
//}
//-------------------------------------------B-Tree
BTree::Node BTree::__NIL(0, 0);
//内部结点构造
BTree::Node::Node(int val) {
	this->count = 1;
	for (int i = 0; i < MAX_M + 1; i++) {
		key[i] = -1;
		child[i] = NIL;
	}
	key[0] = val;
}
//内部结点构造函数重载
BTree::Node::Node(int, int) {
	this->count = 0;
	for (int i = 0; i < MAX_M + 1; i++) {
		key[i] = -1;
		child[i] = NIL;
	}
}
//后续销毁结点
void BTree::clear(Node* root) {
	if (root == NIL)return;
	for (int i = 0, I = root->count; i < I; i++) {
		if (root->child[i] != NIL)clear(root->child[i]);
	}
	delete root;
	return;
}
//插入调整
BTree::Node* BTree::insert_maintain(Node* root, int pos) {
	if (root->child[pos]->count < MAX_M)return root;
	Node* left = new Node(0, 0), * right = new Node(0, 0);
	int mid = MAX_M / 2;
	int LLKey = 0, LRKey = mid, RLKey = mid + 1, RRKey = MAX_M;
	int LLChild = 0, LRChild = mid + 1, RLChild = mid + 1, RRChild = MAX_M + 1;
	left->count = LRKey - LLKey;
	for (int i = LLKey; i < LRKey; i++) {
		left->key[i] = root->child[pos]->key[i];
	}
	for (int i = LLChild; i < LRChild; i++) {
		left->child[i] = root->child[pos]->child[i];
	}
	right->count = RRKey - RLKey;
	for (int i = RLKey; i < RRKey; i++) {
		right->key[i - RLKey] = root->child[pos]->key[i];
	}
	for (int i = RLChild; i < RRChild; i++) {
		right->child[i - RLChild] = root->child[pos]->child[i];
	}
	for (int i = root->count; i > pos; i--) {
		root->key[i] = root->key[i - 1];
		root->child[i + 1] = root->child[i];
	}
	root->count += 1;
	root->key[pos] = root->child[pos]->key[mid];
	delete root->child[pos];
	root->child[pos] = left;
	root->child[pos + 1] = right;
	return root;
}
//插值
BTree::Node* BTree::insert_val(Node* root, int val) {
	if (root == NIL)return new Node(val);
	int pos = 0;
	for (int i = 0; i < root->count; i++)if (val > root->key[i])pos += 1; else break;
	if (root->key[pos] == val)return root;
	for (int i = root->count; i > pos; i--) {
		root->key[i] = root->key[i - 1];
	}
	root->count += 1;
	root->key[pos] = val;
	return root;
}
//三次封装插入函数
BTree::Node* BTree::____insert(Node* root, int val) {
	if (root == NIL || root->child[0] == NIL) {
		return insert_val(root, val);

	}
	int pos = 0;
	for (int i = 0; i < root->count; i++)if (val > root->key[i])pos += 1; else break;
	if (root->key[pos] == val)return root;
	____insert(root->child[pos], val);
	return insert_maintain(root, pos);
}
//二次封装插入函数
BTree::Node* BTree::__insert(Node* root, int val) {
	root = ____insert(root, val);
	if (root->count >= MAX_M) {
		Node* newRoot = new Node(0, 0);
		newRoot->child[0] = root;
		insert_maintain(newRoot, 0);
		root = newRoot;
	}
	return root;
}
//左旋
void BTree::LeftRorate(Node* root, int pos) {
	root->child[pos]->key[root->child[pos]->count] = root->key[pos];
	root->child[pos]->count += 1;
	root->key[pos] = root->child[pos + 1]->key[0];
	root->child[pos + 1]->count -= 1;
	for (int i = 0; i < root->child[pos + 1]->count; i++) {
		root->child[pos + 1]->key[i] = root->child[pos + 1]->key[i + 1];
	}
	return;
}
//右旋
void BTree::RightRorate(Node* root, int pos) {
	for (int i = root->child[pos + 1]->count; i > 0; i--) {
		root->child[pos + 1]->key[i] = root->child[pos + 1]->key[i - 1];
	}
	root->child[pos + 1]->key[0] = root->key[pos];
	root->child[pos + 1]->count += 1;
	root->key[pos] = root->child[pos]->key[root->child[pos]->count - 1];
	root->child[pos]->count -= 1;
	return;
}
//合并
void BTree::mergeNode(Node* root, int pos) {
	Node* newNode = new Node(0, 0);
	int Llen = root->child[pos]->count, Rlen = root->child[pos + 1]->count;
	newNode->count = Llen;
	for (int i = 0; i < Llen; i++) {
		newNode->key[i] = root->child[pos]->key[i];
		newNode->child[i] = root->child[pos]->child[i];
	}
	newNode->child[Llen] = root->child[pos]->child[root->child[pos]->count];
	newNode->key[Llen] = root->key[pos];
	newNode->count += 1;
	newNode->count += Rlen;
	for (int i = 0; i < Rlen; i++) {
		newNode->key[Llen + 1 + i] = root->child[pos + 1]->key[i];
		newNode->child[Llen + 1 + i] = root->child[pos + 1]->child[i];
	}
	newNode->child[newNode->count] = root->child[pos + 1]->child[root->child[pos + 1]->count];
	delete root->child[pos];
	delete root->child[pos + 1];
	root->count -= 1;
	root->child[root->count] = newNode;
	return;
}
//删除调整
void BTree::erase_maintain(Node* root, int pos) {
	if (root->child[pos]->count >= LOW)return;
	if (pos + 1 <= root->count && root->child[pos + 1]->count > LOW) {
		LeftRorate(root, pos);
	}
	else if (pos - 1 >= 0 && root->child[pos - 1]->count > LOW) {
		RightRorate(root, pos - 1);
	}
	else {
		if (pos + 1 <= root->count)mergeNode(root, pos);
		else mergeNode(root, pos - 1);
	}
	return;
}
//三次封装删除函数
void BTree::____erase(Node* root, int val) {
	if (root == NIL)return;
	int pos = 0;
	for (int i = 0; i < root->count; i++)if (val > root->key[i])pos += 1; else break;
	if (root->key[pos] == val) {
		if (root->child[0] == NIL) {
			for (int i = pos; i < root->count; i++) {
				root->key[i] = root->key[i + 1];
			}
			root->count -= 1;
			return;
		}
		else {
			root->key[pos] = root->child[pos]->key[root->child[pos]->count - 1];
			____erase(root->child[pos], root->key[pos]);
		}
	}
	else {
		____erase(root->child[pos], val);
	}
	erase_maintain(root, pos);
	return;
}
//二次封装删除函数
BTree::Node* BTree::__erase(Node* root, int val) {
	____erase(root, val);
	if (root->count == 0) {
		Node* newRoot = root->child[0];
		delete root;
		root = newRoot;
	}
	return root;
}
//打印结点
void BTree::print_node(Node* root) {
	printf("%d : ", root->count);
	for (int i = 0; i < root->count; i++) {
		printf("%4d", root->key[i]);
	}
	printf(" | ");
	if (root->child[0] == NIL) goto output_end;
	for (int i = 0; i <= root->count; i++) {
		printf("%4d", root->child[i]->key[0]);
	}
output_end:
	printf("\n");
	return;
}
void BTree::__output(Node* root) {
	if (root == NIL) return;
	print_node(root);
	for (int i = 0; i <= root->count; i++) {
		__output(root->child[i]);
	}
	return;
}
//查找函数
bool BTree::__find(Node* root, int val) {
	if (root == NIL)return false;
	int pos = 0;
	for (int i = 0; i < root->count; i++)if (val > root->key[i])pos += 1; else break;
	if (root->key[pos] == val)return true;
	return __find(root->child[pos], val);
}
//构造函数
BTree::BTree() {
	root = NIL;
}
//析构函数
BTree::~BTree() {
	clear(root);
}
//插入接口
void BTree::insert(int val) {
	root = __insert(root, val);
}
//删除接口
void BTree::erase(int val) {
	root = __erase(root, val);
}
//打印接口
void BTree::output() {
	__output(root);
}
//查找接口
bool BTree::find(int val) {
	return __find(root, val);
}
//-------------------测试
//int main() {
//	int op;
//	BTree b;
//	while (std::cin >> op) {
//		if (op == -1)break;
//		b.insert(op);
//		b.output();
//	}
//	while (std::cin >> op) {
//		if (op == -1)break;
//		b.erase(op);
//		b.output();
//	}
//	while (std::cin >> op) {
//		if (op == -1)break;
//		if (b.find(op))std::cout << "find\n";
//		else std::cout << "no find\n";
//
//	}
//}
//-------------------------单调队列
namespace monotonic_queue {
	int Deque::operator[](int index) {
		if (index < count_) {
			return data_[(head_ + index) % size_];
		}
		throw std::out_of_range("下标超出范围");
	}
	void Deque::front_pop() {
		if (empty())throw std::runtime_error("队列中已无元素，无法队首出队!");
		head_++;
		if (head_ == size_)head_ = 0;
		count_--;
	}
	void Deque::front_push(int val) {
		if (full())throw std::runtime_error("队列已满，无法队首入队！");
		head_--;
		if (head_ < 0)head_ = size_ - 1;
		data_[head_] = val;
		count_++;
	}
	void Deque::back_pop() {
		if (empty())throw std::runtime_error("队列中已无元素，无法队尾出队！");
		tail_--;
		if (tail_ < 0)tail_ = size_ - 1;
		count_--;
	}
	void Deque::back_push(int val) {
		if (full())throw std::runtime_error("队列已满，无法队尾入队！");
		data_[tail_++] = val;
		count_++;
		if (tail_ == size_)tail_ = 0;
	}
	int Deque::top() {
		if (empty())throw std::runtime_error("队列已空，无法展示队首元素");
		return data_[head_];
	}
	int Deque::back() {
		if (empty())throw std::runtime_error("队列已空，无法展示队尾元素");
		return data_[tail_ - 1];
	}
	void Deque::output() {
		for (int i = 0; i < count_; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << i;
		}
		std::cout.put('\n');
		for (int i = 0; i < count_; i++) {
			std::cout << std::setw(3) << std::setfill('-') << '-';
		}
		std::cout.put('\n');
		for (int i = 0; i < count_; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << data_[(head_ + i) % size_];
		}
	}
	void Monotonic_queue::init() {
		for (int i = step_; i < interval_length_ + step_; i++) {
			while (!que.empty() && arr_[i] < arr_[que.back()])que.back_pop();
			que.back_push(i);
			if (i - que.top() == interval_length_)que.front_pop();
		}
	}
	Monotonic_queue::Monotonic_queue(std::vector<int>&& arr, int interval_length) :que(arr.size()), size_(arr.size()), interval_length_(interval_length), arr_(arr) {
		if (interval_length_ > size_)throw std::out_of_range("区间长度超过了数组长度！");
		init();
	}
	Monotonic_queue::Monotonic_queue(std::vector<int>& arr, int interval_length) :que(arr.size()), size_(arr.size()), interval_length_(interval_length), arr_(arr) {
		if (interval_length_ > size_)throw std::out_of_range("区间长度超过了数组长度！");
		init();
	}
	Monotonic_queue::Monotonic_queue(int arr[], int len, int interval_length) :que(len), interval_length_(interval_length), size_(len), arr_(len) {
		if (interval_length_ > size_)throw std::out_of_range("区间长度超过了数组长度！");
		for (int i = 0; i < len; i++) {
			arr_[i] = arr[i];
		}
		init();
	}
	void Monotonic_queue::Move() {
		int i{ step_ + interval_length_ };
		int last_i{ step_++ };
		if (step_ + interval_length_ > size_) {
			step_--;
			throw std::out_of_range("窗口已经到达底部，无法再次移动！");
		}
		while (!que.empty() && arr_[i] < arr_[que.back()])que.back_pop();
		que.back_push(i);
		if (i - que.top() == interval_length_)que.front_pop();
	}
	void Monotonic_queue::output() {
		for (int i = 0; i < size_; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << i;
		}
		std::cout.put('\n');
		for (int i = 0; i < size_; i++) {
			std::cout << std::setw(3) << std::setfill('-') << '-';
		}
		std::cout.put('\n');
		for (int i = 0; i < size_; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << arr_[i];
		}
		//std::cout.put('\n');
		//std::cout << "----------deque--------------\n";
		//que.output();
		//std::cout.put('\n');
		//std::cout << "----------deque--------------\n";
		std::cout.put('\n');
		int que_ind = 0;
		for (int i = 0; i < size_; i++) {
			if (i < step_ + interval_length_ && i >= step_) {
				if (i <= que[que_ind]) {
					std::cout << std::setw(3) << std::setfill(' ') << arr_[que[que_ind]];
				}
				else {
					que_ind++;
					std::cout << std::setw(3) << std::setfill(' ') << arr_[que[que_ind]];
				}
			}
			else {
				std::cout << std::setw(3) << std::setfill('-') << '-';
			}
		}
		std::cout.put('\n');
	}
	//-------------------测试
	//auto main() -> int {
	//	std::vector<int>q{ 2 ,7 ,8 ,5 ,6 ,2 ,3 ,4 ,1 ,10 ,9 };
	//	Monotonic_queue que(q, 4);
	//	que.output();
	//	int a;
	//	while (1) {
	//		try {
	//			std::cin >> a;
	//			que.Move();
	//			que.output();
	//		}
	//		catch (std::out_of_range& s) {
	//			break;
	//		}
	//		catch (std::runtime_error& s) {
	//			break;
	//		}
	//	}
	//}
};
//------------------------------------单调栈
namespace monotonic_stack {
	void Monotonic_stack::init() {
		if (right_) {
			for (int i = 0; i < size_; i++) {
				while (!sck_.empty() && arr_[i] < arr_[sck_.top()]) {
					ind_[sck_.top()] = i;
					sck_.pop();
				}
				sck_.push(i);
			}
		}
		else {
			for (int i = size_ - 1; i >= 0; i--) {
				while (!sck_.empty() && arr_[i] < arr_[sck_.top()]) {
					ind_[sck_.top()] = i;
					sck_.pop();
				}
				sck_.push(i);
			}
		}
		while (!sck_.empty()) {
			ind_[sck_.top()] = -1;
			sck_.pop();
		}
	}
	Monotonic_stack::Monotonic_stack(int arr[], int len, bool right) :size_(len), arr_(len), right_(right), ind_(len) {
		for (int i = 0; i < len; i++) {
			arr_[i] = arr[i];
		}
		init();
	}
	Monotonic_stack::Monotonic_stack(std::vector<int>& arr, bool right) :size_(arr.size()), arr_(arr), right_(right), ind_(arr.size()) { init(); }
	Monotonic_stack::Monotonic_stack(std::vector<int>&& arr, bool right) :size_(arr.size()), arr_(arr), right_(right), ind_(arr.size()) { init(); }
	void Monotonic_stack::output() {
		for (int i = 0; i < size_; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << i;
		}
		std::cout.put('\n');
		for (int i = 0; i < size_; i++) {
			std::cout << std::setw(3) << std::setfill('-') << '-';
		}
		std::cout.put('\n');
		for (int i = 0; i < size_; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << arr_[i];
		}
		std::cout.put('\n');
		for (int i = 0; i < size_; i++) {
			std::cout << std::setw(3) << std::setfill(' ');
			switch (ind_[i])
			{
			case -1:
				std::cout << -1;
				break;
			default:
				std::cout << arr_[ind_[i]];
				break;
			}
		}
		std::cout.put('\n');
	}
};