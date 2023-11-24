#include "Exceptions.h"

Exceptions::ReadAccessViolationException::ReadAccessViolationException(const char* message) : exception(message) {}
Exceptions::IndexOutOfBoundsException::IndexOutOfBoundsException(const char* message) : exception(message) {}
Exceptions::InvalidInputException::InvalidInputException(const char* message) : exception(message) {}