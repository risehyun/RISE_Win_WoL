#pragma once
#include "Item.h"

class ARCANA_EarthenAegis : public Item
{

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* DescriptRenerer = nullptr;
};
