#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Effect_Spawn : public GameEngineActor
{
public:
	Effect_Spawn();
	~Effect_Spawn();

	Effect_Spawn(const Effect_Spawn& _Other) = delete;
	Effect_Spawn(Effect_Spawn&& _Other) noexcept = delete;
	Effect_Spawn& operator=(const Effect_Spawn& _Other) = delete;
	Effect_Spawn& operator=(Effect_Spawn&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* Renderer;

private:
	void Start() override;
	void Update(float _Delta) override;
};

