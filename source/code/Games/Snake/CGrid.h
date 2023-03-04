#pragma once

#include "Managers/CGameManager.h"

#include <SFML/Graphics.hpp>

class CGrid
{
public:
	CGrid( int GridSize );
	~CGrid( void );

	void Render( void ) { CGameManager::GetInstance().GetWindow().draw( m_Vertices ); }

	void CreateGrid( int GridSize );

	const int& GetGridSize( void ) { return m_GridSize; }
	const float& GetTileSize( void ) { return m_TileSize; }

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
	int m_GridSize;
	float m_TileSize;

	SGridMinMax m_GridMinMax;
};