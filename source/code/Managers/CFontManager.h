#pragma once

#include "CSingleton.h"
#include "CVector.h"

#include <SFML/Graphics/Font.hpp>

class CFontManager : public CSingleton<CFontManager>
{
public:
	CFontManager( void );
	~CFontManager( void );

	// Load font in directory "data/fonts/" + rFileName
	bool Load( std::string FileName, std::string Name );

	sf::Font* GetFont( std::string Name );

private:
	struct SFont
	{
		bool operator<( const SFont& rOther ) { return Name < rOther.Name; }

		sf::Font Font;
		std::string Name;
	};

	CVector<SFont> m_Fonts;
};