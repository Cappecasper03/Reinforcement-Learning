#include "CSnake.h"
#include "Managers/CGameManager.h"
#include "CGameSnake.h"
#include "CGrid.h"

#include <imgui.h>

CSnake::CSnake( void )
	: m_HeadRadius( 0 )
	, m_Head()
	, m_VerticesHead( sf::TriangleFan, 20 )
	, m_MoveDirection( 0, 1 )
	, m_HalfBodySize( 0 )
	, m_Bodies()
	, m_VerticesBody( sf::Triangles )
	, m_StepsTaken( 0 )
	, m_IsDead( false )
	, m_rGame( CGameSnake::GetInstance() )
{
	CGrid& rGrid = m_rGame.GetGrid();
	m_HeadRadius = rGrid.GetTileSize() * .4f;
	m_Head.GridPosition = sf::Vector2f( ( unsigned )( rGrid.GetGridSize() / 2 ), ( unsigned )( rGrid.GetGridSize() / 2 ) );
	m_Head.Direction = sf::Vector2f( 0, 1 );
	for( unsigned i = 0; i < m_VerticesHead.getVertexCount(); i++ )
		m_VerticesHead[i].color = sf::Color::Green;

	UpdateHeadVertices();

	m_HalfBodySize = rGrid.GetTileSize() * .3f;
	m_Bodies.push_back( m_Head );
	sf::Vertex Vertex;
	Vertex.color = sf::Color::Green;
	for( unsigned i = 0; i < 3; i++ )
		m_VerticesBody.append( Vertex );
	UpdateBodyVertices( 0 );

	Update();
}

CSnake::~CSnake( void )
{
}

void CSnake::Update( void )
{
	m_StepsTaken++;

	for( int i = m_Bodies.size() - 1; i > 0; i-- )
	{
		m_Bodies[i] = m_Bodies[i - 1];
		UpdateBodyVertices( i );
	}

	m_Bodies[0] = m_Head;
	UpdateBodyVertices( 0 );

	m_Head.Direction = m_MoveDirection;
	m_Head.GridPosition += m_Head.Direction;

	if( m_rGame.GetFood().GetGridPos() == m_Head.GridPosition )
	{
		AddBody();
		m_rGame.GetFood().RandomizePosition();
	}

	UpdateHeadVertices();
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

void CSnake::Input( void )
{
	if( m_IsDead )
		return;

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && m_Head.Direction != sf::Vector2f( 0, 1 ) )
		m_MoveDirection = sf::Vector2f( 0, -1 );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && m_Head.Direction != sf::Vector2f( 0, -1 ) )
		m_MoveDirection = sf::Vector2f( 0, 1 );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && m_Head.Direction != sf::Vector2f( -1, 0 ) )
		m_MoveDirection = sf::Vector2f( 1, 0 );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && m_Head.Direction != sf::Vector2f( 1, 0 ) )
		m_MoveDirection = sf::Vector2f( -1, 0 );
}

bool CSnake::IsOnSnake( sf::Vector2f& rGridPoint )
{
	if( m_Head.GridPosition == rGridPoint )
		return true;

	for( SBody& rBody : m_Bodies )
	{
		if( rBody.GridPosition == rGridPoint )
			return true;
	}

	return false;
}

bool CSnake::IsDead( void )
{
	if( m_IsDead )
		return true;

	const unsigned GridSize = m_rGame.GetGrid().GetGridSize();
	if( m_Head.GridPosition.x < 0 || m_Head.GridPosition.x >= GridSize || m_Head.GridPosition.y < 0 || m_Head.GridPosition.y >= GridSize )
	{
		m_IsDead = true;
		return true;
	}

	for( SBody& rBody : m_Bodies )
	{
		if( m_Head.GridPosition == rBody.GridPosition )
		{
			m_IsDead = true;
			return true;
		}
	}

	return false;
}

void CSnake::UpdateHeadVertices( void )
{
	CGrid& rGrid = m_rGame.GetGrid();

	sf::Vector2f& rPosition = m_VerticesHead[0].position;

	rPosition = rGrid.GridToScreen( m_Head.GridPosition );
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

void CSnake::UpdateBodyVertices( unsigned BodyIndex )
{
	CGrid& rGrid = m_rGame.GetGrid();
	SBody& rBody = m_Bodies[BodyIndex];

	sf::Vertex& rVertex1 = m_VerticesBody[BodyIndex * 3];
	sf::Vertex& rVertex2 = m_VerticesBody[BodyIndex * 3 + 1];
	sf::Vertex& rVertex3 = m_VerticesBody[BodyIndex * 3 + 2];

	rVertex1.position = rGrid.GridToScreen( rBody.GridPosition ) + ( rBody.Direction * m_HalfBodySize );
	rVertex2.position = rGrid.GridToScreen( rBody.GridPosition ) - ( rBody.Direction * m_HalfBodySize );
	rVertex3.position = rVertex2.position;

	if( rBody.Direction.x != 0 )
	{
		rVertex2.position.y += m_HalfBodySize;
		rVertex3.position.y -= m_HalfBodySize;
	}
	else
	{
		rVertex2.position.x += m_HalfBodySize;
		rVertex3.position.x -= m_HalfBodySize;
	}
}

void CSnake::AddBody( void )
{
	m_Bodies.push_back( m_Bodies.back() );

	for( unsigned i = 0; i < 3; i++ )
		m_VerticesBody.append( m_VerticesBody[0] );
	UpdateBodyVertices( m_Bodies.size() - 1 );
}
