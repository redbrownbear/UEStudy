#pragma once
#include "Classes/Account.h"
#include "Classes/Player.h"

class FLoginSession
{
	friend struct FLogoutTask;

public:
	static FLoginSession* Get(const bool bDestry = false);

public:
	FPlayer* Login(const FAccount& InAccount, std::string_view InPlayerName, EErrorCode* const OptionalOutErrorCode);
	EErrorCode Logout(const FAccount& InAccount, std::string_view InPlayerName);

	FPlayer* IsLogin(const FAccountName& InAccountName);
	FPlayer* IsLogin(const FAccountName& InAccountName, std::string_view InPlayerName);

	EErrorCode ChangeLoginInfo(const FAccountName& InAccountName, FPlayer Ininfo);
	
	void AllAccountLogout();

	const std::unordered_map<FAccountName, FPlayer>& GetPlayers() const { return PlayerMap; }

private:
	EErrorCode Logout(const FAccount& InAccount);

public:
	~FLoginSession();

private:
	FLoginSession() {}
	FLoginSession(const FLoginSession&) = delete;
	FLoginSession& operator=(const FLoginSession&) = delete;

private:
	std::unordered_map<FAccountName, FPlayer> PlayerMap;
};

