#pragma once

#include "../IGame.h"
#include "CGrid.h"
#include "CSnake.h"
#include "CFood.h"
#include "CTimer.h"
#include "CVector.h"
#include "AI/CAgent.h"

class CGameSnake : public IGame
{
public:
	CGameSnake( void );
	~CGameSnake( void );

	void Update( float DeltaTime ) override;
	void Render( void ) override;
	void ImGui( void ) override;
	void Input( void ) override;

	CGrid& GetGrid( void ) { return m_Grid; }
	CAgent<CSnake>* GetSnake( void ) { return m_pAgent; }
	CFood& GetFood( void ) { return m_Food; }

	void Restart( void ) override;

	CAgent<IAgent>* GetAgent( void ) { return ( CAgent<IAgent>* )m_pAgent; }

private:
	CTimer m_FixedUpdateTimer;
	float m_FixedUpdateTarget;

	CGrid m_Grid;
	CAgent<CSnake>* m_pAgent;
	CFood m_Food;

	sf::Text m_Text;
};