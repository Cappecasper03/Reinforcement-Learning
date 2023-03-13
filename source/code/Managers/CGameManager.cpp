#include "CGameManager.h"
#include "CTimer.h"
#include "Games/Snake/CGameSnake.h"
#include "Managers/CFontManager.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <imgui.h>

CGameManager::CGameManager( void )
	: m_Window( sf::VideoMode( 1200, 800 ), "Reinfocment Learning" )
	, m_pGAGame( nullptr )
	, m_FPSText()
	, m_FPSBuffer( 500 )
	, m_FPSIndex( 0 )
	, m_AgentName( "Snake-10x10.txt" )
{
	CFontManager::Initialize();
	CFontManager& rFontManager = CFontManager::GetInstance();
	rFontManager.Load( "batmfa__.ttf", "ForeverBatman" );

	m_FPSText.setFont( *rFontManager.GetFont( "ForeverBatman" ) );
	m_FPSText.move( sf::Vector2f( 10, 00 ) );
	m_FPSText.scale( .6f, .6f );

	m_pGAGame = new CGeneticAlgorithm<CGameSnake>( 1 );
}

CGameManager::~CGameManager( void )
{
	CFontManager::Deinitialize();

	if( m_pGAGame )
		delete m_pGAGame;
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

		m_Window.clear();
		Render();
		ImGui( Timer.GetDeltaTime( false ) );
		m_Window.display();
	}

	ImGui::SFML::Shutdown();
}

void CGameManager::Update( float DeltaTime )
{
	{
		m_FPSBuffer[m_FPSIndex] = 1 / DeltaTime;
		m_FPSIndex = ( m_FPSIndex + 1 ) % m_FPSBuffer.size();
		unsigned FPS = 0;
		for( unsigned& rUnsigned : m_FPSBuffer )
			FPS += rUnsigned;
		FPS /= m_FPSBuffer.size();
		m_FPSText.setString( "FPS: " + std::to_string( FPS ) );
	}

	if( m_pGAGame )
		m_pGAGame->Update( DeltaTime );
}

void CGameManager::Render( void )
{
	m_Window.draw( m_FPSText );

	if( m_pGAGame )
	{
		if( m_pGAGame->GetBestGameLastGen() )
			m_pGAGame->GetBestGameLastGen()->Render();
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
		if( ImGui::BeginTabBar( "GameBar" ) )
		{
			if( ImGui::BeginTabItem( "Agent" ) )
			{
				char* pBuffer = m_AgentName.data();
				if( ImGui::InputText( "Agent Name", pBuffer, m_AgentName.size() + 10 ) )
					m_AgentName = pBuffer;

				if( ImGui::Button( "Save Agent by Name" ) )
				{
					if( m_pGAGame )
						m_pGAGame->SaveBestModel( m_AgentName );
				}

				if( ImGui::Button( "Load Agent by Name" ) )
				{
					if( m_pGAGame )
						m_pGAGame->LoadModel( m_AgentName );
				}

				ImGui::EndTabItem();
			}

			if( m_pGAGame )
			{
				if( m_pGAGame->GetBestGameLastGen() )
					m_pGAGame->GetBestGameLastGen()->ImGui();
			}
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
	ImGui::SFML::Render( m_Window );
}

void CGameManager::Input( void )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
		m_Window.close();

	if( m_pGAGame && m_pGAGame->GetPopulation() <= 1 )
	{
		if( m_pGAGame->GetBestGameLastGen() )
			m_pGAGame->GetBestGameLastGen()->Input();
	}
}
