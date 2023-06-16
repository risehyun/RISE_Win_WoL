#pragma once
#include "Skill.h"

class SKILL_EarthenAegis : public Skill
{
	void SetDir(const float4& _Dir)
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
	GameEngineRenderer* Renderer4 = nullptr;
	GameEngineRenderer* Renderer5 = nullptr;
	GameEngineRenderer* Renderer6 = nullptr;
	GameEngineRenderer* Renderer7 = nullptr;
	GameEngineRenderer* Renderer8 = nullptr;



	GameEngineCollision* BodyCollsion = nullptr;

private:
	float4 Dir;
	float Speed = 500.0f;

	void Start() override;
	void Update(float _Delta) override;

};

