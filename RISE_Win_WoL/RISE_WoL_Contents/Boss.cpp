#include "Boss.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"

#include "Player.h"
#include "EFFECT_RedCastingCircle.h"

#include "SKILL_Boss_AncientEarthDrill.h"
#include "SKILL_Boss_TowersofTerra.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineBase/GameEngineMath.h>

#include <GameEnginePlatform/GameEngineInput.h>

#include <vector>

Boss::Boss()
{
}

Boss::~Boss()
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

void Boss::DirCheck()
{
	float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

	if (DirDeg.AngleDeg() > 90 && DirDeg.AngleDeg() < 270)
	{
		Dir = BossDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	else
	{
		Dir = BossDir::Right;
		ChangeAnimationState(CurState);
		return;
	}
}

void Boss::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case BossDir::Right:
		AnimationName = "Right_";
		break;

	case BossDir::Left:
		AnimationName = "Left_";
		break;

	default:
		break;
	}

	AnimationName += _StateName;
	CurState = _StateName;
	MainRenderer->ChangeAnimation(AnimationName);
}

void Boss::Start()
{
	SetInitStat();

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\Monster\\Boss");

	if (false == ResourcesManager::GetInst().IsLoadTexture("BOSS_LEFT.Bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BOSS_LEFT.bmp"), 9, 6);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("BOSS_RIGHT.Bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BOSS_RIGHT.bmp"), 9, 6);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("BOSS_ATTACK.Bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BOSS_ATTACK.bmp"), 6, 4);
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetRenderScale({ 150, 200 });

	MainRenderer->CreateAnimation("Left_Idle", "BOSS_LEFT.bmp", 0, 0, 0.1f, true);
	MainRenderer->CreateAnimation("Left_Jump", "BOSS_LEFT.bmp", 27, 28, 0.2f, false);
	MainRenderer->CreateAnimation("Left_JumpAir", "BOSS_LEFT.bmp", 29, 30, 0.2f, false);
	MainRenderer->CreateAnimation("Left_JumpFall", "BOSS_LEFT.bmp", 31, 32, 0.5f, false);
	MainRenderer->CreateAnimation("Left_JumpGround", "BOSS_LEFT.bmp", 33, 34, 0.5f, false);
	MainRenderer->CreateAnimation("Left_Damage", "BOSS_LEFT.bmp", 36, 37, 0.5f, false);
	MainRenderer->CreateAnimation("Left_Death", "BOSS_LEFT.bmp", 45, 46, 0.5f, false);

	MainRenderer->CreateAnimation("Right_Idle", "BOSS_RIGHT.bmp", 0, 0, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Jump", "BOSS_RIGHT.bmp", 27, 28, 0.2f, false);
	MainRenderer->CreateAnimation("Right_JumpAir", "BOSS_RIGHT.bmp", 29, 30, 0.2f, false);
	MainRenderer->CreateAnimation("Right_JumpFall", "BOSS_RIGHT.bmp", 31, 32, 0.5f, false);
	MainRenderer->CreateAnimation("Right_JumpGround", "BOSS_RIGHT.bmp", 33, 34, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Damage", "BOSS_RIGHT.bmp", 36, 37, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Death", "BOSS_RIGHT.bmp", 45, 46, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Attack", "BOSS_ATTACK.bmp", 0, 5, 0.2f, false);
	MainRenderer->CreateAnimation("Right_Attack", "BOSS_ATTACK.bmp", 6, 11, 0.2f, false);
	MainRenderer->CreateAnimation("Up_Attack", "BOSS_ATTACK.bmp", 12, 17, 0.2f, false);
	MainRenderer->CreateAnimation("Down_Attack", "BOSS_ATTACK.bmp", 18, 23, 0.2f, false);


	BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);

	MainRenderer->ChangeAnimation("Left_Idle");
	MainRenderer->SetOrder(1);

}

void Boss::Update(float _Delta)
{
	float TickTime = 0.0f;

	if (GameEngineInput::IsDown('Y'))
	{
		ChangeState(BossState::Skill_SeismicSlam);
	}


	if (GameEngineInput::IsDown('T'))
	{
		ChangeState(BossState::Skill_AncientEarthDrill);
	}


	if (GameEngineInput::IsDown('U'))
	{
		ChangeState(BossState::Skill_TowersofTerra);
	}

	if (!(m_iCurHp <= 0))
	{

		// 플레이어의 스킬과 자신의 몸이 충돌하면 데미지 상태로 전환
		std::vector<GameEngineCollision*> _Col;
		if (true == BodyCollsion->Collision(CollisionOrder::PlayerSkill, _Col
			, CollisionType::CirCle
			, CollisionType::CirCle
		))
		{
			for (size_t i = 0; i < _Col.size(); i++)
			{
				GameEngineCollision* Collison = _Col[i];

				GameEngineActor* Actor = Collison->GetActor();

				OnDamaged(Actor->GetAttackPower());


				if (m_iCurHp > 0)
				{
					ChangeState(BossState::Damage);
					// 수정필요
					Actor->Death();
				}

				else
				{
					DirCheck();
					ChangeState(BossState::Death);
				}

			}
		}
	}

	StateUpdate(_Delta);
}

