#include "UI_SkillBar.h"

#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

UI_SkillBar::UI_SkillBar()
{

}

UI_SkillBar::~UI_SkillBar()
{
}

GameEngineRenderer* UI_SkillBar::GetMainRenderer() const
{
	return MainRenderer;
}

void UI_SkillBar::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_SKILLBAR.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\UI");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SKILLBAR.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ICON_ExplodingFireball.bmp"));
	}

	MainRenderer = CreateUIRenderer("UI_SKILLBAR.bmp", RenderOrder::PlayUI);
	MainRenderer->SetRenderScale({ 400, 100 });

	GameEngineRenderer* ICON = CreateUIRenderer("ICON_ExplodingFireball.bmp", RenderOrder::PlayUI);
	ICON->SetRenderScale({ 30, 30 });
	ICON->SetRenderPos({ 174, 746 });


}

void UI_SkillBar::Update(float _Delta)
{


}