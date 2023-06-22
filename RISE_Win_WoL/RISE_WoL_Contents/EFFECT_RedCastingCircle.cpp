#include "EFFECT_RedCastingCircle.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

EFFECT_RedCastingCircle::EFFECT_RedCastingCircle()
{
}

EFFECT_RedCastingCircle::~EFFECT_RedCastingCircle()
{
}

void EFFECT_RedCastingCircle::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("RedCastingCircle.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RedCastingCircle.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("FloorCreater_All.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FloorCreater_All.bmp"), 3, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("IceBlast.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("IceBlast.bmp"), 3, 1);
	}

	MainRenderer = CreateRenderer();
	MainRenderer->SetOrder(0);
	MainRenderer->SetRenderScale({ 200, 200 });
	MainRenderer->SetTexture("RedCastingCircle.bmp");
	MainRenderer->SetRenderPos({ 0.0f, 0.0f });

	HitRenderer = CreateRenderer();
	HitRenderer->SetOrder(1);
	HitRenderer->SetRenderScale({ 200, 200 });
	HitRenderer->SetTexture("IceBlast.bmp");
	HitRenderer->SetRenderPos({ 0.0f, 0.0f });

	MainRenderer->CreateAnimation("FloorCreater", "FloorCreater_All.bmp", 0, 2, 0.5f, false);
}

void EFFECT_RedCastingCircle::Update(float _Delta)
{
	MainRenderer->ChangeAnimation("FloorCreater");
}
