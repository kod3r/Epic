/**
 * @file EpicException.h
 * @brief exception handle class
 * @author Shi Jiabin
 * @version 1.0
 * @data 2015
 */
#ifndef EPIC_INCLUDE_EPICEXCEPTION_H
#define EPIC_INCLUDE_EPICEXCEPTION_H

#include <exception>
#include "include/EpicPrerequisites.h"

namespace epic {
	class Exception : public std::exception{
	public:
		Exception(const String& message);
		~Exception() throw() {}
		virtual const char* what() const throw() {
			return message_.c_str();
		}		
	private:
		Exception();
		String message_;
	}; // EpicException
} // epic

#endif // EPIC_INCLUDE_EPICEXCEPTION_H