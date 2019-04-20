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
	string word;//查询单词
	//这里使用指针是为了避免拷贝，以免文件内容过大导致内存溢出
	shared_ptr<set<lineNo>> linesSetP;//出现的行号
	shared_ptr<vector<string>> fileVectorP;//输入的文件，在vector中以一行一行的形式保存
};

//这里print函数并没有声明为MemoryResult类的成员函数，这是因为MemoryTest需要使用这个函数，
//而MemoryTest又不想持有MemoryResult对象
//这里需要注意，由于函数中第二个参数为MemoryResult对象，
//而该函数又不是MemoryResult的成员，因此需要将其声明为MemoryResult的友元
ostream & print(ostream &os, const MemoryResult &result);

#endif // _MEMORY_RESULT_H_

