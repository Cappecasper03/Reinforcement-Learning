#pragma once

#include "CVector.h"
#include "Games/IGame.h"
#include "AI/CAgent.h"

template<typename T>
class CGeneticAlgorithm
{
public:
	struct SGameAgent
	{
		bool operator<( const SGameAgent& rOther ) { return pAgent < rOther.pAgent; }
		bool operator>( const SGameAgent& rOther ) { return pAgent > rOther.pAgent; }

		IGame* pGame;
		CAgent<IAgent>* pAgent;
	};

	CGeneticAlgorithm( unsigned Population );
	~CGeneticAlgorithm( void );

	void Update( float DeltaTime );

	unsigned GetPopulation( void ) { return m_Games.size(); }

	IGame* GetBestGame( void ) { return m_pBestGame; }

private:
	CVector<SGameAgent> m_Games;
	IGame* m_pBestGame;
};

template<typename T>
inline CGeneticAlgorithm<T>::CGeneticAlgorithm( unsigned Population )
	: m_Games( Population, { new T, nullptr } )
	, m_pBestGame()
{
	if( m_Games.size() > 0 )
		m_pBestGame = m_Games.front().pGame;
}

template<typename T>
inline CGeneticAlgorithm<T>::~CGeneticAlgorithm( void )
{
	m_pBestGame = nullptr;

	for( SGameAgent& rGame : m_Games )
		delete rGame.pGame;
}

template<typename T>
inline void CGeneticAlgorithm<T>::Update( float DeltaTime )
{
	for( SGameAgent& rGame : m_Games )
		rGame.pGame->Update( DeltaTime );
}
