#include "CGameSnake.h"
#include "Managers/CFontManager.h"
#include "Managers/CGameManager.h"

#include <imgui.h>

CGameSnake::CGameSnake( void )
	: m_FixedUpdateTimer()
	, m_FixedUpdateTarget( .5f )
	, m_Grid( 10 )
	, m_Snake()
	, m_Food()
	, m_FPS( "", *CFontManager::GetInstance().GetFont( "ForeverBatman" ) )
	, m_FPSBuffer( 500 )
	, m_FPSIndex( 0 )
{
	m_FPS.move( sf::Vector2f( 10, 0 ) );
}

CGameSnake::~CGameSnake( void )
{
}

void CGameSnake::Update( float DeltaTime )
{
	m_FPSBuffer[m_FPSIndex] = 1 / DeltaTime;
	m_FPSIndex = ( m_FPSIndex + 1 ) % m_FPSBuffer.size();
	unsigned FPS = 0;
	for( unsigned& rUnsigned : m_FPSBuffer )
		FPS += rUnsigned;
	FPS /= m_FPSBuffer.size();
	m_FPS.setString( "FPS: " + std::to_string( FPS ) );

	m_Snake.Input();
	if( m_Snake.IsDead() || m_FixedUpdateTimer.GetDeltaTime( false ) < m_FixedUpdateTarget )
		return;

	m_FixedUpdateTimer.Update();
	m_Snake.Update();

	if( m_Snake.IsDead( m_Food.GetGridPos() ) )
	{
		m_Snake.AddBody();
		m_Food.RandomizePosition();
	}
}

void CGameSnake::Render( void )
{
	m_Grid.Render();
	m_Food.Render();
	m_Snake.Render();

	CGameManager::GetInstance().GetWindow().draw( m_FPS );
}

void CGameSnake::ImGui( void )
{
	if( !ImGui::BeginTabBar( "GameBar" ) )
		return;

	if( ImGui::BeginTabItem( "Game" ) )
	{
		ImGui::InputFloat( "Fixed Update", &m_FixedUpdateTarget, .01f, .1f );

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
