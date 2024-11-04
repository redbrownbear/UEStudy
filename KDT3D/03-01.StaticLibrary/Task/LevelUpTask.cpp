#include "LevelUpTask.h"
#include "Misc/Utils.h"
#include "Classes/DataBase.h"
#include "Classes/LoginSession.h"

FLevelUpTask::FLevelUpTask() noexcept
{
	std::cout << "[ ------  레벨관리  ------- ]" << std::endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	std::string CharacterName;
	std::cout << std::format("Input CharacterName: ");
	std::cin >> CharacterName;

	FDataBase* DataBase = FDataBase::Get();

	EErrorCode ErrorCode = EErrorCode::ESuccessed;
	std::shared_ptr<FPlayer> Player = DataBase->CheckPlayer(Account, CharacterName, &ErrorCode);

	FUtils::PrintSystemSuccessOrFailed(ErrorCode == EErrorCode::ESuccessed,
		std::format("Login Error: {} / ID: {} / Password: {} / CharacterName: {}\n",
			(int)ErrorCode, Account.ID, Account.Password, CharacterName));

	if (ErrorCode == EErrorCode::ESuccessed)
	{
		std::cout << " - 해당계정의 레벨을 조정하시오." << std::endl;
		int ChangeLevel;
		std::cout << std::format("Input Level: ");
		std::cin >> ChangeLevel;

		DataBase->ChangeLevel(Account, CharacterName, ChangeLevel);
	}
}
