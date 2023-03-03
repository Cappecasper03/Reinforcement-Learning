#pragma once

#include "../IGame.h"
#include "CSingleton.h"
#include "CGrid.h"
#include "CFood.h"

class CGameSnake : public IGame, public CSingleton<CGameSnake>
{
public:
	CGameSnake( void );
	~CGameSnake( void );

	void Update( float DeltaTime ) override;
	void Render( void ) override;

	CGrid& GetGrid( void ) { return m_Grid; }
	CFood& GetFood( void ) { return m_Food; }

private:
	CGrid m_Grid;
	CFood m_Food;
};