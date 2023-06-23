#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_SkillBar : public GameEngineActor
{
public:
	UI_SkillBar();
	~UI_SkillBar();

	UI_SkillBar(const UI_SkillBar& _Other) = delete;
	UI_SkillBar(UI_SkillBar&& _Other) noexcept = delete;
	UI_SkillBar& operator=(const UI_SkillBar& _Other) = delete;
	UI_SkillBar& operator=(UI_SkillBar&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* GetMainRenderer() const;


protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};

