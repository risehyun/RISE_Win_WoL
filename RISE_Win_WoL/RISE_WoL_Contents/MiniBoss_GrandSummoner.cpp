#include "MiniBoss_GrandSummoner.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Player.h"

#include "SKILL_MiniBoss_GrandSummoner_Fireball.h"
#include "SKILL_MiniBoss_GrandSummoner_Magicball.h"

#include "ContentsEnum.h"
#include "BossSpawner.h"

MiniBoss_GrandSummoner::MiniBoss_GrandSummoner()
{


}

MiniBoss_GrandSummoner::~MiniBoss_GrandSummoner()
{

}

void MiniBoss_GrandSummoner::Start()
{
	SetInitStat();

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\Monster\\MiniBoss\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("MiniBoss_GrandSummoner_Left.Bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MiniBoss_GrandSummoner_Left.bmp"), 4, 6);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("MiniBoss_GrandSummoner_Right.Bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MiniBoss_GrandSummoner_Right.bmp"), 4, 6);
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetRenderScale({ 140, 200 });

	// 애니메이션 설정
	// IDLE
	MainRenderer->CreateAnimation("Left_Idle", "MiniBoss_GrandSummoner_Left.bmp", 0, 0, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Idle", "MiniBoss_GrandSummoner_Right.bmp", 0, 0, 0.1f, true);

	// MOVE
	MainRenderer->CreateAnimation("Left_Move", "MiniBoss_GrandSummoner_Left.bmp", 4, 7, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Move", "MiniBoss_GrandSummoner_Right.bmp", 4, 7, 0.1f, true);

	// ATTACK
	MainRenderer->CreateAnimation("Left_ATTACK", "MiniBoss_GrandSummoner_Left.bmp", 8, 11, 0.4f, false);
	MainRenderer->CreateAnimation("Right_ATTACK", "MiniBoss_GrandSummoner_Right.bmp", 8, 11, 0.4f, false);

	// DAMAGE
	MainRenderer->CreateAnimation("Left_Damage", "MiniBoss_GrandSummoner_Left.bmp", 16, 17, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Damage", "MiniBoss_GrandSummoner_Right.bmp", 16, 17, 0.1f, false);

	// DEATH
	MainRenderer->CreateAnimation("Left_Death", "MiniBoss_GrandSummoner_Left.bmp", 20, 23, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Death", "MiniBoss_GrandSummoner_Right.bmp", 20, 23, 0.1f, true);

	// 충돌체 설정
	BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);

	MainRenderer->ChangeAnimation("Left_Idle");

	ChangeState(MiniBossState::Idle);
}

void MiniBoss_GrandSummoner::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('T'))
	{
		ChangeState(MiniBossState::Skill_Fireball);
	}

	if (true == GameEngineInput::IsDown('Y'))
	{
		ChangeState(MiniBossState::Skill_MagicOrbWallRush);
	}

	if (true == GameEngineInput::IsDown('U'))
	{
		ChangeState(MiniBossState::Skill_MagicOrbAssault);
	}

	if (!(m_iCurHp <= 0))
	{
		BodyCollsion->CollisionCallBack
		(
			CollisionOrder::PlayerSkill
			, CollisionType::CirCle // _this의 충돌체 타입
			, CollisionType::CirCle // _Other의 충돌체 타입
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

				GameEngineActor* thisActor = _this->GetActor();
				MiniBoss_GrandSummoner* MonsterPtr = dynamic_cast<MiniBoss_GrandSummoner*>(thisActor);

				GameEngineActor* Actor = _Other->GetActor();

				MonsterPtr->OnDamaged(Actor->GetAttackPower());

				if (MonsterPtr->m_iCurHp <= 0)
				{
					MonsterPtr->ChangeState(MiniBossState::Death);
				}

				else
				{
					MonsterPtr->ChangeState(MiniBossState::Damage);
				}

			}
		);


	}

	DirCheck();

	StateUpdate(_Delta);
}

