#pragma once

#include <random>
#include <chrono>

class CRandom
{
public:
	CRandom( void ) : m_Seed( std::chrono::high_resolution_clock::now().time_since_epoch().count() ) { std::srand( m_Seed ); }

	void SetSeed( unsigned int NewSeed ) { m_Seed = NewSeed; std::srand( NewSeed ); }

	int Random( void ) { std::srand( m_Seed ); return std::rand(); }
	int Random( int Min, int Max );
	float Random( float Min, float Max );

private:
	unsigned int m_Seed;
};

inline int CRandom::Random( int Min, int Max )
{
	std::srand( m_Seed );

	if( Min > Max )
		return Random( Max, Min );
	else if( Min == Max )
		return Min;

	return Min + ( std::rand() % ( Max - Min ) );
}

inline float CRandom::Random( float Min, float Max )
{
	std::srand( m_Seed );

	if( Min > Max )
		return Random( Max, Min );
	else if( Min == Max )
		return Min;

	return ( float )Random( ( int )Min, ( int )Max ) + ( ( float )std::rand() / RAND_MAX );
}