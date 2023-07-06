#include "SKILL_Fireball.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "Player.h"

void SKILL_Fireball::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCANA_Fireball_Right.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_Fireball_Right.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_Fireball_Left.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_Fireball_Up.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_Fireball_Down.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_Fireball_Explosion.bmp"), 7, 1);

	}

	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 140, 100 });

	// 애니메이션 생성
	Renderer->CreateAnimation("ARCANA_Fireball_Right", "ARCANA_Fireball_Right.bmp", 0, 4, 0.2f, false);
	Renderer->CreateAnimation("ARCANA_Fireball_Left", "ARCANA_Fireball_Left.bmp", 0, 4, 0.2f, false);
	Renderer->CreateAnimation("ARCANA_Fireball_Up", "ARCANA_Fireball_Up.bmp", 0, 4, 0.2f, false);
	Renderer->CreateAnimation("ARCANA_Fireball_Down", "ARCANA_Fireball_Down.bmp", 0, 2, 0.2f, false);

	Renderer->CreateAnimation("ARCANA_Fireball_Explosion", "ARCANA_Fireball_Explosion.bmp", 0, 6, 0.2f, false);

	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	// 추후 define으로 이동
	m_iAttackPower = 25 + Player::MainPlayer->ItemBuff;
}

void SKILL_Fireball::Update(float _Delta)
{
	if (true == Renderer->IsAnimationEnd())
	{

		Dir = float4::ZERO;

		Renderer->SetRenderScale({ 240, 200 });
		Renderer->ChangeAnimation("ARCANA_Fireball_Explosion");

		if (Renderer->IsAnimation("ARCANA_Fireball_Explosion") && Renderer->IsAnimationEnd())
		{
			Death();
		}
	}

	float4 NextPos = Dir * _Delta * Speed;
	AddPos(NextPos);

}