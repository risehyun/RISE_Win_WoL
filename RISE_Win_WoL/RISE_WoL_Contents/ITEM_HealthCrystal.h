#pragma once
#include "Item.h"
#include <vector>
#include "ITEM_HPBall.h"

class ITEM_HealthCrystal : public Item
{
private:
	void Start() override;
	void Update(float _Delta) override;

	std::vector<ITEM_HPBall*> HpBall;
};