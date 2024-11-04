#include "Derived.h"

FDerived::FDerived()
{
	std::cout << __FUNCTION__ << std::endl;
}

FDerived::~FDerived()
{
	std::cout << __FUNCTION__ << std::endl;
}

void FDerived::PublicMethod()
{
	FBase::PublicMethod(); 
	std::cout << __FUNCTION__ << std::endl;
}
