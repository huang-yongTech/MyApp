#include "pch.h"
#include "AlgorithmTest.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

AlgorithmTest::~AlgorithmTest()
{

}

void AlgorithmTest::lambdaTest() {
	size_t v1 = 40;
	//lambda表达式其实生成的是一个隐藏函数，我们用auto可以获取这个函数，不过获取的是其函数指针
	//lambda表达式最好显示指定返回类型（使用尾置返回类型）
	auto f1 = [v1]() mutable -> size_t {return ++v1; };
	v1 = 0;
	cout << "lambda表达式的运行结果：" << f1() << endl;
}

void AlgorithmTest::inserterTest() {
	list<int> list1{ 1,2,3,4 };
	list<int> list2, list3, list4{ 5,6 };

	copy(list1.begin(), list1.end(), front_inserter(list2));
	copy(list1.begin(), list1.end(), back_inserter(list3));
	copy(list1.begin(), list1.end(), inserter(list4, list4.begin()));

	auto fun = [](int i) -> void {cout << i << ","; };
	for_each(list2.begin(), list2.end(), fun);
	cout << endl;
	for_each(list3.begin(), list3.end(), fun);
	cout << endl;
	for_each(list4.begin(), list4.end(), fun);
}

//通用算法不会改变容器的大小，它只会修改容器元素的值和在容器内部移动元素
void AlgorithmTest::removeTest() {
	list<int> list1{ 1,2,3,4,5,6,7,8,9 };
	remove(list1.begin(), list1.end(), 2);
	cout << "remove操作后的列表数据：";
	for (int elem : list1) {
		cout << elem << " ";
	}
	cout << endl;
} 

void AlgorithmTest::removeIfTest() {
	list<int> sourceList{ 1,2,3,4,5,6,7,8,9 };
	auto ptr = remove_if(sourceList.begin(), sourceList.end(), [](int i) -> bool {return i % 2 == 0; });

	//对容器list的相关操作应该优先使用其成员函数，而不是使用通用算法
	//sourceList.remove_if([](int i) -> int {return i % 2 == 0; });

	//这里会打印1,3,5,7,9,6,7,8,9；
	//这是因为remove_if算法使用的是用保留的元素来覆盖要删除的元素
	//比如这里要删除的是2,4,6,8；
	//将2，4，6，8删除，剩余1,3,5,7,9，这1,3,5,7,9会覆盖掉前面的1-5元素，6,7,8,9会保留下来
	//因此打印删除元素后容器的剩余元素应该采用下面没有被注释掉的代码
	/*cout << "remove_if操作后的列表数据：";
	for (int elem : sourceList) {
		cout << elem << " ";
	}*/

	//正确的打印删除元素后容器剩余的元素
	cout << "remove_if操作后的列表数据：";
	for (auto ptr1 = sourceList.begin(); ptr1 != ptr; ptr1++)
	{
		cout << *ptr1 << " ";
	}
	cout << endl;
}

void AlgorithmTest::removeCopyIfTest() {
	list<int> list1{ 1,2,3,4,5,6,7,8,9 };
	list<int> dstList;
	//凡是带copy的算法，原容易元素保持不变
	//remove_copy_if将不满足谓词的元素拷贝到目的容器中（相当于删除了满足谓词的元素，将剩余的元素拷贝到目的容器中）
	remove_copy_if(list1.begin(), list1.end(), back_inserter(dstList), [](int i) {return i % 2; });
	cout << "remove_copy_if操作后的列表数据：";
	for (int elem : list1) {
		cout << elem << " ";
	}
	cout << endl;

	cout << "remove_copy_if操作后的目的列表数据：";
	for (int elem : dstList) {
		cout << elem << " ";
	}
	cout << endl;
}
