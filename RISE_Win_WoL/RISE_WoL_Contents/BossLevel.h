#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class BossLevel : public GameEngineLevel
{
public:
	BossLevel();
	~BossLevel();

	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator=(const BossLevel& _Other) = delete;
	BossLevel& operator=(BossLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;

};