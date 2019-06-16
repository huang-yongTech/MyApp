#ifndef _QUERY_HISTORY_H_
#define _QUERY_HISTORY_H_

#include <vector>
#include "Query.h"

namespace chapter15 {

	class QueryHistory {

	public:

		QueryHistory();

		~QueryHistory();

		Query& operator[](const std::size_t& pos) const;

		void add(const Query& query);

	private:

		std::vector<std::shared_ptr<Query>> historyVec;
	};
}

#endif