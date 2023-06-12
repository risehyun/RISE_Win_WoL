#pragma once
#include <GameEngineCore/GameEngineActor.h>



class UI_KeyboardF : public GameEngineActor
{
public:
	UI_KeyboardF();
	~UI_KeyboardF();

	UI_KeyboardF(const UI_KeyboardF& _Other) = delete;
	UI_KeyboardF(UI_KeyboardF&& _Other) noexcept = delete;
	UI_KeyboardF& operator=(const UI_KeyboardF& _Other) = delete;
	UI_KeyboardF& operator=(UI_KeyboardF&& _Other) noexcept = delete;


	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* GetMainRenderer() const;


protected:

private:
	void Start() override;
	void Update(float _Delta) override;

};