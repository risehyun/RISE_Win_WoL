#include "TitleLevel.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCamera.h>

#include "UI_Button.h"
#include "BackGround.h"
#include "ContentsEnum.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	GameEngineSound::SetGlobalVolume(0.5f);

	BackGround* Back = CreateActor<BackGround>();

	Back->Init("TitleScreen.Bmp", 0.75f, { 640, 400 });

	if (nullptr == GameEngineSound::FindSound("TitleScreen.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("TitleScreen.wav"));
	}
}

void TitleLevel::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown(VK_RETURN))
	{

		BackGround* SelectScreen = CreateActor<BackGround>();
		SelectScreen->Init("TitleScreenSelect_DEFALUT.Bmp", 0.75f, { 640, 400 });


		if (buttonIndex == 1)
		{
			BGMPlayer.Stop();
			GameEngineCore::ChangeLevel("PlayLevel");
		}

		if (buttonIndex == -1)
		{
			DestroyWindow(GameEngineWindow::MainWindow.GetHWND());
		}

	}

	if (true == GameEngineInput::IsDown('O'))
	{
		BGMPlayer.Stop();
	}





	if (true == GameEngineInput::IsDown('W'))
	{
		BackGround* SelectScreen_Play = CreateActor<BackGround>();
		SelectScreen_Play->Init("TitleScreenSelect_PLAY.Bmp", 0.75f, { 640, 400 });

		buttonIndex = 1;
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		BackGround* SelectScreen_Exit = CreateActor<BackGround>();
		SelectScreen_Exit->Init("TitleScreenSelect_EXIT.Bmp", 0.75f, { 640, 400 });

		buttonIndex = -1;
	}

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineSound::SoundPlay("TitleScreen.wav");

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TitleLevel::Render(float _Delta)
{
}

void TitleLevel::Release()
{
}