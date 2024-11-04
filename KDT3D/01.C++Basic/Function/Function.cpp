#include <iostream>
#include "Function.h"

void FunctionName(int a, int b)
{
	std::cout << a << b << std::endl;
}

int AddFunction(const int a, const int b)
{
	const int Result = a + b;
	return Result;
}

double Addfunction(const double a, const double b)
{
	const double Result = a + b;

	return Result;
}

unsigned long long Factorial(unsigned char InF)
{
	if (InF == 0)
	{
		return 1;
	}

	return InF * Factorial(InF -1);
}

void HasFlags(unsigned char InProperty)
{
	std::cout << "비트 플래그의 활성화\n";
	// 0000 0001
	// 0000 0001
	// ------------AND
	// 0000 0001
	if (InProperty & EPropertyFlags::EProperty1)
	{
		std::cout << "EPropertyFlags::EProperty1\n";
	}
	if (InProperty & EPropertyFlags::EProperty2)
	{
		std::cout << "EPropertyFlags::EProperty2\n";
	}
	if (InProperty & EPropertyFlags::EProperty3)
	{
		std::cout << "EPropertyFlags::EProperty3\n";
	}
	if (InProperty & EPropertyFlags::EProperty4)
	{
		std::cout << "EPropertyFlags::EProperty4\n";
	}
	if (InProperty & EPropertyFlags::EProperty5)
	{
		std::cout << "EPropertyFlags::EProperty5\n";
	}
	if (InProperty & EPropertyFlags::EProperty6)
	{
		std::cout << "EPropertyFlags::EProperty6\n";
	}
	if (InProperty & EPropertyFlags::EProperty7)
	{
		std::cout << "EPropertyFlags::EProperty7\n";
	}
	if (InProperty & EPropertyFlags::EProperty8)
	{
		std::cout << "EPropertyFlags::EProperty8\n";
	}

	std::cout << std::endl;
}

int CallByValue(int InValue)
{
	InValue = 10;

	return InValue;
}

FParam CallByValue(FParam InParam)
{
	InParam.Value[0] = 9999;
	InParam.Value[5] = 5555;

	return InParam;
}

void CallByPointer(int* InPointer)
{
	*InPointer = 1234;
}

void CallByPointer(FParam* InPointer)
{
	InPointer->Value[0] = 9999;
	InPointer->Value[5] = 5555;
	(*InPointer).Value[2] = 2222;
}
void CallByReference(int& InReference)
{
	InReference = 1234;
}

void CallByReference(FParam& InReference)
{
	InReference.Value[0] = 9999;
	InReference.Value[5] = 5555;
	
	InReference.Value[2] = 2222;
}

void TestUnique(std::unique_ptr<int>& OutUnique)
{
	*OutUnique += 100;
}

void TestUnique(std::unique_ptr<int>* OutUnique)
{
	*(*OutUnique) += 100;
}
void TestShared(std::shared_ptr<int> OutShared)
{
	int* Pointer = OutShared.get();
	*OutShared += 100;
}

void TestWeak(std::weak_ptr<FParam> OutWeak)
{
	if(OutWeak.expired())
	{
		//_ASSERT(false);
		return;
	}

	std::shared_ptr<FParam> Shared = OutWeak.lock();
	FParam* Sharedd = Shared.get();
	Shared.use_count();
	Sharedd->A;
	Shared->A;
	OutWeak.lock()->A += 1234;
}

#include <cassert>
void FunctionWIthPointer(int* OutPointer)
{
	if (OutPointer == nullptr)
	{
		//_ASSERT(false);
		return;
	}
	
	*OutPointer += 100;
}

void FunctionWIthReference(int& OutReference)
{
	OutReference += 100;
}

void Swap(int& InOutFirst, int& InOutSecond)
{
	//Temp = InOutFirst(20)
	const int Temp = InOutFirst;

	//InOutFirst = InOutSecond(10)
	InOutFirst = InOutSecond;

	//InOutSecond = Temp(20)
	InOutSecond = Temp;
}

void SeperateOddsAndEvens(const std::array<int, 10>* const InNumbers, 
						 std::vector<int>* const OutOdds, std::vector<int>* const OutEvens)

{
	for(int Value : *InNumbers)
	{
		//std::cout << Value << std::endl;

		//홀수 판정
		if (Value % 2 == 1)
		{
			OutOdds->push_back(Value);
		}
		//짝수 판정
		else if(Value % 2 == 0)
		{
			OutEvens->push_back(Value);
		}
		else
		{
			_ASSERT(false);
		}
	}
}

void Swap(int* InOutFirst, int* InOutSecond)
{
	const int Temp = *InOutFirst;

	*InOutFirst = *InOutSecond;

	*InOutSecond = Temp;

}

void SeperateOddsAndEvens(const std::array<int, 10>& const InNumbers, 
						std::vector<int>& const OutOdds, std::vector<int>& const OutEvens)
{
	for (int Value : InNumbers)
	{
		//std::cout << Value << std::endl;

		//홀수 판정
		if (Value % 2 == 1)
		{
			OutOdds.push_back(Value);
		}
		//짝수 판정
		else if (Value % 2 == 0)
		{
			OutEvens.push_back(Value);
		}
		else
		{
			_ASSERT(false);
		}
	}
}

void SharedTestFunction(std::shared_ptr<FSharedTest> InShared)
{
	InShared->A = 0;
}

FOddsAndEvens SeperateOddsAndEvens(const std::array<int, 10>& const InNumbers)
{
	//RVO
	std::vector<int> Odds, Evens;

	for (int Value : InNumbers)
	{
		//std::cout << Value << std::endl;

		//홀수 판정
		if (Value % 2 == 1)
		{
			Odds.push_back(Value);
		}
		//짝수 판정
		else if (Value % 2 == 0)
		{
			Evens.push_back(Value);
		}
		else
		{
			_ASSERT(false);
		}
	}

	return FOddsAndEvens(Odds, Evens);
}

FOddsAndEvens SeperateOddsAndEvens2(const std::array<int, 10>& const InNumbers)
{
	//NRVO
	FOddsAndEvens OddsAndEvens;

	for (int Value : InNumbers)
	{
		//std::cout << Value << std::endl;

		//홀수 판정
		if (Value % 2 == 1)
		{
			OddsAndEvens.Odds.push_back(Value);
		}
		//짝수 판정
		else if (Value % 2 == 0)
		{
			OddsAndEvens.Evens.push_back(Value);
		}
		else
		{
			_ASSERT(false);
		}
	}

	return OddsAndEvens;
}

FParam::FParam()
{
	std::cout << "FPram\n";
}
FParam::~FParam()
{
	std::cout << "~FPram\n";
}

FOddsAndEvens::FOddsAndEvens()
{
}
