#include "PlayUIManager.h"

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "UI_Inventory.h"
#include <GameEngineCore/ResourcesManager.h>

PlayUIManager* PlayUIManager::UI = nullptr;

PlayUIManager::PlayUIManager()
{
	UI = this;
}

PlayUIManager::~PlayUIManager()
{

}

void PlayUIManager::Start()
{
	{
		GameEngineRenderer* Ptr = CreateUIRenderer("UI_PLAYERBAR.bmp", RenderOrder::PlayUI);
		Ptr->SetRenderPos({ 150, 60 });

		Ptr->SetRenderScale({ 200, 50 });
		Ptr->SetTexture("UI_PLAYERBAR.bmp");
	}

	{
		GameEngineRenderer* Ptr = CreateUIRenderer("UI_HPBAR.bmp", RenderOrder::PlayUI);
		Ptr->SetRenderPos({ 170, 52 });
		Ptr->SetRenderScale({ 150, 20 });
		Ptr->SetTexture("UI_HPBAR.bmp");
	}

	{
		GameEngineRenderer* Ptr = CreateUIRenderer("UI_MANABAR.bmp", RenderOrder::PlayUI);
		Ptr->SetRenderPos({ 154, 72 });

		Ptr->SetRenderScale({ 118, 10 });
		Ptr->SetTexture("UI_MANABAR.bmp");
	}

	MousePtr = CreateUIRenderer("UI_MOUSE.bmp", RenderOrder::PlayUI);
	MousePtr->SetRenderScale({ 44, 44 });
	MousePtr->SetTexture("UI_MOUSE.bmp");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_INVEN_BASE.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\UI");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_INVEN_BASE.bmp"));
	}


}

void PlayUIManager::Update(float _Delta)
{
	float4 t = GameEngineWindow::MainWindow.GetMousePos();
	MousePtr->SetRenderPos(t);

	// 인벤토리 호출
	if (true == GameEngineInput::IsDown(VK_TAB))
	{
		// 1. 인벤토리 UI On
		GameEngineRenderer* NewInven = CreateUIRenderer("UI_INVEN_BASE.bmp", RenderOrder::PlayUI);
		NewInven->SetRenderPos({ 300, 400 });
		NewInven->SetRenderScale({ 400, 700 });
	}
}