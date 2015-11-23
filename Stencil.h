#pragma once

#include <cassert>
#include <utility> //std::swap
#include <algorithm> // std::find_if
#include <vector>
#include "Vector.h"
#include "MatrixLike.h"

template<typename T>
using StencilEntry = std::pair<int, T>; // convenience type for stencil entries

template<typename T>
class Stencil : public MatrixLike< T , Stencil<T> >
{
public:
	Stencil(const std::vector<StencilEntry<T> >& boundaryEntries, const std::vector<StencilEntry<T> >& innerEntries)
		: boundaryStencil_(boundaryEntries), innerStencil_(innerEntries) { }
	Stencil(const std::vector<StencilEntry<T> >& innerEntries)	// c'tor for stencils w/o explicit boundary handling
		: boundaryStencil_(innerEntries), innerStencil_(innerEntries) { }

	Stencil(const Stencil & o);
	//Stencil(Stencil && o) noexcept;

	~Stencil( ) override { }

	Stencil& operator=(const Stencil & o) noexcept;
	//Stencil& operator=(Stencil && o);

	// HINT: stencil entries are stored as offset/coefficient pair, that is the offset specifies which element of a
	// vector, relative to the current index, is to be regarded. It is then multiplied with the according coefficient.
	// All of these expressions are evaluated and then summed up to get the final result.
	Vector<T> operator* (const Vector<T> & o) const override;

	Stencil<T> inverseDiagonal( ) const override;

protected:
	// containers for the stencil entries -> boundary stencils represent the first and last rows of a corresponding
	// matrix and are to be applied to the first and last element of a target vector; inner stencils correspond to
	// the remaining rows of the matrix
	std::vector<StencilEntry<T> > boundaryStencil_;	// feel free to change the datatype if convenient
	std::vector<StencilEntry<T> > innerStencil_;	// feel free to change the datatype if convenient
};


template <typename T>
Vector<T> Stencil<T>::operator * (const Vector<T> & o) const   // Stencil multiplication .....
{
	int size = o.size();
	Vector <T> V_(size);
	int size_boundstencil= boundaryStencil_.size();
	int size_innerstencil= innerStencil_.size();
	V_(0) = this->boundaryStencil_[0].second * (o(0 +( this->boundaryStencil_[0].first)));
	for (int i = 1; i < size-1; ++i)
	{

		for (int j = 0; j < size_innerstencil; ++j)
		{
			V_(i) += (this->innerStencil_[j].second) *(o(i+ this->innerStencil_[j].first)) ;

		}
			}
	V_(size-1) = this->boundaryStencil_[0].second * (o(0 + (this->boundaryStencil_[0].first)));

	return V_;

}

template <typename T>
Stencil<T> Stencil<T>::inverseDiagonal () const
{
	Stencil<double> Anew({{0,0}},{{0,0}}) ;
	Anew.boundaryStencil_[0].second = (1.0/this->boundaryStencil_[0].second);

	int size_innerstencil= (innerStencil_.size()) * 0.5 ;
	Anew.innerStencil_[0].second = 1.0/this->innerStencil_[size_innerstencil].second;

	return Anew;

}

template <typename T>
Stencil<T>& Stencil<T>::operator=(const Stencil & o) noexcept
{
	assert((this)!= &o);

	this->boundaryStencil_=o.boundaryStencil_;
	this->innerStencil_=o.innerStencil_;

	return *(this);

}

template <typename T>
Stencil<T>::Stencil(const Stencil& o)
{
	std::vector<StencilEntry<T> > boundaryStencil_;
	std::vector<StencilEntry<T> > innerStencil_;
	this->boundaryStencil_= o.boundaryStencil_;
	this->innerStencil_=o.innerStencil_;

}
