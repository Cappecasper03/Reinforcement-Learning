#pragma once

#include "CVector.h"

#include <SFML/Graphics.hpp>

class CGameSnake;

class CSnake
{
public:
	CSnake( void );
	~CSnake( void );

	void Update( void );
	void Render( void );
	void ImGui( void );

	bool IsOnSnake( sf::Vector2f& rPoint );

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
	CVector<SBody> m_Bodies;
	sf::VertexArray m_VerticesBody;

	CGameSnake& m_rGame;
};