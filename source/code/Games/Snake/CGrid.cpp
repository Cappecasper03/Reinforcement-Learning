#include "CGrid.h"
#include "CGameSnake.h"

#include <imgui.h>

CGrid::CGrid( unsigned GridSize, CGameSnake* pGame )
	: m_Vertices( sf::Lines, 0 )
	, m_GridSize( GridSize )
	, m_TileSize( 0 )
	, m_GridMinMax()
	, m_pGame( pGame )
{
	CreateGrid( GridSize );
}

CGrid::~CGrid( void )
{
}

void CGrid::ImGui( void )
{
	if( !m_pGame->IsRestartable() )
		return;

	if( ImGui::InputInt( "Grid Size", ( int* )&m_GridSize, 2 ) )
	{
		CreateGrid( m_GridSize );
		m_pGame->CreateNewAgent();
	}
}

void CGrid::CreateGrid( unsigned GridSize )
{
	if( GridSize % 2 == 1 )
		GridSize++;

	m_GridSize = GridSize;
	const sf::Vector2u& rWindowSize = CGameManager::GetInstance().GetWindow().getSize();
	int StartX = rWindowSize.x - rWindowSize.y;

	m_GridMinMax.XMin = abs( StartX );
	m_GridMinMax.XMax = rWindowSize.x;
	m_GridMinMax.YMin = 0;
	m_GridMinMax.YMax = rWindowSize.y;

	m_TileSize = ( float )rWindowSize.y / m_GridSize;

	m_Vertices.clear();
	m_Vertices.resize( ( m_GridSize + 1 ) * 4 );
	for( unsigned i = 0; i <= GridSize; i++ )
	{
		sf::Vector2f Position;
		Position.x = StartX + m_TileSize * i;
		Position.y = 0;
		m_Vertices.append( sf::Vertex( Position ) );

		Position.x = StartX + m_TileSize * i;
		Position.y = rWindowSize.y;
		m_Vertices.append( sf::Vertex( Position ) );

		Position.x = StartX;
		Position.y = m_TileSize * i - ( i == GridSize ? 1 : 0 );
		m_Vertices.append( sf::Vertex( Position ) );

		Position.x = rWindowSize.x;
		Position.y = m_TileSize * i - ( i == GridSize ? 1 : 0 );
		m_Vertices.append( sf::Vertex( Position ) );
	}
}

sf::Vector2f CGrid::GridToScreen( int X, int Y )
{
	sf::Vector2f Position;

	Position.x = m_GridMinMax.XMin + m_TileSize * X + m_TileSize / 2;
	Position.y = m_GridMinMax.YMin + m_TileSize * Y + m_TileSize / 2;

	return std::move( Position );
}
