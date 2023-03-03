#pragma once

#include "CVector.h"

#include <SFML/Graphics.hpp>

class CGameSnake;

class CSnake
{
public:
	CSnake( void );
	~CSnake( void );

	void Update( float DeltaTime );
	void Render( void );

private:
	struct SBody
	{
		sf::Vector2f GridPosition;
		sf::Vector2f Direction;
	};

	void UpdateHeadVertices( void );
	void UpdateBodyVertices( void );
	void AddBody( void );

	float m_HeadRadius;
	float m_BodyHalfWidth;
	SBody m_Head;
	sf::VertexArray m_VerticesHead;
	SBody m_Body;
	sf::VertexArray m_VerticesBody;

	CGameSnake& m_rGame;
};