#include "PlayUIManager.h"

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>

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
		GameEngineRenderer* Ptr = CreateUIRenderer("UI_PLAYERBAR.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 200, 80 });

//		Ptr->SetRenderScale({ 328, 80 });
		Ptr->SetRenderScale({ 286, 70 });
		Ptr->SetTexture("UI_PLAYERBAR.bmp");
	}
}