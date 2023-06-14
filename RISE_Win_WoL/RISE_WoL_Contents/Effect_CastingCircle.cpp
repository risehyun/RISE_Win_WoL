#include "Effect_CastingCircle.h"

#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>


Effect_CastingCircle::Effect_CastingCircle()
{
}

Effect_CastingCircle::~Effect_CastingCircle()
{
}

void Effect_CastingCircle::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("CastingCircle.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Effect");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("CastingCircle.bmp"), 8, 4);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	MainRenderer = CreateRenderer();
	MainRenderer->SetRenderScale({ 400, 400 });
	MainRenderer->CreateAnimation("Start_CastingCircle", "CastingCircle.bmp", 0, 27, 0.05f, false);

	MainRenderer->ChangeAnimation("Start_CastingCircle");
}

void Effect_CastingCircle::Update(float _Delta)
{
}
