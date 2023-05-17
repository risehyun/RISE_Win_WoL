#include "BossLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Player.h"
#include "BackGround.h"


BossLevel::BossLevel()
{
}

BossLevel::~BossLevel()
{
}

void BossLevel::Start()
{
	BackGround* Back = CreateActor<BackGround>();

	Back->Init("BossStage.Bmp", 3.0f, { 640, 400 });

	LevelPlayer = CreateActor<Player>();
}

void BossLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}
}

void BossLevel::Render()
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

}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}