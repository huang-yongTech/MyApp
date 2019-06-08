#ifndef _CHAPTER_SIXTEEN_H_
#define _CHAPTER_SIXTEEN_H_

#include <ostream>
#include <string>
#include <vector>

class Chapter16 {
	
public:

	//�ȽϺ���ģ�����ʹ��ͬһ�ֱȽϲ��������������Խ�ʡ�����ߵĹ�����
	template<typename T>
	int compare(const T& lhs, const T& rhs) {
		if (lhs < rhs) {
			return -1;
		}

		if (rhs < lhs) {
			return 1;
		}

		return 0;
	}

	template<typename IteratorT, typename ValueT>
	bool findX(const IteratorT& firstT, const IteratorT& lastT,
		const ValueT& valueT) {

		IteratorT begins = firstT;
		while (begins != lastT) {
			if (*begins == valueT) {
				return true;
			}
			++begins;
		}
		return false;
	}

	//��ӡ���ⳤ�������С�����飨��ʵ��ƥ��ʱ������ƥ��ú�����
	template<typename T, unsigned N>
	void print(const T(&p1)[N]) {
		for (auto s = p1; s != p1 + N; ++s) {
			cout << *s << " ";
		}
		cout << endl;
	}

	//���ذ汾
	template<typename T>
	void print(const T& arr) {
		for (auto& elem : arr) {
			cout << elem << " ";
		}
		cout << endl;
	}

	//����ͨ��decltype�ƶϳ����ĺ�������������һ����������
	template<typename Arr>
	auto begin(const Arr& arr) -> decltype(arr.begin()) {
		return arr.begin();
	}

	template<typename Arr>
	auto end(const Arr& arr)->decltype(arr.end()) {
		return arr.end();
	}

	template<typename T, unsigned N>
	unsigned getArrLength(const T(&arr)[N]) {
		return N;
	}

	//��16�µ�19��
	template<typename C>
	std::ostream& displayContainerItem(std::ostream& os, const C& c) {
		//ʹ��������size_type��size()��Ա��ѭ����ӡ����
		/*for (typename C::size_type i = 0; i != c.size(); ++i) {
			os << c[i] << " ";
		}*/

		//ʹ�������ĵ�������Ա����ӡ����
		for (auto first = c.begin(); first != c.end(); ++first) {
			os << *first << " ";
		}
		os << endl;

		return os;
	}

	//��16��41��
	template<typename T>
	auto sum(T t1, T t2) -> typename std::remove_reference<decltype(t1 + t2)>::type {
		return t1 + t2;
	}

	//��16��47��
	template<typename F, typename T1, typename T2>
	void flip(F f, T1&& t1, T2&& t2) {
		//f(t2, t1);
		f(std::forward<T2>(t2), std::forward<T1>(t1));

		cout << "t1 = " << t1 << "��t2 = " << t2 << endl;
	}

	//��16��47��
	void g(std::string& s1, std::string& s2) {
		s1 = "changed s1";
		s2 = "changed s2";
	}

	//��16��51��
	template<typename T, typename... Args>
	void foo(const T& t, const Args& ... args) {
		cout << "ģ�����������" << sizeof...(Args) << endl;
		cout << "ʵ�ʴ������������" << sizeof...(args) << endl;
	}

	//��16��53��
	template<typename T>
	std::ostream& print(std::ostream& os, const T& t) {
		os << t << endl;
		return os;
	}

	//��16��53��
	template<typename T, typename...Args>
	std::ostream& print(std::ostream& os, const T& t, const Args& ...args) {
		os << t << ",";
		return print(os, args...);
	}

	//��16��56��
	template<typename T>
	std::string debugRep(const T& t) {
		std::ostringstream sstream;
		sstream << t;
		return sstream.str();
	}

	template<typename T>
	std::string debugRep(T* p) {
		std::ostringstream sstream;
		sstream << "pointer:" << p << ",";

		if (p) {
			sstream << debugRep(*p);
		} else {
			sstream << " null pointer" << endl;
		}

		return sstream.str();
	}

	//��16��65��
	template<>
	std::string debugRep(char* p) {
		std::string str(p);
		return str;
	}

	template<>
	std::string debugRep(const char* p) {
		std::string str(p);
		return str;
	}

	template<typename...Args>
	std::ostream& errorMsg(std::ostream& os, Args...args) {
		return print(os, debugRep(args)...);
	}

	//��16��61��
	template<typename T, typename...Args>
	std::shared_ptr<T> my_make_shared(Args&& ...args) {
		std::shared_ptr<T> ret(new T(std::forward<Args>(args)...));
		return ret;
	}

	//��16��63��
	template<typename T>
	std::size_t countNum(std::vector<T>& vec, const T& t) {
		std::size_t sum = 0;

		for (T& t1 : vec) {
			if (t1 == t) {
				++sum;
			}
		}

		return sum;
	}

	//��16��64��
	template<>
	std::size_t countNum(std::vector<const char*>& vec, const char* const& cp) {
		std::size_t sum = 0;

		for (const char* c : vec) {
			//������ֱ�ӱȽ�����ָ�룬������Ϊ��ͬ���ַ��������Ǳ�����ͬһ���ڴ��ַ�ģ���˿���ֱ�ӱȽ�ָ�롣
			//��������²���ֱ�ӱȽ�ָ�룬��ᵼ��������Ľ����
			/*if (c == cp) {
				++sum;
			}*/

			//�����Բ���C�е�strcmp����������ר�������Ƚ��ַ���������
			sum += std::strcmp(c, cp) == 0 ? 1 : 0;
		}

		return sum;
	}

};

#endif