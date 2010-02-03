#ifndef TYPENAME_C
#define TYPENAME_C

#include <cstdlib>
#include <typeinfo>
#include <stdexcept>
#include <fstream>
#include <matrix/typename.h>

template<typename Type>
std::string TypeName(Type const value, bool const debug)
{
    std::string FileName("./RasterManSymbol");
    std::string RemoveCommand("rm -f ");
    RemoveCommand += FileName;
#if 1
    if (std::system(RemoveCommand.c_str())) {
	throw std::runtime_error("Cannot remove " + FileName);
    }
#else
    {
	int returnvalue = std::system(RemoveCommand.c_str());
	if (returnvalue != 0) {
	    std::cout << RemoveCommand.c_str() << " returns: " << returnvalue
		      << std::endl;
	}
    }
#endif

    std::string Command("c++filt --format=gnu-v3 ");
//    std::string Command("c++filt ");
//    Command += typeid(value).name();
    Command += std::string(typeid(value).name());
    Command += " > ";
    Command += FileName;
//    std::cout << Command << std::endl;
#if 1
    if (std::system(Command.c_str())) {
	throw std::runtime_error("Cannot execute: " + Command);
    }
#else
    {
	int returnvalue = std::system(Command.c_str());
	if (returnvalue != 0) {
	    std::cout << Command.c_str() << " returns: " << returnvalue
		      << std::endl;
	}
    }
#endif

    std::ifstream TypeNameFile(FileName.c_str());
    if (!TypeNameFile) throw std::runtime_error("Cannot open " + FileName);

    std::string TypeName("'Not Known' ");
    const unsigned int BufferSize = 1024;
    char Buffer[BufferSize];
    TypeNameFile.getline(Buffer, BufferSize, '\n');
    TypeName = std::string(Buffer);
//    TypeNameFile >> TypeName;
    TypeNameFile.close();

//    std::cout << "type name read: " << TypeName << std::endl;

#if 1
#if 1
    if (std::system(RemoveCommand.c_str())) {
	throw std::runtime_error("Cannot remove " + FileName);
    }
#endif
#else
    {
	int returnvalue = std::system(RemoveCommand.c_str());
	if (returnvalue != 0) {
	    std::cout << RemoveCommand.c_str() << " returns: " << returnvalue
		      << std::endl;
	}
    }
#endif

    if (debug) {
	std::cout << "TypeName: " << typeid(value).name()
		  << " --> "      << TypeName
		  << std::endl;
    }

    return TypeName;
}

#endif
