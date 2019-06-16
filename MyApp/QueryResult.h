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
		std::string word;//��ѯ����
		//����ʹ��ָ����Ϊ�˱��⿽���������ļ����ݹ������ڴ����
		//���ֵ��к�
		std::shared_ptr<std::set<lineNo>> linesSetP;
		//������ļ�����vector����һ��һ�е���ʽ����
		std::shared_ptr<std::vector<std::string>> fileVectorP;
	};

	std::ostream& operator<<(std::ostream& os, const QueryResult& result);

	std::ostream& print(std::ostream& os, const QueryResult& result, const std::size_t& start, const std::size_t& end);
}

#endif // _MEMORY_RESULT_H_

