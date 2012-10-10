// ------------------------
// projects/matlab/Matrix.h
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------

#ifndef Matrix_h
#define Matrix_h

// --------
// includes
#include <cassert>	// assert
#include <cstddef>	// ptrdiff_t, size_t
#include <vector>	// vector

// ------
// Matrix
template <typename T>
class Matrix {
	public:
		// --------
		// typedefs
		typedef T value_type;

		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;

		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;

		typedef value_type&			reference;
		typedef const value_type&	const_reference;

		typedef typename std::vector< std::vector<T> >::iterator		iterator;
		typedef typename std::vector< std::vector<T> >::const_iterator	const_iterator;

	public:
		// -----------
		// operator ==
		/**
		* <your documentation>
		*/
		friend bool operator == (const Matrix&, const Matrix&) {
			// <your code>
			return true;}

		// -----------
		// operator !=
		/**
		* <your documentation>
		*/
		friend bool operator != (const Matrix& lhs, const Matrix& rhs) {
			return !(lhs == rhs);}

		// ----------
		// operator <
		/**
		* <your documentation>
		*/
		friend bool operator < (const Matrix& lhs, const Matrix& rhs) {
			// <your code>
			return false;}

		// -----------
		// operator <=
		/**
		* <your documentation>
		*/
		friend bool operator <= (const Matrix& lhs, const Matrix& rhs) {
			return !(rhs < lhs);}

		// ----------
		// operator >
		/**
		* <your documentation>
		*/
		friend bool operator > (const Matrix& lhs, const Matrix& rhs) {
			return (rhs < lhs);}

		// -----------
		// operator >=
		/**
		* <your documentation>
		*/
		friend bool operator >= (const Matrix& lhs, const Matrix& rhs) {
			return !(lhs < rhs);}

		// ----------
		// operator +
		/**
		* <your documentation>
		*/
		friend Matrix operator + (Matrix lhs, const T& rhs) {
			return lhs += rhs;}

		/**
		* <your documentation>
		*/
		friend Matrix operator + (Matrix lhs, const Matrix& rhs) {
			return lhs += rhs;}

		// ----------
		// operator -
		/**
		* <your documentation>
		*/
		friend Matrix operator - (Matrix lhs, const T& rhs) {
			return lhs -= rhs;}

		/**
		* <your documentation>
		*/
		friend Matrix operator - (Matrix lhs, const Matrix& rhs) {
			return lhs -= rhs;}

		// ----------
		// operator *
		/**
		* <your documentation>
		*/
		friend Matrix operator * (Matrix lhs, const T& rhs) {
			return lhs *= rhs;}

		/**
		* <your documentation>
		*/
		friend Matrix operator * (Matrix lhs, const Matrix& rhs) {
			return lhs *= rhs;}

	private:
		// ----
		// data
		std::vector< std::vector<T> > _m;

		// -----
		// valid
		/**
		* <your documentation>
		*/
		bool valid () const {
			// <your code>
			return true;}

	public:
		// ------------
		// constructors
		/**
		* <your documentation>
		*/
		Matrix (size_type r = 0, size_type c = 0, const_reference v = T()) {
			// <your code>
			assert(valid());}

		// Default copy, destructor, and copy assignment
		// Matrix  (const Matrix<T>&);
		// ~Matrix ();
		// Matrix& operator = (const Matrix&);

		// -----------
		// operator 
		/**
		* <your documentation>
		*/
		reference operator [] (size_type i) {
			// <your code>
			// dummy is just to be able to compile the skeleton, remove it
			static value_type dummy;
			return dummy;}

		/**
		* <your documentation>
		*/
		const_reference operator [] (size_type i) const {
			return (*const_cast<Matrix*>(this))[i];}

		// -----------
		// operator +=
		/**
		* <your documentation>
		*/
		Matrix& operator += (const T& rhs) {
			// <your code>
			return *this;}

		/**
		* <your documentation>
		*/
		Matrix& operator += (const Matrix& rhs) {
			// <your code>
			return *this;}

		// -----------
		// operator -=
		/**
		* <your documentation>
		*/
		Matrix& operator -= (const T& rhs) {
			// <your code>
			return *this;}

		/**
		* <your documentation>
		*/
		Matrix& operator -= (const Matrix& rhs) {
			// <your code>
			return *this;}

		// -----------
		// operator *=
		/**
		* <your documentation>
		*/
		Matrix& operator *= (const T& rhs) {
			// <your code>
			return *this;}

		/**
		* <your documentation>
		*/
		Matrix& operator *= (const Matrix& rhs) {
			// <your code>
			return *this;}

		// -----
		// begin
		/**
		* <your documentation>
		*/
		iterator begin () {
			return _m.begin();}

		/**
		* <your documentation>
		*/
		const_iterator begin () const {
			return const_cast<Matrix*>(this)->begin();}

		// ---
		// end
		/**
		* <your documentation>
		*/
		iterator end () {
			return _m.end();}

		/**
		* <your documentation>
		*/
		const_iterator end () const {
			return const_cast<Matrix*>(this)->end();}

		// ----
		// size
		/**
		* <your documentation>
		*/
		size_type size () const {
			return _m.size();}};

#endif // Matrix_h
