#include "SKILL_KnightAttack.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_KnightAttack::Start()
{
	// ��ų �ؽ�ó �ε�
	if (false == ResourcesManager::GetInst().IsLoadTexture("SWORDMAN_ATTACK.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\MonsterSkill\\Knight\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SWORDMAN_ATTACK.bmp"), 4, 6);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	SkillRenderer = CreateRenderer();
	SkillRenderer->SetRenderScale({ 100, 100 });

	// �ִϸ��̼� ����
	SkillRenderer->CreateAnimation("ATTACK_LEFT", "SWORDMAN_ATTACK.bmp", 0, 3, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_RIGHT", "SWORDMAN_ATTACK.bmp", 4, 7, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_UP", "SWORDMAN_ATTACK.bmp", 8, 11, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_DOWN", "SWORDMAN_ATTACK.bmp", 16, 19, 0.2f, false);

	// �浹ü ����
	{
		SkillCollsion = CreateCollision(CollisionOrder::MonsterSkill);
		SkillCollsion->SetCollisionScale({ 100, 100 });
		SkillCollsion->SetCollisionType(CollisionType::CirCle);
	}
}

void SKILL_KnightAttack::Update(float _Delta)
{


	if (0.3f < GetLiveTime())
	{
		if (nullptr != SkillRenderer)
		{

			SkillRenderer->Death();
			SkillRenderer = nullptr;

			SkillCollsion->Death();
			SkillCollsion = nullptr;
		}
	}

}
