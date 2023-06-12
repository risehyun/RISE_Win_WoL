#include "UI_KeyboardF.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

UI_KeyboardF::UI_KeyboardF()
{
}

UI_KeyboardF::~UI_KeyboardF()
{
}

GameEngineRenderer* UI_KeyboardF::GetMainRenderer() const
{
	return MainRenderer;
}

void UI_KeyboardF::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("F.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("F.bmp"));
	}

	MainRenderer = CreateRenderer();
	MainRenderer->SetRenderScale({ 32, 32 });
	MainRenderer->SetTexture("F.bmp");
}

void UI_KeyboardF::Update(float _Delta)
{


}
