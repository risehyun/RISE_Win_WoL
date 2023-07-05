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

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Unselect.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Unselect.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Select.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Select.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Descript_AmuletofSundering.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Descript_AmuletofSundering.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Descript_AnalyticalMonocle.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Descript_AnalyticalMonocle.bmp"));
		}
			
	}

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");


		if (false == ResourcesManager::GetInst().IsLoadTexture("ICON_AnalyticalMonocle.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ICON_AnalyticalMonocle.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("ICON_AmuletofSundering.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ICON_AmuletofSundering.bmp"));
		}
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


	Relic_Index0 = CreateUIRenderer();
	Relic_Index0->SetRenderScale({ 30, 30 });
	Relic_Index0->SetRenderPos({ 160, 375 });
	Relic_Index0->SetTexture("ICON_AmuletofSundering.bmp");
	Relic_Index0->SetOrder(2);

	Relic_Index1 = CreateUIRenderer();
	Relic_Index1->SetRenderScale({ 30, 30 });
	Relic_Index1->SetRenderPos({ 200, 375 });
	Relic_Index1->SetTexture("ICON_AnalyticalMonocle.bmp");
	Relic_Index1->SetOrder(2);





	Relic_Frame0 = CreateUIRenderer();
	Relic_Frame0->SetRenderScale({ 30, 30 });
	Relic_Frame0->SetRenderPos({ 160, 375 });
	Relic_Frame0->SetTexture("UI_Unselect.bmp");
	Relic_Frame0->SetOrder(2);

	Relic_Frame1 = CreateUIRenderer();
	Relic_Frame1->SetRenderScale({ 30, 30 });
	Relic_Frame1->SetRenderPos({ 200, 375 });
	Relic_Frame1->SetTexture("UI_Unselect.bmp");
	Relic_Frame1->SetOrder(2);




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
			Relic_Frame0->SetTexture("UI_Unselect.bmp");
			Relic_Frame1->SetTexture("UI_Unselect.bmp");

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


	if (true == GameEngineInput::IsDown(VK_LEFT) && Player::MainPlayer->HasAmuletofSundering())
	{
		OutFitRenderer->Off();
		Relic_Frame0->SetTexture("UI_Select.bmp");
		Relic_Frame1->SetTexture("UI_Unselect.bmp");

		DescriptRenderer->On();
		DescriptRenderer->SetTexture("UI_Descript_AmuletofSundering.bmp");
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT) && Player::MainPlayer->HasAnalyticalMonocle())
	{
		OutFitRenderer->Off();
		Relic_Frame0->SetTexture("UI_Unselect.bmp");
		Relic_Frame1->SetTexture("UI_Select.bmp");

		DescriptRenderer->On();
		DescriptRenderer->SetTexture("UI_Descript_AnalyticalMonocle.bmp");
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT) && true == Player::MainPlayer->HasAnalyticalMonocle())
	{
		Relic_Index1->Off();
		Relic_Frame1->Off();
		DescriptRenderer->SetTexture("UI_CooldownPanel_Index8.bmp");
	}

	if (false == Player::MainPlayer->HasAnalyticalMonocle())
	{
		Relic_Index1->Off();
		Relic_Frame1->Off();
	}


	
	if (true == Player::MainPlayer->HasEarthenAegis() && true == IsOpened )
	{
		Index2->On();
	}

	if (true == Player::MainPlayer->HasSnowflakeChakrams() && true == IsOpened)
	{
		Index3->On();
	}

	if (true == Player::MainPlayer->HasAmuletofSundering() && true == IsOpened)
	{
		Relic_Frame0->On();
		Relic_Index0->On();
	}

		
		
	if (true == Player::MainPlayer->HasAnalyticalMonocle() && true == IsOpened)
	{
		Relic_Frame1->On();
		Relic_Index1->On();
	}

}
