#include "UI_PlayerHpBar.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayUIManager.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

UI_PlayerHpBar::UI_PlayerHpBar()
{
}

UI_PlayerHpBar::~UI_PlayerHpBar()
{
}

void UI_PlayerHpBar::Start()
{

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_HPBAR.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_HPBAR_INDEX1.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX4.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX8.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX12.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX16.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX20.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX24.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX28.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX32.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR_INDEX36.bmp"));
	}

	MainRenderer = CreateUIRenderer("UI_HPBAR.bmp", RenderOrder::PlayUI);
	MainRenderer->SetTexture("UI_HPBAR.bmp");

	MainRenderer->SetRenderScale({ 150, 20 });
}

void UI_PlayerHpBar::Update(float _Delta)
{

	float fCurHpFillAmount = static_cast<float>(Player::MainPlayer->GetCurHp());

	if (fCurHpFillAmount <= 500 && fCurHpFillAmount > 450)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX1.bmp");
	}

	else if (fCurHpFillAmount < 450 && fCurHpFillAmount > 400)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX4.bmp");
	}

	else if (fCurHpFillAmount < 400 && fCurHpFillAmount > 350)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX8.bmp");
	}

	else if (fCurHpFillAmount < 350 && fCurHpFillAmount > 300)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX12.bmp");
	}

	else if (fCurHpFillAmount < 300 && fCurHpFillAmount > 250)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX16.bmp");
	}

	else if (fCurHpFillAmount < 250 && fCurHpFillAmount > 200)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX20.bmp");
	}

	else if (fCurHpFillAmount < 200 && fCurHpFillAmount > 150)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX24.bmp");
	}

	else if (fCurHpFillAmount < 150 && fCurHpFillAmount > 100)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX28.bmp");
	}

	else if (fCurHpFillAmount < 100 && fCurHpFillAmount > 50)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX32.bmp");
	}

	else if (fCurHpFillAmount < 50 && fCurHpFillAmount >= 0)
	{
		MainRenderer->SetTexture("UI_HPBAR_INDEX36.bmp");
	}

}
