#pragma once
#include "Base.h"

class FDerived : public FBase
{
public: 
		FDerived();
		~FDerived();

public:
	void PublicMethod();

public:
	int DerivedPublicValue = 11;
	int DerivedPublicValue2 = 22;

};

