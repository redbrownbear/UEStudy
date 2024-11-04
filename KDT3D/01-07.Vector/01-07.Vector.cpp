// 01-07.Vector.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Vector.h"
#include <vector>
#include <map>

struct FStruct
{
    FStruct()
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    FStruct(const int InValue)
        : Value(InValue)
    {
        std::cout << __FUNCTION__ << " const int" << std::endl;
    }

    FStruct(const FStruct& InOther)
        : Value(InOther.Value)
    {
        std::cout << __FUNCTION__ << " const FStruct&" << std::endl;
    }

    FStruct(FStruct&& InOther) noexcept
        : Value(InOther.Value)
    {
        std::cout << __FUNCTION__ << " FStruct&&" << std::endl;
        InOther.Value = 0;
    }

    FStruct& operator=(const FStruct& InOther)
    {
        Value = InOther.Value;
        return *this;
    }
    FStruct& operator=(const FStruct&& InOther) noexcept
    {
        Value = InOther.Value;
        return *this;
    }

    int Value = 0;
};

int main()
{
    {
        kdt::Test();

        kdt::vector<FStruct> Vector;
        Vector.reserve(10);

        for (int i = 0; i < 10; ++i)
        {

            FStruct Struct;
            Struct.Value = i;
            Vector.push_back(Struct);
        }

        Vector.reserve(3);
        Vector.resize(3);

        const size_t Size = Vector.size();
        for (size_t i = 0; i < Size; ++i)
        {
            FStruct& Struct = Vector[i];
            Struct.Value = 99999;
        }

        Vector.push_back(FStruct(1234));
        Vector.clear();
        

        Vector.push_back(FStruct(234));
        Vector.push_back(FStruct(123));

        kdt::_Vector_iterator<FStruct> Test2;
        kdt::vector<FStruct>::iterator Test3;

        Vector.erase(Vector.begin());

    }

    {
    //    std::cout << "std::vector\n";

    //    std::vector<FStruct> Vector;
    //    Vector.reserve(10);

    //    for (int i = 0; i < 10; ++i)
    //    {
    //        FStruct Struct;
    //        Struct.Value = i;

    //        Vector.push_back(Struct);
    //    }
    //    {
    //        FStruct StructTemp; StructTemp.Value = 1234;
    //        Vector.push_back(StructTemp);
    //    }

    //    for (FStruct& Struct : Vector)
    //    {
    //        std::cout << Struct.Value << std::endl;
    //    }

    //    std::vector<FStruct>::iterator iterEnd = Vector.end();
    //    for (std::vector<FStruct>::iterator iter = Vector.begin(); iter != Vector.end(); ++iter)
    //    {
    //        std::cout << iter->Value << std::endl;
    //        std::cout << (*iter).Value << std::endl;
    //    }

    //    std::vector<FStruct> Struct1;
    }

    //vector 사용시 주의점
    {
        std::vector<int> Vector;
        Vector.emplace_back(10);
        Vector.emplace_back(20);

        std::vector<int>::iterator iter = Vector.begin();
        int& Value = Vector.back();

        //재할당으로 인해 기존에 가리키던 주소가 무효화됨
        //Value, iter가 의미없는 주소를 가리키는 상황이 됨
        Vector.push_back(20);
    }

    {
        kdt::vector<int> Vector;
        Vector.emplace_back(10);
        Vector.emplace_back(10);


        kdt::vector<int>::iterator iter = Vector.begin();
        int& Value = Vector[1];

        Vector.push_back(20);
    }

    {
        std::map<int, int> Map;
        
        Map.insert(std::make_pair(0, 100));

        std::map<int, int>::iterator iter = Map.find(0);

        for (int i = 1; i < 10000; ++i)
        {
            Map.insert(std::make_pair(i, i + 1234));
        }
    }
}

