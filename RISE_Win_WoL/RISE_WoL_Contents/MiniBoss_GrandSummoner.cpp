#include "MiniBoss_GrandSummoner.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Player.h"

#include "MiniBoss_GrandSummoner_Fireball.h"

#include "ContentsEnum.h"

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

	// �ִϸ��̼� ����
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

	// �浹ü ����
	BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 140, 200 });
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

	if (!(m_iCurHp <= 0))
	{
		// �÷��̾��� ��ų�� �ڽ��� ���� �浹�ϸ� ������ ���·� ��ȯ
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

				if (m_iCurHp <= 0)
				{
					DirCheck();
					ChangeState(MiniBossState::Death);
				}

				else
				{
					DirCheck();
					ChangeState(MiniBossState::Damage);

					// �����ʿ�
					Actor->Death();
				}

			}
		}


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

	// �÷��̾��� ��ġ�� üũ�Ѵ�.
	float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

	if (AllFireball.size() == 0)
	{
		// ������
		if (DirDeg.AngleDeg() > 315.0f && DirDeg.AngleDeg() < 360.0f || DirDeg.AngleDeg() > 0.0f && DirDeg.AngleDeg() < 45.0f)
		{
			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 40.0f, GetPos().Y });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index8");
				NewFireball->SetDir(float4::RIGHT);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 10.0f, GetPos().Y - 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index5");
				NewFireball->SetDir(float4::RIGHT);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 10.0f, GetPos().Y + 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index11");
				NewFireball->SetDir(float4::RIGHT);
				AllFireball.push_back(NewFireball);


			}

			AttackIndex = 0;

		}

		// �Ʒ���
		if (DirDeg.AngleDeg() > 45.0f && DirDeg.AngleDeg() < 135.0f)
		{
			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X, GetPos().Y + 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index13");
				NewFireball->SetDir(float4::DOWN);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y + 20.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index15");
				NewFireball->SetDir(float4::DOWN);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X + 10.0f, GetPos().Y + 20.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index11");
				NewFireball->SetDir(float4::DOWN);
				AllFireball.push_back(NewFireball);
			}

			AttackIndex = 1;

		}


		// ����
		if (DirDeg.AngleDeg() > 135.0f && DirDeg.AngleDeg() < 225.0f)
		{
			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 40.0f, GetPos().Y });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index0");
				NewFireball->SetDir(float4::LEFT);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y - 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index3");
				NewFireball->SetDir(float4::LEFT);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y + 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index13");
				NewFireball->SetDir(float4::LEFT);
				AllFireball.push_back(NewFireball);
			}

			AttackIndex = 2;
		}



		// ��
		if (DirDeg.AngleDeg() > 225.0f && DirDeg.AngleDeg() < 315.0f)
		{
			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X, GetPos().Y - 40.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index4");
				NewFireball->SetDir(float4::UP);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
				NewFireball->SetPos(float4{ GetPos().X - 10.0f, GetPos().Y - 20.0f });
				NewFireball->GetMainRenderer()->ChangeAnimation("ATTACK_Index2");
				NewFireball->SetDir(float4::UP);
				AllFireball.push_back(NewFireball);
			}

			{
				MiniBoss_GrandSummoner_Fireball* NewFireball = GetLevel()->CreateActor<MiniBoss_GrandSummoner_Fireball>();
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
	// ���� Define���� ����
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