#include "EFFECT_GoldCastingCircle.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

EFFECT_GoldCastingCircle::EFFECT_GoldCastingCircle()
{
}

EFFECT_GoldCastingCircle::~EFFECT_GoldCastingCircle()
{
}

void EFFECT_GoldCastingCircle::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("GoldCastingCircle.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("GoldCastingCircle.bmp"));
	}


	MainRenderer = CreateRenderer();
	MainRenderer->SetOrder(0);
	MainRenderer->SetRenderScale({ 400, 400 });
	MainRenderer->SetTexture("GoldCastingCircle.bmp");

}

void EFFECT_GoldCastingCircle::Update(float _Delta)
{
}
