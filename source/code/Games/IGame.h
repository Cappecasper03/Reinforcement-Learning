#pragma once

#include "AI/CAgent.h"

class IGame
{
public:
	virtual void Update( float DeltaTime ) = 0;
	virtual void Render( void ) = 0;
	virtual void ImGui( void ) {}
	virtual void Input( void ) {}

	bool IsRestartable( void ) { return m_IsRestartable; }

	virtual void Restart( void ) = 0;

	virtual CAgent<IAgent>* GetAgent( void ) = 0;

	float GetGameSpeed( void ) { return m_GameSpeed; }
	void SetGameSpeed( float NewGameSpeed ) { m_GameSpeed = NewGameSpeed; }

protected:
	bool m_IsRestartable = true;
	float m_GameSpeed = 1;
};