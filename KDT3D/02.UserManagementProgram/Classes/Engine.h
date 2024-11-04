#pragma once
#include "Misc/Headers.h"

enum EMenuEvent : uint8_t
{
	ETermanate,

	ECreateAccount,
	EDeleteAccount,
	EPrintAccount,

	ECreatePlayer,
	EDeletePlayer,
	ELogin,
	ELogout,
	ELevelManage,
	EPritLoginUsers,
};

class FEngine
{
public:
	void Run();

private:
	//초기화
	void Init();
	//정리
	void Release();

	EMenuEvent PrintMenuAndSelectEvent();

private:
	bool bTerminated = false;
};

extern FEngine GEngine;

