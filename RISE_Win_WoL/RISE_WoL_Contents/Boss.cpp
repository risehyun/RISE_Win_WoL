#include "Boss.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"

#include "Player.h"
#include "EFFECT_RedCastingCircle.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>


Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Start()
{
	SetInitStat();

	if (false == ResourcesManager::GetInst().IsLoadTexture("BOSS_LEFT.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\Boss");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BOSS_LEFT.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BOSS_LEFT.bmp"), 9, 6);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("RedCastingCircle.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RedCastingCircle.bmp"));
	}


	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetRenderScale({ 150, 200 });
	MainRenderer->CreateAnimation("Left_Idle", "BOSS_LEFT.bmp", 0, 0, 0.1f, true);
	MainRenderer->CreateAnimation("Left_Jump", "BOSS_LEFT.bmp", 27, 28, 0.2f, false);
	MainRenderer->CreateAnimation("Left_JumpAir", "BOSS_LEFT.bmp", 29, 30, 0.2f, false);
	MainRenderer->CreateAnimation("Left_JumpFall", "BOSS_LEFT.bmp", 31, 32, 0.5f, false);
	MainRenderer->CreateAnimation("Left_JumpGround", "BOSS_LEFT.bmp", 33, 34, 0.5f, false);
	MainRenderer->ChangeAnimation("Left_Idle");
	MainRenderer->SetRenderPos({ 0,0 });


	//TestRenderer = CreateRenderer();
	//TestRenderer->SetRenderScale({ 200, 200 });
	//TestRenderer->SetTexture("RedCastingCircle.bmp");
	//TestRenderer->SetRenderPos({ 0.0f, 0.0f });


}

void Boss::Update(float _Delta)
{
	float4 playerPos = Player::GetMainPlayer()->GetPos();
	float4 Dir = playerPos - GetPos();


	Dir.Normalize();



	float4 MovePos;

	if (true == GameEngineInput::IsPress('P'))
	{
		EFFECT_RedCastingCircle* NewCircle = GetLevel()->CreateActor<EFFECT_RedCastingCircle>();

		NewCircle->GetMainRenderer()->SetRenderPos({ playerPos });

		if (GetLiveTime() < 4.0f)
		{

			AddPos(float4::UP * 100.0f * _Delta);

			MainRenderer->ChangeAnimation("Left_Jump");
		}

		if (GetLiveTime() > 2.0f && GetLiveTime() < 4.0f)
		{
			MainRenderer->ChangeAnimation("Left_JumpAir");

			AddPos((float4::UP + float4::LEFT) * 50.0f * _Delta);
		}

		if (GetLiveTime() > 4.0f && GetLiveTime() < 5.0f)
		{
			MainRenderer->ChangeAnimation("Left_JumpFall");
			
			AddPos(Dir * _Delta * 100.0f);
		}

		if (GetLiveTime() > 5.0f)
		{
			MainRenderer->ChangeAnimation("Left_JumpGround");

			AddPos(Dir * _Delta * 100.0f);
		}


	}
	//Dir.Normalize();

	//AddPos(Dir * _Delta * 100.0f);
//	MainRenderer->SetRenderPos();

}

void Boss::Render(float _Delta)
{

}

void Boss::SetInitStat()
{
	// 이후 Define으로 변경
	m_fMoveSpeed = 100.0f;
	m_fAttackSpeed = 100.0f;
	m_iMaxHp = 100;
	m_iCurHp = m_iMaxHp;
	m_fAttackRange = 100.0f;
}

void Boss::OnDamaged(int _iAttackPower)
{
	m_iCurHp -= _iAttackPower;

	if (DamageRenderer == nullptr)
	{
		DamageRenderer = CreateRenderer(RenderOrder::Play);
		DamageRenderer->SetRenderPos({ 0, -100 });
		DamageRenderer->SetRenderScale({ 200, 40 });
	}

	DamageRenderer->SetText(std::to_string(_iAttackPower), 20);
	DamageRenderer->On();
}

void Boss::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossState::Idle:
		IdleUpdate(_Delta);
		break;

	case BossState::Run:
		RunUpdate(_Delta);
		break;

	case BossState::NormalAttack:
		AttackUpdate(_Delta);
		break;

	case BossState::Damage:
		DamageUpdate(_Delta);
		break;

	case BossState::Death:
		DeathUpdate(_Delta);
		break;
	}
}


#pragma region State Start
void Boss::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Boss::RunStart()
{
	ChangeAnimationState("Move");
}

void Boss::AttackStart()
{
	ChangeAnimationState("Attack");
}

void Boss::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Boss::DeathStart()
{
	ChangeAnimationState("Death");
}

#pragma endregion


#pragma region Start Update
void Boss::IdleUpdate(float _Delta)
{
}

void Boss::RunUpdate(float _Delta)
{
}

void Boss::AttackUpdate(float _Delta)
{
}

void Boss::DamageUpdate(float _Delta)
{
}

void Boss::DeathUpdate(float _Delta)
{
}

#pragma endregion

void Boss::ChangeState(BossState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BossState::Idle:
			IdleStart();
			break;

		case BossState::Run:
			RunStart();
			break;

		case BossState::NormalAttack:
			AttackStart();
			break;

		case BossState::Damage:
			DamageStart();
			break;

		case BossState::Death:
			DeathStart();
			break;

		default:
			break;
		}
	}

	State = _State;
}

void Boss::DirCheck()
{
	float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

	if (DirDeg.AngleDeg() > 90 && DirDeg.AngleDeg() < 270)
	{
		Dir = MonsterDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	else
	{
		Dir = MonsterDir::Right;
		ChangeAnimationState(CurState);
		return;
	}
}


void Boss::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case MonsterDir::Right:
		AnimationName = "Right_";
		break;

	case MonsterDir::Left:
		AnimationName = "Left_";
		break;

	default:
		break;
	}

	AnimationName += _StateName;
	CurState = _StateName;
	MainRenderer->ChangeAnimation(AnimationName);
}
