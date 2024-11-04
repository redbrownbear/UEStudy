#pragma once
#include "Misc/Headers.h"

enum EMenuEvent : uint8_t
{
	ETerminate = 0,

	ECreateRandomItem,
	ECreateCustomItem,
	EDeleteItem,
	EClearInventory,

	EPrintInventory,

	ETakeOnItem,
	ETakeOffItem,

	EPrintEquip,
};

class CMainTool : public CSingleton<CMainTool>
{	
public:
	CMainTool();
	~CMainTool();

public:

public:
	void RUN();

private:
	void Init();
	void Delete();

private:
};

