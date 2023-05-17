#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Arcana : public GameEngineActor
{
public:
	Arcana();
	~Arcana();

	Arcana(const Arcana& _Other) = delete;
	Arcana(Arcana&& _Other) noexcept = delete;
	Arcana& operator=(const Arcana& _Other) = delete;
	Arcana& operator=(Arcana&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer;

	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

protected:

private:
	float4 Dir;
	float Speed = 500.0f;

	void Start() override;
	void Update(float _Delta) override;
};