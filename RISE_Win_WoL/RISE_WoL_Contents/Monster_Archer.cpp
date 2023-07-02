#include "Monster_Archer.h"

#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

#include "SKILL_ArcherBow.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "BossSpawner.h"

#include "UI_DamageText.h"

Monster_Archer::Monster_Archer()
{
}

Monster_Archer::~Monster_Archer()
{
}

void Monster_Archer::Start()
{
	SetInitStat();

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCHER_LEFT.Bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCHER_LEFT.bmp"), 6, 5);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCHER_RIGHT.Bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCHER_RIGHT.bmp"), 6, 5);
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetRenderScale({ 150, 150 });

	// 애니메이션 설정
	// IDLE
	MainRenderer->CreateAnimation("Left_Idle", "ARCHER_LEFT.bmp", 0, 0, 1.0f, true);
	MainRenderer->CreateAnimation("Right_Idle", "ARCHER_RIGHT.bmp", 0, 0, 1.0f, true);

	// MOVE
	MainRenderer->CreateAnimation("Left_Move", "ARCHER_LEFT.bmp", 6, 10, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Move", "ARCHER_RIGHT.bmp", 6, 10, 0.1f, true);

	// ATTACK
	MainRenderer->CreateAnimation("Left_ATTACK", "ARCHER_LEFT.bmp", 12, 15, 0.4f, false);
	MainRenderer->CreateAnimation("Right_ATTACK", "ARCHER_RIGHT.bmp", 12, 15, 0.4f, false);

	// DAMAGE
	MainRenderer->CreateAnimation("Left_Damage", "ARCHER_LEFT.bmp", 18, 19, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Damage", "ARCHER_RIGHT.bmp", 18, 19, 0.5f, false);

	// DEATH
	MainRenderer->CreateAnimation("Left_Death", "ARCHER_LEFT.bmp", 24, 29, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Death", "ARCHER_RIGHT.bmp", 24, 29, 0.1f, false);

	// 충돌체 설정
	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale({ 150, 150 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);

	// 공격 범위 충돌체 설정
	AttackRangeCollision = CreateCollision(CollisionOrder::MonsterAttackRange);
	AttackRangeCollision->SetCollisionScale({ 600, 600 });
	AttackRangeCollision->SetCollisionType(CollisionType::CirCle);

	ChangeState(MonsterState::Idle);
}

void Monster_Archer::Update(float _Delta)
{
	DirCheck();

	if (!(m_iCurHp <= 0))
	{

		AttackRangeCollision->CollisionCallBack
		(
			CollisionOrder::PlayerBody
			, CollisionType::CirCle // _this의 충돌체 타입
			, CollisionType::CirCle // _Other의 충돌체 타입
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

				GameEngineActor* thisActor = _this->GetActor();
				Monster_Archer* MonsterPtr = dynamic_cast<Monster_Archer*>(thisActor);

				MonsterPtr->ChangeState(MonsterState::Attack);



			}
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

				GameEngineActor* thisActor = _this->GetActor();
				Monster_Archer* MonsterPtr = dynamic_cast<Monster_Archer*>(thisActor);

			}
				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				Monster_Archer* MonsterPtr = dynamic_cast<Monster_Archer*>(thisActor);

				MonsterPtr->ChangeState(MonsterState::Idle);
			}


			);

		BodyCollision->CollisionCallBack
		(
			CollisionOrder::PlayerSkill
			, CollisionType::CirCle // _this의 충돌체 타입
			, CollisionType::CirCle // _Other의 충돌체 타입
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

				GameEngineActor* thisActor = _this->GetActor();
				Monster_Archer* MonsterPtr = dynamic_cast<Monster_Archer*>(thisActor);

				GameEngineActor* Actor = _Other->GetActor();

				MonsterPtr->OnDamaged(Actor->GetAttackPower());

				if (MonsterPtr->m_iCurHp < 0)
				{
					MonsterPtr->ChangeState(MonsterState::Death);
				}

				else
				{
					MonsterPtr->ChangeState(MonsterState::Damage);
				}

			}
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

			}
				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				Monster_Archer* MonsterPtr = dynamic_cast<Monster_Archer*>(thisActor);

				if (MonsterPtr->m_iCurHp > 0)
				{
					MonsterPtr->ChangeState(MonsterState::Idle);
				}

				else
				{
					MonsterPtr->ChangeState(MonsterState::Death);
				}
			}


			);

	}

	else
	{
		ChangeState(MonsterState::Death);

	}


	StateUpdate(_Delta);
}

void Monster_Archer::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;

		case MonsterState::Run:
			RunStart();
			break;

		case MonsterState::Attack:
			AttackStart();
			break;

		case MonsterState::Damage:
			DamageStart();
			break;

		case MonsterState::Death:
			DeathStart();
			break;

		default:
			break;
		}
	}

	State = _State;
}

void Monster_Archer::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		IdleUpdate(_Delta);
		break;

	case MonsterState::Run:
		RunUpdate(_Delta);
		break;

	case MonsterState::Attack:
		AttackUpdate(_Delta);
		break;

	case MonsterState::Damage:
		DamageUpdate(_Delta);
		break;

	case MonsterState::Death:
		DeathUpdate(_Delta);
		break;
	}
}

void Monster_Archer::IdleStart()
{
	if (NewBow != nullptr)
	{
		NewBow->Death();
		NewBow = nullptr;
	}

	ChangeAnimationState("Idle");
}

void Monster_Archer::RunStart()
{
	if (NewBow != nullptr)
	{
		NewBow->Death();
		NewBow = nullptr;
	}

	ChangeAnimationState("Move");
}

