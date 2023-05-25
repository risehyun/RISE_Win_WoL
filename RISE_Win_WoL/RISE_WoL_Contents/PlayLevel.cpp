#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Player.h"
#include "BackGround.h"
#include "Monster.h"

#include "PlayUIManager.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("stage1_Col.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;
		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("stage1_Col.bmp"));
	}

	BackGroundPtr = CreateActor<BackGround>();
//	BackGroundPtr->Init("stage1.Bmp", "stage1_Col.bmp", 3.0f, { 640, 400 });
	BackGroundPtr->Init("stage1.Bmp", "stage1_Col.bmp");
	
//	Back->Init("stage1.Bmp", 3.0f, { 640, 400 });
//	Back->Init("BackGround.Bmp", 3.0f, { 770, 770 });
// Back->Init("BossStage.Bmp", 3.0f, { 640, 400 });


	LevelPlayer = CreateActor<Player>();

	LevelPlayer->SetGroundTexture("stage1_Col.bmp");

	CreateActor<PlayUIManager>();
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		GameEngineCore::ChangeLevel("BossLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}

	//// 몬스터 스폰
	//if (1.0f <= GetLiveTime())
	//{
	//	Monster* NewMonster = CreateActor<Monster>();
	//	ResetLiveTime();
	//}
}

void PlayLevel::Render()
{
}

void PlayLevel::Release()
{
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	LevelPlayer->SetGroundTexture("stage1_Col.bmp");

	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}