void MiniBoss_GrandSummoner::ChangeState(MiniBossState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MiniBossState::Idle:
			IdleStart();
			break;

		case MiniBossState::Skill_Fireball:
			Skill_Fireball_Start();
			break;

		case MiniBossState::Skill_MagicOrbWallRush:
			Skill_MagicOrbWallRush_Start();
			break;

		case MiniBossState::Skill_MagicOrbAssault:
			Skill_MagicOrbAssault_Start();
			break;

		case MiniBossState::Damage:
			DamageStart();
			break;

		case MiniBossState::Death:
			DeathStart();
			break;

		default:
			break;
		}
	}

	State = _State;

}

void MiniBoss_GrandSummoner::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MiniBossState::Idle:
		IdleUpdate(_Delta);
		break;

	case MiniBossState::Skill_Fireball:
		Skill_Fireball_Update(_Delta);
		break;

	case MiniBossState::Skill_MagicOrbWallRush:
		Skill_MagicOrbWallRush_Update(_Delta);
		break;

	case MiniBossState::Skill_MagicOrbAssault:
		Skill_MagicOrbAssault_Update(_Delta);
		break;

	case MiniBossState::Damage:
		DamageUpdate(_Delta);
		break;

	case MiniBossState::Death:
		DeathUpdate(_Delta);
		break;
	}
}

void MiniBoss_GrandSummoner::DirCheck()
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

void MiniBoss_GrandSummoner::IdleStart()
{
	ChangeAnimationState("Idle");
}

void MiniBoss_GrandSummoner::RunStart()
{
	ChangeAnimationState("Move");
}

void MiniBoss_GrandSummoner::Skill_Fireball_Start()
{
	ChangeAnimationState("Attack");
}

void MiniBoss_GrandSummoner::Skill_MagicOrbWallRush_Start()
{
	ChangeAnimationState("Attack");
	DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();
}

void MiniBoss_GrandSummoner::Skill_MagicOrbAssault_Start()
{
	ChangeAnimationState("Attack");
}

void MiniBoss_GrandSummoner::DamageStart()
{
	ChangeAnimationState("Damage");
}

void MiniBoss_GrandSummoner::DeathStart()
{
	ChangeAnimationState("Death");
}

