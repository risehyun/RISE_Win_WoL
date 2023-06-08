#include "PlayUIManager.h"

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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


}

void PlayUIManager::Update(float _Delta)
{
	float4 t = GameEngineWindow::MainWindow.GetMousePos();
	MousePtr->SetRenderPos(t);
}
