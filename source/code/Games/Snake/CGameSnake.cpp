#include "CGameSnake.h"

#include <imgui.h>

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
	m_Snake.Update();
}

void CGameSnake::Render( void )
{
	m_Grid.Render();
	m_Food.Render();
	m_Snake.Render();
}

void CGameSnake::ImGui( void )
{
	if( !ImGui::BeginTabBar( "GameBar" ) )
		return;

	if( ImGui::BeginTabItem( "Game" ) )
	{
		ImGui::InputFloat( "Fixed Update", &m_FixedUpdateTarget );

		ImGui::EndTabItem();
	}

	if( ImGui::BeginTabItem( "Snake" ) )
	{
		m_Snake.ImGui();

		ImGui::EndTabItem();
	}

	if( ImGui::BeginTabItem( "Grid" ) )
	{
		m_Grid.ImGui();

		ImGui::EndTabItem();
	}

	if( ImGui::BeginTabItem( "Food" ) )
	{
		m_Food.ImGui();

		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();
}
