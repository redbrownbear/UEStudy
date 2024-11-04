// 01-01.Memory.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include<vector>
#include<unordered_map>
#include<functional>
#include<format>
#include<random>

//프로젝트 속성 -> C/C++ -> 일반 -> 추가 포함 디렉터리
// ->$(ProjectDir)Function
#include "Function.h"

//전역변수 Data 영역
int GInt = 1234;
std::shared_ptr<FStruct>GSharedPtrStruct;
std::weak_ptr<FStruct>GWeakPtrStruct;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(77);

    //Stack memory
    {
        //Stack                                     //Heap
        //[4Byte]i1{1}
        //[4Byte]i2{2}
        //[4Byte]i3{3}

        int i1{ 1 };
        int i2{ 2 };
        int i3{ 3 };
    }
    //Pointer, 동적할당
    {
        //64bit 기준으로 포인터는 8바이트고
        //8바이트인 이유는 64bit주소를 모두 표기하기 위해서는
        //2^64 값이 필요하다.

        //Stack                                                 //Heap
        //[8Byte]Pointer{nullptr(0xHeapAddress)}    ------>     [4Byte]*Pointer{444}
        int* Pointer{ nullptr };

        Pointer = new int{ 444 };

        //Stack                                                 //Heap
        //[8Byte]Pointer{nullptr(0xHeapAddress)}    ------>     [4Byte]*Pointer{444}
        *Pointer = 555;
        *(char*)Pointer = 10;

        delete Pointer;
        Pointer = nullptr;
    }
    //Pointer, 지역변수
    {
        //Stack                                        //Heap
        //[2Byte]A{0}      <---------------------┐     
        //[4Btye]Paddinge                        │
        //[8Byte]Pointer{0xHeapAddress}    ------┘ 

        short A = 0;
        short* Pointer = &A;
        //Stack                                        //Heap
        //[2Byte]A{0}      <---------------------┐     
        //[4Btye]Paddinge                        │
        //[8Byte]Pointer{0xHeapAddress}    ------┘ 
        *Pointer = 231;
    }
    //Pointer, 전역변수
    {
        //Stack                                        //Heap
        //[8Byte]Pointer{0xHeapAddress}    ------>     [4Byte]GInt{1234}
        int* Pointer = &GInt;
        *Pointer = 231;
    }
    //double Pointer, 동적 할당
    {
        //Stack                                        //Heap
        //[8Byte]Pointer{nullptr(0)}                   
        int** DoublePointer{ nullptr };

        //Stack                                        //Heap
        //[8Byte]Pointer{0xHeapAddress}     ----->     [8Byte] *DoublePointer{ trash(0xcdcdcdcd cdcdcdcd) }  
        DoublePointer = new int*;

        //Stack                                        //Heap
        //[8Byte]Pointer{0xHeapAddress}     ----->     [8Byte] *DoublePointer{ trash(0xcdcdcdcd cdcdcdcd) }
        //                                                              ▽
        //                                             [4Byte] **DoublePointer{10}
        *DoublePointer = new int{ 10 };

        **DoublePointer = 1234;

        //Stack                                        //Heap
        //[8Byte]Pointer{0xHeapAddress}     ----->     [8Byte] *DoublePointer{ trash(0xcdcdcdcd cdcdcdcd) }
        //                                                              ▽
        //                                             delete ! [4Byte] **DoublePointer{10}
        delete* DoublePointer;
 
        //Stack                                        //Heap
        //[8Byte]Pointer{0xHeapAddress}     ----->     [8Byte] *DoublePointer{ trash(0xcdcdcdcd cdcdcdcd) }
        //                                                              ▽
        //                                             delete ! [8Byte] *DoublePointer{0xHeapAddress}
        delete DoublePointer;
        DoublePointer = nullptr;
    }
    //Double Pointer tip(COM; Component Object Model)
    {
        int* Pointer = nullptr;

        AllocateWrong(Pointer);
        AllocateCorrect(&Pointer);
        DeAllocate2(&Pointer);
    }
    //메모리 누수(Memory leak)
    {
        //Stack                                 Heap
        //??                                    ?(0xAddress
        new int;
    }
    //배열과 동적 할당
    {
        //배열
        {
            int Array[5]{ 3, 4, 5, 0, 0, };
            //Stack                                 Heap
            //Array[0] {3}
            //Array[1] {4}
            //Array[2] {5}
            //Array[3] {0}
            //Array[4] {0}
        }

        //배열 동적 할당
        {
            int* Pointer = new int[5] {3, 4, 5, /*0, 0*/};
            //Stack                                 Heap
            //[8Byte]Pointer{0xHeapAddress}         Pointer[0] {0} => *(Pointer + 0) {1}
            //                                      Pointer[1] {1} => *(Pointer + 1) {2}
            //                                      Pointer[2] {2} => *(Pointer + 2) {3}
            //                                      Pointer[3] {3} => *(Pointer + 3) {4}
            //                                      Pointer[4] {4} => *(Pointer + 4) {5}

            for (int i = 0; i < 5; ++i)
            {
                Pointer[i] = i;
                // *(Pointer + i) = i + 1;
            }

            delete[] Pointer;
            Pointer = nullptr;
        }

        //2차원 배열
        {
            //Stack                                 Heap
            //Array[0][0] {0}
            //Array[0][1] {1}
            //Array[1][0] {2}
            //Array[1][1] {3}
            //Array[2][0] {4}
            //Array[2][1] {5}

            char Array[3][2]{}; //cache miss 발생을 줄이려면 메모리 구조를 이해하고 가로(?)로 접근해야 한다.
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    Array[i][j] = char(1 * 2 + j);
                }
            }
        }

        //다차원 동적할당은 쓰지 말자
        {

        }

        //함수에 배열을 포인터로 전달
        {
            int Array[1000]{};
            InitArray(Array, 1000);

            //버퍼 오버플로우 : 지정된 공간을 넘어서 데이터를 씀
            //InitArray(Array, 2000);
            //int Array[1000];
        }
        //STL(Standard Template Library)에 있는 자료구조(or 컨테이너)
        {
            std::vector<int> Vector;
            Vector.resize(10);
            InitArray(Vector);
            InitArray(Vector.data(), Vector.size());
        }

        //Sum
        {
            int Result = 0;
            std::vector<int> Numbers{ 1,2,3,4,5,6 };

            Sum(Numbers, &Result);
        }

        //Swap
        {
            int A = 200;
            int B = 100;

            Swap(A, B);
        }
    }
    //Smart Pointer
    {
        //unique_prt
        {
            //단 하나의 동적할당된 인스턴스만 동시에 존재할 수 있다.
            std::unique_ptr<int> Unique = std::make_unique<int>(10);
            *Unique = 1000;
            *Unique.get() = 1234;
        }

        //unique_ptr custom deleter
        {
            std::unique_ptr<int, decltype(&CustomDeleterInt)> Unique(new int(124), CustomDeleterInt);
        }
            
        {
            FStruct Struct = FStruct();
            FStruct Copy = FStruct(Struct);

            Copy = Struct;


            std::unique_ptr<FStruct> Unique = std::make_unique<FStruct>(10);
            std::unique_ptr<FStruct> UniqueCopy = std::make_unique<FStruct>(Unique);
            UniqueCopy->SetValue(1234);

            std::unique_ptr<FStruct> UniqueCopy2 = std::make_unique<FStruct>(*Unique);

            std::unique_ptr<FStruct> UniqueTest = move(Unique);

        }

        //shared_ptr
        {
            //std::shared_ptr<int>SharedPtr{ std::make_shared<int>(100) };
            std::shared_ptr<int>SharedPtr{ new int, CustomDeleterInt };
            std::shared_ptr<int>SharedPtr2 = SharedPtr;

            long Count = SharedPtr.use_count();
        }

        {
            std::shared_ptr<FStruct>SharedPtr = std::make_shared<FStruct>(10);
            GSharedPtrStruct = SharedPtr;
            GWeakPtrStruct = GSharedPtrStruct;

            SharedParam(GSharedPtrStruct);
            GSharedPtrStruct = nullptr;
            SharedPtr.reset();
            WeakParam(GSharedPtrStruct);

        }

    }

