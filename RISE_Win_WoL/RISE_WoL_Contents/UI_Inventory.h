#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Inventory : public GameEngineActor
{
public:
	UI_Inventory();
	~UI_Inventory();

	UI_Inventory(const UI_Inventory& _Other) = delete;
	UI_Inventory(UI_Inventory&& _Other) noexcept = delete;
	UI_Inventory& operator=(const UI_Inventory& _Other) = delete;
	UI_Inventory& operator=(UI_Inventory&& _Other) noexcept = delete;


	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* GetMainRenderer() const;


	GameEngineRenderer* OutFitRenderer = nullptr;

	GameEngineRenderer* DescriptRenderer = nullptr;

	GameEngineRenderer* Index1 = nullptr;

	




protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};