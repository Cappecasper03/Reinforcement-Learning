#pragma once

#include "../IGame.h"
#include "CSingleton.h"
#include "CGrid.h"
#include "CSnake.h"
#include "CFood.h"
#include "CTimer.h"

class CGameSnake : public IGame, public CSingleton<CGameSnake>
{
public:
	CGameSnake( void );
	~CGameSnake( void );

	void Update( float DeltaTime ) override;
	void Render( void ) override;

	CGrid& GetGrid( void ) { return m_Grid; }
	CSnake& GetSnake( void ) { return m_Snake; }
	CFood& GetFood( void ) { return m_Food; }

private:
	CTimer m_FixedUpdateTimer;

	CGrid m_Grid;
	CSnake m_Snake;
	CFood m_Food;
};