#pragma once

#include "CSingleton.h"

#include <SFML/Graphics/RenderWindow.hpp>

class IGame;

class CGameManager : public CSingleton<CGameManager>
{
public:
	CGameManager( void );
	~CGameManager( void );

	void Run( void );

	void Update( float DeltaTime );
	void Render( void );
	void ImGui( float DeltaTime );
	void Input( void );

	sf::RenderWindow& GetWindow( void ) { return m_Window; }

private:
	sf::RenderWindow m_Window;

	IGame* m_pGame;
};