#pragma once

#include <iostream>
#include <fstream>
#include <cassert>
#include "Vector.h"
#include "MatrixLike.h"

using std::cout;
using std::cin;
using std::endl;
using std::ostream;

template <typename T, size_t rows , size_t cols>
class Matrix : public MatrixLike<T , Matrix<T , rows , cols>,rows,cols>
{
	private:
	//int row;
	//int col;
	T *ptr;


	public:
	int getrow()
	{
		return row;
	}


	//Matrix(T ini); //Constructor
	~Matrix() override;//Destructor
	//Matrix(const Matrix &obj);// Copy constructor
	//Matrix(int nrow ,int ncol);// Assignment Constructor




	//Matrix& operator = (const Matrix& obj);//Assignment Operator
 	void display() const ;// Dislplay Function

 	Matrix& operator+=(const Matrix& obj);
 	Matrix& operator-=(const Matrix& obj);
 	//const T& operator()(int r, int c) const;
	//T& operator()(int r, int c ) ;


	Matrix operator+(const Matrix& obj) const;
 	Matrix operator-(const Matrix& obj) const;
 	Matrix& operator*=(const Matrix& obj);
 	Matrix operator*(const Matrix& obj);
 	bool operator==(const Matrix& obj);

 	bool operator!=(const Matrix& obj);
 	Matrix inverseDiagonal() const override;

 	// Matrix Vector multiplication

 	Vector<T> operator*(const Vector<T>& obj) const override ;


};
template <typename T, size_t rows , size_t cols>
const T& Matrix<T, size_t rows, size_t cols>::operator()(int r, int c) const
{
   	return(*(ptr + r * cols + c ));
}

template <typename T, size_t rows , size_t cols>
T& Matrix<T,size_t rows, size_t cols>:: operator()(int r, int c )
{
	return (*(ptr +r * cols + c));

}

template <typename T, size_t rows , size_t cols>
Matrix<T, size_t rows, size_t cols>::Matrix(T ini)
{
	//cout<<" constructor created "<<endl;

	ptr = new T[rows*cols];
	for (int i =0;i < rows*cols ;++i)
		*(ptr+ i)= ini ;
}

template <typename T, size_t rows , size_t cols>
Matrix<T, size_t rows, size_t cols>::Matrix()
{
	int i;
	ptr = new T[rows*cols];
	for (i =0;i < rows*cols ;++i)
		*(ptr+ i)= 0 ;

}


template <typename T, size_t rows , size_t cols>
Matrix<T, size_t rows , size_t cols>::~Matrix()
{

	//cout<<" Destructor called"<<endl;
	delete [] ptr;

}

template <typename T, size_t rows , size_t cols>
Matrix<T, size_t rows, size_t cols>& Matrix<T>:: operator = (const Matrix& obj)
{
	cout<<"The Assignment copy constructor is created"<<endl;
	if (this != &obj)
	{
		for (int i =0;i < rows*cols; ++i)
			*(ptr+i)= *(obj.ptr + i);

	}

	return *this ;
}

template <typename T, size_t rows , size_t cols>
Matrix<T, size_t rows, size_t cols >::Matrix(const Matrix &obj)

{
	cout<<" The copy constructor is created "<<endl;
	ptr = new T [rows*cols];
	for (int j =0;j<rows*cols ;++j)
		*(ptr+j)= *(obj.ptr +j);

}


template <typename T, size_t rows , size_t cols>
Matrix<T>& Matrix<T>::operator+=(const Matrix& obj)
{
	cout<<" Assignment addition operator is called"<<endl;
	row=obj.row;
	col=obj.col;
	for (int i= 0;i <row*col;++i)
	{
		*(ptr +i)+= *(obj.ptr +i) ;
	}
	return(* this);
}

