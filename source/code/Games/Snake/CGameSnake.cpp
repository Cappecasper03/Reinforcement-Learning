#include "CGameSnake.h"
#include "Managers/CFontManager.h"
#include "Managers/CGameManager.h"
#include "AI/CAgent.h"

#include <imgui.h>

CGameSnake::CGameSnake( void )
	: m_FixedUpdateTimer()
	, m_FixedUpdateTarget( .5f )
	, m_Grid( 10, this )
	, m_pAgent( nullptr )
	, m_Food( this )
	, m_Text( "", *CFontManager::GetInstance().GetFont( "ForeverBatman" ) )
{
	m_Text.move( sf::Vector2f( 10, 50 ) );
	m_Text.scale( .6f, .6f );

	std::vector<unsigned> NNTopology = { 3, 5, 4 };
	m_pAgent = new CAgent<CSnake>( this, NNTopology );
}

CGameSnake::~CGameSnake( void )
{
}

void CGameSnake::Update( float DeltaTime )
{
	if( m_IsRestartable )
		return;

	if( m_FixedUpdateTimer.GetDeltaTime( false ) < m_FixedUpdateTarget )
		return;
	else if( m_pAgent->GetAgent()->IsDead() )
	{
		m_IsRestartable = true;
		return;
	}

	m_FixedUpdateTimer.Update();
	m_pAgent->Update( DeltaTime );
}

void CGameSnake::Render( void )
{
	m_Grid.Render();
	m_Food.Render();
	m_pAgent->GetAgent()->Render();

	m_Text.setString( "Score: " + std::to_string( m_pAgent->GetAgent()->GetScore() ) );
	m_Text.setString( m_Text.getString() + "\n" + "Steps Taken: " + std::to_string( m_pAgent->GetAgent()->GetStepsTaken() ) );
	CGameManager::GetInstance().GetWindow().draw( m_Text );
}

void CGameSnake::ImGui( void )
{
	if( ImGui::BeginTabItem( "Game" ) )
	{
		ImGui::InputFloat( "Fixed Update", &m_FixedUpdateTarget, .01f, .1f );

		if( ImGui::Button( "Restart" ) && m_IsRestartable )
			Restart();

		ImGui::EndTabItem();
	}

	if( ImGui::BeginTabItem( "Snake" ) )
	{
		m_pAgent->GetAgent()->ImGui();

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
}

void CGameSnake::Input( void )
{
	m_pAgent->GetAgent()->Input();

	if( m_IsRestartable && ( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Enter ) ) )
		Restart();
}

void CGameSnake::Restart( void )
{
	m_IsRestartable = false;
	m_pAgent->GetAgent()->Restart();
	m_Food.RandomizePosition();
}
