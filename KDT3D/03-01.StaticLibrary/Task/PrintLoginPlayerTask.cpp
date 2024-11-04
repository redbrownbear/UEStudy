#include "PrintLoginPlayerTask.h"
#include "Classes/LoginSession.h"

FPrintLoginPlayerTask::FPrintLoginPlayerTask() noexcept
{
	const auto& Accounts = FLoginSession::Get()->GetPlayers();
	std::cout << "[ ------  Player정보 ------ ]" << std::endl;
	for (const auto& it : Accounts)
	{
		std::cout << std::format("-> ID: {}, Name: {}, Level: {}\n", 
			it.second.GetAccountName(), it.second.GetName(), it.second.GetLevel());
	
	}

	std::cout << "[ ------------------------- ]" << std::endl;
}