#pragma once
#include "Item.h"

class ITEM_VampiresEyeglasses : public Item
{
private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* DescriptRenerer = nullptr;
};