void MiniBoss_GrandSummoner::IdleUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::RunUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::Skill_Fireball_Update(float _Delta)
{
	// 플레이어의 위치를 체크한다.
	float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

	if (AllFireball.size() == 0)
	{
		// 오른쪽
		if (DirDeg.AngleDeg() > 315.0f && DirDeg.AngleDeg() < 360.0f || DirDeg.AngleDeg() > 0.0f && DirDeg.AngleDeg() < 45.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 40.0f, GetPos().Y });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index8");
				NewFireball->SetDir(float4::RIGHT);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 10.0f, GetPos().Y - 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index5");
				NewFireball->SetDir(float4::RIGHT);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 10.0f, GetPos().Y + 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index11");
				NewFireball->SetDir(float4::RIGHT);
				AllFireball.push_back(NewFireball);


			}

			AttackIndex = 0;

		}

		// 아래쪽
		if (DirDeg.AngleDeg() > 45.0f && DirDeg.AngleDeg() < 135.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X, GetPos().Y + 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index13");
				NewFireball->SetDir(float4::DOWN);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y + 20.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index15");
				NewFireball->SetDir(float4::DOWN);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 10.0f, GetPos().Y + 20.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index11");
				NewFireball->SetDir(float4::DOWN);
				AllFireball.push_back(NewFireball);
			}

			AttackIndex = 1;

		}


		// 왼쪽
		if (DirDeg.AngleDeg() > 135.0f && DirDeg.AngleDeg() < 225.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 40.0f, GetPos().Y });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index0");
				NewFireball->SetDir(float4::LEFT);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y - 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index3");
				NewFireball->SetDir(float4::LEFT);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y + 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index13");
				NewFireball->SetDir(float4::LEFT);
				AllFireball.push_back(NewFireball);
			}

			AttackIndex = 2;
		}



		// 위
		if (DirDeg.AngleDeg() > 225.0f && DirDeg.AngleDeg() < 315.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X, GetPos().Y - 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index4");
				NewFireball->SetDir(float4::UP);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y - 20.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index2");
				NewFireball->SetDir(float4::UP);
				AllFireball.push_back(NewFireball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 10.0f, GetPos().Y - 20.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index6");
				NewFireball->SetDir(float4::UP);
				AllFireball.push_back(NewFireball);
			}

			AttackIndex = 3;

		}


	}

	if (AttackIndex == 0)
	{
		for (size_t i = 0; i < AllFireball.size(); i++)
		{
			NextPos = AllFireball[i]->GetDir() * _Delta * Speed;

			if (i == 1)
			{
				NextPos.Y -= 0.5;
			}

			else if (i == 2)
			{
				NextPos.Y += 0.5;
			}

			AllFireball[i]->AddPos(NextPos);
		}
	}

	else if (AttackIndex == 1)
	{

		for (size_t i = 0; i < AllFireball.size(); i++)
		{
			NextPos = AllFireball[i]->GetDir() * _Delta * Speed;

			if (i == 1)
			{
				NextPos.X -= 0.5;
			}

			else if (i == 2)
			{
				NextPos.X += 0.5;
			}

			AllFireball[i]->AddPos(NextPos);
		}
	}

	else if (AttackIndex == 2)
	{

		for (size_t i = 0; i < AllFireball.size(); i++)
		{
			NextPos = AllFireball[i]->GetDir() * _Delta * Speed;

			if (i == 1)
			{
				NextPos.Y -= 0.5;
			}

			else if (i == 2)
			{
				NextPos.Y += 0.5;
			}

			AllFireball[i]->AddPos(NextPos);
		}
	}

	else if (AttackIndex == 3)
	{

		for (size_t i = 0; i < AllFireball.size(); i++)
		{
			NextPos = AllFireball[i]->GetDir() * _Delta * Speed;

			if (i == 1)
			{
				NextPos.X -= 0.5;
			}

			else if (i == 2)
			{
				NextPos.X += 0.5;
			}

			AllFireball[i]->AddPos(NextPos);
		}
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MiniBossState::Idle);
		AllFireball.clear();
	}

}

