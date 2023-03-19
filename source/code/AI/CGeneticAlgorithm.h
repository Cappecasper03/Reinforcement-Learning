#pragma once

#include "CVector.h"
#include "Games/IGame.h"
#include "AI/CAgent.h"
#include "CRandom.h"

#include <string>

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

	IGame* At( unsigned Index ) { return m_GameAgents[Index].pGame; }

	void Update( float DeltaTime );

	// MutationChance is %
	// NrOfParents is how many of the agents will be untouched and those will also be the ones combined in all the other agents
	void CrossoverMutate( unsigned MutationChance, unsigned NrOfParents );

	unsigned GetPopulation( void ) { return m_GameAgents.size(); }

	IGame* GetBestGameLastGen( void ) { return m_pBestGameLastGen; }

	bool SaveBestModel( std::string FileName ) { return m_pBestGameLastGen->GetAgent()->GetNeuralNetwork().SaveModel( FileName ); }
	bool LoadModel( std::string FileName );

	// Total/current generation this session
	unsigned GetGeneration( void ) { return m_Generation; }
	void IncreaseGeneration( void ) { m_Generation++; }

private:
	CVector<SGameAgent> m_GameAgents;
	IGame* m_pBestGameLastGen;

	// Total/current generation this session
	unsigned m_Generation;
};

template<typename T>
inline CGeneticAlgorithm<T>::CGeneticAlgorithm( unsigned Population )
	: m_GameAgents( Population, SGameAgent{ nullptr, nullptr } )
	, m_pBestGameLastGen()
	, m_Generation( 0 )
{
	if( m_GameAgents.size() > 0 )
		m_pBestGameLastGen = m_GameAgents.front().pGame;

	for( SGameAgent& rGameAgents : m_GameAgents )
	{
		rGameAgents.pGame = new T;
		rGameAgents.pAgent = rGameAgents.pGame->GetAgent();
	}

	// TODO: Increase performance
	// Copy bias matrices from first agent to all other to make them have the same biases
	std::vector<CMatrix>& rFirstBiasMatrices = m_GameAgents.front().pAgent->GetNeuralNetwork().GetBiasMatrices();
	for( unsigned AgentIndex = 1; AgentIndex < m_GameAgents.size(); AgentIndex++ )
	{
		CNeuralNetwork& rNeuralNetwork = m_GameAgents[AgentIndex].pAgent->GetNeuralNetwork();
		std::vector<CMatrix>& rBiasMatrices = rNeuralNetwork.GetBiasMatrices();

		for( unsigned MatrixIndex = 0; MatrixIndex < rBiasMatrices.size(); MatrixIndex++ )
		{
			CMatrix& rFirstMatrix = rFirstBiasMatrices[MatrixIndex];
			CMatrix& rBiasMatrix = rBiasMatrices[MatrixIndex];
			rBiasMatrix = rFirstMatrix;
		}
	}
}

template<typename T>
inline CGeneticAlgorithm<T>::~CGeneticAlgorithm( void )
{
	m_pBestGameLastGen = nullptr;

	for( SGameAgent& rGameAgent : m_GameAgents )
		delete rGameAgent.pGame;
}

template<typename T>
inline void CGeneticAlgorithm<T>::Update( float DeltaTime )
{
	for( SGameAgent& rGameAgent : m_GameAgents )
		rGameAgent.pGame->Update( DeltaTime );
}

template<typename T>
inline void CGeneticAlgorithm<T>::CrossoverMutate( unsigned MutationChance, unsigned NrOfParents )
{
	m_GameAgents.Sort( std::greater() );
	m_pBestGameLastGen = m_GameAgents.front().pGame;

	for( unsigned AgentIndex = NrOfParents; AgentIndex < m_GameAgents.size(); AgentIndex++ )
	{
		CNeuralNetwork& rNeuralNetwork = m_GameAgents[AgentIndex].pAgent->GetNeuralNetwork();
		std::vector<CMatrix>& rWeightMatrices = rNeuralNetwork.GetWeightMatrices();

		for( unsigned MatrixIndex = 0; MatrixIndex < rWeightMatrices.size(); MatrixIndex++ )
		{
			CMatrix& rWeightMatrix = rWeightMatrices[MatrixIndex];

			for( unsigned ValueIndex = 0; ValueIndex < rWeightMatrix.GetValues().size(); ValueIndex++ )
			{
				float& rWeightValue = rWeightMatrix[ValueIndex];

				// Gets a random parents weight matrices
				unsigned RandomAgent = Random( 0, NrOfParents - 1 );
				std::vector<CMatrix>& rParentWeightMatrices = m_GameAgents[RandomAgent].pAgent->GetNeuralNetwork().GetWeightMatrices();
				// and chooses the value in the same matrix and value index
				rWeightValue = rParentWeightMatrices[MatrixIndex][ValueIndex];

				if( Random( 0.f, 100.f ) <= MutationChance )
					rWeightValue = Random( -1.f, 1.f ); // TODO: Maybe not hardcode random values
			}
		}
	}
}

template<typename T>
inline bool CGeneticAlgorithm<T>::LoadModel( std::string FileName )
{
	bool AllWasLoaded = true;
	for( SGameAgent& rGameAgent : m_GameAgents )
	{
		if( !rGameAgent.pAgent->GetNeuralNetwork().LoadModel( FileName ) )
			AllWasLoaded = false;
	}

	return AllWasLoaded;
}
