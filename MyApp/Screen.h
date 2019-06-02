#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <ostream>
#include <string>

//��16��14��

//������ģ��
template<unsigned M, unsigned N> class Screen {
	using sizeType = std::string::size_type;

	friend std::ostream& operator<<(std::ostream& os, const Screen& screen) {
		os << "width = " << screen.width << " height = " << screen.height;
		return os;
	}

	//�������������ʱ���������������Ϊconst����Ϊ��Ҫ�޸Ĳ����ĳ�Ա����ֵ
	friend std::istream& operator>>(std::istream& is, Screen& screen) {
		if (is) {
			is >> screen.width >> screen.height;
		}

		return is;
	}

public:

	Screen();

	~Screen();

private:

	//�÷�����ģ�������Ĳ���ֻ�ܽ��ܷǸ����������Windows�ն˵���������������ո�������������ֲ���Ҫ�Ľ��
	decltype(M) width;

	decltype(N) height;
};

template<unsigned M, unsigned N>
Screen<M, N>::Screen() : width(M), height(N) {
}

template<unsigned M, unsigned N>
Screen<M, N>::~Screen() {
}

#endif
