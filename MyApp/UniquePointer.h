#ifndef _UNIQUE_POINTER_H_
#define _UNIQUE_POINTER_H_

#include "DebugDelete.h"

//ตฺ16ีย28ฬโ

template<typename, typename> class UniquePointer;
template<typename T, typename D = DebugDelete> void swap(UniquePointer<T, D> & lhs, UniquePointer<T, D> & rhs);

template<typename T, typename D = DebugDelete>
class UniquePointer {

	friend void swap(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs);

public:

	UniquePointer() = default;

	explicit UniquePointer(T* ptr);

	UniquePointer(const UniquePointer& up) = delete;

	UniquePointer& operator=(const UniquePointer& up) = delete;

	UniquePointer(UniquePointer&& up) noexcept;

	UniquePointer& operator=(UniquePointer&& up) noexcept;

	UniquePointer& operator=(std::nullptr_t n) noexcept;

	~UniquePointer();


	T& operator*() const;

	T& operator->() const;

	operator bool() const;

	T* get() const noexcept;

	void swap(UniquePointer<T, D>& up);

	void reset() noexcept;

	void reset(T* p) noexcept;

	T* release();

private:

	T* ptr = nullptr;

	D deleter = D();
};

#endif

template<typename T, typename D>
inline UniquePointer<T, D>::UniquePointer(T* ptr) : ptr(ptr) {
}

template<typename T, typename D>
inline UniquePointer<T, D>::UniquePointer(UniquePointer&& up) noexcept
	:ptr(up.ptr), deleter(up.deleter) {
	up.ptr = nullptr;
}

template<typename T, typename D>
inline UniquePointer<T, D>& UniquePointer<T, D>::operator=(UniquePointer&& up) noexcept {
	if (*ptr != up.ptr) {
		ptr = up.ptr;
		deleter = up.deleter;

		up.ptr = nullptr;
	}

	return *this;
}

template<typename T, typename D>
inline UniquePointer<T, D>& UniquePointer<T, D>::operator=(std::nullptr_t n) noexcept {
	if (n == nullptrk) {
		deleter(ptr);
		ptr = nullptr;
	}

	return *this;
}

template<typename T, typename D>
inline UniquePointer<T, D>::~UniquePointer() {
	deleter(ptr);
	ptr = nullptr;
}

template<typename T, typename D>
inline T& UniquePointer<T, D>::operator*() const {
	return *ptr;
}

template<typename T, typename D>
inline T& UniquePointer<T, D>::operator->() const {
	return *ptr;
}

template<typename T, typename D>
inline UniquePointer<T, D>::operator bool() const {
	return ptr ? true : false;
}

template<typename T, typename D>
inline T* UniquePointer<T, D>::get() const noexcept {
	return ptr;
}

template<typename T, typename D>
inline void UniquePointer<T, D>::swap(UniquePointer<T, D>& up) {
	::swap(*this, up);
}

template<typename T, typename D>
inline void UniquePointer<T, D>::reset() noexcept {
	deleter(ptr);
	ptr = nullptr;
}

template<typename T, typename D>
inline void UniquePointer<T, D>::reset(T* p) noexcept {
	deleter(ptr);
	ptr = p;
}

template<typename T, typename D>
inline T* UniquePointer<T, D>::release() {
	T* ret = ptr;
	ptr = nullptr;
	return ret;
}

template<typename T, typename D>
void swap(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs) {
	std::swap(lhs->ptr, rhs->ptr);
	std::swap(lhs->deleter, rhs->deleter);
}
