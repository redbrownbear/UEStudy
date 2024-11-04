#pragma once
#include <iostream>


enum EErrorCode : uint8_t
{
	ESuccessed,				//성공
	EUnknown,				//알 수 없는 오류
	EEmptyAccount,			//빈계정
	EDuplicateAccount,		//중복계정
	ECanNotFoundAccount,	//계정을 찾을 수 없다.
	EAccountNotValid,		//계정이 유효하지 않다

	ENoLogin,				//로그인 하지 않았다
	EDuplicatePlayerName,	//중복된 플레이어 이름
	EPlayerNotValid,		//유효하지 않은 플레이어
};
