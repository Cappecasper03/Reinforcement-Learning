#pragma once

#include <vector>
#include <algorithm>

template<typename T>
class CVector : public std::vector<T>
{
public:
	// Bring base class constructors into scope
	using std::vector<T>::vector;

	// Bring base class assignment operators into scope
	using std::vector<T>::operator=;

	// Bring base class element access operators into scope
	using std::vector<T>::operator[];
	using std::vector<T>::at;
	using std::vector<T>::front;
	using std::vector<T>::back;

	// Bring base class modifiers into scope
	using std::vector<T>::assign;
	using std::vector<T>::push_back;
	using std::vector<T>::pop_back;
	using std::vector<T>::insert;
	using std::vector<T>::erase;
	using std::vector<T>::swap;
	using std::vector<T>::clear;

	// Insert element into sorted vector in order
	template<typename Compare>
	void InsertSorted( const T& rValue, Compare CompareFunction ) { insert( FindSorted( rValue, CompareFunction ), rValue ); }
	// Insert element into sorted vector in default (less-than) order
	void InsertSorted( const T& rValue ) { insert( FindSorted( rValue ), rValue ); }

	// Find element in sorted vector in custom comparator
	template<typename Compare>
	auto FindSorted( const T& rValue, Compare CompareFunction ) { return std::lower_bound( this->begin(), this->end(), rValue, CompareFunction ); }
	// Find element in sorted vector in default (less-than) order
	auto FindSorted( const T& rValue ) { return std::lower_bound( this->begin(), this->end(), rValue ); }

	// Find element in vector in custom comparator
	template<typename Compare>
	auto Find( const T& rValue, Compare CompareFunction ) { return std::find( this->begin(), this->end(), rValue, CompareFunction ); }
	// Find element in vector in default (less-than) order
	auto Find( const T& rValue ) { return std::find( this->begin(), this->end(), rValue ); }

	// Sort the vector using custom comparator
	template<typename Compare>
	void Sort( Compare CompareFunction ) { std::sort( this->begin(), this->end(), CompareFunction ); }
	// Sort the vector in default (less-than) order
	void Sort( void ) { std::sort( this->begin(), this->end() ); }
};