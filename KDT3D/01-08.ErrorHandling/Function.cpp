#include "Function.h"

int FunctionErrorCode(int* InPointer)
{
	if (InPointer == nullptr)
		return 0;

	*InPointer = 100;

	return 1;
}

int FunctionErrorCode2(int* InPointer)
{
	if (InPointer == nullptr)
		return 1;

	*InPointer = 100;

	return 0;
}

ErrorCode FunctionErrorCodeEnum(int* InPointer)
{
	if (InPointer == nullptr)
		return ErrorCode::NullptrError;

	*InPointer = 100;
	return ErrorCode::Success;
}

void FunctionException(int* InPointer)
{
	if (InPointer == nullptr)
	{
		throw "Inpointer is nullptr";
	}

	*InPointer = 100;
}
