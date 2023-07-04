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


	GameEngineRenderer* Cooldown_Panel = nullptr;

	GameEngineRenderer* Cooldown_Panel_WhirlingTornado = nullptr;



	GameEngineRenderer* Cooldown_Text = nullptr;

	GameEngineRenderer* Cooldown_Text_WhirlingTornado = nullptr;

	int CoolTime_ExplodingFireball = 0;

	int CoolTime_WhirlingTornado = 0;


protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};

