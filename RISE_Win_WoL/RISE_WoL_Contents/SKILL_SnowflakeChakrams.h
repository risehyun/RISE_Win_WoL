#pragma once
#include "Skill.h"

class SKILL_SnowflakeChakrams : public Skill
{
	void SetDir(const float4 & _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

	GameEngineRenderer* Renderer = nullptr;


	// 렌더링 테스트용 임시 객체
	GameEngineRenderer* Renderer2 = nullptr;
	GameEngineRenderer* Renderer3 = nullptr;

	GameEngineCollision* BodyCollsion = nullptr;
	GameEngineCollision* BodyCollsion2 = nullptr;
	GameEngineCollision* BodyCollsion3 = nullptr;

private:
	float4 Dir;
	float Speed = 500.0f;

	float RollAngle = 45.0f;
	float Degree;
	float4 Range;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

};