void Monster_Archer::AttackStart()
{
	ChangeAnimationState("Attack");
}

void Monster_Archer::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Monster_Archer::DeathStart()
{
	ChangeAnimationState("Death");
}

void Monster_Archer::IdleUpdate(float _Delta)
{
	DirCheck();


	float4 fPosDis = GetPos() - Player::GetMainPlayer()->GetPos();


	float fLength = fPosDis.Size();

	if (fLength > 300.0f)
	{

		fPosDis *= -1.0f;
		ChangeAnimationState("Move");

	}

	AddPos(fPosDis * _Delta);

}

void Monster_Archer::RunUpdate(float _Delta)
{
}

void Monster_Archer::AttackUpdate(float _Delta)
{

	if (1.0f < GetLiveTime())
	{
		float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

		// 위
		if (DirDeg.AngleDeg() >= 258.75f && DirDeg.AngleDeg() < 281.25f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX0");


			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, -20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX0");
		}

		else if (DirDeg.AngleDeg() >= 281.25f && DirDeg.AngleDeg() < 303.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX1");


			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });


			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX1");
		}

		else if (DirDeg.AngleDeg() >= 303.75f && DirDeg.AngleDeg() < 326.25f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX2");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX2");
		}

		else if (DirDeg.AngleDeg() >= 326.25f && DirDeg.AngleDeg() < 348.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX3");


			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX3");
		}



		else if (DirDeg.AngleDeg() >= 11.25f && DirDeg.AngleDeg() < 33.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX4");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX4");
		}

		else if (DirDeg.AngleDeg() >= 33.75f && DirDeg.AngleDeg() < 56.25f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX5");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX5");
		}

		else if (DirDeg.AngleDeg() >= 56.25f && DirDeg.AngleDeg() < 78.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX6");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX6");
		}

		else if (DirDeg.AngleDeg() >= 78.75f && DirDeg.AngleDeg() < 101.25f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX7");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX7");
		}

		else if (DirDeg.AngleDeg() >= 101.25f && DirDeg.AngleDeg() < 123.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX8");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX8");
		}

		else if (DirDeg.AngleDeg() >= 123.75f && DirDeg.AngleDeg() < 146.25f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX9");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX9");
		}

		else if (DirDeg.AngleDeg() >= 146.25f && DirDeg.AngleDeg() < 168.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX10");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX10");
		}

		else if (DirDeg.AngleDeg() >= 168.75f && DirDeg.AngleDeg() < 191.25f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX11");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX11");
		}

		else if (DirDeg.AngleDeg() >= 191.25f && DirDeg.AngleDeg() < 213.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX12");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX12");
		}


		else if (DirDeg.AngleDeg() >= 213.75f && DirDeg.AngleDeg() < 236.25f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX13");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX13");
		}

		else if (DirDeg.AngleDeg() >= 236.25f && DirDeg.AngleDeg() < 258.75f)
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SkillRenderer->SetRenderPos(GetPos() - NewBow->GetPos());
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX14");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX14");
		}

		else
		{
			NewBow = GetLevel()->CreateActor<SKILL_ArcherBow>();
			NewBow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });
			NewBow->SkillRenderer->ChangeAnimation("Arrow_INDEX15");

			SKILL_ArcherAttack* NewArrow = GetLevel()->CreateActor<SKILL_ArcherAttack>();
			NewArrow->SetPos(GetPos() + float4{ 0.0f, 20.0f, 0.0f, 0.0f });

			NewArrow->SetDir(DirDeg);
			NewArrow->SkillRenderer->ChangeAnimation("ArrowShot_INDEX15");
		}


		ResetLiveTime();

	}


}

void Monster_Archer::DamageUpdate(float _Delta)
{
	if (true == IsDeath()) {
		DirCheck();
		ChangeState(MonsterState::Death);
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		DirCheck();
		ChangeState(MonsterState::Run);
	}
}

void Monster_Archer::DeathUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		--BossSpawner::MonsterCount;
		Death();
	}
}

void Monster_Archer::DirCheck()
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

void Monster_Archer::ChangeAnimationState(const std::string& _StateName)
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

void Monster_Archer::Render(float _Delta)
{

}

void Monster_Archer::SetInitStat()
{
	// 이후 Define으로 변경
	m_fMoveSpeed = 100.0f;
	m_fAttackSpeed = 100.0f;
	m_iMaxHp = 100;
	m_iCurHp = m_iMaxHp;
	m_fAttackRange = 100.0f;
}

void Monster_Archer::OnDamaged(int _iAttackPower)
{
	m_iCurHp -= _iAttackPower;

	UI_DamageText* NewText = GetLevel()->CreateActor<UI_DamageText>();

	float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

	if ((DirDeg.AngleDeg() > 0 && DirDeg.AngleDeg() < 45)
		|| (DirDeg.AngleDeg() > 315 && DirDeg.AngleDeg() < 360))
	{
		NewText->SetDir(float4::LEFT);
	}

	else if (DirDeg.AngleDeg() > 225 && DirDeg.AngleDeg() < 316)
	{
		NewText->SetDir(float4::LEFT);
	}

	else if (DirDeg.AngleDeg() > 135 && DirDeg.AngleDeg() < 225)
	{
		NewText->SetDir(float4::RIGHT);
	}

	else if (DirDeg.AngleDeg() > 44 && DirDeg.AngleDeg() < 135)
	{
		NewText->SetDir(float4::RIGHT);
	}

	NewText->GetMainRenderer()->SetText(std::to_string(_iAttackPower), 20, "Noto Sans Med");
	NewText->SetPos({ GetPos().X, GetPos().Y - 100.0f });
}