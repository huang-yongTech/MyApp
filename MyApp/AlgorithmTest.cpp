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
	//lambda���ʽ��ʵ���ɵ���һ�����غ�����������auto���Ի�ȡ���������������ȡ�����亯��ָ��
	//lambda���ʽ�����ʾָ���������ͣ�ʹ��β�÷������ͣ�
	auto f1 = [v1]() mutable -> size_t {return ++v1; };
	v1 = 0;
	cout << "lambda���ʽ�����н����" << f1() << endl;
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

//ͨ���㷨����ı������Ĵ�С����ֻ���޸�����Ԫ�ص�ֵ���������ڲ��ƶ�Ԫ��
void AlgorithmTest::removeTest() {
	list<int> list1{ 1,2,3,4,5,6,7,8,9 };
	remove(list1.begin(), list1.end(), 2);
	cout << "remove��������б����ݣ�";
	for (int elem : list1) {
		cout << elem << " ";
	}
	cout << endl;
} 

void AlgorithmTest::removeIfTest() {
	list<int> sourceList{ 1,2,3,4,5,6,7,8,9 };
	auto ptr = remove_if(sourceList.begin(), sourceList.end(), [](int i) -> bool {return i % 2 == 0; });

	//������list����ز���Ӧ������ʹ�����Ա������������ʹ��ͨ���㷨
	//sourceList.remove_if([](int i) -> int {return i % 2 == 0; });

	//������ӡ1,3,5,7,9,6,7,8,9��
	//������Ϊremove_if�㷨ʹ�õ����ñ�����Ԫ��������Ҫɾ����Ԫ��
	//��������Ҫɾ������2,4,6,8��
	//��2��4��6��8ɾ����ʣ��1,3,5,7,9����1,3,5,7,9�Ḳ�ǵ�ǰ���1-5Ԫ�أ�6,7,8,9�ᱣ������
	//��˴�ӡɾ��Ԫ�غ�������ʣ��Ԫ��Ӧ�ò�������û�б�ע�͵��Ĵ���
	/*cout << "remove_if��������б����ݣ�";
	for (int elem : sourceList) {
		cout << elem << " ";
	}*/

	//��ȷ�Ĵ�ӡɾ��Ԫ�غ�����ʣ���Ԫ��
	cout << "remove_if��������б����ݣ�";
	for (auto ptr1 = sourceList.begin(); ptr1 != ptr; ptr1++)
	{
		cout << *ptr1 << " ";
	}
	cout << endl;
}

void AlgorithmTest::removeCopyIfTest() {
	list<int> list1{ 1,2,3,4,5,6,7,8,9 };
	list<int> dstList;
	//���Ǵ�copy���㷨��ԭ����Ԫ�ر��ֲ���
	//remove_copy_if��������ν�ʵ�Ԫ�ؿ�����Ŀ�������У��൱��ɾ��������ν�ʵ�Ԫ�أ���ʣ���Ԫ�ؿ�����Ŀ�������У�
	remove_copy_if(list1.begin(), list1.end(), back_inserter(dstList), [](int i) {return i % 2; });
	cout << "remove_copy_if��������б����ݣ�";
	for (int elem : list1) {
		cout << elem << " ";
	}
	cout << endl;

	cout << "remove_copy_if�������Ŀ���б����ݣ�";
	for (int elem : dstList) {
		cout << elem << " ";
	}
	cout << endl;
}
