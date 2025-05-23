#include "CreatePlayerTask.h"
#include "Classes/DataBase.h"
#include "Misc/Utils.h"

FCreatePlayerTask::FCreatePlayerTask() noexcept
{
	std::cout << "[ ------ 캐릭터생성  ------- ]" << std::endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();

	std::string CharacterName;
	std::cout << std::format("Input CharacterName: ");
		std::cin >> CharacterName;

	EErrorCode ErrorCode = FDataBase::Get()->CreatePlayer(Account, CharacterName);
	FUtils::PrintSystemSuccessOrFailed(ErrorCode == EErrorCode::ESuccessed, std::format("Login Error: {} / ID: {} / Password: {}\n",
		(int)ErrorCode, Account.ID, Account.Password));
}
