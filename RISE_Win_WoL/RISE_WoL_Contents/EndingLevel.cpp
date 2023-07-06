#include "EndingLevel.h"
#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include "Player.h"
//#include "PlayUIManager.h"

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	BackGround* EndingBackGround = CreateActor<BackGround>();
	EndingBackGround->Init("Background12.Bmp", 0.75f, { 640, 400 });
	EndingBackGround->SetOrder(1000);

	if (nullptr == GameEngineSound::FindSound("Ending.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Ending.wav"));
	}

}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineSound::SoundPlay("Ending.wav");
	Player::MainPlayer->OverOff();
}

void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
