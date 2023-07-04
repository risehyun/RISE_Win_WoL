#include "UI_SkillBar.h"

#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

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

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ICON_WhirlingTornado.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index2.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index3.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index4.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index5.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index6.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index7.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_CooldownPanel_Index8.bmp"));
	}

	MainRenderer = CreateUIRenderer("UI_SKILLBAR.bmp", RenderOrder::PlayUI);
	MainRenderer->SetRenderScale({ 400, 100 });


	GameEngineRenderer* ICON = CreateUIRenderer("ICON_ExplodingFireball.bmp", RenderOrder::PlayUI);
	ICON->SetRenderScale({ 30, 30 });
	ICON->SetRenderPos({ 174, 746 });
	ICON->SetOrder(2);

	GameEngineRenderer* ICON2 = CreateUIRenderer("ICON_WhirlingTornado.bmp", RenderOrder::PlayUI);
	ICON2->SetRenderScale({ 30, 30 });
	ICON2->SetRenderPos({ 132, 746 });




	Cooldown_Panel = CreateUIRenderer("UI_CooldownPanel.bmp", RenderOrder::PlayUI);
	Cooldown_Panel->SetRenderScale({ 36, 36 });
	Cooldown_Panel->SetRenderPos({ 174, 746 });
	Cooldown_Panel->SetOrder(3);


	Cooldown_Panel_WhirlingTornado = CreateUIRenderer("UI_CooldownPanel.bmp", RenderOrder::PlayUI);
	Cooldown_Panel_WhirlingTornado->SetRenderScale({ 36, 36 });
	Cooldown_Panel_WhirlingTornado->SetRenderPos({ 132, 746 });
	Cooldown_Panel_WhirlingTornado->SetOrder(3);









	Cooldown_Text = CreateUIRenderer();
	Cooldown_Text->SetRenderScale({ 30, 30 });
	Cooldown_Text->SetRenderPos({ 170, 736 });
	Cooldown_Text->SetOrder(4);
	Cooldown_Text->SetText("0", 16, "예스체");


	Cooldown_Text_WhirlingTornado = CreateUIRenderer();
	Cooldown_Text_WhirlingTornado->SetRenderScale({ 30, 30 });
	Cooldown_Text_WhirlingTornado->SetRenderPos({ 128, 736 });
	Cooldown_Text_WhirlingTornado->SetOrder(4);
	Cooldown_Text_WhirlingTornado->SetText("0", 16, "예스체");








}

void UI_SkillBar::Update(float _Delta)
{
	{
		float Value = Player::MainPlayer->GetCoolTime_ExplodingFireball();
		CoolTime_ExplodingFireball = static_cast<int>(Value);
	}

	{
		float Value = Player::MainPlayer->GetCoolTime_WhirlingTornado();
		CoolTime_WhirlingTornado = static_cast<int>(Value);
	}



	// ExplodingFireball
	if (CoolTime_ExplodingFireball == 0)
	{
		Cooldown_Text->Off();
		Cooldown_Panel->Off();
		Cooldown_Panel->SetTexture("UI_CooldownPanel_Index8.bmp");
	}

	else
	{
		Cooldown_Text->On();
		Cooldown_Panel->On();

		if (CoolTime_ExplodingFireball == 4)
		{
			Cooldown_Panel->SetTexture("UI_CooldownPanel.bmp");
		}

		else if (CoolTime_ExplodingFireball == 3)
		{
			Cooldown_Panel->SetTexture("UI_CooldownPanel_Index2.bmp");
		}

		else if (CoolTime_ExplodingFireball == 2)
		{
			Cooldown_Panel->SetTexture("UI_CooldownPanel_Index4.bmp");
		}

		else if (CoolTime_ExplodingFireball == 1)
		{
			Cooldown_Panel->SetTexture("UI_CooldownPanel_Index6.bmp");
		}

	}

	Cooldown_Text->SetText(std::to_string(CoolTime_ExplodingFireball), 16, "예스체");




	// WhirlingTornado
	if (CoolTime_WhirlingTornado == 0)
	{
		Cooldown_Text_WhirlingTornado->Off();
		Cooldown_Panel_WhirlingTornado->Off();
		Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel_Index8.bmp");
	}

	else
	{
		Cooldown_Text_WhirlingTornado->On();
		Cooldown_Panel_WhirlingTornado->On();

		if (CoolTime_WhirlingTornado == 12)
		{
			Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel.bmp");
		}

		else if (CoolTime_WhirlingTornado == 10)
		{
			Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel_Index1.bmp");
		}

		else if (CoolTime_WhirlingTornado == 8)
		{
			Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel_Index2.bmp");
		}

		else if (CoolTime_WhirlingTornado == 6)
		{
			Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel_Index3.bmp");
		}

		else if (CoolTime_WhirlingTornado == 4)
		{
			Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel_Index5.bmp");
		}

		else if (CoolTime_WhirlingTornado == 2)
		{
			Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel_Index6.bmp");
		}

		else if (CoolTime_WhirlingTornado == 1)
		{
			Cooldown_Panel_WhirlingTornado->SetTexture("UI_CooldownPanel_Index7.bmp");
		}

	}

	Cooldown_Text_WhirlingTornado->SetText(std::to_string(CoolTime_WhirlingTornado), 16, "예스체");
}