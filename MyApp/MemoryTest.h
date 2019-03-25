#ifndef _MEMORY_TEST_H_
#define _MEMORY_TEST_H_

#include <map>
#include "MemoryResult.h"

using namespace std;

class MemoryTest {
public:
	using lineNo = vector<string>::size_type;

	MemoryTest() = default;
	MemoryTest(ifstream &fileStream);

	//��ѯ����
	MemoryResult query(const string &word) const;

	void runQuries() const;

	void runQuries(ifstream &fileStream) const;

	~MemoryTest();

private:
	//����ʹ��ָ����Ϊ�˱��⿽���������ļ����ݹ������ڴ����
	map<string, shared_ptr<set<lineNo>>> linesMap;//�������������кŵ�ӳ��
	shared_ptr<vector<string>> filesVectorP;//�����ļ�
};

#endif

