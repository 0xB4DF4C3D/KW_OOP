#pragma once

// Class for automatically deallocate instance.
template<typename T>
class Ptr {
public:

	Ptr();
	Ptr(Ptr<T>& otherInstance);
	~Ptr();

	// Create an instance to be managed automatically.
	static Ptr<T> Create();

	// Decrease the reference count.
	void decreaseRef();

	Ptr<T>& operator=(const Ptr<T>& ohterPtr);

	// Make it easy to access.
	T* operator->() { return mSharedInstance; }

private:
	T* mSharedInstance;		// Object to be managed automatically.
	int* mReferenceCount;	// Number of object referenced.
	bool* isBaby;			// flag for Temporary object.
};

template<typename T>
inline Ptr<T>::Ptr() {
	this->mSharedInstance = nullptr;
	this->mReferenceCount = nullptr;
	this->isBaby = nullptr;
}

template<typename T>
inline Ptr<T>::Ptr(Ptr<T>& otherPtr) {
	this->mSharedInstance = otherPtr.mSharedInstance;
	this->mReferenceCount = otherPtr.mReferenceCount;
	this->isBaby = otherPtr.isBaby;

	// Only for non-temporary objects.
	if (*(this->isBaby) == false) {
		cout << "ref cnt : " << *(this->mReferenceCount) << " -> " << *(this->mReferenceCount) + 1 << endl;
		(*(otherPtr.mReferenceCount))++;
	} 
}

template<typename T>
inline Ptr<T>::~Ptr() {
	decreaseRef();
}

template<typename T>
inline Ptr<T> Ptr<T>::Create() {
	Ptr<T> newPtr;

	cout << "ref cnt : " << 0 << " -> " << 1 << endl;
	newPtr.mReferenceCount = new int(1);
	newPtr.mSharedInstance = new T();
	newPtr.isBaby = new bool(true);
	return newPtr;
}

template<typename T>
inline void Ptr<T>::decreaseRef() {

	// Once the temporary object is destroyed,
	// it is no longer a baby.
	if (*(this->isBaby) == true) {
		*(this->isBaby) = false;
		return;
	}

	// Reduce the reference count by one.
	cout << "ref cnt : " << *(this->mReferenceCount) << " -> " << *(this->mReferenceCount) - 1 << endl;
	(*(this->mReferenceCount))--;

	// If the reference count is 0
	if (*(this->mReferenceCount) == 0) {
		cout << "Deallocate the instance." << endl;
		delete this->mSharedInstance;
		delete this->mReferenceCount;
	}
}

template<typename T>
inline Ptr<T>& Ptr<T>::operator=(const Ptr<T>& otherPtr) {
	
	// When it assign itself.
	if (this->mSharedInstance == (otherPtr.mSharedInstance))
		return *this;

	// If the object has not yet been created
	if (this->mReferenceCount != nullptr)
		decreaseRef();
	

	this->mSharedInstance = otherPtr.mSharedInstance;
	this->isBaby = otherPtr.isBaby;

	cout << "ref cnt : " << *(otherPtr.mReferenceCount) << " -> " << *(otherPtr.mReferenceCount) + 1 << endl;
	(*(otherPtr.mReferenceCount))++;
	this->mReferenceCount = otherPtr.mReferenceCount;

	return *this;
}
