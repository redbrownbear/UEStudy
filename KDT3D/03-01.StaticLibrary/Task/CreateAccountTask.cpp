#include "CreateAccountTask.h"
#include "Classes/DataBase.h"
#include "Misc/Utils.h"

FCreateAccountTask::FCreateAccountTask() noexcept
{
	std::cout << "[------ 계정  생성------]" << std::endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	EErrorCode ErrorCode;
	FAccount* NewAccount = FDataBase::Get()->CreateAccount(Account, &ErrorCode);
	FUtils::PrintSystemSuccessOrFailed(NewAccount,
		std::format("Create Account Failed! Error: {} / ID: {} / Password: {}", (int)ErrorCode, Account.ID, Account.Password));
}
