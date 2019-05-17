#ifndef _MEMORY_TEST_H_
#define _MEMORY_TEST_H_

#include <map>
#include "QueryResult.h"

class TextQuery {

public:
	using lineNo = vector<string>::size_type;

	TextQuery() = default;

	TextQuery(ifstream &fileStream);

	//��ѯ����
	QueryResult query(const string &word) const;

	void runQuries() const;

	void runQuries(ifstream &fileStream) const;

	~TextQuery();

private:
	//����ʹ��ָ����Ϊ�˱��⿽���������ļ����ݹ������ڴ����
	map<string, shared_ptr<set<lineNo>>> linesMap;//�������������кŵ�ӳ��

	shared_ptr<vector<string>> filesVectorP;//�����ļ�
};

#endif

