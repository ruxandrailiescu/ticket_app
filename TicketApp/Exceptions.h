#pragma once
#include <iostream>
using namespace std;

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