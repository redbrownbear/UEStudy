// 01.C++Basic.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "crtdbg.h"
#include <Array>
#include <format>
#include <iostream>
#include <string>

#include <Windows.h>

#include "Function/Function.h"

int gInt = 0;

//std::unique_ptr<int> GUnique = std::make_unique<int>(100);
//int* GTest = new int(100);

bool FirstTrue()
{
    std::cout << "FirstTrue";
    return true;
}

bool FirstFalse()
{
    std::cout << "FirstFalse";
    return false;
}

void FunctionName(int a, int b);
void Function2();

int main()
{
    //std::cout << "Hello World!\n";

//#pragma region 01. 표준입출력
//    {
//        int a = 10;
//        auto b = 10;
//
//        std::cout << "원하는 숫자를 입력하시오 : ";
//        std::cin >> a;
//
//        std::cout << "하위" << std::endl;
//        std::cout << "입력된 숫자 : " << a << std::endl;
//    }
//    //int a = 100;
//    //std::cout << "새로운 a의 값: " << a << std::endl;
//
//#pragma endregion

//#pragma region 02. 리터럴(literal)
//    {
//        //리터럴은 코드에 표시한 숫자나 문자열과 같은 값을 의미
//        //10진수
//        int V{ 100 };
//        int W = 100;
//        //8진수
//        int V2{ 0144 }; //쓸일이 없다...
//        int W2 = 0144;
//        //16진수
//        int V3{ 0x64 };
//        int W3 = 0x64;
//        //2진수
//        int V4{ 0b01100100 };
//        int W4 = 0b01100100;
//
//        //부동소수점(floating point) : 3.14f
//        float F{ 3.14f };
//
//        //배정도 부동소수점(double): 3.14
//        double D{ 3.14 };
//
//        //단일 문자
//        char C{ 'a' };
//
//        //문자열
//        std::string S{ "aaa" };
//
//        const char* aa = "aaa";
//
//    }
//#pragma endregion

//#pragma region 03. 변수(Variable) *
//    {
//        // 1Byte == 8bit (0 ~ 255)
//        // 2진수로 나타내는 경우
//        // 0000 0000 ~ 1111 1111
//        // 2의 지수 함수 만큼 나타낸다
//
//        // 자료형: 타입크기는 Byte에 해당
//        // 정수형: char(1Byte), short(2Byte), int(4Byte), long long(8Byte), __int64(8Byte)
//        //         주로 char, int 
//        // 실수형: float(4Byte), double(8Byte)
//
//        {
//            int var{ 0 };   //초기화 연산자로 변수를 선언과 동시에 초기화한다.
//            var = 10;       //대입 연산자를 사용해서 값을 변경
//        }
//        {
//            //4Byte 정수형 signed 타입
//            //signed타입 : 음수를 표현할 수 있다.
//            signed int var{ -1 };
//            var = var + 1;
//
//            //unsigned를 붙히면 부호가 없는 타입
//            //초기화 연산자로 음수를 표기하면 컴파일러에러가 난다.
//            unsigned int var2{ 1 };
//        }
//        {
//            // 2Byte 정수형
//            //
//            short S1{ 32767 };
//            S1 = S1 + 1; //= -32768;
//
//            signed short S2{ 20 };
//        }
//
//        {
//            //4Byte 정수형
//            long L1{ 14L };
//        }
//        {
//            //8Byte 정수형
//            long long LL1{ 14LL };
//            unsigned int Var3{ 4292967295 };
//            unsigned int Var4{ (unsigned int)4292967296 };
//
//            long long LL2{ 4292967296 };
//            long long LL3{ (unsigned int)4292967296 };
//        }
//        {
//            //4Byte 실수형
//            //단정도(Single) 부동 소수점
//            //부동소수점은 컴퓨터에서 부동소수점을 표현하는
//            //특징으로 인해서 오차가 발생할 수 있다.
//            float F{ 3.14F };
//            int Int{ (int)3.14F };
//        }
//        {
//            //8Byte 실수형
//            double D{ 3.14 };
//        }
//        {
//            //1Byte 정수형
//            unsigned char C = 255;
//            char C2 = char(255);
//            unsigned char C3 = 'A';     //ASCII코드표
//
//            int Int = 'A';
//        }
//        //유니코드
//        {
//            //2Byte
//            wchar_t W{ L'A' };
//            wchar_t W2{ L'가' };
//            wchar_t W3{ L'早' };
//            //char C{ '가' };        //표기 불가
//        }
//        //부울 타입(boolean) 참과 거짓
//        {
//            //1Byte
//            bool B0 = true;     //1
//            bool B1 = false;    //0
//            bool B2 = 0;        //false
//            bool B3 = 1;        //true;
//            bool B4 = 22;       //true;
//
//        }
//        //부동 소수점 오차
//        {
//            double Value = 0;
//            if (Value == 0.0)
//            {
//                std::cout << "Value == 0\n";
//            }
//
//            Value = Value + 0.1;
//            Value = Value + 0.1;
//            Value = Value + 0.1;
//
//            if (Value == 0.3)
//            {
//                std::cout << "Value == 0.3\n";
//            }
//        }
//
//        //초기화(Initailization)
//        {
//            int IntNoInt;   //초기화를 하지 않은 변수
//            IntNoInt = 10;  //초기화가 아닌 값을 대입
//
//            int IntZeroInit = 0;        //선언과 동시에 값을 지정(초기화)
//            int IntZeroInit2{ 0 };      //0으로 초기화
//            int IntZeroInit3{  };       //자동으로 0으로 초기화
//        }
//
//        //형변환(Cast) : 서로 다른 타입으로 변환
//        {
//            float Float{ 3.14f };
//            int Int = Float;           //묵시적 Casting "경고 나옴"
//            int Int2 = (int)Float;     //명시적 Casting C스타일 cast
//            int Int3 = int(Float);     //명시적 Casting C스타일 cast
//            int Int4 = static_cast<int>(Float);     //C++ 버전의 명시적 Cast
//            
//
//            //2Byte 정수
//            short Short{ 10 };
//            //4Byte 정수
//            int Int5 = Short;           //묵시적 Casting
//
//            // 4Byte의 정수를 2Byte의 크기의 정수로 형변환 할때 -> 순환 되고 최종숫자를 표기해준다.
//
//        }
//
//    }
//#pragma endregion

//#pragma region 04. 지역변수, 전역변수와 메모리
//    {
//        //지역변수는 지금까지 사용한 바와 같이 스코프의 시작과 끝 내부에서 선언되는 변수를 의미
//
//        //전역변수는 함수 밖에서 선언된 변수를 의미합니다.
//        //선언된 전역변수는 선언 이후에서는 스코프 내부에서 접근 가능
//
//        //유저 영역의 메모리 공간은 크게 4구획을 나누어져 있다.
//        //[코드 영역]   : 소스코드가 기계어로 변환되어 실제 로직을 수행하는 코드 정보
//        //[데이터 영역] : 전역 변수, static 변수 등 
//        //[Heap]        : 동적 할당
//        //[stack]       : 지역 변수
//
//    }
//#pragma endregion

//#pragma region 05. 연산자들
//    {
//        // 단한(unary : 유너리) 연산자      : 표현식 하나를 계산
//        // 아항(binary :바이너리) 연산자    : 표현식 두개를 계산
//        // 삼항(temary : 템머리) 연산자     : 표현식 세개를 계산
//
//        //대입 연산자[이항] : 오른쪽 값을 왼쪽의 표현식에 대임
//        {
//            int i;
//            i = 0;
//        }
//
//        //[단항] 표현식의 참/ 거짓 (참: 보통1, 0이아닌값 / 거짓 : 보통0
//        {
//            bool b1{ true };    //참
//            bool b2{ 1 };       //참
//            bool b3{ false };   //거짓
//            bool b4{ 0 };       //거짓
//
//            bool b5{ !true };   //거짓
//            bool b6{ !false };  //참
//
//            bool b7{ true };    //참
//            bool b8{ !b7 };     //거짓
//        
//        }
//
//        //[이항] 사칙연산
//        {
//            int a{ 1 + 2 };
//            int b{ a + 3 };
//
//            int c{ 1 - 2 };
//            unsigned int c2{(unsigned int)1 - 2 };
//
//            int d{ c * 3 };
//
//            int e{ 10 / 3 };
//
//            float f{ 10 / 3 };
//            float f2{ 10.f / 3.f };
//        }
//
//        //[이항] mod, 나머지 연산자
//        {
//            int m{ 10 % 3 }; //1
//            int m2{ 5 % 2 }; //1
//            int m3{ 6 % 3 }; //0
//        }
//
//        //[단항] 후행 / 선행 연산자
//        {
//            //후행증가, 감소
//            {
//                int i{ 0 };
//                i++;
//
//                int k = i++; //k = 0, i = 1
//
//                //식 내부에 후행연산자를 쓰지 않는게 좋다....
//            }
//
//            //선행증가, 감소
//            {
//                int i{ 0 };
//                ++i;
//
//                int k = ++i; //k = 1, k = 1
//            }
//        }
//
//        //사칙연산 축약표현
//        {
//            int i{ 1 };
//            int k{ 2 };
//
//            i += k;
//        }
//
//        //비트 단위 연산
//        {
//            //AND 연산
//            {
//                //하나라도 0 이면 결과가 0
//
//                //0010 = 2
//                //1111 = 15
//                //----AND----
//                //0010 = 2
//
//                char c1 = 0b0010;
//                char c2 = 0b1111;
//                char c3 = c1 & c2;
//            }
//
//            //OR 연산
//            {
//                //하나라도 1이면 결과가 1
//                
//                //0010
//                //1111
//                //----OR----
//                //1111
//
//                char c1 = 0b0010;
//                char c2 = 0b1111;
//                char c3 = c1 | c2;
//            }
//
//            //XOR 연산 (exclusive or)
//            {
//                //토글 기능을 만들때
//                //서로 다르면 결과가 1
//                
//                //0010
//                //1111
//                //----OR----
//                //1101
//
//                char c1 = 0b0010;
//                char c2 = 0b1111;
//                char c3 = c1 ^ c2;
//            }
//        }
//
//        //비트 이동(shift) 연산
//        {
//            // 왼쪽으로 비트 이동
//            {
//                // 0000 0001
//                // 왼쪽으로 한칸 이동
//                // 0000 0010
//
//                unsigned char c0 = 5;       // 0000 0101
//                unsigned char c1 = c0 << 1; // 0000 1010
//                unsigned char c2 = c0 << 2; // 0001 0100
//                //신기하게도 2배씩 증가함
//
//                unsigned char c3 = c0 << 3; // 0010 1000
//                unsigned char c4 = c0 << 4; // 0101 0000
//
//                unsigned char c5 = c0 << 5; // 1010 0000
//                unsigned char c6 = c0 << 6; // 0100 0000
//                unsigned char c7 = c0 << 7; // 1000 0000
//                unsigned char c8 = c0 << 8; // 0000 0000
//                unsigned char c9 = c0 << 9; // 0000 0000
//            }
//
//            //오른쪽으로 비트 이동
//            {
//
//                unsigned char c0 = 80;      // 0101 0000
//                unsigned char c1 = c0 >> 1; // 0010 1000
//                // 2배씩 감소
//
//                unsigned char c2 = c0 >> 5; // 0000 0010
//                unsigned char c3 = c0 >> 6; // 0000 0001
//                unsigned char c4 = c0 >> 7; // 0000 0000
//                unsigned char c5 = c0 >> 8; // 0000 0000
//            }
//
//            //음수의 경우 비트 이동이 조금 다르게 동작
//            {
//                // MSB(MostSignificant Bit) '1'111 1111
//                char c0 = -1;               // 1111 1111 : -1
//
//                char c1 = c0 >> 1;          // 1111 1111 : -1
//
//                char c2 = c0 << 1;          // 1111 1110 : -2
//                char c3 = c0 << 2;          // 1111 1100 : -4
//                char c4 = c0 << 3;          // 1111 1000 : -8
//
//                char c5 = c0 << 3;          // 1111 1000 : -8
//                char c6 = c0 << 6;          // 1100 0000 : -64
//                char c7 = c0 << 7;          // 1000 0000 : -128
//                char c8 = c0 << 8;          // 1000 0000 : 0
//            }
//
//        }
//        //삼항 연산자(temary operatior) / 조건 연산자
//        {
//            int i = 0;
//
//            //(조건문) ? 참일때 : 거짓일때
//            int k1 = (i == 0) ? 10 : -10;
//            int k2 = (i != 0) ? 10 : -10;
//        }
//
//        //연산자 우선순위
//        {
//            int i1 = 10 - 5 * 5; // 10 -25;
//            int i2 = (10 - 5) * 5; // 5 * 5;
//        }
//    }
//#pragma endregion 

//#pragma region 06. 열거형 (enum; enumerated type; 이넘)
//    {
//
//        {         
//            const int Iron = 0;
//            const int Bronze = 1;
//            const int Silver = 2;
//            const int Gold = 3;
//
//            int MyTier = Gold;
//            if (MyTier == Gold)
//            {
//                std::cout << "골드 티어 입니다. \n";
//            }
//        }
//
//        {
//            enum /*class */Tier : unsigned char
//            {
//                Iron = 0,
//                Bronze,
//                Silver,
//                Gold,
//            };
//
//            unsigned char MyTier = Tier::Gold;
//            Tier eTier = Tier::Bronze;
//
//            if (eTier == Tier::Bronze)
//            {
//                std::cout << "브론즈 티어 입니다. \n";
//            }
//
//            if (MyTier == Tier::Gold)
//            {
//                std::cout << "골드 티어 입니다. \n";
//            }
//
//            //enum을 명시적으로 맞춰주고 싶으면 enum class를 이용하면 다른 타입을 걸러준다(아무리 내부적으로 같아도)
//        }
//
//    }
//#pragma endregion

//#pragma region 07. 구조체(struct)***
//{
//	enum class eTier : unsigned char
//	{
//		None,
//		Iron,
//		Bronze,
//		Silver,
//		Gold
//	};
//
//	struct FPlayer
//	{
//		int Hp = 10;
//		int Mp = 20;
//		double test = 10.0;
//
//		eTier Tier = eTier::Silver;
//	};
//
//	//FPlayer : 구조체 타입(구조체 : 데이터를 묶기)
//	//Player : 인스턴스(instnace; 실체화된 사례) (메모리에 만들어진것)
//	FPlayer Player{.Hp = 100};	//초기화
//
//	Player.Hp = 1000; //맴버변수에 접근해 변수 변환
//
//	std::cout << "[Player Info] \n";
//	std::cout << std::format("Hp :{}\nMp : {}\n", Player.Hp, Player.Mp);
//
//	switch (Player.Tier)
//	{
//	case eTier::None:
//		break;
//	case eTier::Iron:
//		std::cout << "Iron";
//		break;
//	case eTier::Bronze:
//		std::cout << "Bronze";
//		break;
//	case eTier::Silver:
//		std::cout << "Silver";
//		break;
//	case eTier::Gold:
//		std::cout << "Gold";
//		break;
//	default:
//		break;
//	}
//
//	if (Player.Tier == eTier::Iron)
//	{
//		std::cout << "Iron";
//	}
//
//
//
//	//std::cout << "[Player Info] \n";
//	//std::cout << "Hp : " << Player.Hp << "\n" << "Mp : " << Player.Mp << "\n" << "Tier : " << (int)Player.Tier << "\n";
//
//
//#pragma pack(push, 1)
//	struct FPadding
//	{
//		char C;
//		//3Byte padding이 숨겨져 있다.
//		//지금 가장 큰 기본 자료형 크기가 4Byte라서 4Byte padding이 잡힌다.
//
//		int I;	
//
//		char C1;
//		//3Byte padding이 숨겨져 있다.
//		//이런 상황을 피하려면 padding을 고려해서 C1변수를 C아래쪽으로 옮겨야
//		//낭비되는 byte를 줄일 수 있다.
//	};
//
//	//struct Fpadding1
//	//{
//	//	char C1;
//	//	int i;
//	//};
//
//#pragma pack(pop)
//
//	//struct Fpadding2
//	//{
//	//	char C1;
//	//	int i;
//	//};
//
//	//64bit(8Byte)환경에서 한번에 접근해서 연산할 수 있는 최대 단위가 8Byte
//	//padding을 비활성화 해서 다음과 같은 경우
//	//char / double (9Byte)
//	// [00] / [00 00 00 00 00 00 00 00]
//	// [00] / [00 00 00 00 00 00 00] 이후 한번 더 접근[00] <- 총 3번 접근
//
//	//그러나 padding을 넣게 되면
//	//[00] 00 00 00 00 00 00 00 / [00 00 00 00 00 00 00 00] <- 총 2번 접근
//	// 속도가 빨라진다.
//
//	//위와 같은 pragma pack(push, 1)을 사용하는 이유는 네트워크에서의 용량을 줄이기 위해서 사용(성능보다 효율을 우선)
//
//}
//#pragma endregion

//#pragma region 08. 조건문(if / switch)***
//    {
//        //if
//        //{
//        //    int V = 0;
//        //    if (V == 0)
//        //    {
//        //        std::cout << "V == 0\n";
//        //    }
//
//        //    int V2 = 0;
//        //    std::cin >> V2;
//
//        //    if (V2 == 100)
//        //    {
//        //        std::cout << "V == 100\n";
//        //    }
//        //    else if (V2 == 50)
//        //    {
//        //        std::cout << "V == 50\n";
//        //    }
//        //    else
//        //    {
//        //        std::cout << std::format("V2 : {}\n", V2);
//        //    }
//        //}
//
//        //switch
//        //{
//        //    int V2 = 0;
//        //    std::cin >> V2;
//
//        //    switch (V2)
//        //    {
//        //    case 100:
//        //        std::cout << "V2 == 100\n";
//        //        break;
//        //    case 50:
//        //        std::cout << "V2 == 50\n";
//        //        break;
//        //    default:
//        //        std::cout << "default\n";
//        //        break;
//        //    }
//        //}
//
//    }
//#pragma endregion

//#pragma region 09. 논리연산자**
//    {
//        int a = 10;
//        int b = 20;
//        //논리곱(AND)
//
//        int c = 30;
//
//        //int a = 10;
//        //int b = 20;
//        //논리합(OR)
//        //1. a== 10 ? true
//        //if(true) -> true
//        if (a == 10 || b == 10)
//        {
//            std::cout << "a == 10 || b == 10\n";
//        }
//        //1. b== 10 ? false
//        //2. a== 10 ? true
//        //if(false || true) -> true
//        if (b == 10 || a == 10)
//        {
//            std::cout << "b == 10 || a == 10\n";
//        }
//        //1. b== 50 ? false
//        //2. a== 60 ? false
//        //if(false || false) -> flase
//        if (b == 50 || a == 60)
//        {
//            std::cout << "b == 50 || b == 60\n";
//        }
//
//        //1. a == 10 ? true
//        //2. (b == 50 || c == 30) ? true
//        //b == 50 ? false
//        //c == 30 ? true
//        //3. c == 30 ? true
//        //if(true && (false || true)) -> flase
//        if (a == 10 && (b == 50 || c == 30))
//        {
//            std::cout << "a == 20 &&(b == 50 || c == 30)\n";
//        }
//        else
//        {
//            std::cout << "false\n";
//        }
//
//        if (FirstTrue())
//            std::cout << "FirstTrue\n";
//
//        else
//            std::cout << "FirstFalse\n";
//
//        if (FirstFalse())
//            std::cout << "FirstFalse\n";
//
//        else
//            std::cout << "FirstTrue\n";
//
//        //1. FirstFalse -> false
//        //2. FirstTrue -> true;
//
//        if (FirstTrue() || FirstFalse())
//        {
//            std::cout << "FirstTrue\n";
//        }
//    }
//
//#pragma endregion

//#pragma region 10. 함수(function)***
//    {
//        //규모가 큰 프로그램에서 모든 코드를 main함수 안에 담게 되면
//        //관리적인 측면에서 힘들다.
//        //코드 가독성(읽기 쉬운 정도)을 높히려면 코드를 간결하고 명확한
//        //함수 단위로 나누는 것이 좋겠다.
//
//        //C++에서 함수를 사용하려면 먼저 함수 선언을 해야한다.
//        //반환타입 함수이름 (입력 파라미터(옵션; 있어도 되고 없어도 됨))
//        // void FunctionName(int a, int b)
//
//        //함수도 시작 주소가 있다.
//        //함수를 호출한다는건
//        //>>돌아올 다음주소를 Backup 해두고
//        //>>호출할 함수의 주소로 이동
//        //>>함수 수행
//        //>>ret을 만나면 Backup해둔 주소로 이동
//
//        //FunctionName(10, 20);
//
//        //이 함수를 호출하는 위치 기준으로 이 라인보다 위에 함수가
//        ///있다는 것을 알려주지 않으면 함수를 찾을 수 없습니다.
//        //Function2();
//
//        //콜링 컨벤션(Calling Conventions)
//        //함수를 호출하는 방식
//        // __cdecl, __stdcall, __thiscall, __fastcall
//
//        int Result = AddFunction(10, 20);
//
//        //파라미터를 던지는 경우 특정 레지스터(메모리)에 값을 backup 했다가
//        //함수 내부로 진입해서 그 레지스터(메모리)에서 다른 메모리로 값을 복사하고
//        //추가적으로 함수로 이동하는 과정(비옹) 추가적으로 발생
//        //함수 호출의 오버해드라고 표현한다.
//
//        int a = 10, b = 20;
//        int Result2 = AddFunction(a, b);
//        double Result3 = Addfunction(10.34, 3.14);
//
//        //재귀 함수 호출이 많이 발생하는 경우
//        //Debug 설정일 때 함수 호출 오버헤드로 인해서
//        //한번의 함수 호출로 구현해둔 함수에 대해 느릴 수 있다.
//
//        std::cout << Factorial(3);
//
//    }
//#pragma endregion

//#pragma region 11. Bit flag
//    {
//        unsigned char Property1 = EPropertyFlags::EProperty1;
//        unsigned char Property3 = EPropertyFlags::EProperty3;
//
//        // 0000 0001
//        // 0000 0100
//        // ------------OR
//        // 0000 0101
//        unsigned char Property13 = EPropertyFlags::EProperty1 | EPropertyFlags::EProperty3;
//
//        HasFlags(Property13);
//
//        unsigned char Property135 = Property13;
//        Property135 |= EPropertyFlags::EProperty5;
//        HasFlags(Property135);
//
//        unsigned char Property35 = Property135;
//
//        //EPropertyFlags::EProperty1    : 0000 0001
//        //~EPropertyFlags::EProperty1   : 1111 1110
//        //0001 0101
//        //1111 1110
//        //----------AND
//        //0001 0100
//
//        Property35 &= ~EPropertyFlags::EProperty1;
//        HasFlags(Property35);
//
//
//        //0000 0010
//        //0000 1000
//        //----------OR
//        //0000 1010
//        unsigned char Toggle = EProperty2 | EProperty4;
//        HasFlags(Toggle);
//
//        //0000 1010 (2, 4)
//        //0000 1000 (4)
//        //----------XOR
//        //0000 0010 (2)
//        Toggle ^= EProperty4;
//        HasFlags(Toggle);
//        //0000 0010 (2)
//        //0000 1000 (4)
//        //----------XOR
//        //0000 1010 (2, 4)
//        Toggle ^= EProperty4;
//        HasFlags(Toggle);
//
//        unsigned char Flags = EPropertyFlags::ENone;
//        Flags = EProperty1;
//
//        HasFlags(Flags);
//
//        Flags |= EProperty2;
//        HasFlags(Flags);
//
//        Flags &= EProperty2;
//        HasFlags(Flags);
//
//    }
//#pragma endregion

//#pragma region 12. 배열(array)
//    {
//        int a{}, b{}, c{};
//        a = 1;
//        b = 2;
//        c = 3;
//
//        //1차원 배열
//        {
//            int Array[4]{ 5, 6, 7, 8 };
//
//            Array[0] = 1;
//            Array[1] = 2;
//            Array[2] = 3;
//            Array[3] = 4;
//
//            int Size1 = sizeof(int);
//            int Size2 = sizeof(Size1);
//            int ArraySize = sizeof(Array);
//            int ArrayElemSize = sizeof(Array[0]);
//            int ArrayCount = sizeof(ArraySize / ArrayElemSize);
//        }
//
//        //2차원 배열
//        {
//            int Array[2][3]{};
//
//            Array[0][0] = 0;
//            Array[0][1] = 1;
//            Array[0][2] = 2;
//            Array[1][0] = 3;
//            Array[1][1] = 4;
//            Array[1][2] = 5;
//        }
//        //표준 컨테이너
//        {
//            std::array<int, 5> Array{4,5,6,7,8};
//
//            Array[0] = 0;
//            Array[1] = 1;
//            Array[2] = 2;
//            Array[3] = 3;
//            Array[4] = 4;
//
//            size_t Size = Array.size();
//
//            //typedef unsigned __int64 size_t;
//            //typedef는 왼쪽에 있는 타입을 오른쪽에 있는 이름으로 바꿔 사용할 수 있다는것
//        }
//
//
//    }
//#pragma endregion

//#pragma region 13.반복문(loop)**
//    {
//        //while
//        {
//            int i = 0;
//            while (i < 5)
//            {
//                std::cout<<std::format("i: {}\n", i);
//                ++i;
//
//                if (i == 3)
//                {
//                    std::cout << "i가 3일때 탈출\n";
//                    break;
//                }
//            }
//        }
//
//        //do While
//        {
//            //while과는 다르게 조건을 만족하지 못했을 때도
//            //처음 한번은 실행해준다.
//            int i{ 30 };
//            do
//            {
//                std::cout << "Test\n";
//            } while (i < 5);
//        }
//
//        //for
//        {
//            int count = 5;
//            for (int i = 0; i < count; ++i)
//            {
//                std::cout << std::format("i: {}\n", i);
//            }
//
//            const int Size = 5;
//            int Array[Size]{};
//
//            for (int i = 0; i < Size; ++i)
//            {
//                Array[i] = i;
//
//            }
//
//            //범위기반 for(range based for)
//            for (int i : Array)
//            {
//                std::cout << std::format("i :{}\n", i);
//            }
//
//            std::array<int, Size> stdArray{};
//            size_t ArraySize = stdArray.size();
//
//            for (size_t i = 0; i < ArraySize; ++i)
//            {
//                stdArray[i] = i;
//            }
//
//            for (int i : stdArray)
//            {
//                std::cout << std::format("i :{}\n", i);
//            }
//
//            //CTAD(class template argument deduction : 클래스 템플릿 인수 추론)
//            //C++20
//            for (std::array Array2{ 1,2,3 }; int i : Array2)
//            {
//                std::cout << std::format("i :{}\n", i);
//            }
//        }
//
//    }
//#pragma endregion

//#pragma region 14.포인터와 동적할당(pointer*****, dynamic allocation) + 레퍼런스*****(Referenc:참조)
//{
//    //메모리 할당과 이를 관리하는 것은 C++프로그램에서 문제가 발생하기 쉬운 영역
//    //품질이 뛰어난 C++프로그램을 작성하기 위해서는 메모리 내부 작동 방식을 이해하고 있어야함
//    //이번 시간에는 동적 메모리를 다루는 과정에서 어떤 위험에 빠지기 쉬운지 알아보고 이런 상화을
//    //해결하거나 애초에 방지하는 방법을 알아보겠습니다.
//
//    //low-level(저수준; 낮은수준) 메모리 연산 방법은 new, new[], delete, delete[]
//    //또는 C스타일의 malloc(memory allocation, free라는 함수를 사용하는 방법이 있다.
//    //요즘은 로우레벨 메모리 연산을 최대한 피하는 추세라고 생각됨.
//
//    //표준 라이브러리에서 제공하는 vector 컨테이너(동적배열)이 있는데
//    //이를 사용하면 필요할 때 메모리를 늘리거나 줄일 수 있음
//    //또는 동적으로 할당한 메모리를 사용하지 않으면 자동으로 해제해주는 shared_ptr 등의
//    //스마트 포인터를 사용하기도 한다.
//
//    //동적 메모리를 이용하면 컴파일 시간에 크기를 확정할 수 없는 데이터를 다룰수 있습니다.
//    {
//        //지역변수는 시작과 끝 스코프({}) 내부에서 선언되는 변수를 의미
//
//        //실행시간(런타임; Run time)에 동적으로 메모리 공간이 필요한 경우 OS(운영체제; Operating System)
//        //에 메모리를 요청해야 하는데, 이런 과정에서 커널에 요청할 필요가 있다.
//        //커널은 OS중 항상 메모리에 올라가 있는 운영체제의 핵심 부분으로, 하드웨어와 응용 프로그램
//        //사이에서 인터페이스 역할을 제공한다.
//        //커널에 요청하는 경우 이를 system call이라고 합니다. (메모리 할당을 할때마다 system call이 발생
//        //하지는 않을 수 있습니다.
//        //이 system call은 유저영역과 커널 영역을 넘나드는 호출로서 상당한 비용을 지불하게 됩니다.
//    }
//    {
//        //64비트 환경에서는 포인터의 크기가 8Byte(64bit)
//        //32비트 환경에서는 포인터의 크기가 4Byte(32bit)
//        //[Stack]                                     //[Heap]
//        //[0xfff]Pointer(8Byte, 64bit)
//
//        //Pointer 변수는 주소를 들고 있을 것이다.
//        //그리고 그 주소로 접근하면 int 변수가 있을 것이다.
//
//        int* Pointer{nullptr};  //실제 값은 0, 프로그래머를 위해서 0을
//        //쓰는 것 보다 nullptr을 넣어주면 더 명확하게 의미를 전달 할 수 있다.
//        
//        //포인터의 크기는 플랫폼 bit수에(Ex.64, 32) 대응해서 변경된다.
//        //32bit라면 최대 표현 가능한 주소가 FFFF FFFF(10진수로 4,294,967,295)
//        //unsigned int 범위에 해당한다. 즉 4Byte만 있으면 모든 32bit 주소를 표현 할 수 있다.
//        //64bit라면 FFFF FFFF FFFF FFFF 까지 총 8Byte로 모든 주소를 표현할 수 있다.
//
//        //int*의 의미는 지금 내가 가지고 있는 주소(*)로 가면 그값은 int 라는 의미
//        size_t Size = sizeof(int*);
//        //char*의 의미는 지금 내가 가지고 있는 주소(*)로 가면 그 값은 char 라는 의미
//        size_t Size2 = sizeof(char*);
//    }
//
//    {
//        //[Stack]                                               //[Heap]
//        // [0xfff..] a(4Byte) =100
//        // [0xfff..] 4Btye padding
//        // [0xfff..] Pointer(8Byte) = nullptr
//        // [0xfff..] b(4Byte) = 20
//        int a = 100;
//        int* Pointer{ nullptr };
//        int b = 20;
//
//        //[Stack]                                               //[Heap]
//        // [0xfff..] a(4Byte) =100
//        // [0xfff..] 4Btye padding
//        // [0xfff..]Pointer(8Byte) = 0x100         <-------     [0x100] int[4Byte] = 10
//        // [0xfff..] b(4Byte) = 20
//        Pointer = new int{ 10 };
//
//        // [Stack]                                              // [Heap]
//        // [0xfff...] Pointer(8Byte) = 0x100       <-------     [0x100] int[4Byte] = 10 -> 999
//        // 이곳에 붙은 포인터 기호는 역참조 연산이라고 이야기 한다
//        *Pointer = 999;
//
//        //[Stack]                                               //[Heap]
//        // [0xfff..]Pointer(8Byte) = 0x100         <-------     [0x100] int[4Byte] = 999
//        // [0xfff..]Read(4Byte) = 999
//        int Read = *Pointer;
//
//        //할당한 Memory를 해제
//        delete Pointer;
//      
//        //[Stack]                                               //[Heap]
//        // [0xfffffff0] a(4Byte) =100
//        // 
//        // ...
//        // [0xfff...]Pointer2(8Byte) = 0xfffffff0;
//        int* Pointer2 = &a;
//        std::cout << std::format("Pointer2 : {:x}, &a : {:x}, *Pointer2 : {}\n",(size_t)Pointer2, (size_t) &a, *Pointer2);
//        *Pointer2 = 1234;
//
//        std::cout << std::format("*Pointer2 : {}, a : {}\n", *Pointer2, a);
//        // int* Pointer3 = (int*)0xFFFFFFFFFFFFFFFF;
//    }
//
//    {
//            //[Stack]                                               //[Heap]
//            // [0xfffffff0] a(4Byte) =100
//            int* Pointer{ nullptr };
//
//            // [Stack]                                              // [Heap]
//            // [0xfff...] Pointer(8Byte) = 0x100       <-------     [0x100] int[4Byte] = 10;
//            Pointer = new int{ 10 };
//
//            //할당한 메모리를 해제하지 않고 넘어가는 경우 이를
//            //메모리 누수(메모리 릭, Memory leak)이라고 부릅니다.
//
//            //동적 할당한 메모리를 다른 주소로 덮어 쓰는 경우에도
//            //원본 주소를 해제할 수 없다.
//            //Pointer = (int*)10000;
//
//            //int* TempPointer = Pointer;
//            //*TempPointer = 100;
//            delete Pointer;
//
//            //댕글링 포인터 : 이미 Delete된 메모리 주소를 들고 있는 상황
//            //이때 해당 memory에 write하는 경우 프로그램이 죽을 수도 있다.
//            //잠재적인 위험이 아주 높다
//            //가끔 작동하다 죽는 버그 원인인 경우들이 종종 발견된다.
//            //*TempPointer = 100;
//        }
//
//    {
//            //C언어를 배웠다면 malloc을 사용해서 메모리를 할당했을 텐데,
//            //C++에서도 사용 할 수 있다.
//            //malloc과 new는 큰 차이가 있다.
//            //new와 delete는 초기화 및 struct 또는 class에서
//            //생성자와 소멸자를 호출해주는 역할을 수행한다.
//            //그러나, malloc은 순수하게 memory 할당만 해줍니다.
//            //int*를 new로 동적할당 할때는 초기화를 할 수 있었다.
//            //하지만, malloc은 초기화 불가
//            int* Pointer = (int*)malloc(sizeof(int));
//            *Pointer = 1000;
//            free(Pointer);
//        }
//
//    {
//            // [Stack]                                              // [Heap]
//            // [0xfff...] Pointer(8Byte) = 0x100       <-------     [0x100][int][int][int][int][int][int]
//
//            int* ArrayPointer = new int[6] {0, 1, 2, 3, 4, 5};
//            ArrayPointer[0] = 1000;
//            ArrayPointer[1] = 1200;
//
//            //0x100 + 0 * sizeof(int) = 0x100
//            *ArrayPointer = 9999;
//            //0x100 + 1 * sizeof(int) = 0x104
//            *(ArrayPointer + 1) = 8888;
//
//            for (int i = 0; i < 6; ++i)
//            {
//                ArrayPointer[i] = i + 10;
//
//                //Array(int*) + 0   Array + 1 ...
//                //[00 00 00 01]     [00 00 00 02]  ....
//                *(ArrayPointer + i) = i;
//            }
//
//            *((char*)ArrayPointer + 1) = 255;
//            *((char*)ArrayPointer + 2) = 255;
//            *((char*)ArrayPointer + 3) = 255;
//            *((short*)ArrayPointer + 1) = 9999;
//            *((__int64*)ArrayPointer + 0) = 9999;
//            *((__int64*)ArrayPointer + 1) = 9999;
//
//            delete[] ArrayPointer;
//
//            //2차원 이상도 배열도 동적 할당으로 구현 가능하나,
//        }
//
//    {
//            struct FStruct
//            {
//                //생성자 : 인스턴스가 만들어 질떄 호출되는 함수
//                //__thiscall: 호출하는 쪽에서 파라미터로 자기자신의 주소를 전달
//                FStruct(/*FStruct This*/)
//                {
//                    //this + 0Byte = Value
//                    //this + 4Byte = Value2
//                    this;
//
//                    int a = this->Value;
//
//                    std::cout << std::format("V:{}, V2:{}\n", this->Value, Value2);
//                }
//                FStruct(const int InValue) 
//                    //초기화 순서는 변수를 선언한 순서대로 동작한다.
//                    :Value2(Value), Value(InValue)
//                {
//                    std::cout << std::format("V:{}, V2:{}\n", Value, Value2);
//                }
//
//                //소멸자 : 인스턴스가 소멸되는 시점에 호출되는 함수
//                //컴파일러가 소멸예측 지점 (Stack:스코프를 벗어나는 지점, Heap: delete를 하는 시점
//                //에 코드에 소멸자를 호출하도록 심어둔다.
//                ~FStruct() 
//                {
//
//                }
//            
//                int Value = 10;
//                int Value2 = 20;
//            };
//
//            FStruct Struct;
//
//            Struct.Value;
//            FStruct Struct1 = FStruct(100);
//
//            FStruct* StructPointer = new FStruct(12);
//            StructPointer->Value = 999;
//
//            int* Test = (int*)StructPointer;
//            *Test = 888;
//
//            delete StructPointer;
//
//            {
//                //malloc은 요청한 size만큼 메모리 블록만 할당
//                //new은 요청한 size만큼 메모리 블록을 할당 후 초기화(struct와 같은 경우 생성자 호출)
//                FStruct* MallocStruct = (FStruct*)malloc(sizeof(FStruct));
//
//                //free는 해당 메모리 블록을 할당 해제
//                //delete와 다르게 소멸자는 호출하지 않는다.
//                free(MallocStruct);
//            }
//
//            //저수준의 동적할당은 사용빈도가 줄었다고 했지만,
//            //포인터는 사용하지 않는날이 없는 수준
//
//            {
//                int Value = 0;
//                //Function call, 인자 복사
//                //int InValue = Value;
//                //Value = InValue;
//                Value = CallByValue(Value);
//
//                FParam Param = FParam();
//                Param.Value[2] = 1234;
//                FParam InParam = FParam(Param);
//
//                Param = CallByValue(Param);
//            }
//            {
//                int a = 0;
//                int* Pointer = &a;
//                a = 999;
//                //*Pointer = 1234;
//
//                //int* InPointer = Pointer;
//                //*InPointer = 1234;
//                //*Pointer = 1234;
//
//                CallByPointer(&a);
//                CallByPointer(Pointer);
//
//                FParam Param = FParam();
//                FParam* ParamPointer = &Param;
//
//                FParam* InPointer = &Param;
//                InPointer->Value[0] = 9999;
//                InPointer->Value[5] = 5555;
//                (*InPointer).Value[0] = 1234;
//
//                CallByPointer(&Param);
//                CallByPointer(ParamPointer);
//
//            }
//            {
//                FParam Param; TestConstructor(&Param);
//
//                int a = 200;
//                int b = 400;
//
//                TestConstructor(&a);
//            }
//            {
//                //레퍼런스, 참조
//
//                //포인터와 레퍼런스의 차이
//
//                int a = 5;
//                int* Pointer = &a;  //대상을 a로 변경
//                *Pointer = 100;     //a의 값이 변경됨
//
//                //Pointer는 가리키던 대상을 바꿀 수 있다.
//                int b = 999;
//                Pointer = &b;       //대상을 b로 변경
//                *Pointer = 1234;    //b의 값이 변경됨
//
//                int* const PointerLikeReference = &a;
//                //PointerLikeReference = &b // 포인터 오른쪽에 const가 붙으면 가리키던 대상을 바꿀 수 없다(주소) 
//                *PointerLikeReference = 10000;
//
//                const int* ConstPointer = &a;
//                //*ConstPointer = 9999;     // 포인터 왼쪽에 const가 붙으면 가리키던 대상의 값을 바꿀 수 없다.
//                ConstPointer = &b;
//
//                const int* const PointerCnatChange = &a;    //둘다 변경불가
//                //PointerCnatChange = &b;
//                //*PointerCnatChange = 1000;
//
//                int& Reference = a; //처음 초기화 시점에 반드시 대상이 와야하며, 이후 변경할 수 없다.
//                Reference = b;      //대상이 바뀌는게 아니라 값이 바뀌는것
//
//                int TestValue = 0;
//                CallByReference(TestValue);
//                CallByPointer(&TestValue);
//
//                FParam Param;
//                CallByReference(Param);
//
//            }
//
//        }
//
//    {
//        int* Pointer = nullptr;
//        FunctionWIthPointer(Pointer);
//
//        int a = 10;
//        FunctionWIthPointer(&a);
//
//        if (Pointer == nullptr)
//        {
//            Pointer = new int{ 5 };
//            FunctionWIthPointer(Pointer);
//
//            int* PointerB = Pointer;
//            SAFEDELETE(Pointer);
//            FunctionWIthPointer(Pointer);
//            //delete Pointer;
//            //Pointer = nullptr;  //delete이후에 nullptr을 적용해 다시 들어왔을때 예외처리를 적용해주기 위해
//
//            //PointerB는 댕글링 포인터
//            //FunctionWIthPointer(PointerB);
//        }
//
//    }
//    {
//        int* PointerB = new int{ 5 };
//        int& ReferenceB = *PointerB;
//        ReferenceB = 999;
//        *PointerB = 1234;
//        SAFEDELETE(PointerB);
//        FunctionWIthReference(ReferenceB);
//    }
//
//    {
//        int a = 20, b = 10;
//        Swap(a, b);
//
//        int* c = new int{ 40 };
//        int* d = new int{ 30 };
//        Swap(c, d);
//
//        delete c, d;
//    }
//    {
//        std::array Numbers{ 1,2,3,4,5,6,7,8,9,10 };
//        std::vector<int> vecOdds, vecEvens;
//
//        SeperateOddsAndEvens(&Numbers, &vecOdds, &vecEvens);
//
//        std::vector<int> vecPointerOdds, vecPointerEvens;
//        SeperateOddsAndEvens(Numbers, vecPointerOdds, vecPointerEvens);
//    }
//     
//
//
//}
//#pragma endregion

//#pragma region 15. SmartPointer**
//{
//    using namespace std;
//    //unique_ptr
//    {
//        // unique_ptr 생성 및 역참조
//        // 소멸자 호출이 되면서 Heap memory를 delete한다.
//        unique_ptr<int> Unique = make_unique<int>(100);
//        *Unique = 200;
//    }
//    //다른 unique_ptr에 대입을 할 수 없다.
//    {
//        unique_ptr<int> Unique = make_unique<int>(100);
//        *Unique = 200;
//        //unique_ptr<int> Unique2 = Unique;
//
//        int* Pointer = Unique.get();
//        *Pointer = 999;
//
//        CallByPointer(Unique.get());
//        TestUnique(Unique);
//        TestUnique(&Unique);
//
//        //소유권 이전을 통해서 unique_ptr 전달 가능
//        unique_ptr<int> Unique2 = std::move(Unique);
//        int* Pointer2 = Unique.get();
//        int* Pointer3 = Unique2.get();
//
//        
//    }
//    //int* Test222 = GUnique.get();
//
//    //shared_ptr
//    {
//        //레퍼런스 카운팅 방식으로, 참조 횟수를 저장하고 있다가
//        //0이되면 실제로 Memory를 delete한다.
//
//        shared_ptr<int> SharedPtr;
//        {
//            shared_ptr<int> Shared = make_shared<int>(100);
//            long Count = Shared.use_count();
//
//            shared_ptr<int> Shared2 = Shared;
//            long Count2 = Shared.use_count();
//
//            SharedPtr = Shared;
//            long Count3 = Shared.use_count();
//
//            TestShared(Shared);
//        }
//        long Count4 = SharedPtr.use_count();
//
//        {
//            shared_ptr<FParam> Shared = make_shared<FParam>();
//            shared_ptr<FParam> Shared2 = Shared;
//        }
//    }
//
//    //shared_ptr + weak_ptr
//    {
//        weak_ptr<FParam> Weak;
//        {
//            shared_ptr<FParam> Shared = make_shared<FParam>();
//            shared_ptr<FParam> Shared2 = Shared;
//            Weak = Shared;
//            TestWeak(Shared);
//            TestWeak(Weak);
//        }
//
//        if (!Weak.expired())
//        {
//            cout << "진행";
//        }
//        TestWeak(Weak);
//    }
//
//    //shared_Ptr -> .get()으로 Pointer를 뽑아온 다음
//    //그 Pointer를 다시 shared_ptr로 바꾸기
//    {
//        shared_ptr<FSharedTest> Shared = make_shared<FSharedTest>(1234);
//
//        {
//            FSharedTest* Test = Shared.get();
//            Test->A = 123456;
//
//            shared_ptr<FSharedTest> SharedTest = Test->shared_from_this();
//            SharedTestFunction(SharedTest);
//        }
//    }
//
//}
//#pragma endregion

//#pragma region 16. RVO(Return Value Optimization), NRVO(Named Return Value Optimization)
//    {
//        std::array Numbers{ 1,2,3,4,5,6,7,8,9,10 };
//
//        {
//            //RVO
//            FOddsAndEvens OddsAndEvens = SeperateOddsAndEvens(Numbers);
//        }
//        {
//            //NRVO
//            FOddsAndEvens OddsAndEvens = SeperateOddsAndEvens2(Numbers);
//        }
//        
//    }
//#pragma endregion

#pragma region 17. Memory 누수(leak, 릭) 탐지
    {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        //_crtBreakAlloc = 153;

        int* Pointer = new int(10);
        double* DoublePointer = new double(3.14);
    }
#pragma endregion

#pragma region 18. 구조적 바인딩(structrued binding)
    {
        struct FStruct
        {
            int a = 0;
            int b{ 10 };
            int c = 20;
        };

        FStruct Instance{};
        FStruct Instance2{.a = 10};
        FStruct Instance3{.b = 20, .c =100};

    }
#pragma endregion

#pragma region 19. 타입 앨리어스(type alias)
    {
        typedef int Hello;

        int a = 50;
        Hello b = 500;

        typedef int* IntPtr;
        IntPtr aa = nullptr;
        aa = &a;

        //타입 앨리어스
        using Hello2 = int;
        Hello2 cc = 100;

        using V = std::vector<int>;
        V vv = V{ 1,2,3,4,5 };
        vv.push_back(100);
        std::vector<int> vvv = std::vector<int>{ 1,2,3,4,5 };
    }
#pragma endregion

#pragma region 20. 문자열(string)**
    {
//      //[Stack]                                     //[data]
//      //[0xfff...]Text(8Byte, 64bit) = 0x100...        (0x100...)"Hello World!"
        const char* Text = "Hello World!";
        //[0xfff...]Text2(8Byte, 64bit) = 0x100...        (0x100...)"Hello World!"
        const char* Text2 = "Hello World!";
        //[0xfff...]Text3(8Byte, 64bit) = 0x100...        (0x100...)"Hello World@"
        const char* Text3 = "Hello World@";
        //[0xfff...]TextStack = "Hello World@"

        //문자열 길이가 12글자 이지만, 배열은 13으로 잡히는데,
        //문자열의 끝인 \0이라는 특수문자(1글자로 취급)가 생략되어 있다.
        //그렇기 때문에 총 13자리가 필요
        const char TextStack[13] = "Hello World@";
        int Hello = 100;


        //너무 긴 문자열이 들어오면 heap에 동적할당
        //초기화 시점에 문자열이 결정되고, 짧은 문자열 같은 경우 stack에
        //올라올 수 있다.
        std::string String = "Hello World!";
        //String.append("Wow");
        String += " Wow";
        String[5] = '_';
        String = "Oh Hello";
        //std::cout << String << std::endl;

        //if (Text == Text2)
        //{
        //    std::cout << "Same\n" << std::endl;
        //}
    }
    //문자열비교
    {
        std::string String = "Hello World";
        std::string String2 = "Hello World";
        if (String == String2)
        {
            //std::cout << "Same" << std::endl;
        }
        else
        {
            //std::cout << "not Same" << std::endl;
        }
    }

    //다양한 타입을 문자열
    //문자열을 다양한 타입으로 변환
    {
        int Value = 5000;
        float Float = 3.14f;
        std::string ValueToString = "정수 : ";
        ValueToString += std::to_string(Value);
        ValueToString += "Float" + std::to_string(Float);


       // std::cout << ValueToString << std::endl;
    }
    //다국어 처리
    {
        //UTF-8
        std::string MultipleLanguage;

        //UTF-16
        wchar_t WideCharacter = L'갈';
        std::wstring WString = TEXT("어ㅣㄴㅇ러ㅣㅇㄴ리ㅓ");
        WString[6] = L'갈';

        WString.find('갈');
    }

#pragma endregion

#pragma region 21. Class(클래스)*****
    {
        //구조체 : 함수와 변수를 묶어서 관리
        struct FStruct
        {
            //접근지정자
            //기본 접근지정자 : public
        public:

            //생성자 : 인스턴스가 만들어질 때 호출
            // - 전역변수(Data영역) : 프로그램이 시작할 때
            // - 지역변수(Stack영역) : FStruct Instance; 이 코드가 실행되는 시점
            // - 동적할당(Heap영역) : new를 호출하는 경우
            FStruct()
            {
                a = 1234;
                this->b = 6666;
            }

            //소멸자 : 인스턴스의 수명이 끝날 때 호출
            // - 전역변수(Data영역) : 프로그램이 종료되기 전
            // - 지역변수(Stack영역) : 스코프({})를 벗어나는 경우
            // - 동적할당(Heap영역) : delete를 호출하는 경우
            ~FStruct()
            {

            }

            int a = 0;
        private:
            int b = 20;
        };

        //Code 영역에 함수
        //생성자() 코드
        //소멸자() 코드

        //instnace는
        //[int a = 0]
        //[int b = 20]
        FStruct Instance;
        Instance.a = 999;

        class FClass
        {
            //접근지정자
            //기본 접근지정자 : private

        public:
            FClass() {}

            FClass(const int newB) : b(newB) {}

            ~FClass() {}

        public:
            void Hello()
            {
                std::cout << std::format("A:{}, B:{}\n", a, b);
            }

            void SetA(const int NewA)
            {
                a = NewA;
            }
            int GetA() const
            {
                //함수 선언 뒤에 const를 붙이면
                //this pointer가 const this*로 된다.
                //즉 맴버 변수를 수정할 수 없고
                //맴버 함수는 const가 동일하게 붙어있는 맴버 함수만 호출 할 수 있다.
                //SetA(10);
                //int bb = GetA

                return a;
            }
            int GetB() const
            {
                return b;
            }

        private:
            int a = 0;
            int b = 10;;
        };

        FClass ClassInstance;

        ClassInstance.SetA(100);
        int A = ClassInstance.GetA();

        FClass ClassInstance2 = FClass(1234);
        int B2 = ClassInstance2.GetB();
        ClassInstance2.Hello();
        //B2 = 


    }
#pragma endregion
}


void Function2()
{

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
