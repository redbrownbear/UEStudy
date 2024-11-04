#pragma once
#include "Misc/Headers.h"

//부모에 virtual이 하나라도 있으면
//Virtual Table을 가리키는 주소가 하나라도 있으면 
class FBaseVirtual
{
public:
	FBaseVirtual();
	virtual~FBaseVirtual();

public:
	virtual void PublicMethod();
	void PublicMethod2();

public:
	int PublicValue = 0;

protected:
	int ProtectedValue = 1;

private:
	int privateValue = 2;
	int privateValue2 = 3;
};

void Test(FBaseVirtual* InBaseVirtual);