void MiniBoss_GrandSummoner::Skill_MagicOrbWallRush_Update(float _Delta)
{
	if (AllMagicball.size() == 0)
	{
		// 0
		if (DirDeg.AngleDeg() > 270.0f && DirDeg.AngleDeg() < 360.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 120.0f, GetPos().Y - 80.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 80.0f, GetPos().Y - 40.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			// 중심
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 40.0f, GetPos().Y });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X, GetPos().Y + 40.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 40.0f, GetPos().Y + 80.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 80.0f, GetPos().Y + 120.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			for (size_t i = 0; i < AllMagicball.size(); i++)
			{
				Speed = 800.0f;
				NextPos = AllMagicball[i]->GetDir() * _Delta * Speed;

				AllMagicball[i]->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index13");

				NextPos.Y -= 0.5;
				NextPos.X += 1.5;

			}

		}

		// 1
		if (DirDeg.AngleDeg() > 0.0f && DirDeg.AngleDeg() < 90.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 120.0f, GetPos().Y + 80.0f });
				NewMagicball->SetDir(float4::RIGHT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 80.0f, GetPos().Y + 40.0f });
				NewMagicball->SetDir(float4::RIGHT);
				AllMagicball.push_back(NewMagicball);
			}

			// 중심
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 40.0f, GetPos().Y });
				NewMagicball->SetDir(float4::RIGHT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X, GetPos().Y - 40.0f });
				NewMagicball->SetDir(float4::RIGHT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 40.0f, GetPos().Y - 80.0f });
				NewMagicball->SetDir(float4::RIGHT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 80.0f, GetPos().Y - 120.0f });
				NewMagicball->SetDir(float4::RIGHT);
				AllMagicball.push_back(NewMagicball);
			}


			for (size_t i = 0; i < AllMagicball.size(); i++)
			{
				Speed = 800.0f;
				NextPos = AllMagicball[i]->GetDir() * _Delta * Speed;

				AllMagicball[i]->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index1");

				NextPos.Y += 0.5;
				NextPos.X += 0.5;
			}

		}

		// 2
		if (DirDeg.AngleDeg() > 90.0f && DirDeg.AngleDeg() < 180.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 120.0f, GetPos().Y + 80.0f });
				NewMagicball->SetDir(float4::LEFT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 80.0f, GetPos().Y + 40.0f });
				NewMagicball->SetDir(float4::LEFT);
				AllMagicball.push_back(NewMagicball);
			}

			// 중심
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 40.0f, GetPos().Y });
				NewMagicball->SetDir(float4::LEFT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X, GetPos().Y - 40.0f });
				NewMagicball->SetDir(float4::LEFT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 40.0f, GetPos().Y - 80.0f });
				NewMagicball->SetDir(float4::LEFT);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 80.0f, GetPos().Y - 120.0f });
				NewMagicball->SetDir(float4::LEFT);
				AllMagicball.push_back(NewMagicball);
			}

			for (size_t i = 0; i < AllMagicball.size(); i++)
			{
				Speed = 800.0f;
				NextPos = AllMagicball[i]->GetDir() * _Delta * Speed;

				AllMagicball[i]->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index6");

				NextPos.Y += 0.5;
				NextPos.X -= 0.5;

			}
		}

		// 3
		if (DirDeg.AngleDeg() > 180.0f && DirDeg.AngleDeg() < 270.0f)
		{
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 120.0f, GetPos().Y - 80.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 80.0f, GetPos().Y - 40.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			// 중심
			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X + 40.0f, GetPos().Y });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X, GetPos().Y + 40.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 40.0f, GetPos().Y + 80.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			{
				SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicball = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
				NewMagicball->SetPos(float4{ GetPos().X - 80.0f, GetPos().Y + 120.0f });
				NewMagicball->SetDir(float4::UP);
				AllMagicball.push_back(NewMagicball);
			}

			for (size_t i = 0; i < AllMagicball.size(); i++)
			{
				Speed = 800.0f;
				NextPos = AllMagicball[i]->GetDir() * _Delta * Speed;

				AllMagicball[i]->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index10");

				NextPos.Y -= 0.5;
				NextPos.X -= 1.5;

			}

		}

	}

	else
	{
		for (size_t i = 0; i < AllMagicball.size(); i++)
		{
			AllMagicball[i]->AddPos(NextPos);
		}

	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		AllMagicball.clear();
		ChangeState(MiniBossState::Idle);
	}

}