#pragma region auto
    {
        //컴파일러가 타입을 추론할 수 있는 경우 타입을 추론해주는 기능
        //컴파일러가 타입을 추론해야 하기 때문에 컴파일 시간이 살짝 늘어나는 단점
        //하자만 소소하게 쓰면 의미 없는 시간이다.

        int a = 10;
        auto aa = 10;
        auto Double = 3.0;
        auto Float = 3.5f;

        bool bResult = ReturnTrue();
        auto bResult2 = ReturnTrue();

        int Int = 100;
        int* IntPointer = &Int;

        auto AutoPointer = &Int;

        auto* AutoPointer2 = &Int;

        auto IntAuto = Int;
        auto& RefIntAUto = Int;

        std::vector<int> Vector{};
        Vector.resize(10);
        for (int& i : Vector)
        {
            i = 1234;
        }

        for (auto i : Vector)
        {
            i = 2345;
        }

        for (auto& i : Vector)
        {
            i = 2345;
        }

        std::unordered_map<int, double> Map;

        for (std::pair<int, double> i : Map) {}
        for (auto i : Map) {}


    }
#pragma endregion

#pragma region 함수 포인터(Function Pointer)
    {
        //함수도 주소가 부여되어 있다.
        //C++에서는 함수의 주소를 구해서 변수처럼 사용할 수 있다.
        {
            bool(*FunctionName)(void) = ReturnTrue;
            bool bResult = FunctionName();
            FunctionName = ReturnFalse;
            bResult = FunctionName();

            using FFunctionPointer = bool(*) ();
            FFunctionPointer FunctionTest = ReturnTrue;
            bool bResult2 = FunctionTest();
            FunctionTest = ReturnFalse;
            bResult2 = FunctionTest();
        }
        {
            std::function Function = ReturnTrue;
            std::function<bool()> Function2 = ReturnTrue;

            bool bResult = Function2();
            Function2 = ReturnFalse;
            bResult = Function2();
        }
        {
            std::function<int(int, int)> Function = SumFunction;

            int Result = Function(10, 20);
            int Result2 = Function(30, 20);
        }
        {
            //FStruct Instance;
            //Instance.SetValue(100);

            //auto Function = std::bind(&FStruct::SetValue, &Instance, std::placeholders::_1);
            //Function(1234);

            //std::function<void()> Function2 = std::bind(&FStruct::SetValue, &Instance);
            //Function2();
        }
    }
