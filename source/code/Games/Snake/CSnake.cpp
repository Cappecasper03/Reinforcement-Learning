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
	for( unsigned i = 0; i < m_VerticesHead.getVertexCount(); i++ )
		m_VerticesHead[i].color = sf::Color::Green;

	UpdateHeadVertices();

	m_Body = m_Head;
	float Offset = rGrid.GetTileSize() / 2;
	sf::Vertex Vertex;
	Vertex.color = sf::Color::Green;
	sf::Vector2f& rPosition = Vertex.position;
	sf::Vector2f NewPosition = rGrid.GridToScreen( m_Body.GridPosition.x, m_Body.GridPosition.y );
	rPosition.x = NewPosition.x + m_BodyHalfWidth;
	rPosition.y = NewPosition.y;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x - m_BodyHalfWidth;
	rPosition.y = NewPosition.y;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x + m_BodyHalfWidth;
	rPosition.y = NewPosition.y + Offset;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x - m_BodyHalfWidth;
	rPosition.y = NewPosition.y + Offset;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x + m_BodyHalfWidth;
	rPosition.y = NewPosition.y - Offset;
	m_VerticesBody.append( Vertex );

	rPosition.x = NewPosition.x - m_BodyHalfWidth;
	rPosition.y = NewPosition.y - Offset;
	m_VerticesBody.append( Vertex );

	Update();
}

CSnake::~CSnake( void )
{
}

void CSnake::Update( void )
{
	m_Body = m_Head;
	m_Head.GridPosition += m_Head.Direction;

	UpdateHeadVertices();
	UpdateBodyVertices();
}

void CSnake::Render( void )
{
	sf::RenderWindow& rWindow = CGameManager::GetInstance().GetWindow();
	rWindow.draw( m_VerticesBody );
	rWindow.draw( m_VerticesHead );
}

void CSnake::ImGui( void )
{
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
	// Updates all vertice except the 4 first
	for( unsigned i = m_VerticesBody.getVertexCount() - 1; i > 3; i-- )
		m_VerticesBody[i] = m_VerticesBody[i - 2];

	// Updates first 2 vertices
	{
		sf::Vector2f& rPosition0 = m_VerticesBody[0].position;
		rPosition0 = m_VerticesHead[0].position;

		sf::Vector2f& rPosition1 = m_VerticesBody[1].position;
		rPosition1 = m_VerticesHead[0].position;

		if( m_Body.Direction.x == 0 )
		{
			rPosition0.x += m_BodyHalfWidth;
			rPosition1.x -= m_BodyHalfWidth;
		}
		else
		{
			rPosition0.y += m_BodyHalfWidth;
			rPosition1.y -= m_BodyHalfWidth;
		}
	}

	// Updates vertices 3 & 4
	{
		CGrid& rGrid = m_rGame.GetGrid();

		sf::Vector2f& rPosition0 = m_VerticesBody[2].position;
		rPosition0 = rGrid.GridToScreen( m_Body.GridPosition.x, m_Body.GridPosition.y );

		sf::Vector2f& rPosition1 = m_VerticesBody[3].position;
		rPosition1 = rPosition0;

		float Offset = rGrid.GetTileSize() / 2;
		if( m_Body.Direction.x == 0 )
		{
			rPosition0.x += m_BodyHalfWidth;
			rPosition0.y += Offset;
			rPosition1.x -= m_BodyHalfWidth;
			rPosition1.y += Offset;
		}
		else
		{
			rPosition0.x += Offset;
			rPosition0.y += m_BodyHalfWidth;
			rPosition1.x += Offset;
			rPosition1.y -= m_BodyHalfWidth;
		}
	}
}

void CSnake::AddBody( void )
{
	unsigned VertexCount = m_VerticesBody.getVertexCount();
	sf::Vertex Vertex1 = m_VerticesBody[VertexCount - 2];
	sf::Vertex Vertex2 = m_VerticesBody[VertexCount - 1];

	m_VerticesBody.append( std::move( Vertex1 ) );
	m_VerticesBody.append( std::move( Vertex2 ) );
}
