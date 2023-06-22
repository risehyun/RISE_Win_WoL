#include "Monster_Swordman.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "SKILL_KnightAttack.h"


// 아이템 드롭 테스트용
#include "ITEM_Gold.h"

Monster_Swordman::Monster_Swordman()
{

}

Monster_Swordman::~Monster_Swordman()
{

}

void Monster_Swordman::DirCheck()
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

void Monster_Swordman::ChangeAnimationState(const std::string& _StateName)
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

void Monster_Swordman::LevelStart()
{

}

void Monster_Swordman::Start()
{
	SetInitStat();

	if (false == ResourcesManager::GetInst().IsLoadTexture("SWORDMAN_TEST.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("SWORDMAN_TEST.bmp"));

		// 텍스처 로딩과 함께 애니메이션을 위한 시트 분할
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SWORDMAN_LEFT.bmp"), 6, 5);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SWORDMAN_RIGHT.bmp"), 6, 5);
	}

	{
		MainRenderer = CreateRenderer("SWORDMAN_TEST.bmp", RenderOrder::Play);
		MainRenderer->SetRenderScale({ 150, 150 });
		MainRenderer->SetTexture("SWORDMAN_TEST.bmp");



		// 애니메이션 설정
		// IDLE
		MainRenderer->CreateAnimation("Left_Idle", "SWORDMAN_LEFT.bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "SWORDMAN_RIGHT.bmp", 0, 0, 0.1f, true);

		// MOVE
		MainRenderer->CreateAnimation("Left_Move", "SWORDMAN_LEFT.bmp", 6, 11, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Move", "SWORDMAN_RIGHT.bmp", 6, 11, 0.1f, true);

		// ATTACK
		MainRenderer->CreateAnimation("Left_ATTACK", "SWORDMAN_LEFT.bmp", 12, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_ATTACK", "SWORDMAN_RIGHT.bmp", 12, 14, 0.1f, false);

		// DAMAGE
		MainRenderer->CreateAnimation("Left_Damage", "SWORDMAN_LEFT.bmp", 18, 19, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Damage", "SWORDMAN_RIGHT.bmp", 18, 19, 0.1f, true);

		// DEATH
		MainRenderer->CreateAnimation("Left_Death", "SWORDMAN_LEFT.bmp", 24, 28, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Death", "SWORDMAN_RIGHT.bmp", 24, 28, 0.1f, true);

		if (nullptr == GameEngineSound::FindSound("ENEMY_DIED.mp3"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("ENEMY_DIED.mp3"));
		}

		if (nullptr == GameEngineSound::FindSound("ENEMY_HITTED.mp3"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("ENEMY_HITTED.mp3"));
		}

	}

	// 충돌체 설정
	BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
}

void Monster_Swordman::Update(float _Delta)
{

	if (!(m_iCurHp <= 0))
	{

		// 플레이어와 자신의 몸이 충돌하면 공격 상태로 전환
		std::vector<GameEngineCollision*> _ColTest;
		if (true == BodyCollsion->Collision(CollisionOrder::PlayerBody, _ColTest
			, CollisionType::CirCle
			, CollisionType::CirCle
		))
		{
			DirCheck();
			ChangeState(MonsterState::Attack);
		}

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

				if (m_iCurHp <= 0)
				{
					DirCheck();
					ChangeState(MonsterState::Death);
				}

				else
				{
					DirCheck();
					ChangeState(MonsterState::Damage);

					// 수정필요
					Actor->Death();
				}

			}
		}

	}

	StateUpdate(_Delta);

}

void Monster_Swordman::Render(float _Delta)
{



}

void Monster_Swordman::SetInitStat()
{
	// 이후 Define으로 변경
	m_fMoveSpeed = 100.0f;
	m_fAttackSpeed = 100.0f;
	m_iMaxHp = 100;
	m_iCurHp = m_iMaxHp;
	m_fAttackRange = 100.0f;
}

void Monster_Swordman::OnDamaged(int _AttackPower)
{
	m_iCurHp -= _AttackPower;

	if (DamageRenderer == nullptr)
	{
		DamageRenderer = CreateRenderer(RenderOrder::Play);
		DamageRenderer->SetRenderPos({ 0, -100 });
		DamageRenderer->SetRenderScale({ 200, 40 });
	}

	DamageRenderer->SetText(std::to_string(_AttackPower), 20);
	DamageRenderer->On();

}

void Monster_Swordman::DropItem(float4 _DropPos)
{
	ITEM_Gold* NewGold = GetLevel()->CreateActor<ITEM_Gold>();
	NewGold->SetPos({ _DropPos });
}

void Monster_Swordman::IdleStart()
{
//	DirCheck();
	ChangeAnimationState("Idle");
}

void Monster_Swordman::RunStart()
{
//	DirCheck();
	ChangeAnimationState("Move");
}

void Monster_Swordman::AttackStart()
{
//	DirCheck();
	ChangeAnimationState("Attack");
}

void Monster_Swordman::DamageStart()
{
//	DirCheck();
	EffectPlayer = GameEngineSound::SoundPlay("ENEMY_HITTED.mp3");
	ChangeAnimationState("Damage");
}

void Monster_Swordman::DeathStart()
{
	DropItem(GetPos());
	EffectPlayer = GameEngineSound::SoundPlay("ENEMY_DIED.mp3");
	ChangeAnimationState("Death");
}

void Monster_Swordman::IdleUpdate(float _Delta)
{

}

void Monster_Swordman::RunUpdate(float _Delta)
{

	DirCheck();

	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	Dir.Normalize();

	AddPos(Dir * _Delta * 100.0f);
}

void Monster_Swordman::AttackUpdate(float _Delta)
{
	if (1.0f < GetLiveTime())
	{
		float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

		if ((DirDeg.AngleDeg() > 0 && DirDeg.AngleDeg() < 45)
			|| (DirDeg.AngleDeg() > 315 && DirDeg.AngleDeg() < 360))
		{
			SKILL_KnightAttack* NewAttack = GetLevel()->CreateActor<SKILL_KnightAttack>();

			NewAttack->SetDir(float4::LEFT);
			NewAttack->SetPos(GetPos() + float4{ 100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->SkillRenderer->ChangeAnimation("ATTACK_RIGHT");

		}

		if (DirDeg.AngleDeg() > 225 && DirDeg.AngleDeg() < 316)
		{
			SKILL_KnightAttack* NewAttack = GetLevel()->CreateActor<SKILL_KnightAttack>();

			NewAttack->SetDir(float4::LEFT);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, -100.0f, 0.0f, 0.0f });
			NewAttack->SkillRenderer->ChangeAnimation("ATTACK_UP");
		}

		if (DirDeg.AngleDeg() > 135 && DirDeg.AngleDeg() < 225)
		{
			SKILL_KnightAttack* NewAttack = GetLevel()->CreateActor<SKILL_KnightAttack>();

			NewAttack->SetDir(float4::RIGHT);
			NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->SkillRenderer->ChangeAnimation("ATTACK_LEFT");
		}

		if (DirDeg.AngleDeg() > 44 && DirDeg.AngleDeg() < 135)
		{
			SKILL_KnightAttack* NewAttack = GetLevel()->CreateActor<SKILL_KnightAttack>();

			NewAttack->SetDir(float4::RIGHT);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, 100.0f, 0.0f, 0.0f });
			NewAttack->SkillRenderer->ChangeAnimation("ATTACK_DOWN");
		}

		ChangeState(MonsterState::Run);
		ResetLiveTime();
	}
}

void Monster_Swordman::DamageUpdate(float _Delta)
{
	if (true == IsDeath()) {
		DirCheck();
		ChangeState(MonsterState::Death);
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		DamageRenderer->Off();
		DirCheck();
		ChangeState(MonsterState::Run);
	}

}

void Monster_Swordman::DeathUpdate(float _Delta)
{
	EffectPlayer.Stop();

	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
	}

}

void Monster_Swordman::StateUpdate(float _Delta)
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

void Monster_Swordman::ChangeState(MonsterState _State)
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