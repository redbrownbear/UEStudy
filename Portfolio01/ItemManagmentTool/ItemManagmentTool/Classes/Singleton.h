#pragma once
#include "Misc/Headers.h"

template <typename _Ty>
class CSingleton
{
public:
    // CSingleton 객체에 대한 접근을 제공하는 메소드
    static _Ty* GetInstance()
    {
        //static std::unique_ptr<_Ty> instance;
        if (!instance)
        {
            instance.reset(new _Ty());
        }
        return instance.get();
    }

    // CSingleton 인스턴스를 삭제하는 메소드 (원하는 경우 사용)
    static void destroyInstance()
    {
        instance.reset();
    }

    // 복사 생성자와 대입 연산자를 삭제하여 복사 방지
    CSingleton(const CSingleton&) = delete;
    CSingleton& operator=(const CSingleton&) = delete;

protected:

    CSingleton() {}
    virtual ~CSingleton() {}

private:
    // CSingleton 인스턴스를 관리하는 unique_ptr
    static std::unique_ptr<_Ty> instance;
};

template <typename _Ty>
std::unique_ptr<_Ty> CSingleton<_Ty>::instance = nullptr;  // 정적 멤버 변수의 정의