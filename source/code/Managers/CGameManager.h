#pragma once

#include "CSingleton.h"
#include "AI/CGeneticAlgorithm.h"

#include <SFML/Graphics.hpp>
#include <string>

class CGameSnake;

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

	CGeneticAlgorithm<CGameSnake>* m_pGAGame;

	sf::Text m_FPSText;
	CVector<unsigned> m_FPSBuffer;
	unsigned m_FPSIndex;

	std::string m_AgentName;
};