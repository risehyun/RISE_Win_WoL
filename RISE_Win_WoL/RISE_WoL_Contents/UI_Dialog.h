#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Dialog : public GameEngineActor
{
public:
	UI_Dialog();
	~UI_Dialog();

	UI_Dialog(const UI_Dialog& _Other) = delete;
	UI_Dialog(UI_Dialog&& _Other) noexcept = delete;
	UI_Dialog& operator=(const UI_Dialog& _Other) = delete;
	UI_Dialog& operator=(UI_Dialog&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* GetMainRenderer() const
	{
		return MainRenderer;
	}


protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};