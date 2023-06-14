#include "NPC_Outfit.h"
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

NPC_Outfit::NPC_Outfit()
{
}

NPC_Outfit::~NPC_Outfit()
{
}

void NPC_Outfit::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_Outfit.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\OUTFIT");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_Outfit.bmp"));
	}

	MainRenderer = CreateRenderer("NPC_Outfit.bmp", RenderOrder::BackGround);

	MainRenderer->SetRenderScale({ 150, 150 });
}

void NPC_Outfit::Update(float _Delta)
{
}
