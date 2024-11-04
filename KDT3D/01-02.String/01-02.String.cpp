// 01-02.String.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <iostream>
#include <format>
#include <string>
#include <Windows.h>
#include <codecvt>

const char GString[]{ "Hello" };
const char GString2[]{ "Hello" };

int main()
{
#pragma region C스타일 문자열
	{
		//stack												//data
		//[8byte]String {0xDataAreaAddress}		---->		//char[0]{'H'}
															//char[1]{'e'}
															//char[2]{'l'}
															//char[3]{'l'}
															//char[4]{'o'}
															//char[5]{'\0'}
		const char* String = "Hello";

		//stack												//data
		//[8byte]String {0xDataAreaAddress}		---->		//위와 동일한 주소
		const char* String2 = "Hello";

		//const가 붙어서 메모리 변환이 불가
		//String[0] = 'W';
	}
	{
		//Stack
		//[1byte]char[0] {'H'}
		//[1byte]char[0] {'e'}
		//[1byte]char[0] {'l'}
		//[1byte]char[0] {'l'}
		//[1byte]char[0] {'o'}
		//[1byte]char[0] {'\0'}
		char String[]{ "Hello" };
		//Stack
		//[1byte]char[0] {'H'}
		//[1byte]char[0] {'e'}
		//[1byte]char[0] {'l'}
		//[1byte]char[0] {'l'}
		//[1byte]char[0] {'o'}
		//[1byte]char[0] {'\0'}
		char String2[]{ "Hello" };

		//메모리 변환이 가능
		//String[0] = 'W';
		//그러나 문자열이 확보되는 순간 배열도 확보가 되어
		//오버플로우에 주의해야 한다.
		//Sting2[0] = 'B' <- 안됨

		//포인터를 하나 선언하고 만들어도 안됨
		char* Pointer = String;
		*(Pointer + 1) = 'A';	//가능
		//*(Pointer + 9) = 'B';	//불가능

		std::cout << GString << std::endl;
		std::cout << GString2 << std::endl;

		//장점
		// - 사용법과 구조가 간단하다
		// - 가볍다. 메모리를 꼭 필요한 만큼만 사용한다.
		// - 저수준(low level)이다. 메모리 조작이 쉽다.

		//단점
		// - 편의 기능(복사, 사이즈 확인)등 관련 기능을 찾거나 구현하려면 별도의 노력이 필요.
		// - 찾기 힘든 메모리 관련 버그가 발생하기 쉽다.
		// - C++의 객체지향적인 특성을 활용하지 못한다.


	}
#pragma endregion

#pragma region C++스타일 문자열
	{
		int a;
		std::string A = "Hello ";
		std::string B;// = "World!";
		B = "World!";

		std::string C = A + B;	//Hello World!

		A += B;			//Hello World!
		A.append(B);	//Hello World!World!
	}
	//문자열 비교
	{
		const char* StringA{ "Hello" };		//Data영역
		const char StringB[]{ "Hello" };	//Stack영역
		const char* StringC{ "Hello" };		//Data영역

		//주소를 비교하는 것으로, 문자열 비교를 의미하지 않음
		//아래는 Data영역 주소와  Stack영역 주소를 비교하고 있기 때문에
		//서로 다르다고 처리된다.
		if (StringA == StringB)
		{
			std::cout << "StringA == StringB\n";
		}
		else
		{
			std::cout << "else StringA == StringB\n";
		}
		
		bool bSame = true;
		for (int i = 0; i < 5; ++i)
		{
			if (StringA[i] != StringB[i])
			{
				bSame = false;
				break;
			}
		}

		if (bSame)
		{
			std::cout << "StringA == StringB\n";
		}

		const int Result = strcmp(StringA, StringB);
		if (Result == 0)
		{
			std::cout << "StringA == StringB\n";
		}


		if (StringA == StringB)
		{
			std::cout << "StringA == StringC\n";
		}
		else
		{
			std::cout << "else StringA == StringC\n";
		}

		std::string AA{ "Wow" };
		std::string BB{ "Wow" };

		if (AA == BB)
		{
			std::cout << "Same\n";
			bool bResult = AA._Equal(BB);
		}
	
	}

	{
		// - 

		std::wstring String{L"안녕, Hello!"};
		std::wstring String2{ TEXT("안녕, Hello!") };

		if (String == String2)
		{
			std::cout << "Same\n";
		}

		std::wstring Wstring;
		if (Wstring.empty())
		{
			Wstring = TEXT("Hello World!");
			
			const size_t FindIndex = Wstring.find(TEXT("d!"));
			const size_t FindIndex2 = Wstring.find(TEXT("!!!!"));

			if (FindIndex != std::wstring::npos)
			{
				std::cout << std::format("\nd! Index = {}\n", FindIndex);

				Wstring.replace(FindIndex, 2, TEXT("@#"));
			}

			if (FindIndex2 == std::wstring::npos)
			{
				//std::cout<<
			}

		}
	}

	// 문자열을 다른 자료형으로 변환
	{
		//문자열을 정수로 (string to int : stoi)
		{
			std::wstring StringNumber{ TEXT("20") };
			int Number = std::stoi(StringNumber);
			std::cout << Number << std::endl;
		}

		//정수를 문자열로
		{
			std::wstring WString = std::to_wstring(1000);
			std::string String = std::to_string(1000);
		}

		//UTF-8 ->WString(UTF-16)
		{
			std::string String = "Hello 한글\n";
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring WString = converter.from_bytes(String);

			//std::wstring WString = std::wstring(String.begin(), String.end());
		}

		//정수를 float로
		{
			std::wstring String = TEXT("3.14f");
			float Float = std::stof(String);

			std::wstring String2 = std::to_wstring(Float);
			String2 = std::format(TEXT("{}"), Float);
		}

		{
			class FString : public std::wstring
			{
				public:
					int ToInt() const
					{
						return std::stoi(*this);
					}
			};

			FString String{ TEXT("1024") };
			int Int = String.ToInt();

			wchar_t* Data = String.data();
			Data[0] = TEXT('3');
			
			Int = String.ToInt();
				
			Data[1] = TEXT('A');
			Int = String.ToInt();

		}
	}
#pragma endregion

#pragma region StartingView
	//C++17에 추가된 읽기 전용 String class
	{
		std::wstring String{ TEXT("Hello") };

		//복사가 발생
		std::wstring String2 = String;
		String2[0] = TEXT('A');	//String에 영향x

		//이렇게 해도 string이 복사되지 않음
		std::wstring& StringReference = String;
		std::wstring* const StringPointer = &String;
		StringReference[0] = TEXT('W');

		//복사가 발생하지 않음
		std::wstring_view WStringView = String;
		std::wstring_view WStringView2 = TEXT("Hello");
		//WStringView[0] = L"11";		//수정안됨
		WStringView2 = String;

		auto Function1 = [](std::wstring InString)
			{

			};
		auto Function2 = [](std::wstring_view InStringView)
			{
				std::wcout << InStringView << std::endl;
			};
		auto Function3 = [](const std::wstring& InString)
			{
				std::wcout << InString << std::endl;
			};

		Function1(TEXT("asdasd"));
		Function2(TEXT("asdasd"));

		//Data영역에 있던 asdasd가
		//const wstring&로 변환되기 위해서는
		//wstring 임시객체가 만들어 져야 한다.
		//그래서 불필요한 복사가 발생할 수 있다.
		//하지만 wstring_view를 사용하면 TEXT("asdasd")를 사용할때와, 그냥 wstring을 넘길때 둘다 복사없이 사용가능
		
		//복사 발생
		Function3(TEXT("asdasd"));

		std::wstring TestString = TEXT("asdasdf");
		//복사가 발생하지 않음
		Function3(TestString);

		//복사 발생
		Function2(TestString);
		
	}
#pragma endregion
}