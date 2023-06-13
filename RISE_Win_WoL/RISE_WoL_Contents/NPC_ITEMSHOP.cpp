#include "NPC_ITEMSHOP.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ITEM_AmuletofSundering.h"
#include "ITEM_GiantsHeart.h"
#include "ITEM_AnalyticalMonocle.h"
#include "ITEM_DaggerofMidas.h"
#include "ITEM_VampiresEyeglasses.h"
#include "ITEM_Potion.h"

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
	}

	MainRenderer = CreateRenderer("NPC_ITEMSHOP.bmp", RenderOrder::BackGround);
		
	MainRenderer->SetRenderScale({ 100, 150 });


	//PotionRenderer = CreateRenderer("ITEM_POTION.bmp", RenderOrder::BackGround);

	//PotionRenderer->SetRenderScale({ 80, 120 });

	//PotionRenderer->SetRenderPos({ -255, -35 });

	{
		GameEngineRenderer* Ptr = CreateRenderer("GROUND_ITEMSHOP.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 480, 150 });

		Ptr->SetRenderPos({ 0, 200 });
	}

	// 리팩토링 할 때 리스트로 묶어서 관리하도록 수정
	ITEM_AmuletofSundering* NewAmulet = GetLevel()->CreateActor<ITEM_AmuletofSundering>();
	ITEM_GiantsHeart* NewHeart = GetLevel()->CreateActor<ITEM_GiantsHeart>();
	ITEM_AnalyticalMonocle* NewMonocle = GetLevel()->CreateActor<ITEM_AnalyticalMonocle>();
	ITEM_DaggerofMidas* NewDagger = GetLevel()->CreateActor<ITEM_DaggerofMidas>();
	ITEM_VampiresEyeglasses* NewEyeglasses = GetLevel()->CreateActor<ITEM_VampiresEyeglasses>();
	ITEM_Potion* NewPotion = GetLevel()->CreateActor<ITEM_Potion>();


	NewHeart->GetMainRenderer()->SetRenderPos({ 500, 1800 });
	NewHeart->GetBodyCollsion()->SetCollisionPos({ 500, 1800 });

	NewMonocle->GetMainRenderer()->SetRenderPos({ 600, 1800 });
	NewMonocle->GetBodyCollsion()->SetCollisionPos({ 600, 1800 });

	NewAmulet->GetMainRenderer()->SetRenderPos({ 700, 1800 });
	NewAmulet->GetBodyCollsion()->SetCollisionPos({ 700, 1800 });

	NewDagger->GetMainRenderer()->SetRenderPos({ 800, 1800 });
	NewDagger->GetBodyCollsion()->SetCollisionPos({ 800, 1800 });

	NewEyeglasses->GetMainRenderer()->SetRenderPos({ 900, 1800 });
	NewEyeglasses->GetBodyCollsion()->SetCollisionPos({ 900, 1800 });

	NewPotion->GetMainRenderer()->SetRenderPos({ 450, 1600 });
	NewPotion->GetBodyCollsion()->SetCollisionPos({ 450, 1600 });

}