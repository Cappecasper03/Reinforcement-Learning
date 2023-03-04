#pragma once

#include "Managers/CGameManager.h"

#include <SFML/Graphics.hpp>

class CGameSnake;

class CFood
{
public:
	CFood( void );
	~CFood( void );

	void Render( void ) { CGameManager::GetInstance().GetWindow().draw( m_Vertices ); }
	void ImGui( void );

	void RandomizePosition( void );

	const sf::Vector2f& GetGridPos( void ) { return m_GridPos; }

private:
	sf::VertexArray m_Vertices;
	sf::Vector2f m_GridPos;
	float m_Radius;

	CGameSnake& m_rGame;
};