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


	GameEngineRenderer* Index0 = nullptr;

	GameEngineRenderer* Index1 = nullptr;

	GameEngineRenderer* Index2 = nullptr;

	GameEngineRenderer* Index3 = nullptr;


	GameEngineRenderer* Relic_Index0 = nullptr;

	GameEngineRenderer* Relic_Index1 = nullptr;

	GameEngineRenderer* Relic_Frame0 = nullptr;

	GameEngineRenderer* Relic_Frame1 = nullptr;

	bool IsOpened = false;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};