void MiniBoss_GrandSummoner::Skill_MagicOrbAssault_Update(float _Delta)
{

	if (AllMagicorb.size() == 0)
	{
		// 0
		{
			SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicOrb = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
			NewMagicOrb->SetPos(float4{ GetPos().X, GetPos().Y - 300.0f });
			NewMagicOrb->SetDir(float4::DOWN);
			NewMagicOrb->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index4");
			AllMagicorb.push_back(NewMagicOrb);
		}

		// 1
		{
			SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicOrb = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
			NewMagicOrb->SetPos(float4{ GetPos().X + 200.0f, GetPos().Y - 200.0f });
			NewMagicOrb->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index6");
			NewMagicOrb->SetDir(float4::DOWN);
			AllMagicorb.push_back(NewMagicOrb);
		}

		// 2
		{
			SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicOrb = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
			NewMagicOrb->SetPos(float4{ GetPos().X + 300, GetPos().Y });
			NewMagicOrb->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index8");
			NewMagicOrb->SetDir(float4::LEFT);
			AllMagicorb.push_back(NewMagicOrb);
		}


		// 3
		{
			SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicOrb = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
			NewMagicOrb->SetPos(float4{ GetPos().X + 100.0f, GetPos().Y + 200.0f });
			NewMagicOrb->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index10");
			NewMagicOrb->SetDir(float4::UP);
			AllMagicorb.push_back(NewMagicOrb);
		}

		// 4
		{
			SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicOrb = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
			NewMagicOrb->SetPos(float4{ GetPos().X - 100.0f, GetPos().Y + 200.0f });
			NewMagicOrb->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index14");
			NewMagicOrb->SetDir(float4::UP);
			AllMagicorb.push_back(NewMagicOrb);
		}

		// 5
		{
			SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicOrb = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
			NewMagicOrb->SetPos(float4{ GetPos().X - 300, GetPos().Y });
			NewMagicOrb->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index0");
			NewMagicOrb->SetDir(float4::RIGHT);
			AllMagicorb.push_back(NewMagicOrb);
		}


		// 6
		{
			SKILL_MiniBoss_GrandSummoner_Magicball* NewMagicOrb = GetLevel()->CreateActor<SKILL_MiniBoss_GrandSummoner_Magicball>();
			NewMagicOrb->SetPos(float4{ GetPos().X - 200, GetPos().Y - 200.0f });
			NewMagicOrb->GetMainRenderer()->ChangeAnimation("MagicBall_ATTACK_Index2");
			NewMagicOrb->SetDir(float4::DOWN);
			AllMagicorb.push_back(NewMagicOrb);
		}

	}

	else
	{
		for (size_t i = 0; i < AllMagicorb.size(); i++)
		{
			if (AllMagicorb[i] == nullptr)
			{
				continue;
			}

			Speed = 200.0f;

			NextPos = AllMagicorb[i]->GetDir() * _Delta * Speed;

			if (i == 0)
			{
				
				NextPos.Y += 0.5f;
			}

			else if (i == 1)
			{
				
				NextPos.X -= 0.7f;
				NextPos.Y += 0.1f;
			}

			else if (i == 2)
			{
			
				NextPos.X -= 0.5f;
			}

			else if (i == 3)
			{
				
				NextPos.X -= 0.4f;
				NextPos.Y -= 0.1f;
			}

			else if (i == 4)
			{
				
				NextPos.X += 0.4f;
				NextPos.Y -= 0.1f;
			}

			else if (i == 5)
			{
				NextPos.X += 0.5f;
			}

			else if (i == 6)
			{
				NextPos.X += 0.7f;
				NextPos.Y += 0.1f;
			}

			AllMagicorb[i]->AddPos(NextPos * 2.0f);

		}
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		AllMagicorb.clear();
		ChangeState(MiniBossState::Idle);
	}
}

void MiniBoss_GrandSummoner::DamageUpdate(float _Delta)
{
	if (true == IsDeath()) {
		DirCheck();
		ChangeState(MiniBossState::Death);
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		//		DamageRenderer->Off();
		DirCheck();
		ChangeState(MiniBossState::Idle);
	}

}

void MiniBoss_GrandSummoner::DeathUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		--BossSpawner::MonsterCount;
		Death();
	}
}

void MiniBoss_GrandSummoner::ChangeAnimationState(const std::string& _StateName)
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

void MiniBoss_GrandSummoner::Render(float _Delta)
{

}

void MiniBoss_GrandSummoner::SetInitStat()
{
	// 이후 Define으로 변경
	m_fMoveSpeed = 100.0f;
	m_fAttackSpeed = 100.0f;
	m_iMaxHp = 100;
	m_iCurHp = m_iMaxHp;
	m_fAttackRange = 100.0f;
}

void MiniBoss_GrandSummoner::OnDamaged(int _iAttackPower)
{
	m_iCurHp -= _iAttackPower;
}
