#include "CSnake.h"
#include "Managers/CGameManager.h"
#include "CGameSnake.h"
#include "CGrid.h"

CSnake::CSnake( void )
	: m_HeadRadius( 0 )
	, m_Bodys()
	, m_VerticesHead( sf::TriangleFan, 20 )
	, m_VerticesBody( sf::TriangleStrip )
	, m_rGame( CGameSnake::GetInstance() )
{
	CGrid& rGrid = m_rGame.GetGrid();
	m_HeadRadius = rGrid.GetTileSize() * .4f;
	SBody Head;
	Head.GridPosition = sf::Vector2f( ( int )( rGrid.GetGridSize() / 2 ), ( int )( rGrid.GetGridSize() / 2 ) );
	Head.Direction = sf::Vector2f( 0, 1 );

	sf::Vector2f& rPosition = m_VerticesHead[0].position;
	rPosition = rGrid.GridToScreen( Head.GridPosition.x, Head.GridPosition.y );
	int VertexCount = m_VerticesHead.getVertexCount();

	float AnglePerVertex = ( float )360 / ( VertexCount - 2 );
	AnglePerVertex *= std::acos( -1 ) / 180;

	for( unsigned int i = 1; i < VertexCount; i++ )
	{
		sf::Vertex& rVertex = m_VerticesHead[i];

		if( i == VertexCount - 1 )
		{
			rVertex = m_VerticesHead[1];
			break;
		}

		rVertex.position.x = rPosition.x + m_HeadRadius * cos( AnglePerVertex * i );
		rVertex.position.y = rPosition.y + m_HeadRadius * sin( AnglePerVertex * i );
	}

	m_Bodys.push_back( std::move( Head ) );
}

CSnake::~CSnake( void )
{
}

void CSnake::Update( float DeltaTime )
{
}

void CSnake::Render( void )
{
	sf::RenderWindow& rWindow = CGameManager::GetInstance().GetWindow();
	rWindow.draw( m_VerticesBody );
	rWindow.draw( m_VerticesHead );
}

void CSnake::AddBody( void )
{
}
