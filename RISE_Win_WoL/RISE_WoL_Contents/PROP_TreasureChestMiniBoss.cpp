#include "PROP_TreasureChestMiniBoss.h"

#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineBase/GameEngineRandom.h>

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

	// 렌더러 생성과 로딩된 텍스처 지정
	MainRenderer = CreateRenderer();
	MainRenderer->SetRenderScale({ 300, 400 });

	MainRenderer->CreateAnimation("Idle_TreasureChest", "TreasureChestMiniBoss_.bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Open_TreasureChest", "TreasureChestMiniBoss_.bmp", 1, 4, 0.1f, false);

	BodyCollision = CreateCollision(CollisionOrder::Map);
	BodyCollision->SetCollisionScale({ 100, 100 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);

	MainRenderer->ChangeAnimation("Idle_TreasureChest");
	MainRenderer->SetOrder(0);

}

void PROP_TreasureChestMiniBoss::Update(float _Delta)
{
	// 함수를 애니메이션 이름으로 작동시킬 수 있도록 수정 필요
	if (true == MainRenderer->IsAnimation("Open_TreasureChest")
		&& true == MainRenderer->IsAnimationEnd())
	{
		Death();
	}

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerSkill, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		MainRenderer->ChangeAnimation("Open_TreasureChest");

		// <테스트용>
		// 드롭할 골드의 개수를 랜덤하게 정해서 그 값만큼 드롭하도록 한다.
		// 드롭 위치의 경우 상자를 기준으로 랜덤 값만큼 offset을 줘서 처리한다. 
		// 골드의 Order 값은 기존의 상자보다 높아야 가리지 않는다.

		int Test = GameEngineRandom::MainRandom.RandomInt(1, 10);

		int a = 0;

		for (size_t i = 0; i < Test; i++)
		{
			int Test2 = GameEngineRandom::MainRandom.RandomInt(0, 500);
			ITEM_Gold* NewGold = GetLevel()->CreateActor<ITEM_Gold>();
			NewGold->SetPos({ 1850 + static_cast<float>(Test2), 1700 });
			NewGold->SetOrder(1);
			BodyCollision->Off();
		}


	}
}