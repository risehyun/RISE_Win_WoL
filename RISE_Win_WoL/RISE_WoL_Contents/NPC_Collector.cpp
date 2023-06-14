#include "NPC_Collector.h"

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "ARCANA_EarthenAegis.h"
#include "ARCANA_SnowflakeChakrams.h"

NPC_Collector::NPC_Collector()
{
}

NPC_Collector::~NPC_Collector()
{
}

void NPC_Collector::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_Collector.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\COIIECTOR");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_Collector.bmp"));
	}

	MainRenderer = CreateRenderer("NPC_Collector.bmp", RenderOrder::BackGround);

	MainRenderer->SetRenderScale({ 150, 150 });

}

void NPC_Collector::Update(float _Delta)
{
}
