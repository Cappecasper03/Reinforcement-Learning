#pragma once

#include <random>
#include <chrono>

static std::mt19937_64 rng( std::chrono::high_resolution_clock::now().time_since_epoch().count() );

static inline void Seed( unsigned NewSeed ) { rng.seed( NewSeed ); }

static inline int Random( void ) { return rng(); }

static inline int Random( int Min, int Max )
{
	std::uniform_int_distribution<int> dist( Min, Max );
	return dist( rng );
}

static inline float Random( float Min, float Max )
{
	std::uniform_real_distribution<float> dist( Min, Max );
	return dist( rng );
}
