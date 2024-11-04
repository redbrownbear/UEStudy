#pragma once
#include "Misc/Headers.h"
#include "Classes/Account.h"

class FPlayer
{
public:
	FPlayer(std::string_view InAccountName, std::string_view InName, const int InLevel)
		: AccountName(InAccountName)
		, Name(InName)
		, Level(InLevel) {}

	std::string_view GetAccountName() const { return AccountName; }
	std::string_view GetName() const { return Name; }
	int GetLevel() const { return Level; }
	void SetLevel(int InLevel) { Level = InLevel; }

	void OnLogout();

public:
	void Save(rapidjson::Value& OutValue, rapidjson::Document::AllocatorType& InAllocator);
	bool Load(const rapidjson::Value& InValue);

private:
	FAccountName AccountName;
	std::string Name;
	int Level;
};