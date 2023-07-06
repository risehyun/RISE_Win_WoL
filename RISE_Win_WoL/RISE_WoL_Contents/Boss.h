#pragma once
#include "Monster.h"
#include <vector>

#include "SKILL_Boss_AncientEarthDrill.h"
#include "SKILL_Boss_TowersofTerra.h"

class Boss : public Monster
{
public:
	Boss();
	~Boss();

	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;


	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* AttackRangeCollision = nullptr;

	GameEngineRenderer* TestRenderer = nullptr;
	GameEngineRenderer* MainRenderer = nullptr;

	std::vector<SKILL_Boss_TowersofTerra*> Towers;

	GameEngineRenderer* GetMainRenderer()
	{
		return MainRenderer;
	}

	int GetCurHp() const
	{
		return m_iCurHp;
	}


	float cooldown = 2.0f;
	float currentCooldown = 0.0f;

	void UpdateCooldown(float deltaTime)
	{
		if (currentCooldown > 0)
		{
			currentCooldown -= deltaTime;
		}
	}

	bool IsReady()
	{
		return currentCooldown <= 0;
	}

protected:
	void StateUpdate(float _Delta);

	void IdleStart();

	void Skill_SeismicSlam_Start();
	void Skill_AncientEarthDrill_Start();
	void Skill_TowersofTerra_Start();

	void DamageStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DamageUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	void Skill_SeismicSlam_Update(float _Delta);
	void Skill_AncientEarthDrill_Update(float _Delta);
	void Skill_TowersofTerra_Update(float _Delta);

	BossState State = BossState::Max;

	BossDir Dir = BossDir::Left;
	std::string CurState = "";

	GameEngineCollision* BodyCollsion = nullptr;


	void DirCheck();
	void ChangeAnimationState(const std::string & _StateName);
	void ChangeState(BossState _State);

private:
	GameEngineSoundPlayer EffectPlayer;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



	void SetInitStat() override;
	void OnDamaged(int _iAttackPower) override;

	float4 DirDeg;
	SKILL_Boss_AncientEarthDrill* NewAttack;



	///// 아이템 드롭 테스트용
	//void DropItem(float4 _DropPos);


	//////////////////////// DebugValue
	float4 LeftCheck = { -50.0f, 0.0f };
	float4 RightCheck = { 50.0f, 0.0f };
	float4 UpCheck = { 0.0f, -50.0f };
	float4 DownCheck = { 0.0f, 50.0f };

	//float fDamageRendererDuration = 0;

};