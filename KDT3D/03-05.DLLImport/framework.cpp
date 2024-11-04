#include "pch.h"

void MYDLL_API HelloDLL_0305()
{
	std::cout << "hello";
}

FClassDLLImport::FClassDLLImport()
{
	std::cout << __FUNCTION__;
}

FClassDLLImport::~FClassDLLImport()
{
}
