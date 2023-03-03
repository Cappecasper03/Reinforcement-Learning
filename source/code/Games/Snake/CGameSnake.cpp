#include "CGameSnake.h"

CGameSnake::CGameSnake( void )
	: m_FixedUpdateTimer()
	, m_FixedUpdateTarget( 1 )
	, m_Grid( 10 )
	, m_Snake()
	, m_Food()
{
}

CGameSnake::~CGameSnake( void )
{
}

void CGameSnake::Update( float DeltaTime )
{
	if( m_FixedUpdateTimer.GetDeltaTime( false ) < m_FixedUpdateTarget )
		return;

	m_FixedUpdateTimer.Update();
	m_Snake.Update( DeltaTime );
}

void CGameSnake::Render( void )
{
	m_Grid.Render();
	m_Food.Render();
	m_Snake.Render();
}
