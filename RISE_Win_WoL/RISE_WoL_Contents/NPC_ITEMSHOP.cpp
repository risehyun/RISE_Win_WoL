#include "NPC_ITEMSHOP.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"

//#include <GameEngineCore/GameEngineCollision.h>
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
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("POTION.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("GROUND_ITEMSHOP.bmp"));
		
	}

	MainRenderer = CreateRenderer("NPC_ITEMSHOP.bmp", RenderOrder::BackGround);
		
	MainRenderer->SetRenderScale({ 100, 150 });


	PotionRenderer = CreateRenderer("POTION.bmp", RenderOrder::BackGround);

	PotionRenderer->SetRenderScale({ 80, 120 });

	PotionRenderer->SetRenderPos({ -225, -35 });

	//GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::Map);
	//BodyCollsion->SetCollisionScale({ 100, 100 });
	//BodyCollsion->SetCollisionType(CollisionType::CirCle);

}