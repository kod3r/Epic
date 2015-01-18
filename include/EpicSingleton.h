/**
 * @file EpicPrerequisites.h
 * @brief Singleton template class
 * @author Shi Jiabin
 * @version 1.0
 * @data 2015
 */
/* Original version Copyright (C) Scott Bilas, 2000.
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Bilas, 2000"
 */
#ifndef EPIC_INCLUDE_EPICSINGLETON_H
#define EPIC_INCLUDE_EPICSINGLETON_H

#include "include/EpicPrerequisites.h"
#pragma warning(disable:4661)

namespace epic {
	template<typename T>
	class Singleton{
	public:
		Singleton() {
			assert(!singleton_);
			// add by shi
			// Visual Studio C compiler versions
			// MS VC++ 11.0 _MSC_VER = 1700 (Visual C++ 2012)
			// MS VC++ 10.0 _MSC_VER = 1600 (Visual C++ 2010)
			// MS VC++ 9.0 _MSC_VER = 1500 (Visual C++ 2008)
			// MS VC++ 8.0 _MSC_VER = 1400 (Visual C++ 2005)
			// MS VC++ 6.0 _MSC_VER = 1200
			//
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
			int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
			singleton_ = (T*)((int)this + offset);
#else
			singleton_ = static_cast<T*>(this);
#endif
		}
		~Singleton() {
			assert(singleton_);
			singleton_ = 0;
		}
		static T& GetInstance(void) {
			assert(singleton_);
			return *singleton_;
		}
		static T* GetInstancePtr(void) {
			return singleton_;
		}
	protected:
		static T* singleton_;
	private:
		Singleton(Singleton<T>&);
		Singleton& operator=(Singleton<T>&);
	}; // Singleton
} // epic

#endif