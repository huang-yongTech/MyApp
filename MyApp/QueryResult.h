#ifndef _MEMORY_RESULT_H_
#define _MEMORY_RESULT_H_

#include <vector>
#include <set>
#include <memory>
#include <string>

namespace chapter12 {

	class QueryResult {

		friend std::ostream& operator<<(std::ostream& os, const QueryResult& result);

		friend std::ostream& print(std::ostream& os, const QueryResult& result, const std::size_t& start, const std::size_t& end);

	public:

		using lineNo = std::vector<std::string>::size_type;

		QueryResult(std::string word, std::shared_ptr<std::set<lineNo>> linesSetP,
			std::shared_ptr<std::vector<std::string>> fileVectorP);

		~QueryResult();

		std::set<lineNo>::iterator begin() const;

		std::set<lineNo>::iterator end() const;

		std::shared_ptr<std::vector<std::string>> getFile();

	private:
		std::string word;//查询单词
		//这里使用指针是为了避免拷贝，以免文件内容过大导致内存溢出
		//出现的行号
		std::shared_ptr<std::set<lineNo>> linesSetP;
		//输入的文件，在vector中以一行一行的形式保存
		std::shared_ptr<std::vector<std::string>> fileVectorP;
	};

	std::ostream& operator<<(std::ostream& os, const QueryResult& result);

	std::ostream& print(std::ostream& os, const QueryResult& result, const std::size_t& start, const std::size_t& end);
}

#endif // _MEMORY_RESULT_H_

