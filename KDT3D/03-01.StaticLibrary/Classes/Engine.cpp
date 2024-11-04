#include "Engine.h"
#include "Classes/DataBase.h"
#include "Classes/LoginSession.h"
#include "Misc/Utils.h"
#include "Task/Tasks.h"

FEngine GEngine;

void FEngine::Run()
{
	Init();

	while (!bTerminated)
	{
		system("pause");
		EMenuEvent MenuEvent = PrintMenuAndSelectEvent();

		switch (MenuEvent)
		{
		case ETermanate:
		{
			bTerminated = true;
		}
			break;
		case ECreateAccount:
		{
			FPrintAccountTask PrintAccountTask;
			FCreateAccountTask CreateAccountTask;
		}	
			break;
		case EDeleteAccount:
		{
			FPrintAccountTask PrintAccountTask;
			FDeleteAccountTask DeleteAccountTask;
		}
			break;
		case EPrintAccount:
		{
			FPrintAccountTask Task;
		}
			break;
		case ECreatePlayer:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FCreatePlayerTask CreatePlayerTask;
		}
		break;
		case EDeletePlayer:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FDeletePlayerTask DeletePlayerTask;
		}
		break;
		case ELogin:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FLoginTask LoginTask;		
		}
		break;
		case ELogout:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FLogoutTask LoginTask;
		}
		break;
		case ELevelManage:
		{
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FLevelUpTask LevelUpTask;
		}
			break;
		case EPritLoginUsers:
		{
			FPrintLoginPlayerTask PrintLoginPlayerTask;
		}
		break;
		default:
			break;
		}
	}

	Release();
}

void FEngine::Init()
{
	FDataBase::Get();
	FLoginSession::Get();

	//std::cout << std::format("[System] {}\n", __FUNCTION__);
}

void FEngine::Release()
{
	FLoginSession::Get(true);
	FDataBase::Get(true);

	//std::cout << std::format("[System] {}\n", __FUNCTION__);
}

EMenuEvent FEngine::PrintMenuAndSelectEvent()
{
	EMenuEvent MenuEvent = EMenuEvent::ETermanate;
	system("cls");	//화면을 지워준다.
	std::cout << "[-------------------------------------]" << std::endl;
	std::cout << "	0) 프로그램 종료					 " << std::endl;
	std::cout << "	1) 회원 가입						 " << std::endl;
	std::cout << "	2) 회원 탈퇴						 " << std::endl;
	std::cout << "	3) 회원 정보 출력					 " << std::endl;
	std::cout << "	4) 캐릭터 생성						 " << std::endl;
	std::cout << "	5) 캐릭터 삭제						 " << std::endl;
	std::cout << "	6) 로그인							 " << std::endl;
	std::cout << "	7) 로그아웃							 " << std::endl;
	std::cout << "	8) 레벨관리							 " << std::endl;
	std::cout << "	9) 로그인 유저 정보 출력			 " << std::endl;
	std::cout << "[-------------------------------------]" << std::endl;
	std::cout << "* Please input event number" << std::endl;
	std::cout << "-->" << std::endl;

	int EventNumber = 0;
	std::cin >> EventNumber;
	MenuEvent = static_cast<EMenuEvent>(EventNumber);

	return MenuEvent;
}
