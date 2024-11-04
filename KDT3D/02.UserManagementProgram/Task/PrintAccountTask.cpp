#include "PrintAccountTask.h"
#include "Classes/DataBase.h"

FPrintAccountTask::FPrintAccountTask() noexcept
{
	const auto& Accounts = FDataBase::Get()->GetAccounts();
	std::cout << "[ ------ 계정  정보 ------- ]" << std::endl;
	for (const auto& it : Accounts)
	{
		std::cout << std::format("-> ID: {}, Password: {}\n", it.second.ID, it.second.Password);
	}
}
