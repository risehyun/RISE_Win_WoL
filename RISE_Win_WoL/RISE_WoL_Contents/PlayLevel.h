#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "BossSpawner.h"
#include "Effect_CastingCircle.h"
#include "PROP_TreasureChestMiniBoss.h"
#include "PROP_Teleport.h"


class Player;
class PlayLevel : public GameEngineLevel
{
public:
	PlayLevel();
	~PlayLevel();

	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	class BackGround* BackGroundPtr;
//	class Player* LevelPlayer = nullptr;

	GameEngineSoundPlayer BGMPlayer;

	BossSpawner* Spawner;

	Effect_CastingCircle* NewEffect;
	PROP_TreasureChestMiniBoss* NewChest;
	PROP_Teleport* NewTeleport;


	int LevelState = -1;

};