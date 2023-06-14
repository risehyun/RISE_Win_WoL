#include "UI_Inventory.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

UI_Inventory::UI_Inventory()
{
}

UI_Inventory::~UI_Inventory()
{
}

GameEngineRenderer* UI_Inventory::GetMainRenderer() const
{
	return MainRenderer;
}

void UI_Inventory::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_INVENTORY.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\UI");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_INVENTORY.bmp"));
	}

	MainRenderer = CreateRenderer();
	MainRenderer->SetRenderScale({ 576, 865 });
	MainRenderer->SetTexture("UI_INVENTORY.bmp");
}

void UI_Inventory::Update(float _Delta)
{
}
