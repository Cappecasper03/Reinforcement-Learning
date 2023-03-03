#include "CGameSnake.h"

CGameSnake::CGameSnake( void )
	: m_Grid( 10 )
	, m_Snake()
	, m_Food()
{
}

CGameSnake::~CGameSnake( void )
{
}

void CGameSnake::Update( float DeltaTime )
{
}

void CGameSnake::Render( void )
{
	m_Grid.Render();
	m_Food.Render();
	m_Snake.Render();
}