void Boss::Render(float _Delta)
{

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



#pragma region State Start
void Boss::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Boss::Skill_SeismicSlam_Start()
{
	ChangeAnimationState("Jump");
}

void Boss::Skill_AncientEarthDrill_Start()
{
	DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();
	NewAttack = GetLevel()->CreateActor<SKILL_Boss_AncientEarthDrill>();
	ChangeAnimationState("Attack");
}

void Boss::Skill_TowersofTerra_Start()
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

void Boss::AttackUpdate(float _Delta)
{
}

void Boss::DamageUpdate(float _Delta)
{

	if (true == IsDeath()) {
		//	DirCheck();
		ChangeState(BossState::Death);
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		DamageRenderer->Off();
		//	DirCheck();
		ChangeState(BossState::Idle);
	}

}

void Boss::DeathUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
	}
}

void Boss::Skill_SeismicSlam_Update(float _Delta)
{
	float4 TargetPos = Player::GetMainPlayer()->GetPos();

	static float TickTime = 0.0f;
	static float FallY = 0.0f;
	static float StartY = 0.0f;

	//// **TODO : 처음에 시작 위치를 기억해서 스폰한 뒤, 다음 스테이트로 넘어가게 만들도록 수정
	////float4 CirclePos = TargetPos - GetPos();
	////TestRenderer->SetRenderPos({ CirclePos });
	TickTime += _Delta;


	if (TickTime < 0.4f)
	{
		MainRenderer->ChangeAnimation("Left_Jump");
	}

	if (TickTime > 0.4f && TickTime < 0.8f)
	{
		FallY = TargetPos.Y;
		StartY = TargetPos.Y - 200.0f;

		float fT = TickTime / 0.2f;
		SetPos(float4{ TargetPos.X, (StartY * (1.f - fT) + (StartY - 100.0f) * fT) });


		MainRenderer->ChangeAnimation("Left_JumpAir");

		return;
	}

	if (TickTime > 0.8f)
	{
		if (GetPos().Y < FallY)
		{
			AddPos(float4::DOWN);
			MainRenderer->ChangeAnimation("Left_JumpFall");
		}

		MainRenderer->ChangeAnimation("Left_JumpGround");

		if (true == MainRenderer->IsAnimationEnd())
		{
			ChangeState(BossState::Idle);
			TickTime = 0.0f;
		}
	}
}

void Boss::Skill_AncientEarthDrill_Update(float _Delta)
{
	float Speed = 500.0f;

	float4 MovePos = float4::ZERO;



	if ((DirDeg.AngleDeg() > 0 && DirDeg.AngleDeg() < 45)
		|| (DirDeg.AngleDeg() > 315 && DirDeg.AngleDeg() < 360))
	{

		NewAttack->SetDir(float4::RIGHT);
		NewAttack->SetPos(GetPos() + float4{ 100.0f, 0.0f, 0.0f, 0.0f });
		NewAttack->SkillRenderer->ChangeAnimation("AncientEarthDrill_RIGHT");
		MainRenderer->ChangeAnimation("Up_Attack");
		MovePos = { Speed * _Delta, 0.0f };

		AddPos(MovePos);

		if (true == MainRenderer->IsAnimationEnd())
		{
			NewAttack->Death();
			ChangeState(BossState::Idle);
		}
	}

	if (DirDeg.AngleDeg() > 225 && DirDeg.AngleDeg() < 316)
	{

		NewAttack->SetDir(float4::RIGHT);
		NewAttack->SetPos(GetPos() + float4{ 0.0f, -100.0f, 0.0f, 0.0f });
		NewAttack->SkillRenderer->ChangeAnimation("AncientEarthDrill_UP");
		MainRenderer->ChangeAnimation("Right_Attack");
		MovePos = { 0.0f, -Speed * _Delta };

		AddPos(MovePos);

		if (true == MainRenderer->IsAnimationEnd())
		{
			NewAttack->Death();
			ChangeState(BossState::Idle);
		}
	}

	if (DirDeg.AngleDeg() > 135 && DirDeg.AngleDeg() < 225)
	{

		NewAttack->SetDir(float4::LEFT);
		NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
		NewAttack->SkillRenderer->ChangeAnimation("AncientEarthDrill_LEFT");
		MainRenderer->ChangeAnimation("Left_Attack");
		MovePos = { -Speed * _Delta, 0.0f };

		AddPos(MovePos);

		if (true == MainRenderer->IsAnimationEnd())
		{
			NewAttack->Death();
			ChangeState(BossState::Idle);
		}
	}

	if (DirDeg.AngleDeg() > 44 && DirDeg.AngleDeg() < 135)
	{

		NewAttack->SetDir(float4::LEFT);
		NewAttack->SetPos(GetPos() + float4{ 0.0f, 100.0f, 0.0f, 0.0f });
		NewAttack->SkillRenderer->ChangeAnimation("AncientEarthDrill_DOWN");
		MainRenderer->ChangeAnimation("Down_Attack");
		MovePos = { 0.0f, Speed * _Delta };

		AddPos(MovePos);

		if (true == MainRenderer->IsAnimationEnd())
		{
			NewAttack->Death();
			ChangeState(BossState::Idle);
		}
	}
}

