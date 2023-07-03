#include "UI_MiniBossNameBar.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "MiniBoss_GrandSummoner.h"

#include "UI_HPBar.h"

UI_MiniBossNameBar::UI_MiniBossNameBar()
{
}

UI_MiniBossNameBar::~UI_MiniBossNameBar()
{
}

void UI_MiniBossNameBar::Start()
{

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_MINIBOSS_NAMEBAR.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MINIBOSS_NAMEBAR.bmp"));
	}

	MainRenderer = CreateUIRenderer("UI_MINIBOSS_NAMEBAR.bmp", RenderOrder::PlayUI);

	MainRenderer->SetRenderScale({ 300, 60 });

	NewHpBar = GetLevel()->CreateActor<UI_HPBar>();
	NewHpBar->GetMainRenderer()->SetRenderPos({ 650, 66 });
	NewHpBar->GetMainRenderer()->SetRenderScale({ 240, 23 });
}

void UI_MiniBossNameBar::Update(float _Delta)
{


}
