#pragma once

#include "CVector.h"
#include "AI/IAgent.h"

#include <SFML/Graphics.hpp>

class CGameSnake;

class CSnake : public IAgent
{
public:
	CSnake( IGame* pGame );
	~CSnake( void );

	void Update( float DeltaTime = 0 ) override;
	void Render( void ) override;
	void ImGui( void );
	void Input( const std::vector<float>* pActions = nullptr ) override;

	bool IsOnSnake( sf::Vector2f& rGridPoint );
	bool IsDead( void );
	void AddBody( void );

	unsigned GetStepsLeft( void ) { return m_StepsLeft; }
	unsigned GetScore( void ) { return m_Bodies.size() - 1; }

	void Restart( void );

private:
	struct SBody
	{
		sf::Vector2f GridPosition;
		sf::Vector2f Direction;
	};

	void UpdateHeadVertices( void );
	void UpdateBodyVertices( unsigned BodyIndex );

	float m_HeadRadius;
	SBody m_Head;
	sf::VertexArray m_VerticesHead;
	sf::Vector2f m_MoveDirection;

	float m_HalfBodySize;
	CVector<SBody> m_Bodies;
	sf::VertexArray m_VerticesBody;

	int m_StepsLeft;
	bool m_IsDead;

	CGameSnake* m_pGame;

	static const sf::Vector2f s_Directions[4];
};