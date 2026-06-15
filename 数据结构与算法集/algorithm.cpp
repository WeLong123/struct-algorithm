# define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
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
#include<limits>
#include<utility>
#include<sstream>
#include<stdexcept>
#include<Windows.h>
# include<conio.h>
#include<fstream>
#include<iomanip>
#include<chrono>
#include<ctime>
#include<cmath>
//指数型枚举
static int arr_index[20] = { 0 };
void Print1(int n) {
	for (int i = 0; i <= n; i++) {
		printf("%d ", arr_index[i]);
	}
	printf("\n");
	return;
}
void function_index(int i, int j, int n) {
	if (j > n) { 
		return;
	}
	for (int q = j; q <= n; q++) {
		arr_index[i] = q;
		Print1(i);
		function_index(i + 1, q + 1, n);
	}
	return;
}
//组合型枚举
static int arr_combination[20] = { 0 };
void Print2(int n) {
	for (int i = 0; i <=n; i++) {
		printf("%d ", arr_combination[i]);
	}
	printf("\n");
	return;
}
void function_combination(int i, int j, int n,int k) {
	if (j > n) {
		return;
	}
	for (int q = j; q <= n; q++) {
		arr_combination[i] = q;
		if (i == k-1)Print2(i);
		function_combination(i + 1, q + 1, n, k);
	}
	return;
}
//排列型枚举
static int arr_rank[20] = { 0 };
static int flag[21] = { 0 };
void Print3(int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr_rank[i]);
	}
	printf("\n");
	return;
}
void function_rank(int i, int n) {
	if (i == n) {
		Print3(i);
		return;
	}
	for (int q = 1; q <= n; q++) {
		if (flag[q])continue;
		arr_rank[i] = q;
		flag[q] = 1;
		function_rank(i + 1, n);
		flag[q] = 0;
	}
	return;
}
//-----------------------排序
#define SMALL_DATA 50000
#define BIG_DATA 5000000
#define BOUNDARY 65536
#define TEST(func,arr,size){\
	int start=clock();\
	func(arr,0,size);\
	int FuncTime = clock() - start;\
	if(check(arr,size))std::cout<<""#func"time:"<<FuncTime<<"ms"<<std::endl;\
	else std::cout<<""#func"faild"<<std::endl;\
}
//------------------------常见排序算法 ：堆排序 选择排序 冒泡排序 插入排序 希尔排序 快速排序 归并排序 基数排序
//-------------堆排序
namespace Sort {
	class Heap {
		int* data, * _data;
		int count, size;
		int time;
#define LEFT(n) n*2
#define RIGHT(n) n*2+1
#define FATHER(n) n/2
	public:
		Heap(int size = 1625) :count(0), size(1625), time(0) {
			_data = new int[size + 1];
			data = _data - 1;
		}
		~Heap() {
			delete[] _data;
		}
		void copy(const int* arr, int l, int r) {
			while (r - l >= size) {
				int* temp = new int[size * 2];
				delete[]_data;
				_data = temp;
				data = _data - 1;
				size *= 2;
			}
			for (int i = l; i < r; i++) {
				_data[i - l] = arr[i];
			}
		}
		void up_update(int index) {
			while (FATHER(index) >= 1 && data[index] < data[FATHER(index)]) {
				{
					int temp = data[index];
					data[index] = data[FATHER(index)];
					data[FATHER(index)] = temp;
				}
				index = FATHER(index);
			}
		}
		void down_update(int index) {
			while (LEFT(index) <= count) {
				int ind = index, l = LEFT(ind), r = RIGHT(ind);
				if (data[l] < data[ind])ind = l;
				if (r <= count && data[r] < data[ind])ind = r;
				if (ind == index)break;
				{
					int temp = data[ind];
					data[ind] = data[index];
					data[index] = temp;
				}
				index = ind;
			}
		}
		void line_buildHeap() {
			for (int i = count / 2; i >= 1; i--) {
				down_update(i);
			}
		}
		void popHeap() {
			if (count == 0)return;
			data[1] = data[count--];
			down_update(1);
			return;
		}
		void pushHeap(int val) {
			if (count == size) {
				int* temp = new int[size * 2];
				for (int i = 0; i < size; i++) {
					temp[i] = _data[i];
				}
				delete[]_data;
				_data = temp;
				data = _data - 1;
				size *= 2;
			}
			data[++count] = val;
			up_update(count);
		}
		void heap_sort(int* arr, int l, int r) {
			copy(arr, l, r);
			count = r - l;
			int start = clock();
			line_buildHeap();
			for (int i = l; i < r; i++) {
				arr[i] = data[1];
				popHeap();
			}
			time = clock() - start;
		}
		int getTime() {
			return time;
		}
	};
}
//---------------------------------选择排序
void select_sort(int* arr, int l, int r) {
	for (int i = l; i < r - 1; i++) {
		int ind = i;
		for (int j = i + 1; j < r; j++) {
			if (arr[j] < arr[ind])ind = j;
		}
		if (ind != i) {
			int temp = arr[ind];
			arr[ind] = arr[i];
			arr[i] = temp;
		}
	}
}
//-----------------------------冒泡排序
void bubble_sort(int* arr, int l, int r) {
	for (int i = r - 1; i > l; i--) {
		for (int j = l; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
//--------------------------插入排序（哨兵）
void insert_sort(int* arr, int l, int r) {
	int min = l;
	for (int i = l + 1; i < r; i++) {
		if (arr[min] > arr[i])min = i;
	}
	{
		int temp = arr[min];
		arr[min] = arr[l];
		arr[l] = temp;
	}
	for (int i = l + 2; i < r; i++) {
		int key = arr[i];
		int j = i - 1;
		while (arr[j] > key) {
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = key;
	}
}
//------------------希尔排序（Knuth)
void shell_sort(int* arr, int l, int r) {
	int step = 1;
	while (step < (r - l) / 3) {
		step = step * 3 + 1;
	}
	for (step; step >= 1; step /= 3) {
		for (int i = l + step; i < r; i++) {
			int key = arr[i];
			int j = i - step;
			while (j >= l && arr[j] > key) {
				arr[j + step] = arr[j];
				j -= step;
			}
			arr[j + step] = key;
		}
	}
}
//------------------------快速排序（交换优化，单边递归，插入封装,三值取点）
void quick_insertSort(int* arr, int l, int r) {
	for (int i = l + 1; i < r; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= l && arr[j] > key) {
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = key;
	}
}
int getMiddle(int a, int b, int c) {
	if (a > b) {
		if (a > c) {
			if (b > c)return b;
			else return c;
		}
		else return a;
	}
	else {
		if (b > c) {
			if (a > c)return a;
			else return c;
		}
		else return b;
	}
}
#define TERROR 16
void __quick_sort(int* arr, int l, int r) {
	while ((r - l) >= TERROR) {
		int x = l, y = r - 1, mid = getMiddle(arr[l], arr[r - 1], arr[(r + l) / 2]);
		while (x <= y) {
			while (arr[x] < mid)x++;
			while (arr[y] > mid)y--;
			if (x < y) {
				int temp = arr[x];
				arr[x] = arr[y];
				arr[y] = temp;
			}
			x++, y--;
		}
		__quick_sort(arr, l, y + 1);
		l = x;
	}
	return;
}
void quick_sort(int* arr, int l, int r) {
	__quick_sort(arr, l, r);
	quick_insertSort(arr, l, r);
}
//-------------------------------归并排序

void __merge_sort(int* arr, int l, int r, int* buff) {
	if (r - l <= 1)return;
	int mid = (l + r) / 2;
	__merge_sort(arr, l, mid, buff);
	__merge_sort(arr, mid, r, buff);
	int p1 = l, p2 = mid, k = 0;
	while (p1 < mid || p2 < r) {
		if (p2 == r || (p1 < mid && arr[p1] < arr[p2])) {
			buff[k++] = arr[p1++];
		}
		else {
			buff[k++] = arr[p2++];
		}
	}
	for (int i = l; i < r; i++)arr[i] = buff[i - l];
}
void merge_sort(int* arr, int l, int r) {
	int* buff = new int[BIG_DATA];
	__merge_sort(arr, l, r, buff);
	delete[]buff;
}
//------------------------------------------基数排序
void radix_sort(int* arr, int l, int r) {
	int k = static_cast<int>(sqrt(BOUNDARY));
	int* cnt = new int[k];
	int* temp = new int[r - l];
	memset(cnt, 0, sizeof(int) * k);
	for (int i = l; i < r; i++)cnt[arr[i] % k]++;
	for (int i = 1; i < k; i++)cnt[i] += cnt[i - 1];
	for (int i = r - 1; i >= l; i--)temp[--cnt[arr[i] % k]] = arr[i];
	memcpy(arr, temp, sizeof(int) * (r - l));
	memset(cnt, 0, sizeof(int) * k);
	for (int i = l; i < r; i++)cnt[arr[i] / k]++;
	for (int i = 1; i < k; i++)cnt[i] += cnt[i - 1];
	for (int i = r - 1; i >= l; i--)temp[--cnt[arr[i] / k]] = arr[i];
	memcpy(arr, temp, sizeof(int) * (r - l));
	delete[]cnt;
	delete[]temp;
}
//-----------------------------------------测试
int* getRandom(int size) {
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % BOUNDARY;
	}
	return arr;
}
bool check(int* arr, int size) {
	for (int i = 1; i < size; i++) {
		if (arr[i] < arr[i - 1])return false;
	}
	return true;
}
int getFuncTime(int* arr, int size, void(*func)(int* arr, int l, int r)) {
	int start = clock();
	func(arr, 0, size);
	return clock() - start;
}
//int main() {
//	Sort::Heap h;
//	int* small_arr[8], * big_arr[8];
//	void(*func[7])(int* arr, int l, int r) = { select_sort,bubble_sort,insert_sort,shell_sort,quick_sort,merge_sort,radix_sort };
//	for (int i = 0; i < 8; i++) {
//		small_arr[i] = getRandom(SMALL_DATA);
//		big_arr[i] = getRandom(BIG_DATA);
//	}
//	std::cout << "SAMLL_DATA" << std::endl;
//	h.heap_sort(small_arr[0], 0, SMALL_DATA);
//	if (check(small_arr[0], SMALL_DATA))std::cout << "heap_sort time :" << h.getTime() << "ms" << std::endl;
//	else std::cout << "heap_sort faild" << std::endl;
//	TEST(select_sort, small_arr[1], SMALL_DATA);
//	TEST(bubble_sort, small_arr[2], SMALL_DATA);
//	TEST(insert_sort, small_arr[3], SMALL_DATA);
//	TEST(shell_sort, small_arr[4], SMALL_DATA);
//	TEST(quick_sort, small_arr[5], SMALL_DATA);
//	TEST(merge_sort, small_arr[6], SMALL_DATA);
//	TEST(radix_sort, small_arr[7], SMALL_DATA);
//	std::cout << "BIG_DATA" << std::endl;
//	h.heap_sort(big_arr[0], 0, BIG_DATA);
//	if (check(big_arr[0], BIG_DATA))std::cout << "heap_sort time:" << h.getTime() << "ms" << std::endl;
//	//TEST(select_sort, big_arr[1], BIG_DATA);/*选择排序：请输入文本*/
//	//TEST(bubble_sort, big_arr[2], BIG_DATA);/*冒泡排序：请输入文本*/
//	//TEST(insert_sort, big_arr[3], BIG_DATA);/*插入排序：请输入文本*/
//	TEST(shell_sort, big_arr[4], BIG_DATA);
//	TEST(quick_sort, big_arr[5], BIG_DATA);
//	TEST(merge_sort, big_arr[6], BIG_DATA);
//	TEST(radix_sort, big_arr[7], BIG_DATA);
//
//}
//-------------------------------二分查找
int Binary_search(int* arr, int len, int val) {
	int l = 0, r = len - 1, mid = (l + r) / 2;
	printf("[%d,%d],mid=%d\n", l, r, mid);
	while (l <= r) {
		if (arr[mid] == val)return mid;
		else if (arr[mid] > val)r = mid - 1;
		else l = mid + 1;
		mid = (l + r) / 2;
		printf("[%d,%d],mid=%d\n", l, r, mid);
	}
	return -1;
}
void Binary_search_output(int* arr, int len, int index) {
	if (index == -1) {
		printf("no find\n");
		return;
	}
	int flag = 0;
	if (index >= len) {
		printf("index faild\n");
		index = len; flag = 1;
	}
	int lenth = 0;
	for (int i = 0; i < len; i++) lenth += printf("%4d", i);
	putchar('\n');
	for (int i = 0; i < lenth; i++)printf("-");
	putchar('\n');
	for (int i = 0; i < index; i++)printf("%4d", arr[i]);
	if (!flag) {
		printf("\033[1;32m");
		printf("%4d", arr[index]);
		printf("\033[0m");
		for (int i = index + 1; i < len; i++)printf("%4d", arr[i]);
	}
	return;
}
//---------------------------二分查找-泛型
int Binary_search1(int arr[], int len) {
	int l = 0, r = len - 1, mid = (l + r) >> 1;
	printf("[%d,%d],mid=%d\n", l, r, mid);
	while (l <= r) {
		if (l == r && arr[mid] == 1)return mid;
		else if (arr[mid] == 1)r = mid;
		else if (arr[mid] == 0)l = mid + 1;
		printf("[%d,%d],mid=%d\n", l, r, mid);
		mid = (l + r) >> 1;
	}
	return -1;
}
//---------------------------测试
//int main() {
//	srand(time(0));
//	int arr[20] = { 0 };
//	arr[0] = rand() % 10;
//	for (int i = 1; i < 20; i++)arr[i] += arr[i - 1] + rand() % 5;
//	Binary_search_output(arr, 20, 20);
//	int val, ind;
//	putchar('\n');
//	while (scanf("%d", &val) == 1) {
//		ind = Binary_search(arr, 20, val);
//		Binary_search_output(arr, 20, ind);
//		printf("\n");
//	}
//	fflush(stdout);
//	int arr1[10] = { 0,0,0,0,0,0,1,1,1,1 };
//	Binary_search_output(arr1, 10, 10);
//	putchar('\n');
//	Binary_search_output(arr1, 10, Binary_search1(arr1, 10));
//}
//----------------------------二分答案
#define EXP 1e-4
#define min(a,b) ((a)<(b)?(a):(b))
double tax_post_salary(double salary) {
	if (salary > 0)salary -= min(salary, 3000) * 0.03;
	if (salary > 3000)salary -= (min(salary, 12000) - 3000) * 0.1;
	if (salary > 12000)salary -= (min(salary, 25000) - 12000) * 0.2;
	if (salary > 25000)salary -= (min(salary, 35000) - 25000) * 0.25;
	if (salary > 35000)salary -= (min(salary, 55000) - 35000) * 0.30;
	if (salary > 55000)salary -= (min(salary, 80000) - 55000) * 0.35;
	if (salary > 80000)salary -= (salary - 80000) * 0.45;
	return salary;
}
double tax_sub_salary(double post_salary) {
	double l = 0, r = 100000, mid = (l + r) / 2.0, ret = tax_post_salary(mid);
	while (r - l >= EXP) {
		if (fabs(ret - post_salary) <= EXP)return mid;
		else if (ret > post_salary)r = mid;
		else if (ret < post_salary)l = mid;
		mid = (l + r) / 2.0;
		ret = tax_post_salary(mid);
	}
}
////----------------------------测试
//int main() {
//	int salary;
//	std::cout << "输入税后工资:";
//	std::cin >> salary;
//	std::cout << std::endl << "税前工资为：" << tax_sub_salary(salary) << std::endl;
//	return 0;
//}
//------------------------------递归转非递归
//----------------阶乘
namespace multi {
	struct Data {
		int n;
		int ret, code, * pre_ret;
	};
	int f(int n) {
		std::stack<Data>s;
		Data a;
		a.code = 0;
		a.n = n;
		int ans;
		a.pre_ret = &ans;
		s.push(a);
		for (; !s.empty();) {
			Data& temp = s.top();
			switch (temp.code) {
			case 0:
				if (temp.n == 1) {
					temp.code = 2;
				}
				else {
					temp.code = 1;
				}
				break;
			case 1: {
				Data n;
				n.code = 0;
				n.n = temp.n - 1;
				n.pre_ret = &temp.ret;
				temp.code = 2;
				s.push(n);
			}break;
			case 2: {
				if (temp.n == 1)*(temp.pre_ret) = 1;
				else *(temp.pre_ret) = temp.ret * temp.n;
				s.pop();
			}break;
			}
		}

		return ans;
	}
}
//--------------测试
//int main() {
//	std::cout << multi::f(5);
//}
#include"struct_algorithm.h"
namespace in_order {
	using namespace Base_struct;
	struct Data {
		Base_struct::TreeNode* n;
		int code, ret;
		Data(TreeNode* n, int code) :n(n), code(code) {
			ret = 0;
		}
	};
	void non_in_order(TreeNode* root) {
		std::stack<Data>s;
		Data data(root, 0);
		s.push(data);
		while (!s.empty()) {
			Data& top = s.top();
			switch (top.code) {
			case 0: {
				if (top.n == NULL) {
					top.code = 4;
				}
				else {
					top.code += 1;
				}
			}break;
			case 1: {
				if (top.n->left != NULL) {
					Data left(top.n->left, 0);
					s.push(left);
				}
				top.code += 1;
			}break;
			case 2: {
				std::cout << top.n->val << ' ';
				top.code += 1;
			}break;
			case 3: {
				if (top.n->right != NULL) {
					Data right(top.n->right, 0);
					s.push(right);
				}
				top.code += 1;
			}break;
			case 4: {
				s.pop();
			}break;
			}
		}
	}
}
//int main() {
//	srand(time(0));
//	TreeNode* root = randomTree(10);
//	in_order::non_in_order(root);
//	std::cout.put('\n');
//	bfs(root, 10);
//}
//--------------------------------------拓补序法（归并排序）
namespace non_merge_sort {
	struct Data {
		int l, r;
		Data(int l, int r) {
			this->l = l;
			this->r = r;
		}
	};
	void __merge_sort(int* arr, int l, int r, int* buff) {
		if (r - l <= 1)return;
		int mid = (r + l) / 2;
		__merge_sort(arr, l, mid, buff);
		__merge_sort(arr, mid, r, buff);
		int p1 = l, p2 = mid, k = 0;
		while (p1 < mid || p2 < r) {
			if (p1 == mid || (p2 < r && arr[p2] < arr[p1])) {
				buff[k++] = arr[p2++];
			}
			else {
				buff[k++] = arr[p1++];
			}
		}
		for (int i = l; i < r; i++)arr[i] = buff[i - l];
	}
	void merge_sort(int* arr, int l, int r) {
		int* buff = (int*)malloc(sizeof(int) * (r - l));
		__merge_sort(arr, l, r, buff);
		free(buff);
		return;
	}
	void merge_sort_once(int* arr, int l, int r) {
		int mid{ (l + r) / 2 };
		int p1 = l, p2 = mid, k = 0;
		int* buff = new int((r - l) + 10);
		while (p1 < mid || p2 < r) {
			if (p1 == mid || (p2 < r && arr[p2] < arr[p1])) {
				buff[k++] = arr[p2++];
			}
			else {
				buff[k++] = arr[p1++];
			}
		}
		for (int i = l; i < r; i++)arr[i] = buff[i - l];
	}
	void non_merge_sort(int* arr, int l, int r) {
		std::vector<Data>v;
		Data data(l, r);
		v.push_back(data);
		for (int i = 0; i < v.size(); i++) {
			int left = v[i].l, right = v[i].r;
			int mid{ (left + right) / 2 };
			if (mid - left > 1) {
				v.push_back(Data(left, mid));
			}
			if (right - mid > 1) {
				v.push_back(Data(mid, right));
			}
		}
		for (int i = v.size() - 1; i >= 0; i--) {
			merge_sort_once(arr, v[i].l, v[i].r);
		}
	}
}
//int main() {
//	int arr[] = { 9, 5, 2, 7, 1, 8, 3, 6, 4, 0 };
//	int n = 10;
//
//	// 调用非递归版本
//	non_merge_sort::non_merge_sort(arr, 0, n);
//
//	printf("排序结果: ");
//	for (int i = 0; i < n; i++) printf("%d ", arr[i]);
//	printf("\n");
//
//	return 0;
//}
//------------------------------------------------系统栈法（快速排序）
namespace non_quick_sort {
	int getMiddle(int a, int b, int c) {
		if (a > b) {
			if (a > c) {
				if (b > c)return b;
				else return c;
			}
			else return a;
		}
		else {
			if (b > c) {
				if (a > c)return a;
				else return c;
			}
			else return b;
		}
	}

	std::ostream& operator<<(std::ostream& os, int* arr) {
		for (int i = 0; i < 10; i++) {
			os << arr[i] << ' ';
		}
		return os;
	}
	void quick_sort(int* arr, int l, int r) {
		while (r >= l) {
			//std::cout << arr << std::endl;
			if (r - l <= 2) {
				if (r - l <= 1)return;
				if (arr[l] > arr[l + 1]) {
					int temp = arr[l];
					arr[l] = arr[l + 1];
					arr[l + 1] = temp;
				}
				return;
			}
			int x = l, y = r - 1, pivot = getMiddle(arr[l], arr[r - 1], arr[(l + r) / 2]);
			while (y >= x) {
				while (arr[y] > pivot)y--;
				while (arr[x] < pivot)x++;
				if (y >= x) {
					int temp = arr[x];
					arr[x] = arr[y];
					arr[y] = temp;
					y--, x++;
				}
			}
			quick_sort(arr, l, y + 1);
			l = x;
		}
	}

	struct Data {
		int* arr, l, r;
		int x, y, pivot;
		int code;
		Data(int* arr, int l, int r) :arr(arr), l(l), r(r) {
			x = l, y = r - 1, pivot = getMiddle(arr[l], arr[r - 1], arr[(l + r) / 2]);
			code = 0;
		}
		friend std::ostream& operator<<(std::ostream& os, Data& A);
	};
	std::ostream& operator<<(std::ostream& os, Data& A) {
		os << "l:" << A.l << " r:" << A.r << " x:" << A.x << " y:" << A.y << " code:" << A.code << " pivot:" << A.pivot;
		return os;
	}

	void non_quick_sort(int* arr, int l, int r) {
		std::stack<Data>s;
		Data data(arr, l, r);
		s.push(data);
		while (!s.empty()) {
			Data& top = s.top();
			//std::cout << top << std::endl;
			//std::cout << arr << std::endl;
			switch (top.code) {
			case 0: {
				if (top.r >= top.l)top.code += 1;
				else top.code = 4;
			}break;
			case 1: {
				if (top.r - top.l <= 2) {
					if (top.r - top.l <= 1) { top.code = 4; break; }
					if (top.arr[top.l] > top.arr[top.l + 1]) {
						int temp = top.arr[top.l];
						top.arr[top.l] = top.arr[top.l + 1];
						top.arr[top.l + 1] = temp;
					}
					top.code = 4;
					break;
				}
				while (top.y >= top.x) {
					while (top.arr[top.y] > top.pivot)top.y--;
					while (top.arr[top.x] < top.pivot)top.x++;
					if (top.y >= top.x) {
						int temp = top.arr[top.x];
						top.arr[top.x] = top.arr[top.y];
						top.arr[top.y] = temp;
						top.y--, top.x++;
					}
				}
				top.code += 1;
			}break;
			case 2: {
				Data newdata(top.arr, top.l, top.y + 1);
				s.push(newdata);
				top.code += 1;
			}break;
			case 3: {
				top.l = top.x;
				top.x = top.l;
				top.y = top.r - 1;
				top.pivot = getMiddle(arr[top.l], arr[top.r - 1], arr[(top.l + top.r) / 2]);
				top.code = 0;
			}break;
			case 4: {
				s.pop();
			}break;
			}
		}
	}
	void quick_sort1(int* arr, int l, int r) {
		if (r - l <= 2) {
			if (r - l <= 1)return;
			if (arr[l] > arr[l + 1]) {
				int temp = arr[l];
				arr[l] = arr[l + 1];
				arr[l + 1] = temp;
			}
			return;
		}
		int x = l, y = r - 1, pivot = arr[l], i = l;
		while (i <= y) {
			if (arr[i] < pivot) {
				{
					int temp = arr[i];
					arr[i] = arr[x];
					arr[x] = temp;
				}
				x++;
			}
			else if (arr[i] > pivot) {
				{
					int temp = arr[i];
					arr[i] = arr[y];
					arr[y] = temp;
				}
				y--;
			}
			else {
				i++;
			}
		}
		quick_sort1(arr, l, x);
		quick_sort1(arr, y + 1, r);

	}
}
//int main() {
//	int arr[] = { 9, 5, 2, 7, 1, 8, 3, 6, 4, 0 };
//	int n = 10;
//
//	// 调用非递归版本
//	non_quick_sort::non_quick_sort(arr, 0, n);
//
//	printf("排序结果: ");
//	for (int i = 0; i < n; i++) printf("%d ", arr[i]);
//	printf("\n");
//
//	return 0;
//}

// --------------------------------------Quick-find
//class Quick_find {
//private:
//#define MAX_COUNT 1000
//	int color[MAX_COUNT + 1]{ 0 };
//	int count;
//public:
//	Quick_find() = delete;
//	explicit Quick_find(int n) :count{ n } {
//		for (int i = 0; i <= n; i++)color[i] = i;
//	}
//	int find(int x) {
//		return color[x];
//	}
//	bool merge(int x, int y) {
//		if (color[x] == color[y])return false;
//		int base_color = color[x];
//		for (int i = 0; i <= count; i++) {
//			if (color[i] == base_color)color[i] = color[y];
//		}
//		return true;
//	}
//	void output() {
//		int length = 0;
//		for (int i = 0; i <= count; i++) {
//			std::cout << std::setw(3) << std::setfill(' ') << i;
//			length += 3;
//		}
//		std::cout.put('\n');
//		for (int i = 0; i <=length; i++) {
//			std::cout.put('-');
//		}
//		std::cout.put('\n');
//		for (int i = 0; i <= count; i++) {
//			std::cout << std::setw(3) << std::setfill(' ') << color[i];
//		}
//	}
//#undef MAX_COUNT
//};
//auto main() -> int {
//	Quick_find q(10);
//	int a, b;
//	while (std::cin >> a >> b) {
//		q.merge(a, b);
//		q.output();
//		std::cout.put('\n');
//	}
//}

//---------------------------------------------------Quick-union
#define MAX_COUNT 1000
class Quick_union {
private:
	int arr[MAX_COUNT + 1]{ 0 };
	int size[MAX_COUNT + 1]{ 0 };
	int count;
public:
	Quick_union() = delete;
	explicit Quick_union(int count) :count(count) {
		if (count > MAX_COUNT)throw std::out_of_range("超出范围");
		for (int i = 0; i <= count; i++) {
			arr[i] = i;
			size[i] = 1;
		}
	}
	int find(int x) {
		if (x > count || x < 0)throw std::runtime_error("x超范围");
		if (arr[x] != x) {
			arr[x] = find(arr[x]);
		}
		return arr[x];
	}
	bool merge(int x, int y) {
		if (x > count || y > count || x < 0 || y < 0)return false;
		int xx{ find(x) }, yy{ find(y) };
		if (xx == yy)return false;
		if (size[xx] <= size[yy]) {
			arr[xx] = arr[yy];
			size[yy] += size[xx];
		}
		else {
			arr[yy] = arr[xx];
			size[xx] += size[yy];
		}
		return true;
	}
	void output() {
		int length = 0;
		for (int i = 0; i <= count; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << i;
			length += 3;
		}
		std::cout.put('\n');
		for (int i = 0; i <= length; i++) {
			std::cout.put('-');
		}
		std::cout.put('\n');
		for (int i = 0; i <= count; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << arr[i];
		}
		std::cout.put('\n');
		for (int i = 0; i <= count; i++) {
			std::cout << std::setw(3) << std::setfill(' ') << size[i];
		}
	}
};
#undef MAX_COUNT
//-------------------------测试
//auto main() -> int {
//	Quick_union q(10);
//	int a, b;
//	q.output();
//	std::cout.put('\n');
//	while (std::cin >> a >> b) {
//		q.merge(a, b);
//		q.output();
//		std::cout.put('\n');
//	}
//}