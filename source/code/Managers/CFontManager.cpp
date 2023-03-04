#include "CFontManager.h"

CFontManager::CFontManager( void )
	: m_Fonts()
{
}

CFontManager::~CFontManager( void )
{
}

bool CFontManager::Load( std::string FileName, std::string Name )
{
	SFont Font;
	bool FoundFont = Font.Font.loadFromFile( "data/fonts/" + FileName );
	Font.Name = Name;

	if( FoundFont )
		m_Fonts.InsertSorted( std::move( Font ) );

	return FoundFont;
}

sf::Font* CFontManager::GetFont( std::string Name )
{
	SFont Font;
	Font.Name = Name;
	auto it = m_Fonts.FindSorted( Font );

	if( it != m_Fonts.end() && it._Ptr->Name == Name )
		return &it._Ptr->Font;

	return nullptr;
}
