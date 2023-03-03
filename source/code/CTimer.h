#pragma once

#include <chrono>

class CTimer
{
public:
	CTimer( void );

	void Update( void ) { m_LastUpdate = std::chrono::high_resolution_clock::now(); }

	// Gets deltatime in seconds
	// DeltaTime = now - lastupdate
	double GetDeltaTime( bool DoUpdate = true ) { return GetDeltaNanoseconds( DoUpdate ) / 1'000'000'000; }
	// Gets deltatime in milliseconds
	// DeltaTime = now - lastupdate
	double GetDeltaMilliseconds( bool DoUpdate = true ) { return GetDeltaNanoseconds( DoUpdate ) / 1'000'000; }
	// Gets deltatime in microseconds
	// DeltaTime = now - lastupdate
	double GetDeltaMicroseconds( bool DoUpdate = true ) { return GetDeltaNanoseconds( DoUpdate ) / 1'000; }
	// Gets deltatime in nanoseconds
	// DeltaTime = now - lastupdate
	double GetDeltaNanoseconds( bool DoUpdate = true );

	// Gets lifetime in seconds
	double GetLifeTime( void ) { return GetLifeNanoseconds() / 1'000'000'000; }
	// Gets lifetime in milliseconds
	double GetLifeMilliseconds( void ) { return GetLifeNanoseconds() / 1'000'000; }
	// Gets lifetime in microseconds
	double GetLifeMicroseconds( void ) { return GetLifeNanoseconds() / 1'000; }
	// Gets lifetime in nanoseconds
	double GetLifeNanoseconds( void );

private:
	std::chrono::high_resolution_clock::time_point m_Start;
	std::chrono::high_resolution_clock::time_point m_LastUpdate;
};

CTimer::CTimer( void )
	: m_Start( std::chrono::high_resolution_clock::now() )
	, m_LastUpdate( std::chrono::high_resolution_clock::now() )
{
}

inline double CTimer::GetDeltaNanoseconds( bool DoUpdate )
{
	auto Now = std::chrono::high_resolution_clock::now();
	double DeltaTime = std::chrono::duration_cast< std::chrono::nanoseconds >( Now - m_LastUpdate ).count();

	if( DoUpdate )
		m_LastUpdate = Now;

	return DeltaTime;
}

inline double CTimer::GetLifeNanoseconds( void )
{
	auto Now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast< std::chrono::nanoseconds >( Now - m_Start ).count();
}