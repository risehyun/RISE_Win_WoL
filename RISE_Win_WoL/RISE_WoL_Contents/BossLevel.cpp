#include "BossLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ITEM_HealthCrystal.h"
#include "EFFECT_GoldCastingCircle.h"

#include "PlayUIManager.h"

#include "Spawner_BossTrigger.h"


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

	if (nullptr == GameEngineSound::FindSound("Boss.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Boss.wav"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("BossStage_resize.Bmp", "BossStage_Col_resize.Bmp");



}

void BossLevel::Update(float _Delta)
{

	float4 t = GameEngineWindow::MainWindow.GetMousePos();
	PlayUIManager::UI->MousePtr->SetRenderPos(t);

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

	BGMPlayer = GameEngineSound::SoundPlay("Boss.wav");

	PlayUIManager::UI->NewHpBar->OverOff();

	Player::MainPlayer->SetGroundTexture("BossStage_Col_resize.bmp");
	Player::MainPlayer->SetPos({ 1720, 2630 });

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(Player::MainPlayer->GetPos() - WinScale.Half());

	ITEM_HealthCrystal* HealthCrystal = CreateActor<ITEM_HealthCrystal>();
	HealthCrystal->SetPos({ 1720, 1600 });

	EFFECT_GoldCastingCircle* GoldCastingCircle = CreateActor<EFFECT_GoldCastingCircle>();
	GoldCastingCircle->SetPos({ 1720, 1650 });


	CreateActor<PlayUIManager>();



	Spawner_BossTrigger* NewTigger = CreateActor<Spawner_BossTrigger>();
	NewTigger->SetPos({ 1700, 900 });

}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}