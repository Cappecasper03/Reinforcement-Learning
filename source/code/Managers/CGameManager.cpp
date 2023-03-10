#include "CGameManager.h"
#include "CTimer.h"
#include "Games/Snake/CGameSnake.h"
#include "Managers/CFontManager.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <imgui.h>

CGameManager::CGameManager( void )
	: m_Window( sf::VideoMode( 1200, 800 ), "Reinfocment Learning" )
	, m_pGame( nullptr )
{
	CFontManager::Initialize();
	CFontManager::GetInstance().Load( "batmfa__.ttf", "ForeverBatman" );

	m_pGame = new CGeneticAlgorithm<CGameSnake>( 1 );
}

CGameManager::~CGameManager( void )
{
	CFontManager::Deinitialize();

	if( m_pGame )
		delete m_pGame;
}

void CGameManager::Run( void )
{
	CTimer Timer;
	ImGui::SFML::Init( m_Window );

	while( m_Window.isOpen() )
	{
		sf::Event WindowEvent;

		while( m_Window.pollEvent( WindowEvent ) )
		{
			ImGui::SFML::ProcessEvent( WindowEvent );

			if( WindowEvent.type == sf::Event::Closed )
				m_Window.close();
		}

		Input();
		Update( Timer.GetDeltaTime() );

		m_Window.clear( sf::Color::Black );
		Render();
		ImGui( Timer.GetDeltaTime( false ) );
		m_Window.display();
	}

	ImGui::SFML::Shutdown();
}

void CGameManager::Update( float DeltaTime )
{
	if( m_pGame )
		m_pGame->Update( DeltaTime );
}

void CGameManager::Render( void )
{
	if( m_pGame )
	{
		if( m_pGame->GetBestGame() )
			m_pGame->GetBestGame()->Render();
	}
}

void CGameManager::ImGui( float DeltaTime )
{
#if defined( FINAL )
	return;
#endif

	sf::Time Time( sf::seconds( DeltaTime ) );
	ImGui::SFML::Update( m_Window, Time );

	if( ImGui::Begin( "Game" ) )
	{
		if( m_pGame )
		{
			if( m_pGame->GetBestGame() )
				m_pGame->GetBestGame()->ImGui();
		}
	}

	ImGui::End();
	ImGui::SFML::Render( m_Window );
}

void CGameManager::Input( void )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
		m_Window.close();

	if( m_pGame && m_pGame->GetPopulation() == 1 )
	{
		if( m_pGame->GetBestGame() )
			m_pGame->GetBestGame()->Input();
	}
}
