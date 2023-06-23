#include "BossLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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

	LevelPlayer = CreateActor<Player>();

	LevelPlayer->SetGroundTexture("BossStage_Col_resize.bmp");

}

void BossLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
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
	//if (nullptr == LevelPlayer)
	//{
	//	MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	//}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());


	Boss* NewBoss = CreateActor<Boss>();

	NewBoss->SetPos({ 1850, 1400 });

}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}