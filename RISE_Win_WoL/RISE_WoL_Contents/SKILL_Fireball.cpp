#include "SKILL_Fireball.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

void SKILL_Fireball::Start()
{
	// ��ų �ؽ�ó �ε�
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
	}


	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 120, 100 });

		// �ִϸ��̼� ����
	Renderer->CreateAnimation("ARCANA_Fireball_Right", "ARCANA_Fireball_Right.bmp", 0, 4, 0.2f, false);
	Renderer->CreateAnimation("ARCANA_Fireball_Left", "ARCANA_Fireball_Left.bmp", 0, 4, 0.2f, false);
	Renderer->CreateAnimation("ARCANA_Fireball_Up", "ARCANA_Fireball_Up.bmp", 0, 4, 0.2f, false);
	Renderer->CreateAnimation("ARCANA_Fireball_Down", "ARCANA_Fireball_Down.bmp", 0, 2, 0.2f, false);

	// �浹ü ����
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	// ���� define���� �̵�
	m_iAttackPower = 25;
}

void SKILL_Fireball::Update(float _Delta)
{

}