#pragma once

#include <vector>

class CMatrix
{
public:
	CMatrix( unsigned Columns = 0, unsigned Rows = 0 );
	~CMatrix( void );

	float& At( unsigned Column, unsigned Row ) { return m_Values[Row * m_Columns + Column]; }
	const float& At( unsigned Column, unsigned Row )const { return m_Values[Row * m_Columns + Column]; }

	float& operator[]( unsigned Index ) { return m_Values[Index]; }
	const float& operator[]( unsigned Index ) const { return m_Values[Index]; }

	std::vector<float>& GetValues( void ) { return m_Values; }

	CMatrix Transposed( void );

	CMatrix MultiplyElements( const CMatrix& rOther );
	CMatrix operator*( const CMatrix& rOther );
	void operator*=( const CMatrix& rOther );

	CMatrix operator*( const float Scalar );
	void operator*=( const float Scalar );

	CMatrix operator+( const CMatrix& rOther );
	void operator+=( const CMatrix& rOther );

	CMatrix operator+( const float Scalar );
	void operator+=( const float Scalar );

	CMatrix Negative( void );

	unsigned GetColumnSize( void ) { return m_Columns; }
	unsigned GetRowSize( void ) { return m_Rows; }

private:
	unsigned m_Columns;
	unsigned m_Rows;

	std::vector<float> m_Values;
};