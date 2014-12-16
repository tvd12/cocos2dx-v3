#ifndef _SingLeton_H
#define _SingLeton_H
#include <string>
#include <assert.h>  

template <typename T> class SingLeton
{
protected:
    
	static T* mSingleton;
    
public:
	SingLeton( void )
	{
	}
	~SingLeton( void )
	{  
		//assert( ms_FMSingleton );  
		delete mSingleton;
        mSingleton = NULL;
	}
	static T& getSingleton( void )
	{	
        if (mSingleton == NULL) mSingleton = new T;
        
        assert(mSingleton != NULL);
        
		return ( *mSingleton );
	}
	static T* getSingletonPtr( void )
	{
        if (mSingleton == NULL) mSingleton = new T;
        
        assert(mSingleton != NULL);
        
        return mSingleton;
    }
};

//! static class member initialisation.
template <typename T> T* SingLeton<T>::mSingleton = NULL;

#endif

