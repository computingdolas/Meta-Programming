#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

template <typename T>
class Vector
{
private:
	int num;
	T *ptr;

public:

	Vector(int unum, T ini); // Constructor
	~Vector(); // Destructor
	Vector(const Vector& obj); // Copy Constructor
	Vector(int unum); // Assignment constructor

	Vector& operator = (const Vector& obj); // Assignment copy operator
	Vector& operator += (const Vector& obj);// Addition assignment operator
	Vector& operator -= (const Vector& obj);// sunstraction assignment operator
	Vector operator + (const Vector& obj)const; //Addition operator
	Vector operator - (const Vector& obj) const; //Substraction

	const T& operator()(int index) const;
	T& operator()(int index);
	void display() const;



	double l2Norm() const;
	int size() const;


};

template <typename T>
Vector<T>::Vector(int unum,T ini)
{
	//cout<<" The constructor is created "<<endl;
	num = unum;
	ptr = new T [num];
	for (int i = 0;i <num ;++i)
		*(ptr+i)= ini;

}
template <typename T>
Vector<T>::~Vector()
{
	//cout<<" Destructor called"<<endl;
	delete [] ptr;
}
template <typename T>
Vector<T>::Vector(const Vector& obj)
{
	//cout<<" The copy constructor is called "<<endl;

	num = obj.num;
	ptr = new T [num];
	for (int i =0; i<num; ++i)
		*(ptr +i)= *(obj.ptr +i);

}
template <typename T>
Vector<T>::Vector(int unum)
{
	//cout<<" The assignment constructot is called"<<endl;
	num = unum ;
	ptr = new T [num];
	for (int i =0; i < num ; ++i)
		*(ptr +i)= 0;

}
template <typename T>
Vector<T>& Vector<T>:: operator=(const Vector& obj)
{
	//cout<<" Assignmnet operator is called"<<endl ;
	if (this != &obj)
	{
		num=obj.num;
		for (int i =0; i <num ;++i)
		{
			*(this->ptr +i)= *(obj.ptr +i);
		}
	}
	return *(this);
}

template <typename T>
Vector<T>& Vector<T>::operator +=(const Vector& obj)
{
	//cout<<" assignment Addition operator is called"<<endl;
	num= obj.num;
	for (int i =0 ; i<num ; ++i )
	{
		*(this->ptr +i) += *(obj.ptr+i);
	}

	return (*this);
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector& obj)
{
	//cout<<" assignment substraction operator is called"<<endl;
	num= obj.num;
	for (int i =0 ; i<num ; ++i )
	{
		*(this->ptr +i) -= *(obj.ptr+i);
	}

	return (*this);
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector& obj) const
{
	//cout<<" Addition operator is called"<<endl;
	Vector temp(*this);
	temp+=obj;
	return temp;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector& obj) const
{
	//cout<<" substraction operator is called"<<endl;
	Vector temp(*this);
	temp-=obj;
	return temp;
}
template <typename T>
int Vector<T>::size() const
{
	return (this->num);
}

template <typename T>
const T& Vector<T>::operator()(int index) const
{
	return(*(this->ptr + index));
}


template <typename T>
T& Vector<T>::operator()(int index)
{
	return(*(this->ptr + index));
}

template <typename T>
double Vector<T>::l2Norm() const
{
	//cout<<" Calling l2 norm function "<<endl;

	double norm =0;
	for(int i =0 ; i< (this->num); ++i )
	{
		norm += (*this)(i) * (*this)(i);
	}
	return (sqrt(norm));
}

template <typename T>
void Vector<T>::display() const
{
	//cout<<" display function is called"<<endl;
	for (int i =0; i < this->num;++i)
		std::cout<<(*this)(i)<<std::endl;
}
