#include "MainTool.h"

CMainTool::CMainTool()
{
	//게임 시작시 호출
}

CMainTool::~CMainTool()
{
	//게임 종료시 호출
}

void CMainTool::RUN()
{
	Init();

	//--- 인터 페이스

	Delete();
}

void CMainTool::Init()
{
	//초기화
}

void CMainTool::Delete()
{
	//삭제
}