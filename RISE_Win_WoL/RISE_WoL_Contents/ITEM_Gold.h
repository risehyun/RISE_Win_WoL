#pragma once
#include "Item.h"

class ITEM_Gold : public Item
{
private:
	void Start() override;
	void Update(float _Delta) override;
};
