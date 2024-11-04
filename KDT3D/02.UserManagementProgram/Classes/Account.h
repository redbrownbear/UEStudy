#pragma once
#include "Misc/Headers.h"

using FAccountName = std::string;

class FAccount
{
public:

	std::string ID;
	std::string Password;

	FAccount() = default;
	FAccount(std::string_view InID, std::string_view InPassword)
		: ID(InID)
		, Password(InPassword) {}

	//둘 중 하나라도 비어 있으면 true
	bool IsEmpty() const
	{
		const bool bID = ID.empty();
		const bool bPassword = Password.empty();

		return bID || bPassword;
	}

	bool operator==(const FAccount& InAccount) const
	{
		const bool bEmpty = IsEmpty();
		if (bEmpty) { return false; }

		const bool bID = ID == InAccount.ID;
		const bool bPassword = Password == InAccount.Password;

		return bID && bPassword;
	}
	bool operator!=(const FAccount& InAccount) const
	{
		return !(*this == InAccount);
	}

};

