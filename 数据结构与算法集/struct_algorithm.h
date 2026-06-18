/*
目的：本文件目的是将所学初等数据结构复现一下，仅供参考
作者：鑨
时间：2026.1.31
介绍：本次数据结构均为手搓，没有涉及到相互封装，在实现过程中最好运用相互封装，本文件仅为“裸展示”因此去除掉了相互封装
网址：https://github.com/WeLong123/struct-algorithm.git
*/
/*
* 日志：
4.5更新
优化了跳跃表的删除 和 哈希表的删除
更新了 二叉排序树 和 AVL树
4.19更新
更新了 红黑树的插入 删除 查找
4.26更新
更新了 B树的插入删除查找
5.3更新
更新了 系统栈法 将递归版阶乘 中序遍历 快速排序 转为非递归
	   拓补序法 将归并排序 递归版转为非递归
6.14更新
更新了并查集：按大小合并 路径压缩
重构了全局结构，避免了命名空间的错误
6.15更新
更新了单调队列，单调栈
*/
#pragma once
#include<cstdlib>
#include<vector>
#include<map>
#include<stack>
#include<list>
#include<algorithm>
#include<queue>
#include<set>
#include<functional>
#include<unordered_map>
#include<iterator>
#include<iomanip>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>
#include<limits>
#include<utility>
#include<sstream>
#include<stdexcept>
#include<Windows.h>
# include<conio.h>
#include<fstream>
#include<chrono>
#include<ctime>
#include<cmath>
namespace Base_struct {
#define FATHER(n) (n/2)//父节点
#define LEFT(n) (n*2)//左节点
#define RIGHT(n) (n*2+1)//右节点
	typedef struct VECTOR {
		int* data;
		int size, count;
	}Vector;
	typedef struct QUEUE {
		int* data;
		int tail, head;
		int count, size;
	}Queue;
	typedef struct NodeList {
		int val;
		struct NodeList* next;
	}NodeList;
	typedef struct STACK {
		int* data;
		int top;
		int size;
	}Stack;
	typedef struct TREENODE {
		int val;
		int ltag, rtag;//线索化 是否为虚线
		struct TREENODE* left, * right;
	}TreeNode;
	typedef struct HAFFTREE {
		int fre;
		char character;
		struct HAFFTREE* left, * right;
	}HaffTree;
	typedef struct HEAP {
		int* data, * __data;
		int count, size;
	}Heap;
	Vector* initVector(int size);
	int fullVector(Vector* vec);
	int emptyVector(Vector* vec);
	bool insertVector(Vector* vec, int pos, int val);
	bool earseVector(Vector* vec, int pos);
	void clearVector(Vector* vec);
	void PrintVector(Vector* vec);
	int seek_PositionVector(Vector* vec, int pos);
	int seek_ValueVector(Vector* vec, int val);
	int sizeVector(Vector* vec);

	NodeList* initNodeList(int val);
	void clearNodeList(NodeList* head);
	NodeList* insertNodeList(NodeList* head, int pos, int val);
	NodeList* tail_insertNodeList(NodeList* head, int val);
	NodeList* head_insertNodeList(NodeList* head, int val);
	NodeList* earseNodeList(NodeList* head, int pos);
	NodeList* reserveNodeList_all(NodeList* head);
	NodeList* reserveNodeList_2_2(NodeList* head);
	NodeList* reserveNodeList1(NodeList* head, int start, int end);
	NodeList* reserveNodeList(NodeList* head, int start, int end);
	NodeList* build_cycleNodeList(NodeList* head);
	bool check_cycleNodeList(NodeList* head);
	int size_cycleNodeList(NodeList* head);
	int size_allcycleNodeList(NodeList* head);
	void print_cycleNodeList(NodeList* head);
	void PrintNodeList(NodeList* head);

	Queue* initQueue(int size);
	void clearQueue(Queue* que);
	int emptyQueue(Queue* que);
	int fullQueue(Queue* que);
	bool pushQueue(Queue* que, int val);
	bool popQueue(Queue* que);
	int frontQueue(Queue* que);
	int sizeQueue(Queue* que);
	void PrintQueue(Queue* que);

	Stack* pushStack(Stack* sta, int val);
	bool popStack(Stack* sta);
	int frontStack(Stack* sta);
	void clearStack(Stack* sta);
	void Prints(Stack* sta);

