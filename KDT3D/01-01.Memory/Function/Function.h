#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include<functional>


void AllocateWrong(int* InPointer);
void AllocateCorrect(int** InDoublePointer);
void DeAllocate(int* InPointer);
void DeAllocate2(int** InDoublePointer);

void InitArray(int* const InOutArray, size_t InSize);
void InitArray(std::vector<int>& InVector);
void InitArray(std::vector<int>* InOutVector);

void Sum(const std::vector<int>& InNumbers, int* const OutResult);
void Swap(int& InOutFirst, int& InOutSecond);

void CustomDeleterInt(int* InPointer);

struct FStruct
{
	FStruct() {};
	//FStruct() = default;
	FStruct(const int InValue);
	FStruct(std::function<void()> InFunction)
		:Function(InFunction)
	{

	}
	FStruct(const FStruct& InOther)
		:Value(InOther.Value)
	{
		std::cout << "Copy contructor\n";
	}
	FStruct(const std::unique_ptr<FStruct>& InOther) 
		: Value(InOther->Value)
	{

	}

	~FStruct();

	FStruct& operator=(const FStruct&) = default;

	void Hello() { std::cout << "hello\n"; }
	void SetValue(const int InValue);

private:
	int Value = 0;
	std::function<void()> Function;

};

void SharedParam(std::shared_ptr<FStruct> InPointer);
void WeakParam(std::weak_ptr<FStruct> InPointer);

bool ReturnTrue();
bool ReturnFalse();
int SumFunction(int a, int b);

void Test();
void Function(std::function<void()> InFunction);