#pragma once
#include <iostream>
#include <format>

class FClass
{
public:
	FClass()
	{

	}
	FClass(const FClass& InOther)
		:a(InOther.a)
		, a2(InOther.a2)
		, a3(InOther.a3)
	{

	}

	~FClass()
	{

	}
	//return이 없어서 연쇄적으로 대입 불가
	//Ex) A = B = C불가
	//Ex) A = B는 가능

	constexpr FClass& operator=(const FClass& InOther)
	{
		a = InOther.a;
		a2 = InOther.a2;
		a3 = InOther.a3;

		return *this;
	}

	int a = 0;
	int a2 = 1;
	int a3 = 2;

	int* Pointer = nullptr;

};

//내부에 동적 할당한 Data가 있으면
//기본 복사 생성자와, 기본 대입 연산자에 의도와 다른 문제가 생길 수 있다.
class FClass2
{
public:
	FClass2()
	{
		Pointer = new int{ 100 };
		a = 1234;
	}

	//복사 생성자
	FClass2(const FClass2& InOther)
		:a(InOther.a)
		, Pointer(new int{*InOther.Pointer})
	{
		
	}

	//이동 생성자
	FClass2(FClass2&& InOther) noexcept
		:a(InOther.a)
		,Pointer(InOther.Pointer)
	{
		InOther.a = 0;
		InOther.Pointer = nullptr;
	}

	FClass2(const int InValue)
		:a(InValue)
		,Pointer(new int(100))
	{
	}

	~FClass2()
	{
		delete Pointer;
		Pointer = nullptr;
	}

	constexpr FClass2& operator=(const FClass2& InOther)
	{
		a = InOther.a;
		*Pointer = *InOther.Pointer;

		return *this;
	}

	void HelloConst() const
	{

	}
	void HelloNoConst()
	{

	}

	void Hello() const
	{
		std::cout << std::format("Hello : {}\n", this->a);

		//const 맴버 함수 내부에서는 const 맴버 함수만 호출 가능
		HelloConst();
		//HelloNoConst();

		//static은 상관 없음
	}
	void HelloTest() const
	{
		std::cout << std::format("this가 nullptr지만 작동했죠? \n");
	}

	//this를 파라미터로 전달하지 않는다.
	static void Hello2()
	{
		std::cout << std::format("Hello : {}\n", StaticVar1);
	}

private:
	int a = 0;
	int* Pointer = nullptr;

public:
	static int StaticVar1;
	inline static int StaticVar2 = 1234;
};

