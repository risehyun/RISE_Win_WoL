#include "UI_Inventory.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Player.h"

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

	Index0 = CreateUIRenderer();
	Index0->SetRenderScale({ 30, 30 });
	Index0->SetRenderPos({ 272, 224 });
	Index0->SetTexture("ICON_WhirlingTornado.bmp");
	Index0->SetOrder(2);

	// Q 자리
	Index1 = CreateUIRenderer();
	Index1->SetRenderScale({ 30, 30 });
	Index1->SetRenderPos({ 325, 224 });
	Index1->SetTexture("ICON_ExplodingFireball.bmp");
	Index1->SetOrder(2);

	// E 자리 
	Index2 = CreateUIRenderer();
	Index2->SetRenderScale({ 30, 30 });
	Index2->SetRenderPos({ 380, 224 });
	Index2->SetTexture("ICON_EarthenAegis.bmp");
	Index2->SetOrder(2);

	// R 자리
	Index3 = CreateUIRenderer();
	Index3->SetRenderScale({ 30, 30 });
	Index3->SetRenderPos({ 435, 224 });
	Index3->SetTexture("ICON_SnowflakeChakrams.bmp");
	Index3->SetOrder(2);


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
		IsOpened = false;
		OutFitRenderer->Off();
		DescriptRenderer->Off();
	}

	else
	{
		IsOpened = true;
	}

	if (true == GameEngineInput::IsDown(VK_UP))
	{
		if (false == OutFitRenderer->GetUpdateValue())
		{
			OutFitRenderer->On();
			DescriptRenderer->On();

			if (true == Player::MainPlayer->IsOutfitReinforced())
			{
				DescriptRenderer->SetTexture("UI_OUTFIT_REINFORCED.bmp");
			}

			else
			{
				DescriptRenderer->SetTexture("UI_OUTFIT_BASIC.bmp");
			}

		}
	}


	if (true == Player::MainPlayer->HasEarthenAegis() && true == IsOpened )
	{
		Index2->On();
	}

	if (true == Player::MainPlayer->HasSnowflakeChakrams() && true == IsOpened)
	{
		Index3->On();
	}

}
