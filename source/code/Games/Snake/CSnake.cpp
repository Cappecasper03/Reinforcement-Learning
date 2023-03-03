#include "CSnake.h"
#include "Managers/CGameManager.h"
#include "CGameSnake.h"
#include "CGrid.h"

CSnake::CSnake( void )
	: m_HeadRadius( 0 )
	, m_BodyHalfWidth( 0 )
	, m_Head()
	, m_VerticesHead( sf::TriangleFan, 20 )
	, m_Body()
	, m_VerticesBody( sf::TriangleStrip )
	, m_rGame( CGameSnake::GetInstance() )
{
	CGrid& rGrid = m_rGame.GetGrid();
	m_HeadRadius = rGrid.GetTileSize() * .4f;
	m_BodyHalfWidth = rGrid.GetTileSize() * .3f;
	m_Head.GridPosition = sf::Vector2f( ( int )( rGrid.GetGridSize() / 2 ), ( int )( rGrid.GetGridSize() / 2 ) );
	m_Head.Direction = sf::Vector2f( 0, 1 );
	UpdateHeadVertices();

	m_Body = m_Head;
	sf::Vertex Vertex;
	sf::Vector2f& rPosition = Vertex.position;
	sf::Vector2f NewPosition = rGrid.GridToScreen( m_Body.GridPosition.x, m_Body.GridPosition.y );
	rPosition.x = NewPosition.x + m_BodyHalfWidth;
	rPosition.y = NewPosition.y;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x - m_BodyHalfWidth;
	rPosition.y = NewPosition.y;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x + m_BodyHalfWidth;
	rPosition.y = NewPosition.y + rGrid.GetTileSize() / 2;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x - m_BodyHalfWidth;
	rPosition.y = NewPosition.y + rGrid.GetTileSize() / 2;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x + m_BodyHalfWidth;
	rPosition.y = NewPosition.y - rGrid.GetTileSize() / 2;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x - m_BodyHalfWidth;
	rPosition.y = NewPosition.y - rGrid.GetTileSize() / 2;
	m_VerticesBody.append( Vertex );
}

CSnake::~CSnake( void )
{
}

void CSnake::Update( float DeltaTime )
{
	m_Body = m_Head;
	m_Head.GridPosition += m_Head.Direction;

	UpdateBodyVertices();
	UpdateHeadVertices();
}

void CSnake::Render( void )
{
	sf::RenderWindow& rWindow = CGameManager::GetInstance().GetWindow();
	rWindow.draw( m_VerticesBody );
	rWindow.draw( m_VerticesHead );
}

void CSnake::UpdateHeadVertices( void )
{
	CGrid& rGrid = m_rGame.GetGrid();

	sf::Vector2f& rPosition = m_VerticesHead[0].position;

	rPosition = rGrid.GridToScreen( m_Head.GridPosition.x, m_Head.GridPosition.y );
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
}

void CSnake::UpdateBodyVertices( void )
{
	// 6 first vertices is the first body
	// 2 first is in head to connect head and body
	// next 4 is fills first body tile 
}

void CSnake::AddBody( void )
{
	unsigned VertexCount = m_VerticesBody.getVertexCount();
	sf::Vertex Vertex1 = m_VerticesBody[VertexCount - 2];
	sf::Vertex Vertex2 = m_VerticesBody[VertexCount - 1];

	m_VerticesBody.append( std::move( Vertex1 ) );
	m_VerticesBody.append( std::move( Vertex2 ) );
}