void Boss::Skill_TowersofTerra_Update(float _Delta)
{
	// 오른쪽
	for (size_t i = 0; i < 6; i++)
	{

		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();

		NewTower->SetOrder(-5500);

		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X + 200.0f, GetPos().Y });
		}

		else
		{
			NewTower->SetPos({ GetPos().X + 200.0f + 100.0f * i + 1, GetPos().Y });
		}

		Towers.push_back(NewTower);
	}

	// 오른쪽 위
	for (size_t i = 0; i < 3; i++)
	{

		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();
		NewTower->SetOrder(-1000);

		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X + 100.0f, GetPos().Y - 100.0f });
		}
		 
		else
		{
			NewTower->SetPos({ GetPos().X + 100.0f * i + 1, GetPos().Y - 100.0f * i + 1 });
		}

		Towers.push_back(NewTower);
	}

	// 오른쪽 아래
	for (size_t i = 0; i < 3; i++)
	{
		
		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();
		NewTower->SetOrder(-1000);

		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X + 100.0f, GetPos().Y + 100.0f});
		}

		else
		{
			NewTower->SetPos({ GetPos().X + 100.0f * i + 1, GetPos().Y + 100.0f * i + 1 });
		}

		Towers.push_back(NewTower);
	}

	// 아래
	for (size_t i = 0; i < 1; i++)
	{

		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();

		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X, GetPos().Y + 200.0f });
		}

		else
		{
			NewTower->SetPos({ GetPos().X, GetPos().Y + 200.0f * i + 1 });
		}

		Towers.push_back(NewTower);
	}

	// 위
	for (size_t i = 0; i < 1; i++)
	{

		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();

		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X, GetPos().Y - 200.0f });
		}

		else
		{
			NewTower->SetPos({ GetPos().X, GetPos().Y - 200.0f * i + 1 });
		}

		Towers.push_back(NewTower);
	}

	// 왼쪽
	for (size_t i = 0; i < 6; i++)
	{

		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();

		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X - 200.0f, GetPos().Y });
		}

		else
		{
			NewTower->SetPos({ GetPos().X - 200.0f - 100.0f * i + 1, GetPos().Y });
		}

		Towers.push_back(NewTower);
	}

	// 왼쪽 아래
	for (size_t i = 0; i < 3; i++)
	{

		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();
		NewTower->SetOrder(-5500);
		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X - 100.0f, GetPos().Y + 100.0f });
		}

		else
		{
			NewTower->SetPos({ GetPos().X - 100.0f * i + 1, GetPos().Y + 100.0f * i + 1 });
		}

		Towers.push_back(NewTower);
	}

	// 왼쪽 위
	for (size_t i = 0; i < 3; i++)
	{

		SKILL_Boss_TowersofTerra* NewTower = GetLevel()->CreateActor<SKILL_Boss_TowersofTerra>();
		NewTower->SetOrder(-5500);
		if (i == 0)
		{
			NewTower->SetPos({ GetPos().X - 100.0f, GetPos().Y - 100.0f });
		}

		else
		{
			NewTower->SetPos({ GetPos().X - 100.0f * i + 1, GetPos().Y - 100.0f * i + 1 });
		}

		Towers.push_back(NewTower);
	}


	ChangeState(BossState::Idle);

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

		case BossState::Skill_SeismicSlam:
			Skill_SeismicSlam_Start();
			break;

		case BossState::Skill_AncientEarthDrill:
			Skill_AncientEarthDrill_Start();
			break;

		case BossState::Skill_TowersofTerra:
			Skill_TowersofTerra_Start();
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

void Boss::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossState::Idle:
		IdleUpdate(_Delta);
		break;

	case BossState::Skill_SeismicSlam:
		Skill_SeismicSlam_Update(_Delta);
		break;

	case BossState::Skill_AncientEarthDrill:
		Skill_AncientEarthDrill_Update(_Delta);
		break;

	case BossState::Skill_TowersofTerra:
		Skill_TowersofTerra_Update(_Delta);
		break;

	case BossState::Damage:
		DamageUpdate(_Delta);
		break;

	case BossState::Death:
		DeathUpdate(_Delta);
		break;
	}
}


