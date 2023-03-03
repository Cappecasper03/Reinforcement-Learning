#pragma once

template<typename T>
class CSingleton
{
public:
	CSingleton( void ) { s_pInstance = ( T* )this; }
	virtual ~CSingleton( void ) { s_pInstance = nullptr; }

	static T& GetInstance( void ) { return *s_pInstance; }
	static T* GetInstancePtr( void ) { return s_pInstance; }

	static bool Initialize( void );
	static bool Deinitialize( void );

private:
	static T* s_pInstance;
};

template<typename T>
T* CSingleton<T>::s_pInstance = nullptr;

template<typename T>
inline bool CSingleton<T>::Initialize( void )
{
	if( s_pInstance )
		return false;

	s_pInstance = new T;
	return true;
}

template<typename T>
inline bool CSingleton<T>::Deinitialize( void )
{
	if( !s_pInstance )
		return false;

	s_pInstance = nullptr;
	return true;
}
