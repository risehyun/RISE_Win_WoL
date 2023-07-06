#include "NPC_ArcanaShop.h"

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "ARCANA_EarthenAegis.h"
#include "ARCANA_SnowflakeChakrams.h"


NPC_ArcanaShop::NPC_ArcanaShop()
{
}

NPC_ArcanaShop::~NPC_ArcanaShop()
{
}

void NPC_ArcanaShop::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_SKILLSHOP.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\SKILLSHOP");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_SKILLSHOP.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("GROUND_SKILLSHOP.bmp"));
	}

	MainRenderer = CreateRenderer("NPC_SKILLSHOP.bmp", RenderOrder::BackGround);

	MainRenderer->SetRenderScale({ 150, 150 });

	{
		GameEngineRenderer* Ptr = CreateRenderer("GROUND_SKILLSHOP.bmp", RenderOrder::BackGround);

		Ptr->SetRenderScale({ 480, 150 });

		Ptr->SetRenderPos({ 10, 200 });
	}

	ARCANA_EarthenAegis* NewEarthenAegis = GetLevel()->CreateActor<ARCANA_EarthenAegis>();
	NewEarthenAegis->GetMainRenderer()->SetRenderPos({ 3350, 1800 });
	NewEarthenAegis->GetBodyCollsion()->SetCollisionPos({ 3350, 1800 });

	ARCANA_SnowflakeChakrams* NewSnowflakeChakrams = GetLevel()->CreateActor<ARCANA_SnowflakeChakrams>();
	NewSnowflakeChakrams->GetMainRenderer()->SetRenderPos({ 3550, 1800 });
	NewSnowflakeChakrams->GetBodyCollsion()->SetCollisionPos({ 3550, 1800 });

}

void NPC_ArcanaShop::Update(float _Delta)
{


}
