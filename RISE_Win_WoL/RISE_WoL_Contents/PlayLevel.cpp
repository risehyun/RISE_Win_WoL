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
#include "BossSpawner.h"

#include "PlayUIManager.h"

#include "NPC_ITEMSHOP.h"
#include "NPC_ArcanaShop.h"
#include "NPC_Collector.h"
#include "NPC_Outfit.h"

#include "ContentsEnum.h"


// 06-25 테스트용
#include "Monster_Archer.h"


// 06-26 테스트용
#include "MiniBoss_GrandSummoner.h"


// 06-14 테스트용
#include "Effect_CastingCircle.h"
#include "PROP_TreasureChestMiniBoss.h"
#include "PROP_Teleport.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{

	GameEngineWindow::MainWindow.CursorOff();


	if (false == ResourcesManager::GetInst().IsLoadTexture("stage1_Col.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;
		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("stage1_Col.bmp"));
	}

	if (nullptr == GameEngineSound::FindSound("Earth.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Earth.wav"));
	}

	BackGroundPtr = CreateActor<BackGround>();

	BackGroundPtr->Init("stage1.bmp", "stage1_Col.bmp");

	Player::MainPlayer = CreateActor<Player>();




	CreateActor<PlayUIManager>();



	// 보스스포너 -> 따로 빼기
	Spawner = CreateActor<BossSpawner>();


	// 플레이어 스폰 효과
	Effect_Spawn* NewSpawn = CreateActor<Effect_Spawn>();
	NewSpawn->SetPos({ 1850, 1800 });
	NewSpawn->SpawnObject(SpawnType::Player, { 100, 365 });




	NPC_ArcanaShop* NewArcanaShop = CreateActor<NPC_ArcanaShop>();
	NewArcanaShop->SetPos({ 3000, 1600 });

	NPC_ITEMSHOP* NewShop = CreateActor<NPC_ITEMSHOP>();
	NewShop->SetPos({ 700, 1600 });

	NPC_Collector* NewCollector = CreateActor<NPC_Collector>();
	NewCollector->SetPos({ 1850, 2800 });

	NPC_Outfit* NewOutfit = CreateActor<NPC_Outfit>();
	NewOutfit->SetPos({ 1850, 700 });

}

void PlayLevel::Update(float _Delta)
{
	//if (true == GameEngineInput::IsDown(VK_RIGHT))
	//{
	//	GameEngineCore::ChangeLevel("BossLevel");
	//}

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}

	if (true == Spawner->GetLevelState())
	{
		if (NewEffect == nullptr)
		{
			NewEffect = CreateActor<Effect_CastingCircle>();
			NewEffect->SetPos({ 1850, 1700 });

		}

		if (NewChest == nullptr)
		{
			NewChest = CreateActor<PROP_TreasureChestMiniBoss>();
			NewChest->SetPos({ 1870, 1650 });
		}

		if (NewTeleport == nullptr)
		{
			NewTeleport = CreateActor<PROP_Teleport>();
			NewTeleport->SetPos({ 1850, 2000 });

			Effect_Spawn* NewSpawn = CreateActor<Effect_Spawn>();
			NewSpawn->SetPos({ 1850, 2000 });
			NewSpawn->SpawnObject(SpawnType::Player, { 300, 365 });

		}

	}

}

void PlayLevel::Render(float _Delta)
{
}

void PlayLevel::Release()
{
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->SetGroundTexture("stage1_Col.bmp");



//	BGMPlayer = GameEngineSound::SoundPlay("Earth.wav");

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	Player::MainPlayer->OverOn();
}