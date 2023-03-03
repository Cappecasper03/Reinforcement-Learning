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

	void AddBody( void );

	float m_HeadRadius;
	CVector<SBody> m_Bodys;
	sf::VertexArray m_VerticesHead;
	sf::VertexArray m_VerticesBody;

	CGameSnake& m_rGame;
};