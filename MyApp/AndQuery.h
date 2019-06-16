#ifndef _AND_QUERY_H_
#define _AND_QUERY_H_

#include "BinaryQuery.h"
#include <iostream>

namespace chapter15 {

	class AndQuery : public BinaryQuery {

		friend inline Query operator&(const Query& lq, const Query& rq);

	public:

		AndQuery();

		AndQuery(const Query& lQuery, const Query& rQuery)
			:BinaryQuery(lQuery, rQuery, "&") {
			std::cout << "AndQuery(const Query& lQuery, const Query& rQuery)" << std::endl;
		}

		~AndQuery();

	private:

		chapter12::QueryResult eval(const chapter12::TextQuery& textQuery) const override;
	};

	//��ע���˴������� & �������������ļ��ⲿҪʹ��ʱ�����������ͷ�ļ�������ᱨ�޷����ʵ��ⲿ���Ӵ���Link2019����
	inline Query operator&(const Query& lq, const Query& rq) {
		//��return�����ʽ������Query�Ĺ��캯�����ȼ���Query(shared_ptr<QueryBase>(new AndQuery(lq, rq)))
		return std::shared_ptr<QueryBase>(new AndQuery(lq, rq));
	}
}

#endif