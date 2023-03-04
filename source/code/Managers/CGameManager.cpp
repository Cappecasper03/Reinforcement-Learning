#include "CGameManager.h"
#include "CTimer.h"
#include "Games/IGame.h"
#include "Games/Snake/CGameSnake.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

CGameManager::CGameManager( void )
	: m_Window( sf::VideoMode( 1200, 800 ), "Reinfocment Learning" )
	, m_pGame( new CGameSnake )
{
}

CGameManager::~CGameManager( void )
{
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

			if( WindowEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
				m_Window.close();
		}

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
		m_pGame->Render();
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
			m_pGame->ImGui();
	}

	ImGui::End();
	ImGui::SFML::Render( m_Window );
}
