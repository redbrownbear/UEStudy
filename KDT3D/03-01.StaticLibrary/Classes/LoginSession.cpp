#include "LoginSession.h"
#include "Classes/DataBase.h"


FLoginSession* FLoginSession::Get(const bool bDestroy)
{
	static std::unique_ptr<FLoginSession> Instance{ new FLoginSession };
	if (bDestroy) { Instance = nullptr; }
	return Instance.get();
}

FPlayer* FLoginSession::Login(const FAccount& InAccount, std::string_view InPlayerName, EErrorCode* const OptionalOutErrorCode)
{
	std::shared_ptr<FPlayer> Player = FDataBase::Get()->CheckPlayer(InAccount, InPlayerName, OptionalOutErrorCode);
	if (!Player)
	{
		return nullptr;
	}
	{
		FPlayer* Player = IsLogin(InAccount.ID);
		//접속중인 상황
		if (Player != nullptr)
		{
			EErrorCode ErrorCode = Logout(InAccount);
			if (ErrorCode != EErrorCode::ESuccessed)
			{
				//로그아웃 시도 실패? 왜?
				_ASSERT(false);
				if (OptionalOutErrorCode) { *OptionalOutErrorCode = ErrorCode; }
				return nullptr;
			}

			Player = nullptr;
		}
	}

	//auto Pair = PlayerMap.try_emplace(Account->ID, Account->ID, 0);
	std::pair Pair = PlayerMap.insert(std::make_pair(InAccount.ID, *Player.get()));
	if (!Pair.second)
	{
		_ASSERT(false);
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::EUnknown; }
		return nullptr;
	}

	if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::ESuccessed; }

	return &Pair.first->second;
}

EErrorCode FLoginSession::Logout(const FAccount& InAccount)
{
	EErrorCode ErrorCode = EErrorCode::ESuccessed;
	FAccount* Account = FDataBase::Get()->CheckAccount(InAccount, &ErrorCode);
	if (!Account)
	{
		return ErrorCode;
	}

	FPlayer* Player = IsLogin(InAccount.ID);
	if (!Player)
	{
		return ENoLogin;
	}

	PlayerMap.erase(InAccount.ID);

	return ErrorCode;
}

FLoginSession::~FLoginSession()
{
	AllAccountLogout();
}

EErrorCode FLoginSession::Logout(const FAccount& InAccount, std::string_view InPlayerName)
{
	EErrorCode ErrorCode;

	FAccount* Account = FDataBase::Get()->CheckAccount(InAccount, &ErrorCode);
	if (!Account)
	{
		return ErrorCode;
	}

	FPlayer* Player = IsLogin(InAccount.ID);
	if (!Player)
	{
		return ENoLogin;
	}

	Player->OnLogout();
	PlayerMap.erase(InAccount.ID);

	return ErrorCode;
}

FPlayer* FLoginSession::IsLogin(const FAccountName& InAccountName)
{
	auto It = PlayerMap.find(InAccountName);

	// 로그인 하지 않았다
	if (It == PlayerMap.end())
	{
		return nullptr;
	}

	return &It->second;
}

FPlayer* FLoginSession::IsLogin(const FAccountName& InAccountName, std::string_view InPlayerName)
{
	FPlayer* Player = IsLogin(InAccountName);
	if (!Player)
	{
		return nullptr;
	}

	if (Player->GetName() != InPlayerName)
	{
		return nullptr;
	}

	return Player;
}

EErrorCode FLoginSession::ChangeLoginInfo(const FAccountName& InAccountName, FPlayer Ininfo)
{
	auto It = PlayerMap.find(InAccountName);

	// 로그인 하지 않았다
	if (It == PlayerMap.end())
	{
		return EErrorCode::ENoLogin;
	}

	It->second = Ininfo;
	return EErrorCode::ESuccessed;
}

void FLoginSession::AllAccountLogout()
{
	const std::unordered_map<FAccountName, FAccount>& Accounts = FDataBase::Get()->GetAccounts();

	for (auto It = Accounts.begin(); It != Accounts.end();)
	{
		auto TargetPlayer = PlayerMap.find(It->first);
		if (TargetPlayer == PlayerMap.end())
		{
			_ASSERT(false);
			++It;
			continue;
		}

		auto TargetAccount = It;
		++It;
		
		Logout(TargetAccount->second, TargetPlayer->second.GetName());
	}
}
