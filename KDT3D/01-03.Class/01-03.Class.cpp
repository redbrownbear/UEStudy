// 01-03.Class.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Class/Class.h"
#include <iostream>
#include <vector>

int main()
{
    int aa = 0;
    static int a = 0;
    int bb = 0;
    {
        {
            //FClass라는 설계도(청사진)을 기반으로
            //실체화된 사례(Instance)를 만든다.
            //An Object is instance of a class
            FClass ClassInstance;
            FClass ClassInstance2 = FClass();
            FClass ClassInstance3 = FClass(ClassInstance2);
        }

        {
            FClass ClassInstance;
            FClass ClassInstnace2;
            FClass ClassInstnace3;

            ClassInstnace2.operator=(ClassInstnace3);
            ClassInstnace2 = ClassInstnace3;

            ClassInstance = ClassInstnace2 = ClassInstnace3;
            ClassInstance.operator=(ClassInstnace2.operator=(ClassInstnace3));
        }

        {
            FClass2 ClassInstance;
            FClass2 ClassInstance2 = FClass2(ClassInstance);
            //ClassInstance.a = 9999;
            ClassInstance2 = ClassInstance;
        }

        {
            FClass2* ClassInstance = new FClass2;
            FClass2* ClassInstnace2 = new FClass2(*ClassInstance);

            //주소만 바뀜 주의
            //ClassInstnace2 = ClassInstance;
            *ClassInstnace2 = *ClassInstance;

            //delete 할섣

            delete ClassInstance;
            ClassInstance = nullptr;
            delete ClassInstnace2;
            ClassInstnace2 = nullptr;
        }
        {
            int a = FClass2::StaticVar1;

            FClass2 ClassInstance;
            ClassInstance.Hello();

            FClass2::Hello2();
            ClassInstance.Hello2();
        }
        {
            FClass2* Class = nullptr;

            //Hello 함수 내부에서 this에서 접근할 수 있어서 nullptr에 들어가는
            //Crash발생
            //HelloTest는 내부에서 this에 접근하고 있지 않아 문제 없음
            //Class->HelloTest();
            //Class->Hello();
        }
    }
    //Friend: 내가 대상을 친구로 생각하면
    //대상이 내 private(protected)에 접근할 수 있다.
    {
        class FClassA 
        {
            friend class FManagerClass;

        private:
            FClassA()
            {

            }

            void SetValue(const int InValue)
            {
                ClassAPrivateDataButCanAccessFromFriend = InValue;
            }

        private:
            int ClassAPrivateDataButCanAccessFromFriend = 10;
        };

        //생성자가 private이라 instance를 만들 수 없다.
        //FClassA ClassInstance;

        //싱글턴(Singleton) 패턴
        class FManagerClass
        {
        public:
            static FManagerClass* Get(bool bDestroy = false)
            {
                static std::unique_ptr<FManagerClass> Instance{ new FManagerClass };

                if (bDestroy)
                {
                    Instance.reset();
                    return nullptr;
                }

                return Instance.get();
            }

            ~FManagerClass()
            {

            }

            void SetValue(const int InValue)
            {
                ClassA.SetValue(InValue);
            }

        private:
            FManagerClass()
            {

            }

        private:
            FClassA ClassA;
        };

        FManagerClass* SInstnace = FManagerClass::Get();
        SInstnace->Get()->SetValue(200);
        //FManagerClass::Get(true);
        FManagerClass::Get()->SetValue(200);

    }

    //이동 의미론(move semantics)
    {
        // l-value(left value : 좌측값) : 이름이 있는 변수(이름으로 주소를 얻어올 수 있다.
        // r-value(right value : 우측값) : lvalue가 아닌 나머지, 리터럴(상수), 임시 객체

        int a = 5 + 10;     //a는 lvalue이면, 이름(a)를 갖고 있으며, &a로 주소를 가져올 수 있다.
                            //5 + 10이라는 표현식은 rvalue이다.

        const char* Hello = "Hello";
        std::string Message = std::string(Hello);
        //                                  lvalue reference
        auto LValueFunction = [](std::string& InString)
            {
                InString;
            };


        std::string* StringPointer = nullptr;
        //                                      rvalue reference
        auto RValueFunction = [&StringPointer](std::string&& InString)
            {
                InString[0] = 'A';
                StringPointer = &InString;
            };

        LValueFunction(Message);
        RValueFunction("aaa");

        std::string Test = *StringPointer;

        struct FTest
        {
            FTest()
            {
                std::cout << "FTest()\n";

            }
            ~FTest()
            {
                std::cout << Value << std::endl;
            }

            int Value = 10;
        };

        FTest* Test2 = nullptr;
        auto Function = [&Test2](FTest&& InTest)
            {
                Test2 = &InTest;
            };

        Function(FTest());
    }

    {
        FClass2 Class = FClass2();

        //복사 생성자 호출
        FClass2 ClassCopy = Class;

        //std::move : lvalue를 rvalue로 cast한다
        //FClass2 ClassMove = std::move(Class);
        //이동 생성자가 구현되어 있지 않다면 복사 생성자가 호출된다.
        FClass2 ClassMove = (FClass2&&)(Class);
        FClass2 ClassMove2 = std::move(Class);
    }

    {
        std::vector<int> Vector;
        Vector.resize(10000);
        Vector[0] = 100;
        Vector[2] = 1234;

        std::vector<int> VectorCopy = Vector;
        VectorCopy[0] = 1000;
        VectorCopy[2] = 2000;

        int* Address = &Vector[0];
        std::vector<int> VectorMove = std::move(Vector);
        int* Address2 = &VectorMove[0];

        VectorMove[3] = 1234;
    }

    {
        std::vector<FClass2> Vector;
        Vector.resize(2);

        std::vector<FClass2> Vector2 = Vector;

        std::vector<FClass2> Vector3 = std::move(Vector);
    }
    {
        std::vector<FClass2> Vector;
        Vector.reserve(4); //미리 공간만 할당

        FClass2 Test;
        Vector.push_back(FClass2());
        Vector.push_back(Test);
        Vector.emplace_back(100);
        Vector.emplace_back(100);
        Vector.emplace_back(100);

        size_t C = Vector.capacity();
        size_t S = Vector.size();

    }

}