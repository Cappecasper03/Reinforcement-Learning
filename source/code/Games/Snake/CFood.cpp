#include "CFood.h"
#include "CGameSnake.h"
#include "CRandom.h"

CFood::CFood( CGameSnake* pGame )
	: m_Vertices( sf::TriangleFan, 12 )
	, m_GridPos( 0, 0 )
	, m_Radius()
	, m_pGame( pGame )
{
	for( unsigned i = 0; i < m_Vertices.getVertexCount(); i++ )
		m_Vertices[i].color = sf::Color::Red;
}

CFood::~CFood( void )
{
}

void CFood::ImGui( void )
{
}

void CFood::RandomizePosition( void )
{
	CGrid& rGrid = m_pGame->GetGrid();

	m_Radius = m_pGame->GetGrid().GetTileSize() * .5f / 2;
	int GridSize = rGrid.GetGridSize();
	sf::Vector2f NewPosition( -1, -1 );
	sf::Vector2f& rPosition = m_Vertices[0].position;

	do
	{
		NewPosition.x = Random( 0, GridSize - 1 );
		NewPosition.y = Random( 0, GridSize - 1 );
	} while( rPosition == NewPosition || m_pGame->GetSnake()->GetAgent()->IsOnSnake( NewPosition ) );

	m_pGame->UpdateAgentInput( m_GridPos.x, m_GridPos.y, 0 );
	m_GridPos = NewPosition;
	m_pGame->UpdateAgentInput( m_GridPos.x, m_GridPos.y, 1 );

	int VertexCount = m_Vertices.getVertexCount();
	rPosition = rGrid.GridToScreen( NewPosition );

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
