#ifndef _SHARED_POINTER_H_
#define _SHARED_POINTER_H_

#include <functional>
#include "DebugDelete.h"

//第16章28题

template<typename> class SharedPointer;
template<typename T> void swap(SharedPointer<T>& lhs, SharedPointer<T>& rhs);

template<typename T>
class SharedPointer {

	friend void swap(SharedPointer<T>& lhs, SharedPointer<T>& rhs);

public:

	SharedPointer() = default;

	explicit SharedPointer(T* ptr, std::function<void(T*)> deleter = DebugDelete());

	SharedPointer(const SharedPointer& sp);

	SharedPointer(SharedPointer&& sp) noexcept;

	SharedPointer& operator=(const SharedPointer& sp);

	SharedPointer& operator=(SharedPointer&& sp) noexcept;

	~SharedPointer();


	operator bool() const;

	T& operator*() const;

	T& operator->() const;

	size_t useCount() const;

	T* get() const noexcept;

	bool isUnique() const noexcept;

	void swap(SharedPointer<T> sp);

	void reset() noexcept;

	void reset(T* p);

	void reset(T* p, const std::function<void(T*)> d);

private:
	//指针
	T* ptr = nullptr;
	//引用计数
	size_t* refCount = new size_t(0);

	std::function<void(T*)> deleter;

	void decrementAndDestroy();
};

template<typename T>
SharedPointer<T>::SharedPointer(T* ptr, std::function<void(T*)> deleter)
	: ptr(ptr), refCount(new size_t(1)), deleter(deleter) {
}

template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& sp)
	: ptr(sp.ptr), refCount(sp.refCount), deleter(sp.deleter) {
	++* refCount;
}

template<typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& sp) noexcept
	: ptr(sp.ptr), refCount(sp.refCount), deleter(std::move(sp.deleter)) {
	sp.ptr = nullptr;
	sp.refCount = nullptr;
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& sp) {
	++* sp.refCount;

	decrementAndDestroy();

	ptr = sp.ptr;
	refCount = sp.refCount;
	deleter = sp.deleter;

	return *this;
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer&& sp) noexcept {
	if (*this != sp) {
		decrementAndDestroy();

		::swap(*this, sp);

		sp.ptr = nullptr;
		sp.refCount = nullptr;
	}

	return *this;
}

template<typename T>
SharedPointer<T>::~SharedPointer() {
	decrementAndDestroy();
}

template<typename T>
SharedPointer<T>::operator bool() const {
	return ptr ? true : false;
}

template<typename T>
T& SharedPointer<T>::operator *() const {
	return *ptr;
}

template<typename T>
T& SharedPointer<T>::operator ->() const {
	return *ptr;
}

template<typename T>
size_t SharedPointer<T>::useCount() const {
	return *refCount;
}

template<typename T>
T* SharedPointer<T>::get() const noexcept {
	return ptr;
}

template<typename T>
bool SharedPointer<T>::isUnique() const noexcept {
	return *refCount == 1;
}

template<typename T>
void SharedPointer<T>::swap(SharedPointer<T> sp) {
	::swap(*this, sp);
}

template<typename T>
void SharedPointer<T>::reset() noexcept {
	decrementAndDestroy();
}

template<typename T>
void SharedPointer<T>::reset(T* p) {
	if (ptr != p) {
		decrementAndDestroy();

		ptr = p;
		refCount = new std::size_t(1);
	}
}

template<typename T>
void SharedPointer<T>::reset(T* p, const std::function<void(T*)> d) {
	if (ptr != p) {
		decrementAndDestroy();

		ptr = p;
		refCount = new std::size_t(1);
		deleter = d;
	}
}

template<typename T>
void SharedPointer<T>::decrementAndDestroy() {
	if (ptr) {
		if (-- * refCount == 0) {
			delete refCount;
			deleter(ptr);
		}
		refCount = nullptr;
		ptr = nullptr;
	}
}

template<typename T>
inline void swap(SharedPointer<T>& lhs, SharedPointer<T>& rhs) {
	std::swap(lhs->ptr, rhs->ptr);
	std::swap(lhs->refCount, rhs->refCount);
	std::swap(lhs->deleter, rhs->deleter);
}

#endif
