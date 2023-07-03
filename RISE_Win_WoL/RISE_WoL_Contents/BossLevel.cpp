#include "BossLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "ITEM_HealthCrystal.h"
#include "EFFECT_GoldCastingCircle.h"

#include "PlayUIManager.h"



#include "Player.h"
#include "BackGround.h"

#include "Boss.h"

BossLevel::BossLevel()
{
}

BossLevel::~BossLevel()
{
}

void BossLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("BossStage_Col_resize.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;
		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BossStage_Col_resize.bmp"));
	}

	BackGroundPtr = CreateActor<BackGround>();

	//	BackGroundPtr->Init("stage1.Bmp", "stage1_Col.bmp", 3.0f, { 640, 400 });
	BackGroundPtr->Init("BossStage_resize.Bmp", "BossStage_Col_resize.Bmp");

}

void BossLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		Player::MainPlayer->OverOff();
		GameEngineCore::ChangeLevel("EndingLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}
}

void BossLevel::Render(float _Delta)
{
}

void BossLevel::Release()
{
}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	Player::MainPlayer->SetGroundTexture("BossStage_Col_resize.bmp");
	Player::MainPlayer->SetPos({ 1720, 2630 });

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(Player::MainPlayer->GetPos() - WinScale.Half());

	ITEM_HealthCrystal* HealthCrystal = CreateActor<ITEM_HealthCrystal>();
	HealthCrystal->SetPos({ 1720, 1600 });

	EFFECT_GoldCastingCircle* GoldCastingCircle = CreateActor<EFFECT_GoldCastingCircle>();
	GoldCastingCircle->SetPos({ 1720, 1650 });


	CreateActor<PlayUIManager>();








	Boss* NewBoss = CreateActor<Boss>();
	NewBoss->SetPos({ 1750, 700 });

}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}