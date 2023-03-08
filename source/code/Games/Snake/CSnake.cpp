#include "CSnake.h"
#include "Managers/CGameManager.h"
#include "CGameSnake.h"
#include "CGrid.h"

CSnake::CSnake( void )
	: m_HeadRadius( 0 )
	, m_Head()
	, m_VerticesHead( sf::TriangleFan, 20 )
	, m_Bodies()
	, m_VerticesBody( sf::Triangles )
	, m_StepsTaken( 0 )
	, m_IsDead( false )
	, m_rGame( CGameSnake::GetInstance() )
{
	CGrid& rGrid = m_rGame.GetGrid();
	m_HeadRadius = rGrid.GetTileSize() * .4f;
	m_Head.GridPosition = sf::Vector2f( ( int )( rGrid.GetGridSize() / 2 ), ( int )( rGrid.GetGridSize() / 2 ) );
	m_Head.Direction = sf::Vector2f( 0, 1 );
	for( unsigned i = 0; i < m_VerticesHead.getVertexCount(); i++ )
		m_VerticesHead[i].color = sf::Color::Green;

	UpdateHeadVertices();
	m_Bodies.push_back( m_Head );

	// TODO: Setup one triangle per body/tile

	Update();
}

CSnake::~CSnake( void )
{
}

void CSnake::Update( void )
{
	m_StepsTaken++;

	for( unsigned i = m_Bodies.size() - 1; i > 0; i-- )
		m_Bodies[i] = m_Bodies[i - 1];

	m_Bodies[0] = m_Head;
	m_Head.GridPosition += m_Head.Direction;

	if( m_rGame.GetFood().GetGridPos() == m_Head.GridPosition )
	{
		AddBody();
		m_rGame.GetFood().RandomizePosition();
	}

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

void CSnake::Input( void )
{
	// TODO: Better input

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
		m_Head.Direction = sf::Vector2f( 0, -1 );
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
		m_Head.Direction = sf::Vector2f( 0, 1 );
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
		m_Head.Direction = sf::Vector2f( 1, 0 );
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
		m_Head.Direction = sf::Vector2f( -1, 0 );
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
	// TODO: Update one triangle per body/tile
}

void CSnake::AddBody( void )
{
	// TODO: Add Vertices

	m_Bodies.push_back( m_Bodies.back() );
}
