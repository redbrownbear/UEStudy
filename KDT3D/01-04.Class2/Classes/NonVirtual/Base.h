#pragma once
//프로젝트 속성 ->C/C++ -> 일반 -> 추가포함 디렉터리
#include "Misc/Headers.h"

//접근 지정자
// public : 어디서든 접근 가능
// protected : 자식에서는 public동작 / 외부에서 private처럼 동작
// private : 외부에서 접근 불가, 해당 class(struct) 내부에서 접근가능
//			자식에서 접근 불가
// Class는 접근 지정자가 없으면 private, struct public

class FBase
{
public:
	FBase();
	~FBase();

public:
	void PublicMethod();

public:
	int PublicValue = 0;

protected:
	int ProtectedValue = 1;

private:
	int privateValue = 2;
	int privateValue2 = 3;

};

