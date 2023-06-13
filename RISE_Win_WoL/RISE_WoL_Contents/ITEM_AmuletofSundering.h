#pragma once
#include "Item.h"

class ITEM_AmuletofSundering : public Item
{

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* DescriptRenerer = nullptr;
};

