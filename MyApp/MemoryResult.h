#ifndef _MEMORY_RESULT_H_
#define _MEMORY_RESULT_H_

#include <vector>
#include <set>
#include <memory>
#include <string>

using namespace std;

class MemoryResult {
	friend ostream & print(ostream &os, const MemoryResult &result);
public:
	using lineNo = vector<string>::size_type;
	MemoryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP);

	~MemoryResult();

private:
	string word;//��ѯ����
	//����ʹ��ָ����Ϊ�˱��⿽���������ļ����ݹ������ڴ����
	shared_ptr<set<lineNo>> linesSetP;//���ֵ��к�
	shared_ptr<vector<string>> fileVectorP;//������ļ�����vector����һ��һ�е���ʽ����
};

//����print������û������ΪMemoryResult��ĳ�Ա������������ΪMemoryTest��Ҫʹ�����������
//��MemoryTest�ֲ������MemoryResult����
//������Ҫע�⣬���ں����еڶ�������ΪMemoryResult����
//���ú����ֲ���MemoryResult�ĳ�Ա�������Ҫ��������ΪMemoryResult����Ԫ
ostream & print(ostream &os, const MemoryResult &result);

#endif // _MEMORY_RESULT_H_

