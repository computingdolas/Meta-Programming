#pragma once

template<typename T>
class Vector;


template<typename T, class Derived>
class MatrixLike {
public:
	/// c'tor/ d'tor
	virtual ~MatrixLike ( ) noexcept = 0 ; // pure virtual destructor noexcept

	/// virtual operators
	virtual Vector<T> operator* (const Vector<T> & o) const = 0;

	virtual Derived inverseDiagonal( ) const = 0;
	// feel free to extend as required

protected:
};

template<typename T, class Derived>
inline MatrixLike<T, Derived>::~MatrixLike ( ) noexcept {}
