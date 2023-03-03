#include "CGameManager.h"
#include "CTimer.h"

#include <SFML/Window/Event.hpp>

CGameManager::CGameManager( void )
	: m_Window( sf::VideoMode( 1200, 800 ), "Reinfocment Learning" )
	, m_Games()
{
}

CGameManager::~CGameManager( void )
{
}

void CGameManager::Run( void )
{
	CTimer Timer;

	while( m_Window.isOpen() )
	{
		sf::Event WindowEvent;

		while( m_Window.pollEvent( WindowEvent ) )
		{
			if( WindowEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
				m_Window.close();

			Update( Timer.GetDeltaTime() );

			m_Window.clear( sf::Color::Black );
			Render();
			m_Window.display();
		}
	}
}

void CGameManager::Update( float DeltaTime )
{
}

void CGameManager::Render( void )
{
}