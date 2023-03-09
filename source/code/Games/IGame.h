#pragma once

class IGame
{
public:
	virtual void Update( float DeltaTime ) = 0;
	virtual void Render( void ) = 0;
	virtual void ImGui( void ) {}
	virtual void Input( void ) {}

	bool IsRestartable( void ) { return m_IsRestartable; }

protected:
	virtual void Restart( void ) {}

	bool m_IsRestartable = false;
};