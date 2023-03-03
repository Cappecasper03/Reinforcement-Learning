#pragma once

#include "CSingleton.h"
#include "CVector.h"

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

private:
	sf::RenderWindow m_Window;

	CVector<IGame*> m_Games;
};