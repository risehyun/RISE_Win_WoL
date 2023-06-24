#include "ITEM_HPBall.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

void ITEM_HPBall::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_HPBall.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Item");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_HPBall.bmp"));
	}


	MainRenderer = CreateRenderer();
	MainRenderer->SetOrder(3);
	MainRenderer->SetRenderScale({ 64, 64 });
	MainRenderer->SetTexture("ITEM_HPBall.bmp");



}

void ITEM_HPBall::Update(float _Delta)
{
}
