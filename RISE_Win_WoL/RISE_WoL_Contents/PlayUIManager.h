#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayUIManager : public GameEngineActor
{
public:
	static PlayUIManager* UI;

public:
	PlayUIManager();
	~PlayUIManager();

	PlayUIManager(const PlayUIManager& _Other) = delete;
	PlayUIManager(PlayUIManager&& _Other) noexcept = delete;
	PlayUIManager& operator=(const PlayUIManager& _Other) = delete;
	PlayUIManager& operator=(PlayUIManager&& _Other) noexcept = delete;

	GameEngineCollision* ButtonCollsion = nullptr;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MousePtr = nullptr;
};