#pragma endregion

#pragma region 람다(Lambda)
    {
        //이름없는 함수 라고 부름
        {
            //이렇게 선언만 하면 호출 불가!
            []()
                {
                    std::cout << "Lambda Function!\n";
                };
            []()
                {
                    std::cout << "Lambda Function!\n";
                }();        //()를 여기에 추가하면 함수 호출 가능

            std::function Lambda = []()
                {
                    std::cout << "Lambda Function!\n";
                };

            for (int i = 0; i < 10; ++i)
            {
                Lambda();
            }

            Lambda();
            {

            }
        }
        //람다를 사용해서 파라미터 처리
        {
            std::function Lambda = [](const int InValue)
                {
                    std::cout << InValue << std::endl;
                };

            for (int i = 0; i < 10; ++i)
            {
                Lambda(i);
            }
            Lambda(60);
        }
        //람다를 사용해서 리턴 처리
        {
            std::function Lambda = [](const int InValue)->int
                {
                    std::cout << InValue << std::endl;
                    return InValue + 100;
                };

            int Value = Lambda(100);
        }
        //람다를 사용해서 외부 변수 캡쳐
        {
            int a = 10, b = 20, c = 30;
            //명시적으로 특정 변수를 Captur(&없으면 값으로 캡쳐되고, 값을 수정할 수 없다(읽기 전용))
            //&로 캡쳐하면 수정 가능
            std::function Lambda = [a, b, &c](const int InValue)->int
                {
                    c = 10;

                    std::cout << a << std::endl;
                    std::cout << b << std::endl;
                    std::cout << c << std::endl;

                    return InValue + 100;
                };
                int Value = Lambda(100);
        }
        {
            int a = 10, b = 20, c = 30;
            //&로 캡쳐하면 수정 가능
            std::function Lambda = [=, &c](const int InValue)->int
                {
                    c = 10;

                    std::cout << a << std::endl;
                    std::cout << b << std::endl;
                    std::cout << c << std::endl;

                    return InValue + 100;
                };

            a = 999;    //이미 a값이 Lambda에 10으로 Capture되어 있어서
            //여기에서 999로 바꿔도 Lambda내부에서는 10이다.

            int Value = Lambda(100);
        }
        // Struct를 캡처 하는 경우
        {
            FStruct Struct;
            Struct.SetValue(100);
            std::function Lambda = [Struct]()
                {
                    std::cout << "Lambda\n";
                };
            Struct.SetValue(1000);
            Lambda();
        }

        //함수와 람다
        {
            Function(Test);
            Function([]()
                {
                    for (int i = 0; i < 10; ++i)
                    {
                        std::cout << std::format("Lambda! {}\n", i);
                    }
                }
            );

            //int Count = 10;
            //std::cout << std::endl;
            //std::cout << "input: ";
            //std::cin >> Count;
            //Function(
            //    [Count]()
            //    {
            //        for (int i = 0; i < 10; ++i)
            //        {
            //            std::cout << std::format("Lambda! {}\n", i);
            //        }
            //    }
            //);

            FStruct Struct = FStruct
            (
                []()
                {
                    std::cout << "Hello";
                }
            );

        }

        //람다를 사용할때 주의점
        {
            //만약 등록해둔 람다 함수가 늦게 호출되는 경우
            //늦게라는 의미는 아래처럼 즉시 함수호출 후 람다가 실행되는 경우
            //Ex) 스레드,

            int* Pointer = new int(100);

            FStruct Struct = FStruct(
                [Pointer]()
                {
                    std::cout << "Hello" << *Pointer << std::endl;
                }
            );
            Struct.SetValue(100);

            delete Pointer;
            Struct.SetValue(100);
        }


    }
#pragma endregion

#pragma region random, sort
    {
        //컴퓨터에서 ramdom 함수는 진짜 random이 아닐 수 있다.
        //좋은 random 함수를 사용해야 더 random에 가깝다.

        std::random_device RD;
        std::mt19937 Gen(RD());
        std::uniform_int_distribution<int> Dist(0, 999);
        int RandomValue = Dist(Gen);

        std::vector<int> Vector;
        Vector.resize(100);
        std::cout << "RandomStart ---\n";
        for (int& i : Vector)
        {
            i = Dist(Gen);
            std::cout << i << ", ";
        }
        std::cout << "RandomEnd ---\n";

        std::sort(Vector.begin(), Vector.end());

        std::cout << "SortStart ---\n";
        for (int i : Vector)
        {
            std::cout << i << ", ";
        }
        std::cout << "SortEnd ---\n";

    }
#pragma endregion

    
}
