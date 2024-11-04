#include "DeleteAccountTask.h"
#include "Classes/DataBase.h"
#include "Misc/Utils.h"
#include "Task/LogoutTask.h"

FDeleteAccountTask::FDeleteAccountTask() noexcept
{
	std::cout << "[------ 계정  삭제------]" << std::endl;

	const FAccount Account = FUtils::MakeAccountFromUserInput();
	FDataBase* DataBase = FDataBase::Get();

	{
		
		EErrorCode ErrorCode;
		FAccount* Result = DataBase->CheckAccount(Account, &ErrorCode);
		if (ErrorCode != EErrorCode::ESuccessed)
		{
			FUtils::PrintSystemSuccessOrFailed(ErrorCode == EAccountNotValid,
				std::format("Create Account Failed! Error: {} / ID: {} / Password: {}", (int)ErrorCode, Account.ID, Account.Password));
		}
	}

	// Login 상태였다면
	// Logout 처리도 해야한다
	{
		FLogoutTask LogoutTask(Account);
	}

	{
		EErrorCode ErrorCode = DataBase->DeleteAccount(Account);
		FUtils::PrintSystemSuccessOrFailed(ErrorCode == EErrorCode::ESuccessed,
			std::format("Delete Account Failed! Error: {} / ID: {} / Password: {}", (int)ErrorCode, Account.ID, Account.Password));
	}

}
