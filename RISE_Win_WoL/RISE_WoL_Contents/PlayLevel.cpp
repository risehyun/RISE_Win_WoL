#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEnginePlatform/GameEngineSound.h>

#include "Player.h"
#include "BackGround.h"
#include "Monster.h"
#include "Effect_Spawn.h"

#include "PlayUIManager.h"


#include "ContentsEnum.h"


PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
//	GameEngineSound::SoundLoad("aaa", "aaa");

	if (false == ResourcesManager::GetInst().IsLoadTexture("stage1_Col.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;
		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("stage1_Col.bmp"));



		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MiniBossActivationCircle.bmp"));

// 애니메이션을 사용하는 경우 중복해서 로드하면 오류 발생함
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("SPAWN_PLAYER.bmp"));

	}

	BackGroundPtr = CreateActor<BackGround>();

	BackGroundPtr->Init("stage1.Bmp", "stage1_Col.bmp");

	LevelPlayer = CreateActor<Player>();

	LevelPlayer->SetGroundTexture("stage1_Col.bmp");

	CreateActor<PlayUIManager>();








	// 보스스포너 -> 따로 빼기

	BackGround* SmallObjPtr = CreateActor<BackGround>();

	SmallObjPtr->Init("MiniBossActivationCircle.bmp", 3.0f, { 1850, 1800 });


	// 플레이어 스폰 효과

	Effect_Spawn* NewSpawn = CreateActor<Effect_Spawn>();

	NewSpawn->SetPos({ 1850, 1800 });


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

	// 몬스터 스폰
	//if (1.0f <= GetLiveTime())
	//{
	//	Monster* NewMonster = CreateActor<Monster>();
	//	ResetLiveTime();
	//}
}

void PlayLevel::Render(float _Delta)
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