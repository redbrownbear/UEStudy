#pragma once

// Error code를 return값으로 전달
// [return]
// 0: error(nullptr)
// 1: 성공
// 2: 배정하기 곤란
int FunctionErrorCode(int* InPointer) noexcept;

// Error code를 return값으로 전달
// [return]
// 0: error(nullptr)
// 1: 성공
// 2: 배정하기 곤란
int FunctionErrorCode2(int* InPointer);

enum  ErrorCode : uint8_t
{
	Success = 0,
	NullptrError = 1,

};

ErrorCode FunctionErrorCodeEnum(int* InPointer);

void FunctionException(int* InPointer);

class FClass
{
public:
	FClass(int* InPointer)
	{
		if (InPointer == nullptr)
		{
			throw "InPointer is nullptr";
		}

		Value = *InPointer;
	}

	int Value = 0;
};
