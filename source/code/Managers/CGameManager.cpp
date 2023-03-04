#include "CGameManager.h"
#include "Games/IGame.h"
#include "Games/Snake/CGameSnake.h"

#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

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
	sf::Clock Clock;
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

		ImGui::SFML::Update( m_Window, Clock.restart() );
		ImGui();

		m_Window.clear( sf::Color::Black );
		Render();
		ImGui::SFML::Render();
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

void CGameManager::ImGui( void )
{
}
