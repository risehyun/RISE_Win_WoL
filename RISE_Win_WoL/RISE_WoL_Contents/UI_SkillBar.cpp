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

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ICON_EarthenAegis.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ICON_SnowflakeChakrams.bmp"));

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

	ICON3 = CreateUIRenderer("ICON_EarthenAegis.bmp", RenderOrder::PlayUI);
	ICON3->SetRenderScale({ 30, 30 });
	ICON3->SetRenderPos({ 218, 746 });
	ICON3->Off();

	ICON4 = CreateUIRenderer("ICON_SnowflakeChakrams.bmp", RenderOrder::PlayUI);
	ICON4->SetRenderScale({ 30, 30 });
	ICON4->SetRenderPos({ 261, 746 });
	ICON4->Off();








	Cooldown_Panel = CreateUIRenderer("UI_CooldownPanel.bmp", RenderOrder::PlayUI);
	Cooldown_Panel->SetRenderScale({ 36, 36 });
	Cooldown_Panel->SetRenderPos({ 174, 746 });
	Cooldown_Panel->SetOrder(3);


	Cooldown_Panel_WhirlingTornado = CreateUIRenderer("UI_CooldownPanel.bmp", RenderOrder::PlayUI);
	Cooldown_Panel_WhirlingTornado->SetRenderScale({ 36, 36 });
	Cooldown_Panel_WhirlingTornado->SetRenderPos({ 132, 746 });
	Cooldown_Panel_WhirlingTornado->SetOrder(3);


	Cooldown_Panel_EarthenAegis = CreateUIRenderer("UI_CooldownPanel.bmp", RenderOrder::PlayUI);
	Cooldown_Panel_EarthenAegis->SetRenderScale({ 36, 36 });
	Cooldown_Panel_EarthenAegis->SetRenderPos({ 218, 746 });
	Cooldown_Panel_EarthenAegis->SetOrder(3);


	Cooldown_Panel_SnowflakeChakrams = CreateUIRenderer("UI_CooldownPanel.bmp", RenderOrder::PlayUI);
	Cooldown_Panel_SnowflakeChakrams->SetRenderScale({ 36, 36 });
	Cooldown_Panel_SnowflakeChakrams->SetRenderPos({ 261, 746 });
	Cooldown_Panel_SnowflakeChakrams->SetOrder(3);



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


	Cooldown_Text_EarthenAegis = CreateUIRenderer();
	Cooldown_Text_EarthenAegis->SetRenderScale({ 30, 30 });
	Cooldown_Text_EarthenAegis->SetRenderPos({ 214, 736 });
	Cooldown_Text_EarthenAegis->SetOrder(4);
	Cooldown_Text_EarthenAegis->SetText("0", 16, "예스체");


	Cooldown_Text_SnowflakeChakrams = CreateUIRenderer();
	Cooldown_Text_SnowflakeChakrams->SetRenderScale({ 30, 30 });
	Cooldown_Text_SnowflakeChakrams->SetRenderPos({ 256, 736 });
	Cooldown_Text_SnowflakeChakrams->SetOrder(4);
	Cooldown_Text_SnowflakeChakrams->SetText("0", 16, "예스체");

}

void UI_SkillBar::Update(float _Delta)
{
	if (true == Player::MainPlayer->HasSnowflakeChakrams())
	{
		ICON4->On();
	}

	if (true == Player::MainPlayer->HasEarthenAegis())
	{
		ICON3->On();
	}

	{
		float Value = Player::MainPlayer->GetCoolTime_ExplodingFireball();
		CoolTime_ExplodingFireball = static_cast<int>(Value);
	}

	{
		float Value = Player::MainPlayer->GetCoolTime_WhirlingTornado();
		CoolTime_WhirlingTornado = static_cast<int>(Value);
	}

	{
		float Value = Player::MainPlayer->GetCoolTime_EarthenAegis();
		CoolTime_EarthenAegis = static_cast<int>(Value);
	}

	{
		float Value = Player::MainPlayer->GetCoolTime_SnowflakeChakrams();
		CoolTime_SnowflakeChakrams = static_cast<int>(Value);
	}


#pragma region ExplodingFireball

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

#pragma endregion

#pragma region WhirlingTornado

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

#pragma endregion

#pragma region EarthenAegis

	if (CoolTime_EarthenAegis == 0)
	{
		Cooldown_Text_EarthenAegis->Off();
		Cooldown_Panel_EarthenAegis->Off();
		Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index8.bmp");
	}

	else
	{
		Cooldown_Text_EarthenAegis->On();
		Cooldown_Panel_EarthenAegis->On();

		if (CoolTime_EarthenAegis == 16)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel.bmp");
		}

		else if (CoolTime_EarthenAegis == 14)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index1.bmp");
		}

		else if (CoolTime_EarthenAegis == 12)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index2.bmp");
		}

		else if (CoolTime_EarthenAegis == 10)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index3.bmp");
		}

		else if (CoolTime_EarthenAegis == 8)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index4.bmp");
		}

		else if (CoolTime_EarthenAegis == 6)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index5.bmp");
		}

		else if (CoolTime_EarthenAegis == 4)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index6.bmp");
		}

		else if (CoolTime_EarthenAegis == 2)
		{
			Cooldown_Panel_EarthenAegis->SetTexture("UI_CooldownPanel_Index7.bmp");
		}

	}

	 Cooldown_Text_EarthenAegis->SetText(std::to_string(CoolTime_EarthenAegis), 16, "예스체");

#pragma endregion

#pragma region SnowflakeChakrams

	if (true == Player::MainPlayer->HasSnowflakeChakrams())
	{
		ICON4->On();
	}

	if (CoolTime_SnowflakeChakrams == 0)
	{
		Cooldown_Text_SnowflakeChakrams->Off();
		Cooldown_Panel_SnowflakeChakrams->Off();
		Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel_Index8.bmp");
	}

	else
	{
		Cooldown_Text_SnowflakeChakrams->On();
		Cooldown_Panel_SnowflakeChakrams->On();

		if (CoolTime_SnowflakeChakrams == 14)
		{
			Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel.bmp");
		}

		else if (CoolTime_SnowflakeChakrams == 12)
		{
			Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel_Index1.bmp");
		}

		else if (CoolTime_SnowflakeChakrams == 10)
		{
			Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel_Index2.bmp");
		}

		else if (CoolTime_SnowflakeChakrams == 8)
		{
			Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel_Index3.bmp");
		}

		else if (CoolTime_SnowflakeChakrams == 6)
		{
			Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel_Index4.bmp");
		}

		else if (CoolTime_SnowflakeChakrams == 4)
		{
			Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel_Index5.bmp");
		}

		else if (CoolTime_SnowflakeChakrams == 2)
		{
			Cooldown_Panel_SnowflakeChakrams->SetTexture("UI_CooldownPanel_Index6.bmp");
		}

	}

	Cooldown_Text_SnowflakeChakrams->SetText(std::to_string(CoolTime_SnowflakeChakrams), 16, "예스체");




#pragma endregion

}


