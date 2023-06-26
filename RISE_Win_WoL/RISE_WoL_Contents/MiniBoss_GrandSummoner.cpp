#include "MiniBoss_GrandSummoner.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"

MiniBoss_GrandSummoner::MiniBoss_GrandSummoner()
{
	

}

MiniBoss_GrandSummoner::~MiniBoss_GrandSummoner()
{
}

void MiniBoss_GrandSummoner::DirCheck()
{
}

void MiniBoss_GrandSummoner::ChangeAnimationState(const std::string& _StateName)
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
	BodyCollsion->SetCollisionScale({ 80, 300 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);


	MainRenderer->ChangeAnimation("Left_Idle");
}

void MiniBoss_GrandSummoner::Update(float _Delta)
{
}

void MiniBoss_GrandSummoner::Render(float _Delta)
{
}

void MiniBoss_GrandSummoner::SetInitStat()
{
}

void MiniBoss_GrandSummoner::OnDamaged(int _iAttackPower)
{
}

void MiniBoss_GrandSummoner::StateUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::IdleStart()
{
}

void MiniBoss_GrandSummoner::RunStart()
{
}

void MiniBoss_GrandSummoner::AttackStart()
{
}

void MiniBoss_GrandSummoner::DamageStart()
{
}

void MiniBoss_GrandSummoner::DeathStart()
{
}

void MiniBoss_GrandSummoner::IdleUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::RunUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::AttackUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::DamageUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::DeathUpdate(float _Delta)
{
}

void MiniBoss_GrandSummoner::ChangeState(MonsterState _State)
{
}
