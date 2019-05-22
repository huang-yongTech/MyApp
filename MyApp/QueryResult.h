#ifndef _MEMORY_RESULT_H_
#define _MEMORY_RESULT_H_

#include <vector>
#include <set>
#include <memory>
#include <string>

using namespace std;

class QueryResult {

	friend ostream& operator<<(ostream& os, const QueryResult& result);

	friend ostream& print(ostream& os, const QueryResult& result, const std::size_t& start, const std::size_t& end);

public:

	using lineNo = vector<string>::size_type;

	QueryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP);

	~QueryResult();

	set<lineNo>::iterator begin() const;

	set<lineNo>::iterator end() const;

	shared_ptr<vector<string>> getFile();

private:
	string word;//查询单词
	//这里使用指针是为了避免拷贝，以免文件内容过大导致内存溢出
	//出现的行号
	shared_ptr<set<lineNo>> linesSetP;
	//输入的文件，在vector中以一行一行的形式保存
	shared_ptr<vector<string>> fileVectorP;
};

ostream& operator<<(ostream& os, const QueryResult& result);

ostream& print(ostream& os, const QueryResult& result, const std::size_t& start, const std::size_t& end);

#endif // _MEMORY_RESULT_H_

