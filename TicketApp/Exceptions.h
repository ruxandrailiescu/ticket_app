#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
using namespace std;

// log errors ?

namespace Exceptions {
	class ReadAccessViolationException : public exception
	{
	public:
		ReadAccessViolationException(const char* message);
	};

	class IndexOutOfBoundsException : public exception
	{
	public:
		IndexOutOfBoundsException(const char* message);
	};

	class InvalidInputException : public exception
	{
	public:
		InvalidInputException(const char* message);
	};
}


#endif