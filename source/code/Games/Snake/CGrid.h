#pragma once

#include "Managers/CGameManager.h"

#include <SFML/Graphics.hpp>

class CGrid
{
public:
	CGrid( unsigned GridSize );
	~CGrid( void );

	void Render( void ) { CGameManager::GetInstance().GetWindow().draw( m_Vertices ); }
	void ImGui( void );

	void CreateGrid( unsigned GridSize );

	const unsigned& GetGridSize( void ) { return m_GridSize; }
	const float& GetTileSize( void ) { return m_TileSize; }

	sf::Vector2f GridToScreen( sf::Vector2f& rVector ) { return GridToScreen( rVector.x, rVector.y ); }
	sf::Vector2f GridToScreen( int X, int Y );

private:
	struct SGridMinMax
	{
		float XMin;
		float XMax;
		float YMin;
		float YMax;
	};

	sf::VertexArray m_Vertices;
	unsigned m_GridSize;
	float m_TileSize;

	SGridMinMax m_GridMinMax;
};