#include "UI_Inventory.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

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
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\UI");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_INVEN_BASE.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_INVEN_BASE.bmp"));	
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_OUTFIT_SELECTED.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_OUTFIT_SELECTED.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_OUTFIT_BASIC.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_OUTFIT_BASIC.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_OUTFIT_REINFORCED.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_OUTFIT_REINFORCED.bmp"));
	}


	
	MainRenderer = CreateUIRenderer();
	MainRenderer->SetRenderScale({ 576, 865 });
	MainRenderer->SetTexture("UI_INVEN_BASE.bmp");
	MainRenderer->SetOrder(1);


	OutFitRenderer = CreateUIRenderer();
	OutFitRenderer->SetRenderScale({ 400, 100 });
	OutFitRenderer->SetRenderPos({ 300, 100 });
	OutFitRenderer->SetTexture("UI_OUTFIT_SELECTED.bmp");
	OutFitRenderer->SetOrder(2);
	OutFitRenderer->Off();


	// E 자리 KEEP
	// Index1->SetRenderPos({ 380, 224 });


	// Q자리
	Index1 = CreateUIRenderer();
	Index1->SetRenderScale({ 30, 30 });
	Index1->SetRenderPos({ 325, 224 });
	Index1->SetTexture("ICON_ExplodingFireball.bmp");
	Index1->SetOrder(2);







	DescriptRenderer = CreateUIRenderer();
	DescriptRenderer->SetRenderScale({ 360, 220 });
	DescriptRenderer->SetRenderPos({ 300, 624 });
	DescriptRenderer->SetTexture("UI_CooldownPanel_Index8.bmp");
	DescriptRenderer->SetOrder(2);

}

void UI_Inventory::Update(float _Delta)
{

	if (false == MainRenderer->GetUpdateValue())
	{
		OutFitRenderer->Off();
		DescriptRenderer->Off();
	}


	if (true == GameEngineInput::IsDown(VK_UP))
	{
		if (false == OutFitRenderer->GetUpdateValue())
		{
			OutFitRenderer->On();
			DescriptRenderer->On();

			DescriptRenderer->SetTexture("UI_OUTFIT_BASIC.bmp");
		}

	}


}
