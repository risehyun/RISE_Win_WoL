#pragma once
#include "Skill.h"

class SKILL_PlayerNormalAttack : public Skill
{

public:
	class GameEngineRenderer* Renderer;


	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

private:
	float4 Dir;
	float Speed = 500.0f;

	void Start() override;
	void Update(float _Delta) override;

};

