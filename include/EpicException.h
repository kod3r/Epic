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

namespace epic {
	class Exception : public std::exception{
	public:
		Exception(const char* message) {}
		~Exception() throw() {}
		virtual const char* what() const throw() {
			return message_;
		}		
	private:
		Exception();
		const char* message_;
	}; // EpicException
} // epic

#endif // EPIC_INCLUDE_EPICEXCEPTION_H