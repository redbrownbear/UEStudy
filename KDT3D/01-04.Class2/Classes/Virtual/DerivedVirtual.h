#pragma once
#include "BaseVirtual.h"

class FDerivedVirtual : public FBaseVirtual
{
public:
	FDerivedVirtual();
	virtual ~FDerivedVirtual() override;

public:
	virtual void PublicMethod() override;

public:
	int DerivedPublicValue = 11;
	int DerivedPublicValue2 = 22;

};

