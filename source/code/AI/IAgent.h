#pragma once

#include <vector>

class IGame;

class IAgent
{
public:
	IAgent( IGame* pGame ) : m_Fitness( 0 ), m_pGame( pGame ) {}

	virtual void Update( float DeltaTime ) = 0;
	virtual void Render( void ) {}
	// pActions is the agents predicted actions
	virtual void Input( const std::vector<float>* pActions = nullptr ) = 0;

	bool operator<( const IAgent& rOther ) { return m_Fitness < rOther.m_Fitness; }
	bool operator>( const IAgent& rOther ) { return m_Fitness > rOther.m_Fitness; }

	bool operator<( const IAgent* pOther ) { return m_Fitness < pOther->m_Fitness; }
	bool operator>( const IAgent* pOther ) { return m_Fitness > pOther->m_Fitness; }

protected:
	float m_Fitness;

	IGame* m_pGame;
};