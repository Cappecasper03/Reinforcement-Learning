#pragma once

#include "../IGame.h"
#include "CSingleton.h"
#include "CGrid.h"
#include "CSnake.h"
#include "CFood.h"
#include "CTimer.h"
#include "CVector.h"

class CGameSnake : public IGame, public CSingleton<CGameSnake>
{
public:
	CGameSnake( void );
	~CGameSnake( void );

	void Update( float DeltaTime ) override;
	void Render( void ) override;
	void ImGui( void ) override;

	CGrid& GetGrid( void ) { return m_Grid; }
	CSnake& GetSnake( void ) { return m_Snake; }
	CFood& GetFood( void ) { return m_Food; }

private:
	CTimer m_FixedUpdateTimer;
	float m_FixedUpdateTarget;

	CGrid m_Grid;
	CSnake m_Snake;
	CFood m_Food;

	sf::Text m_FPS;
	CVector<unsigned> m_FPSBuffer;
	unsigned m_FPSIndex;
};