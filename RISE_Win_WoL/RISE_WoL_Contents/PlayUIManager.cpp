#include "PlayUIManager.h"

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "UI_Inventory.h"
#include "UI_SkillBar.h"

#include "UI_HPBar.h"

#include <GameEngineCore/ResourcesManager.h>
#include "Player.h"

#include "UI_MiniBossNameBar.h"
#include "UI_Dialog.h"

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
		Ptr->SetOrder(0);
	}

	{
		GameEngineRenderer* Ptr = CreateUIRenderer();
		Ptr->SetRenderPos({ 640, 740 });
		Ptr->SetRenderScale({ 16, 16 });
		Ptr->SetTexture("UI_MONEY.bmp");
		Ptr->SetOrder(5);
	}

	PlayerBarText = CreateUIRenderer();
	PlayerBarText->SetRenderPos({ 150, 28 });
	PlayerBarText->SetRenderScale({ 200, 50 });
	PlayerBarText->SetText("0", 28, "나눔스퀘어");
	PlayerBarText->SetOrder(5);

	PlayerMoneyText = CreateUIRenderer();
	PlayerMoneyText->SetRenderPos({ 660, 730 });
	PlayerMoneyText->SetRenderScale({ 200, 50 });
	PlayerMoneyText->SetText("0", 20, "나눔스퀘어");
	PlayerMoneyText->SetOrder(5);


	NewHpBar = GetLevel()->CreateActor<UI_PlayerHpBar>();
	NewHpBar->GetMainRenderer()->SetRenderPos({ 170, 52 });


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
	
	// 스킬바 적용
	UI_SkillBar* NewSkillBar = GetLevel()->CreateActor<UI_SkillBar>();
	NewSkillBar->GetMainRenderer()->SetRenderPos({ 225, 740 });
	NewSkillBar->SetOrder(3);


	// 몬스터 네임바 적용
	MiniBossNameBar = GetLevel()->CreateActor<UI_MiniBossNameBar>();
	MiniBossNameBar->SetPos({ 650, 60 });
	MiniBossNameBar->GetMainRenderer()->Off();
	MiniBossNameBar->NewHpBar->GetMainRenderer()->Off();

	BossNameBar = GetLevel()->CreateActor<UI_BossNameBar>();
	BossNameBar->SetPos({ 650, 60 });
	BossNameBar->GetMainRenderer()->Off();
	BossNameBar->NewHpBar->GetMainRenderer()->Off();


	// 플레이어 인벤토리

	NewInven = GetLevel()->CreateActor<UI_Inventory>();
	NewInven->GetMainRenderer()->SetRenderPos({ 300, 400 });
	NewInven->GetMainRenderer()->SetRenderScale({ 400, 700 });
	NewInven->GetMainRenderer()->SetOrder(10);

	NewInven->GetMainRenderer()->Off();

	NewInven->Index0->SetOrder(11);
	NewInven->Index0->Off();

	NewInven->Index1->SetOrder(11);
	NewInven->Index1->Off();

	NewInven->Index2->SetOrder(11);
	NewInven->Index2->Off();

	NewInven->Index3->SetOrder(11);
	NewInven->Index3->Off();



	NewInven->Relic_Index0->SetOrder(11);
	NewInven->Relic_Index1->SetOrder(11);

	NewInven->Relic_Index0->Off();
	NewInven->Relic_Index1->Off();


	NewInven->Relic_Frame0->SetOrder(12);
	NewInven->Relic_Frame1->SetOrder(12);

	NewInven->Relic_Frame0->Off();
	NewInven->Relic_Frame1->Off();


	NewInven->OutFitRenderer->SetOrder(11);
	NewInven->DescriptRenderer->SetOrder(11);


	// 대화상자
	NewDialog = GetLevel()->CreateActor<UI_Dialog>();
	NewDialog->GetMainRenderer()->SetRenderPos({ 620, 660 });
	NewDialog->GetMainRenderer()->SetOrder(10);



}

void PlayUIManager::Update(float _Delta)
{
	float4 t = GameEngineWindow::MainWindow.GetMousePos();
	MousePtr->SetRenderPos(t);

	// 인벤토리 호출
	if (true == GameEngineInput::IsDown(VK_TAB))
	{

		// 1. 인벤토리 UI On/Off
		if (true == NewInven->GetMainRenderer()->GetUpdateValue())
		{
			NewInven->GetMainRenderer()->Off();
			NewInven->Index0->Off();
			NewInven->Index1->Off();
			NewInven->Index2->Off();
			NewInven->Index3->Off();

			NewInven->Relic_Frame0->Off();
			NewInven->Relic_Index0->Off();

			NewInven->Relic_Frame1->Off();
			NewInven->Relic_Index1->Off();

			NewInven->Relic_Frame0->SetTexture("UI_Unselect.bmp");
			NewInven->Relic_Frame1->SetTexture("UI_Unselect.bmp");
		}

		else
		{
			NewInven->GetMainRenderer()->On();
			NewInven->Index0->On();
			NewInven->Index1->On();
		}
	}








	std::string PlayerHpText = "";

	if (Player::MainPlayer->GetCurHp() < 0)
	{
		PlayerHpText += "0";
	}

	else
	{
		PlayerHpText += std::to_string(Player::MainPlayer->GetCurHp());
	}

	PlayerHpText += "/" + std::to_string(Player::MainPlayer->GetMaxHp());

	PlayerBarText->SetText(PlayerHpText, 20, "나눔스퀘어");


	PlayerMoneyText->SetText(std::to_string(Player::MainPlayer->GetTotalGold()), 20, "나눔스퀘어");

	



}

