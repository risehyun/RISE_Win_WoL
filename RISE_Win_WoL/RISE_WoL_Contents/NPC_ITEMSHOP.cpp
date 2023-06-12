#include "NPC_ITEMSHOP.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>

NPC_ITEMSHOP::NPC_ITEMSHOP()
{
}

NPC_ITEMSHOP::~NPC_ITEMSHOP()
{
}

void NPC_ITEMSHOP::Update(float _Delta)
{

}

void NPC_ITEMSHOP::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_ITEMSHOP.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_ITEMSHOP.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("GROUND_ITEMSHOP.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_POTION.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_AmuletofSundering.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_AnalyticalMonocle.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_DaggerofMidas.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_VampiresEyeglasses.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_GiantsHeart.bmp"));
		
		
	}

	MainRenderer = CreateRenderer("NPC_ITEMSHOP.bmp", RenderOrder::BackGround);
		
	MainRenderer->SetRenderScale({ 100, 150 });


	PotionRenderer = CreateRenderer("ITEM_POTION.bmp", RenderOrder::BackGround);

	PotionRenderer->SetRenderScale({ 80, 120 });

	PotionRenderer->SetRenderPos({ -255, -35 });

	{
		GameEngineRenderer* Ptr = CreateRenderer("GROUND_ITEMSHOP.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 480, 150 });

		Ptr->SetRenderPos({ 0, 200 });
	}


	// 아이템 렌더링 테스트 -> 추후 아이템 목록을 리스트화해서 출력

	{
		GameEngineRenderer* Ptr = CreateRenderer("ITEM_AmuletofSundering.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 74, 100 });

		Ptr->SetRenderPos({ 0, 200 });
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("ITEM_AnalyticalMonocle.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 74, 100 });

		Ptr->SetRenderPos({ 80, 200 });
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("ITEM_DaggerofMidas.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 74, 100 });

		Ptr->SetRenderPos({ -80, 200 });
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("ITEM_VampiresEyeglasses.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 74, 100 });

		Ptr->SetRenderPos({ -160, 200 });
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("ITEM_GiantsHeart.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 74, 100 });

		Ptr->SetRenderPos({ 160, 200 });
	}


	//GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::Map);
	//BodyCollsion->SetCollisionScale({ 100, 100 });
	//BodyCollsion->SetCollisionType(CollisionType::CirCle);

}