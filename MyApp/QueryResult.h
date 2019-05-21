#ifndef _MEMORY_RESULT_H_
#define _MEMORY_RESULT_H_

#include <vector>
#include <set>
#include <memory>
#include <string>

using namespace std;

class QueryResult {

	friend ostream& operator<<(ostream& os, const QueryResult& result);

public:

	using lineNo = vector<string>::size_type;

	QueryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP);

	~QueryResult();

	set<lineNo>::iterator begin() const;

	set<lineNo>::iterator end() const;

	shared_ptr<vector<string>> getFile();

private:
	string word;//��ѯ����
	//����ʹ��ָ����Ϊ�˱��⿽���������ļ����ݹ������ڴ����
	//���ֵ��к�
	shared_ptr<set<lineNo>> linesSetP;
	//������ļ�����vector����һ��һ�е���ʽ����
	shared_ptr<vector<string>> fileVectorP;
};

ostream& operator<<(ostream& os, const QueryResult& result);

#endif // _MEMORY_RESULT_H_

