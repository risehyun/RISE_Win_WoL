#include "UI_BossNameBar.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "Boss.h"

#include "UI_HPBar.h"

UI_BossNameBar::UI_BossNameBar()
{
}

UI_BossNameBar::~UI_BossNameBar()
{
}

void UI_BossNameBar::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BOSS_NAMEBAR.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BOSS_NAMEBAR.bmp"));
	}

	MainRenderer = CreateUIRenderer("UI_BOSS_NAMEBAR.bmp", RenderOrder::PlayUI);

	MainRenderer->SetRenderScale({ 300, 60 });

	NewHpBar = GetLevel()->CreateActor<UI_HPBar>();
	NewHpBar->GetMainRenderer()->SetRenderPos({ 650, 66 });
	NewHpBar->GetMainRenderer()->SetRenderScale({ 240, 23 });
}

void UI_BossNameBar::Update(float _Delta)
{
}
