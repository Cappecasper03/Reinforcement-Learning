#pragma once

#include "Games/IGame.h"
#include "IAgent.h"
#include "CNeuralNetwork.h"

#include <vector>
#include <string>

template<typename T>
class CAgent
{
public:
	CAgent( IGame* pGame, std::string FileName = "NeuralNetwork.txt" );
	CAgent( IGame* pGame, std::vector<unsigned>& rNNTopology );
	~CAgent( void );

	bool operator<( const CAgent& rOther ) { return m_pAgent < rOther.m_pAgent; }
	bool operator>( const CAgent& rOther ) { return m_pAgent > rOther.m_pAgent; }

	bool operator<( const CAgent* pOther ) { return m_pAgent < pOther->m_pAgent; }
	bool operator>( const CAgent* pOther ) { return m_pAgent > pOther->m_pAgent; }

	// pInputs is the enviroment inputs that the agent can use to calculate actions
	void Update( float DeltaTime, const std::vector<float>* pInputs = nullptr );

	T* GetAgent( void ) { return ( T* )m_pAgent; }
	CNeuralNetwork& GetNeuralNetwork( void ) { return m_NeuralNetwork; }

private:
	IAgent* m_pAgent;
	CNeuralNetwork m_NeuralNetwork;
};

template<typename T>
inline CAgent<T>::CAgent( IGame* pGame, std::string FileName )
	: m_pAgent( new T( pGame ) )
	, m_NeuralNetwork( FileName )
{
}

template<typename T>
inline CAgent<T>::CAgent( IGame* pGame, std::vector<unsigned>& rNNTopology )
	: m_pAgent( new T( pGame ) )
	, m_NeuralNetwork( rNNTopology )
{
}

template<typename T>
inline CAgent<T>::~CAgent( void )
{
	if( m_pAgent )
		delete m_pAgent;
}

template<typename T>
inline void CAgent<T>::Update( float DeltaTime, const std::vector<float>* pInputs )
{
	if( pInputs && m_NeuralNetwork.Predict( *pInputs ) )
		m_pAgent->Input( &m_NeuralNetwork.GetAllPredictions() );

	m_pAgent->Update( DeltaTime );
}
