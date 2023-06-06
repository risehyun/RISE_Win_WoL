#include "Monster_Swordman.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "SKILL_KnightAttack.h"

Monster_Swordman::Monster_Swordman()
{

}

Monster_Swordman::~Monster_Swordman()
{

}

void Monster_Swordman::DirCheck()
{
}

void Monster_Swordman::ChangeAnimationState(const std::string& _StateName)
{
}

void Monster_Swordman::LevelStart()
{
}

void Monster_Swordman::Start()
{
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

	
		// 시작 애니메이션
		MainRenderer->ChangeAnimation("Left_Move");

	}

	// 충돌체 설정
	BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
}

void Monster_Swordman::Update(float _Delta)
{
	//// 생성 직후부터 플레이어를 쫓아서 이동
	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	Dir.Normalize();

	AddPos(Dir * _Delta * 100.0f);

	StateUpdate(_Delta);

	std::vector<GameEngineCollision*> _ColTest;
	if (true == BodyCollsion->Collision(CollisionOrder::PlayerBody, _ColTest
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		ChanageState(MonsterState::Attack);
	}

}

void Monster_Swordman::Render(float _Delta)
{


}

void Monster_Swordman::IdleStart()
{
	MainRenderer->ChangeAnimation("Left_Idle");
}

void Monster_Swordman::RunStart()
{
	MainRenderer->ChangeAnimation("Left_Move");
}

void Monster_Swordman::AttackStart()
{
	MainRenderer->ChangeAnimation("Right_ATTACK");
}

void Monster_Swordman::IdleUpdate(float _Delta)
{

}

void Monster_Swordman::RunUpdate(float _Delta)
{

}

void Monster_Swordman::AttackUpdate(float _Delta)
{
	if (1.0f < GetLiveTime())
	{
		SKILL_KnightAttack* NewAttack = GetLevel()->CreateActor<SKILL_KnightAttack>();

		NewAttack->SetDir(float4::LEFT);
		NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
		NewAttack->SkillRenderer->ChangeAnimation("ATTACK_LEFT");

		ChanageState(MonsterState::Run);
		ResetLiveTime();
	}

	// 플레이어와 충돌할 경우

	


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

		break;

	case MonsterState::Death:

		break;
	}
}

void Monster_Swordman::ChanageState(MonsterState _State)
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
			break;

		case MonsterState::Death:
			break;

		default:
			break;
		}
	}

	State = _State;
}