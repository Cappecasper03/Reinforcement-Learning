#include "CMatrix.h"

#include <assert.h>

CMatrix::CMatrix( unsigned Columns, unsigned Rows )
	: m_Columns( Columns )
	, m_Rows( Rows )
	, m_Values()
{
	m_Values.resize( m_Columns * m_Rows, 0 );
}

CMatrix::~CMatrix( void )
{
}

CMatrix CMatrix::Transposed( void )
{
	CMatrix Result( m_Rows, m_Columns );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
			Result.At( Column, Row ) = At( Row, Column );
	}

	return Result;
}

CMatrix CMatrix::MultiplyElements( const CMatrix& rOther )
{
	assert( m_Columns == rOther.m_Columns && m_Rows == rOther.m_Rows );

	CMatrix Result( rOther.m_Columns, m_Rows );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
			Result.At( Column, Row ) = At( Column, Row ) * rOther.At( Column, Row );
	}

	return Result;
}

CMatrix CMatrix::operator*( const  CMatrix& rOther )
{
	assert( m_Columns == rOther.m_Rows );

	CMatrix Result( rOther.m_Columns, m_Rows );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
		{
			float Value = 0;
			for( unsigned i = 0; i < m_Columns; i++ )
				Value += At( i, Row ) * rOther.At( Column, i );

			Result.At( Column, Row ) = Value;
		}
	}

	return Result;
}

void CMatrix::operator*=( const CMatrix& rOther )
{
	assert( m_Columns == rOther.m_Rows );

	CMatrix Result( rOther.m_Columns, m_Rows );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
		{
			float Value = 0;
			for( unsigned i = 0; i < m_Columns; i++ )
				Value += At( i, Row ) * rOther.At( Column, i );

			Result.At( Column, Row ) = Value;
		}
	}

	m_Columns = Result.m_Columns;
	m_Rows = Result.m_Rows;
	m_Values = Result.m_Values;
}

CMatrix CMatrix::operator*( const float Scalar )
{
	CMatrix Result( m_Columns, m_Rows );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		float Value = 0;
		for( unsigned i = 0; i < m_Columns; i++ )
			Value += At( i, Row ) * Scalar;

		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
			Result.At( Column, Row ) = Value;
	}

	return Result;
}

void CMatrix::operator*=( const float Scalar )
{
	for( unsigned Row = 0; Row < m_Rows; Row++ )
	{
		float Value = 0;
		for( unsigned i = 0; i < m_Columns; i++ )
			Value += At( i, Row ) * Scalar;

		for( unsigned Column = 0; Column < m_Columns; Column++ )
			At( Column, Row ) = Value;
	}
}

CMatrix CMatrix::operator+( const CMatrix& rOther )
{
	assert( m_Columns == rOther.m_Columns && m_Rows == rOther.m_Rows );

	CMatrix Result( m_Columns, m_Rows );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
			Result.At( Column, Row ) = At( Column, Row ) + rOther.At( Column, Row );
	}

	return Result;
}

void CMatrix::operator+=( const CMatrix& rOther )
{
	assert( m_Columns == rOther.m_Columns && m_Rows == rOther.m_Rows );

	for( unsigned Row = 0; Row < m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < m_Columns; Column++ )
			At( Column, Row ) = At( Column, Row ) + rOther.At( Column, Row );
	}
}

CMatrix CMatrix::operator+( const float Scalar )
{
	CMatrix Result( m_Columns, m_Rows );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
			Result.At( Column, Row ) = At( Column, Row ) + Scalar;
	}

	return Result;
}

void CMatrix::operator+=( const float Scalar )
{
	for( float& rValue : m_Values )
		rValue = rValue + Scalar;
}

CMatrix CMatrix::Negative( void )
{
	CMatrix Result( m_Columns, m_Rows );

	for( unsigned Row = 0; Row < Result.m_Rows; Row++ )
	{
		for( unsigned Column = 0; Column < Result.m_Columns; Column++ )
			Result.At( Column, Row ) = -At( Column, Row );
	}

	return Result;
}
