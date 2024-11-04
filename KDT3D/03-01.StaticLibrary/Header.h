#pragma once
#include <iostream>

class FClass
{
public:
	FClass();
	~FClass();

	void Hello();

	void Hello2()
	{
		std::cout << "Hello\n";
	}

private:
	int Value;
};