#pragma once

#include "CVector.h"
#include "Games/IGame.h"
#include "AI/CAgent.h"
#include "CRandom.h"

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

	// Mutation happens 1 / MutationChance
	// NrOfParents is how many of the agents will be untouched and those will also be the ones combined in all the other agents
	void CrossoverMutate( unsigned MutationChance, unsigned NrOfParents );

	unsigned GetPopulation( void ) { return m_GameAgents.size(); }

	IGame* GetBestGameLastGen( void ) { return m_pBestGameLastGen; }

private:
	CVector<SGameAgent> m_GameAgents;
	IGame* m_pBestGameLastGen;

	unsigned m_Generation;
};

template<typename T>
inline CGeneticAlgorithm<T>::CGeneticAlgorithm( unsigned Population )
	: m_GameAgents( Population, SGameAgent{ new T, nullptr } )
	, m_pBestGameLastGen()
	, m_Generation( 0 )
{
	if( m_GameAgents.size() > 0 )
		m_pBestGameLastGen = m_GameAgents.front().pGame;

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
	bool GenerationIsDead = true;
	for( SGameAgent& rGameAgent : m_GameAgents )
	{
		rGameAgent.pGame->Update( DeltaTime );

		if( !rGameAgent.pGame->IsRestartable() )
			GenerationIsDead = false;
	}

	if( !GenerationIsDead || m_GameAgents.size() <= 1 )
		return;

	CrossoverMutate( 50, 4 );
	for( SGameAgent& rGameAgent : m_GameAgents )
		rGameAgent.pGame->Restart();
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
				std::vector<CMatrix>& rParentWeightMatrices = m_GameAgents[Random( 0, NrOfParents - 1 )].pAgent->GetNeuralNetwork().GetWeightMatrices();
				// and chooses the value in the same matrix and value index
				rWeightValue = rParentWeightMatrices[MatrixIndex][ValueIndex];

				if( Random( 0, MutationChance - 1 ) == 0 )
					rWeightValue = Random( 0.f, 1.f ); // TODO: Maybe not hardcode random values
			}
		}
	}
}
