#pragma once

class IGame
{
public:
	virtual void Update( float DeltaTime ) = 0;
	virtual void Render( void ) {};
};