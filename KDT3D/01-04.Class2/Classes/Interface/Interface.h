#pragma once
#include "Misc//Headers.h"

//class이름 앞에 I(i)를 붙여서
//interface라고 티를 내주는 방식을 사용

class IInterface
{
public:
	virtual void MustFunction() = 0;	//순수 가상 함수

	virtual void MustFunction2()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	//interface는 내부에 변수를 만들지 않고
	//사용하는 것이 일반적
//public:
//	int Value = 0;
};

__interface IInterface2
{
public:
	virtual void MustMustFunction() abstract;

	/*int Value = 0;*/
};

//class IInterface3 abstract
//{
//	virtual void MustMustMustFunction2()
//	{
//		std::cout << __FUNCTION__ << std::endl;
//	}
//};