	TreeNode* initTree(int val);
	void clearTree(TreeNode* root);
	TreeNode* randomTree(int count);
	TreeNode* __randomTree(TreeNode* root);
	void bfs(TreeNode* root, int count);
	void __dfs(TreeNode* root, int* tot);
	void dfs(TreeNode* root);
	void __preOrder(TreeNode* root);
	void preOrder(TreeNode* root);
	void __inOrder(TreeNode* root);
	void inOrder(TreeNode* root);
	void __postOrder(TreeNode* root);
	void postOrder(TreeNode* root);
	void __tagTree(TreeNode* root, TreeNode** preroot);
	void tagTree(TreeNode* root);
	void __tagVerseTree(TreeNode* root);
	void tagVerseTree(TreeNode* root);
	void clearTagTree(TreeNode* root);
	void __tagPreOrder(TreeNode* root);
	void tagPreOrder(TreeNode* root);
	void tagInOrder(TreeNode* root);
	void __tagInOrder(TreeNode* root);
	void tagPostOrder(TreeNode* root);
	void __tagPostOrder(TreeNode* root);
	char* GeneralCode(TreeNode* root, char destination[]);
	void __GeneralCode(TreeNode* root, char buff[], int* len);
	TreeNode* antiGeneralCode(char buff[], int count);
	HaffTree* initHaffTree(int fre, char character);
	HaffTree* haffmanCode(char Data[][100], int count, char Result[][100]);
	void anti_HaffmanCode(HaffTree* root, int count, char Result[128][100], char buff[100], int k);
	void PrintHaffman(char Result[128][100]);
	void reserveTree(TreeNode* root);
	bool match_one_node(TreeNode* Tree, TreeNode* subTree);
	bool compareTreeAndSubTree(TreeNode* Tree, TreeNode* subTree);

	Heap* initHeap(int);
	void clearHeap(Heap* h);
	void swap_arr(int* arr, int index1, int index2);
	void up_update_small(int* data, int index);
	void down_update_small(int* data, int index, int len);
	void up_update_large(int* data, int index);
	void down_update_large(int* data, int index, int len);
	int fullHeap(Heap* heap);
	int emptyHeap(Heap* heap);
	void pushHeap_small(Heap* heap, int val);
	void pushHeap_large(Heap* heap, int val);
	void popHeap_small(Heap* heap);
	void popHeap_large(Heap* heap);
	int frontHeap(Heap* heap);
	void linearHeap_small(int* arr, int len);
	void linearHeap_large(int* arr, int len);
	void PrintHeap(Heap* heap);
	/*
	HeapTree* initHeapTree(int fre, char ch);
	void clearHeapTree(HeapTree* root);\
	Heap* initHeap(int size) ;
	int emptyHeap(Heap* h);
	int fullHeap(Heap* h);
	HeapTree* frontHeap(Heap* h);
	void swapHeap(Heap* h, int index1,int index2);
	void up_updatehaff(Heap* h, int index);
	void down_updatehaff(Heap* h,int index) ;
	int popHeap(Heap* h);
	int pushHeap(Heap* h,HeapTree*root);
	HeapTree* haffmanTree_build(Heap*h);
	void __antiHaffmanCode(HeapTree* root, char buff[128][100],char result[], int k);
	void antiHaffmanCode(HeapTree* root,char buff[128][100]);*/ 
}
//-----------------跳跃表
namespace SkipList_ {
#define MAX_LEVEL 32
	class Node {
	public:
		int val, level;
		Node* up, * down, * next;
		Node(int val = 0, int level = 0);
		~Node();
	};
	class SkipList {
	protected:
		int max_level, Node_max_level;
		Node* head, * tail;
		int getRandomLevel();
		double getRandomDouble();
	private:
		void getMaxLevel();
	public:
		SkipList();
		~SkipList();
		Node* find(int val);
		bool insert(int val);
		void output();
		void erase(int val);
	};
}
//-------------------------哈希表
namespace HashList_ {
	struct Node {
		char* str;
		Node* next;
	};
	struct HashList {
		Node* arr;
		int count, size;
	};
	void expandHashList(HashList* h);
	Node* initNode(char* string = 0);
	HashList* initHashList(int size);
	void clearNode(Node* node);
	void clearHashList(HashList* h);
	int Hash_function(char* str);
	bool insertHashList(HashList* h, char* des);
	bool findHashList(HashList* h, char* des);
	void expandHashList(HashList* h);
	void outputHashList(HashList* h);
	void eraseHashList(HashList* h, char* des);
}
//-------------------------------二叉排序树
namespace SortTree {
#define KEY(n) (n?n->key:-1)
	struct Node {
		int key;
		Node* lchild, * rchild;
		Node(int val=0);
		~Node();
	};
	class SortTree {
	private:
		Node* root;
	private:
		void clear(Node* root);
		Node* __insert(Node* root, int val);
		Node* __earse(Node* root, int val);
		void __pre_output(Node* root);
		void __in_output(Node* root);
	public:
		SortTree();
		~SortTree();
		void insert(int val);
		void earse(int val);
		void pre_output();
		void in_output();
	};
};

