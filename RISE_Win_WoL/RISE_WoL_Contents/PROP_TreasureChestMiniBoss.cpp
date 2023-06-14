#include "PROP_TreasureChestMiniBoss.h"

#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ITEM_Gold.h"

PROP_TreasureChestMiniBoss::PROP_TreasureChestMiniBoss()
{
}

PROP_TreasureChestMiniBoss::~PROP_TreasureChestMiniBoss()
{
}

void PROP_TreasureChestMiniBoss::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("TreasureChestMiniBoss_.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Item");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("TreasureChestMiniBoss_.bmp"), 5, 1);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	MainRenderer = CreateRenderer();
	MainRenderer->SetRenderScale({ 300, 400 });
	MainRenderer->CreateAnimation("Idle_TreasureChest", "TreasureChestMiniBoss_.bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Open_TreasureChest", "TreasureChestMiniBoss_.bmp", 1, 4, 0.1f, false);


	BodyCollision = CreateCollision(CollisionOrder::Map);
	BodyCollision->SetCollisionScale({ 100, 100 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);



	MainRenderer->ChangeAnimation("Idle_TreasureChest");

}

void PROP_TreasureChestMiniBoss::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerSkill, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		MainRenderer->ChangeAnimation("Open_TreasureChest");

		// <�׽�Ʈ��>
		// ����� ����� ������ �����ϰ� ���ؼ� �� ����ŭ ����ϵ��� �Ѵ�.
		// ��� ��ġ�� ��� ���ڸ� �������� ���� ����ŭ offset�� �༭ ó���Ѵ�. 
		ITEM_Gold* NewGold = GetLevel()->CreateActor<ITEM_Gold>();
		NewGold->SetPos({ 1850, 1700 });
	}

}
