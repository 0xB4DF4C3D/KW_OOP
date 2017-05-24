#pragma once

template<typename T>
class Ptr {
public:

	Ptr();
	Ptr(Ptr<T>& otherInstance);
	~Ptr();

	static Ptr<T> Create();

	void deleteThis();

	Ptr<T>& operator=(const Ptr<T>& ohterPtr);

	T* operator->() { return mSharedInstance; }

private:
	T* mSharedInstance;
	int* mReferenceCount;
};

template<typename T>
inline Ptr<T>::Ptr() {
	this->mSharedInstance = nullptr;
	this->mReferenceCount = nullptr;
}

template<typename T>
inline Ptr<T>::Ptr(Ptr<T>& otherPtr) {
	this->mSharedInstance = otherPtr.mSharedInstance;

	this->mReferenceCount = otherPtr.mReferenceCount;

	if (*(this->mReferenceCount) > 0) {
		cout << "ref cnt : " << *(this->mReferenceCount) << " -> " << *(this->mReferenceCount) + 1 << endl;
	}
	
	(*(otherPtr.mReferenceCount))++;
}

template<typename T>
inline Ptr<T>::~Ptr() {
	deleteThis();
}

template<typename T>
inline Ptr<T> Ptr<T>::Create() {
	Ptr<T> newPtr;

	cout << "ref cnt : " << 0 << " -> " << 1 << endl;
	newPtr.mReferenceCount = new int(-2);
	newPtr.mSharedInstance = new T();
	return newPtr;
}

template<typename T>
inline void Ptr<T>::deleteThis() {
	if (this->mReferenceCount == nullptr)
		return;

	if (*(this->mReferenceCount) == -1) {
		*(this->mReferenceCount) = 1;
		return;
	}

	cout << "ref cnt : " << *(this->mReferenceCount) << " -> " << *(this->mReferenceCount) - 1 << endl;
	(*(this->mReferenceCount))--;

	if (*(this->mReferenceCount) == 0) {
		cout << "Deallocate the instance." << endl;
		delete this->mSharedInstance;
		delete this->mReferenceCount;
	}
}

template<typename T>
inline Ptr<T>& Ptr<T>::operator=(const Ptr<T>& otherPtr) {
	
	if (this->mSharedInstance == (otherPtr.mSharedInstance))
		return *this;

	if (this->mReferenceCount != nullptr) {
		deleteThis();
	}

	this->mSharedInstance = otherPtr.mSharedInstance;

	cout << "ref cnt : " << *(otherPtr.mReferenceCount) << " -> " << *(otherPtr.mReferenceCount) + 1 << endl;
	(*(otherPtr.mReferenceCount))++;
	this->mReferenceCount = otherPtr.mReferenceCount;

	return *this;
}