//-----------------------------------AVL树（二叉平衡搜索树）
class AVLTree {
private:
#define NIL (&__NIL)
#define Max(x,y) ((x)>(y)?x:y)
	struct Node {
		int val, high;
		Node* left, * right;
		Node(int val = 0);
		Node(int val, int high, Node* left, Node* right);
		~Node();
	};
	static Node __NIL;
	Node* root;
private:
	Node* leftRorate(Node* root);
	Node* rightRorate(Node* root);
	void updateHigh(Node* root);
	Node* maintainBalance(Node* root);
	Node* __insert(Node* root, int val);
	Node* __erase(Node* root, int val);
	bool __find(Node* root, int val);
	void __output(Node* root);
public:
	void insert(int val);
	void erase(int val);
	bool find(int val);
	void output();
	AVLTree();
	~AVLTree();
};
//---------------------------------------红黑树（二叉平衡搜索数）
typedef class RedBlackTree {
#define NIL (&__NIL)
	struct Node {
		int val, color;
		Node* left, * right;
		Node(int val);
		Node(int val, int color, Node* left, Node* right);
		~Node();
	};
	static Node __NIL;
	Node* root;
private:
	void clear(Node* root);
	Node* LeftRorate(Node* root);
	Node* RightRorate(Node* root);
	bool isHaveRedNode(Node* root);
	bool isHaveDoubleBlackNode(Node* root);
	Node* insertMaintain(Node* root);
	Node* eraseMaintain(Node* root);
	Node* __insert(Node* root, int val);
	Node* __erase(Node* root, int val);
	Node* __find(Node* root, int val);
	void __output(Node* root);
public:
	RedBlackTree();
	~RedBlackTree();
	void insert(int val);
	void erase(int val);
	Node* find(int val);
	void output();
}RBTree;
//--------------------------------------------B-树（基于磁盘的二叉平衡搜索树）
class BTree {
#define MAX_M 7
#define NIL (&__NIL)
#define LOW ((MAX_M+1)/2-1)
	struct Node {
		int count;
		int key[MAX_M + 1];
		Node* child[MAX_M + 1];
		Node(int val);
		Node(int, int);
	};
	static Node __NIL;
	Node* root;
private:
	void clear(Node* root);
	Node* insert_maintain(Node* root, int pos);
	Node* insert_val(Node* root, int val);
	Node* ____insert(Node* root, int val);
	Node* __insert(Node* root, int val);
	void LeftRorate(Node* root, int pos);
	void RightRorate(Node* root, int pos);
	void mergeNode(Node* root, int pos);
	void erase_maintain(Node* root, int pos);
	void ____erase(Node* root, int val);
	Node* __erase(Node* root, int val);
	void print_node(Node* root);
	void __output(Node* root);
	bool __find(Node* root, int val);
public:
	BTree();
	~BTree();
	void insert(int val);
	void erase(int val);
	void output();
	bool find(int val);
};
//----------------------------------------单调队列
namespace monotonic_queue {
	class Deque {
	private:
		int count_, size_;
		int* data_;
		int head_, tail_;
	public:
		int operator[](int index);
		explicit Deque(int size = 16) :size_(size), count_(0), head_(0), tail_(0) {
			data_ = new int[size];
		}
		~Deque() {
			delete[] data_;
		}
		bool empty() { return count_ == 0; }
		bool full() { return count_ == size_; }
		void front_pop();
		void front_push(int val);
		void back_pop();
		void back_push(int val);
		int top();
		int back();
		void output();
	};
	class Monotonic_queue {
	private:
		int size_;
		int interval_length_;
		std::vector<int>arr_;
		Deque que;
		int step_{ 0 };
	private:
		void init();
	public:
		Monotonic_queue() = delete;
		Monotonic_queue(std::vector<int>&& arr, int interval_length);
		Monotonic_queue(std::vector<int>& arr, int interval_length);
		Monotonic_queue(int arr[], int len, int interval_length);
		~Monotonic_queue() {}
		void Move();
		void output();
	};
};
//-----------------------------------------单调栈
namespace monotonic_stack {
	class Monotonic_stack {
	private:
		std::stack<int>sck_;
		int size_;
		std::vector<int>arr_;
		std::vector<int>ind_;
		bool right_;
	private:
		void init();
	public:
		Monotonic_stack() = delete;
		Monotonic_stack(int arr[], int len, bool right = 1);
		Monotonic_stack(std::vector<int>& arr, bool right = 1);
		Monotonic_stack(std::vector<int>&& arr, bool right = 1);
		~Monotonic_stack() {}
		void output();
	};
};