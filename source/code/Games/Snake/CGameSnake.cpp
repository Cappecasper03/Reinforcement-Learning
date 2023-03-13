#include "CGameSnake.h"
#include "Managers/CFontManager.h"
#include "Managers/CGameManager.h"
#include "AI/CAgent.h"

#include <imgui.h>

CGameSnake::CGameSnake( void )
	: m_FixedUpdateTimer()
	, m_FixedUpdateTarget( .5f )
	, m_Grid( 10, this )
	, m_AgentInputs( 100, 0 )
	, m_pAgent( nullptr )
	, m_Food( this )
	, m_Text( "", *CFontManager::GetInstance().GetFont( "ForeverBatman" ) )
{
	m_Text.move( sf::Vector2f( 10, 100 ) );
	m_Text.scale( .6f, .6f );

	CreateNewAgent();
}

CGameSnake::~CGameSnake( void )
{
}

void CGameSnake::Update( float DeltaTime )
{
	if( m_IsRestartable )
		return;

	if( m_FixedUpdateTimer.GetDeltaTime( false ) < m_FixedUpdateTarget / m_GameSpeed )
		return;
	else if( m_pAgent->GetAgent()->IsDead() )
	{
		m_IsRestartable = true;
		return;
	}

	m_FixedUpdateTimer.Update();
	m_pAgent->Update( DeltaTime, &m_AgentInputs );
}

void CGameSnake::Render( void )
{
	m_Grid.Render();
	m_Food.Render();
	m_pAgent->GetAgent()->Render();

	m_Text.setString( "Score: " + std::to_string( m_pAgent->GetAgent()->GetScore() ) );
	m_Text.setString( m_Text.getString() + "\n" + "Steps Left: " + std::to_string( m_pAgent->GetAgent()->GetStepsLeft() ) );
	m_Text.setString( m_Text.getString() + "\n" + "Fitness: " + std::to_string( m_pAgent->GetAgent()->GetFitness() ) );
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

void CGameSnake::CreateNewAgent( void )
{
	unsigned GridSize = m_Grid.GetGridSize();
	unsigned InputSize = GridSize * GridSize;
	std::vector<unsigned> NNTopology = { InputSize, InputSize / 3, 4 };
	m_AgentInputs.resize( InputSize, 0 );

	if( m_pAgent )
		delete m_pAgent;
	m_pAgent = new CAgent<CSnake>( this, NNTopology );
}

void CGameSnake::Restart( void )
{
	unsigned GridSize = m_Grid.GetGridSize();

	for( float& rValue : m_AgentInputs )
		rValue = 0;

	m_IsRestartable = false;
	m_pAgent->GetAgent()->Restart();
	m_Food.RandomizePosition();
}
