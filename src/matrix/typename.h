#ifndef TYPENAME_H
#define TYPENAME_H

#include <iostream>
#include <iomanip>
#include <string>

template<typename Type>
std::string TypeName(Type const value, bool const debug = false);

#ifdef INSTANTIATE
#include <matrix/typename.C>
#endif
#endif