template <typename T, size_t rows , size_t cols>
Matrix<T>& Matrix<T>::operator-=(const Matrix& obj)
{
	cout<<" Assignment subtraction operator is called "<<endl;
	row=obj.row;
	col=obj.col;
	for(int i=0;i<row*col;++i)
	{
		*(ptr +i)-= *(obj.ptr +i);
	}
	return (*this);
}


template <typename T, size_t rows , size_t cols>
Matrix<T> Matrix<T>::operator+(const Matrix& obj) const
{
	cout<<" the Assignment binary addition operator is created"<<endl;
	Matrix temp(*this);
	temp+= obj;
	return temp;

}


template <typename T, size_t rows , size_t cols>
Matrix<T> Matrix<T>::operator-(const Matrix& obj) const
{
	cout<<" the Assignment binary substraction operator is created"<<endl;
	Matrix temp(* this);
	temp-=obj;
	return temp;

}


template <typename T, size_t rows , size_t cols>
Matrix<T>& Matrix<T>::operator*=(const Matrix& obj)
{
	 assert(this->col == obj.row);

		Matrix temp (* this );
		cout<<"Assignment Matrix Mult is created"<<endl;
		int j;
		double sum;
		int colu =obj.col;
		cout<<" col"<<colu<<endl;
		Matrix m3(this->row,obj.col,0);
		for (int i=0;i<this->row;++i)
		{
			for ( j=0;j<colu;++j)
			{
			sum =0;
				for (int k=0;k< obj.row;++k)
				{

					sum+= temp(i,k)* obj(k,j);
				}
				cout<<"the total sum is"<<sum<<endl;
			*(m3.ptr +  i*(obj.col) +j) = sum;
			}
		}
		(*this) = m3;
		return (*this);


}

template <typename T, size_t rows , size_t cols>
Matrix<T> Matrix<T>::operator*(const Matrix& obj)
{
	cout<<" The binary Assignment multiplication operator is initialised "<<endl;
	Matrix temp(*this);
	temp *= obj;
	return temp;
}


template <typename T, size_t rows , size_t cols>
bool Matrix<T>::operator==(const Matrix& obj)
{
	bool var =true ;
	row= obj.row;
	col= obj.col;

	if(this->row!=obj.row || this->col!=obj.col)
	{
		var =false;
	}
	else
	{
		for(int i =0; i <row* col ;++i)
		{
			if(*(ptr +i) != *(obj.ptr +i))
			{
			var=false;
			break;
			}

		}
	}
	return var;
}

template <typename T, size_t rows , size_t cols>
bool Matrix<T>:: operator !=(const Matrix& obj)
 {

 	if(*this == obj)
 		return false;
 	else
 		return true;
 }


template <typename T, size_t rows , size_t cols>
void Matrix<T>::display() const
{
	Matrix m3 = (* this);
	cout<<" The contents of the matrix are being displayed "<<endl;
	int i ;
	int j;
		for (i=0;i<row;++i)
		{
			cout<<endl;
			for (j=0; j<col;++j)
			//cout<<i<<"  "<<j<<endl;
			cout<<(m3(i,j))<<"\t\t";

		}

}

template <typename T, size_t rows , size_t cols>
Matrix<T> Matrix<T>::inverseDiagonal() const
{

	assert(this->row == this->col);
	Matrix m3(this->row,this->col,0);
	int i=0;
	int j=0;
	for (i=0;i<(this->row);++i)
	{
		j = i;
		m3(i,j)= 1/ (*this)(i,j);

	}
	return m3;

}

template <typename T, size_t rows , size_t cols>
ostream& operator<<(ostream& os,const Matrix<T>& obj )
{
	obj.display();
	return os;


}

template <typename T, size_t rows , size_t cols>
Vector<T> Matrix<T>::operator*(const Vector<T>& obj) const
{

	//assert(this->col = obj.size());
	int num = obj.size();
	Vector<T> v(num);

	for (int i =0 ; i <this->row; ++i)

		{
			for (int j =0 ; j< this->col ; ++j )
				v(i)+= (*this)(i,j) * obj(j);

		}


	return v;
}
