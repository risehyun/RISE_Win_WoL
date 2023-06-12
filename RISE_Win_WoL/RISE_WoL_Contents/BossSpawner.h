#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_KeyboardF.h"

class BossSpawner : public GameEngineActor
{
	friend GameEngineActor;

public:
	BossSpawner();
	~BossSpawner();

	BossSpawner(const BossSpawner& _Other) = delete;
	BossSpawner(BossSpawner&& _Other) noexcept = delete;
	BossSpawner& operator=(const BossSpawner& _Other) = delete;
	BossSpawner& operator=(BossSpawner&& _Other) noexcept = delete;

	class UI_KeyboardF* m_InteractUI;

	GameEngineRenderer* Renderer_Altar;
	GameEngineRenderer* Renderer_ActivationCircle;
	
//	GameEngineRenderer* InputRenderer;

	GameEngineRenderer* Renderer_FenceUp;
	GameEngineRenderer* Renderer_FenceDown;
	GameEngineRenderer* Renderer_FenceRight;
	GameEngineRenderer* Renderer_FenceLeft;

	GameEngineCollision* Collsion_Altar;
	GameEngineCollision* Collsion_ActivationCircle;

	GameEngineCollision* Collsion_FenceUp;
	GameEngineCollision* Collsion_FenceDown;
	GameEngineCollision* Collsion_FenceRight;
	GameEngineCollision* Collsion_FenceLeft;

private:
	void Start() override;
	void Update(float _Delta) override;


};