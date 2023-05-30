#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Button : public GameEngineActor
{
public:
	UI_Button();
	~UI_Button();

	UI_Button(const UI_Button& _Other) = delete;
	UI_Button(UI_Button&& _Other) noexcept = delete;
	UI_Button& operator=(const UI_Button& _Other) = delete;
	UI_Button& operator=(UI_Button&& _Other) noexcept = delete;

	GameEngineCollision* Collision = nullptr;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

};

