#include "Monster_Swordman.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>


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

		// �ؽ�ó �ε��� �Բ� �ִϸ��̼��� ���� ��Ʈ ����
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SWORDMAN_LEFT.bmp"), 6, 5);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SWORDMAN_RIGHT.bmp"), 6, 5);
	}

	{
		MainRenderer = CreateRenderer("SWORDMAN_TEST.bmp", RenderOrder::Play);
		MainRenderer->SetRenderScale({ 150, 150 });
		MainRenderer->SetTexture("SWORDMAN_TEST.bmp");



		// �ִϸ��̼� ����
		// IDLE
		MainRenderer->CreateAnimation("Left_Idle", "SWORDMAN_LEFT.bmp", 0, 0, 0.1f, true);

		MainRenderer->CreateAnimation("Right_Idle", "SWORDMAN_RIGHT.bmp", 0, 0, 0.1f, true);

		// MOVE
		MainRenderer->CreateAnimation("Left_Move", "SWORDMAN_LEFT.bmp", 6, 11, 0.1f, true);

		MainRenderer->CreateAnimation("Right_Move", "SWORDMAN_RIGHT.bmp", 6, 11, 0.1f, true);

		MainRenderer->ChangeAnimation("Right_Idle");

	}

	// �浹ü ����
	GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
}

void Monster_Swordman::Update(float _Delta)
{
	// ���� ���ĺ��� �÷��̾ �ѾƼ� �̵�
	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	Dir.Normalize();

	MainRenderer->ChangeAnimation("Right_Move");

	AddPos(Dir * _Delta * 100.0f);
}

void Monster_Swordman::Render(float _Delta)
{


}

void Monster_Swordman::StateUpdate(float _Delta)
{
}

void Monster_Swordman::IdleStart()
{
}

void Monster_Swordman::RunStart()
{
}

void Monster_Swordman::AttackStart()
{
}

void Monster_Swordman::IdleUpdate(float _Delta)
{
}

void Monster_Swordman::RunUpdate(float _Delta)
{
}

void Monster_Swordman::AttackUpdate(float _Delta)
{
}

void Monster_Swordman::ChanageState(MonsterState State)
{
}