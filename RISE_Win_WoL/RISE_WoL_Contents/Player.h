#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class PlayerState
{
	Idle,
	Run,
	Attack,
	Skill_ICEBLAST,
	Skill_EarthenAegis,
	Skill_SnowflakeChakrams,
	Dash,
	Damage,
	Death,
	Max, // default
};

enum class PlayerDir
{
	Right,
	Left,
	Up,
	Down,
	Max,
};

class Player : public PlayActor
{

private:
	static Player* MainPlayer;
public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	// 임시로 옮겨둠
	void OnDamagedStart();

	void SetTotalGold(int _GoldCount);

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();
	void DashStart();
	void AttackStart();
	void Skill_ICEBLAST_Start();
	void DeathStart();

	void Skill_EarthenAegis_Start();
	void Skill_SnowflakeChakrams_Start();


	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void DashUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void Skill_ICEBLAST_Update();
	void OnDamagedUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void Skill_EarthenAgis_Update(float _Delta);
	void Skill_SnowflakeChakrams_Update(float _Delta);


	void ChanageState(PlayerState State);

	PlayerState State = PlayerState::Max;

	PlayerDir Dir = PlayerDir::Right;
	std::string CurState = "";

	int TestValue = 0;

	GameEngineCollision* BodyCollsion = nullptr;

	void DirCheck();
	void ChangeAnimationState(const std::string& _StateName);

private:
	GameEngineSoundPlayer EffectPlayer;

	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void SetInitStat() override;
	void OnDamaged(int _iAttackPower) override;

	// Stat
	float	m_fDashSpeed = 0.0f;
	
	int		m_iMaxMp = 0;
	int		m_iCurMp = 0;
	int		m_iTotalGold = 0;
	int		m_iTotalCrystal = 0;


	////////////////////// DebugValue
	float4 LeftCheck = { -50.0f, 0.0f };
	float4 RightCheck = { 50.0f, 0.0f };
	float4 UpCheck = { 0.0f, -50.0f };
	float4 DownCheck = { 0.0f, 50.0f };




	float RunningTime = 0.0f;






	float fRadian = 0.0f;
};