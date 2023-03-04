#include "CFood.h"
#include "CGameSnake.h"
#include "CRandom.h"

CFood::CFood( void )
	: m_Vertices( sf::TriangleFan, 12 )
	, m_GridPos( -1, -1 )
	, m_Radius()
	, m_rGame( CGameSnake::GetInstance() )
{
	m_Radius = m_rGame.GetGrid().GetTileSize() * .5f / 2;

	for( unsigned i = 0; i < m_Vertices.getVertexCount(); i++ )
		m_Vertices[i].color = sf::Color::Red;

	RandomizePosition();
}

CFood::~CFood( void )
{
}

void CFood::RandomizePosition( void )
{
	sf::Vector2f NewPosition( -1, -1 );
	CGrid& rGrid = m_rGame.GetGrid();
	int GridSize = rGrid.GetGridSize();
	sf::Vector2f& rPosition = m_Vertices[0].position;

	do
	{
		NewPosition.x = Random( 0, GridSize - 1 );
		NewPosition.y = Random( 0, GridSize - 1 );
	} while( rPosition == NewPosition );

	m_GridPos = NewPosition;
	rPosition = rGrid.GridToScreen( NewPosition.x, NewPosition.y );
	int VertexCount = m_Vertices.getVertexCount();

	float AnglePerVertex = ( float )360 / ( VertexCount - 2 );
	AnglePerVertex *= std::acos( -1 ) / 180;

	for( unsigned int i = 1; i < VertexCount; i++ )
	{
		sf::Vertex& rVertex = m_Vertices[i];

		if( i == VertexCount - 1 )
		{
			rVertex = m_Vertices[1];
			break;
		}

		rVertex.position.x = rPosition.x + m_Radius * cos( AnglePerVertex * i );
		rVertex.position.y = rPosition.y + m_Radius * sin( AnglePerVertex * i );
	}
}