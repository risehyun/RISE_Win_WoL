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
#include "ContentsEnum.h"

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

	BackGroundPtr->Init("stage1.Bmp", "stage1_Col.bmp");

	//if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_ITEMSHOP.Bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	GameEnginePath FolderPath = FilePath;
	//	FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_ITEMSHOP.bmp"));

	//	GameEngineRenderer* Ptr = CreateRenderer("UI_PLAYERBAR.bmp", RenderOrder::Play);
	//	Ptr->SetRenderPos({ -425, -320 });
	//	Ptr->SetRenderScale({ 328, 80 });
	//	Ptr->SetTexture("UI_PLAYERBAR.bmp");
	//}

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

	// ���� ����
	if (1.0f <= GetLiveTime())
	{
		Monster* NewMonster = CreateActor<Monster>();
		ResetLiveTime();
	}
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
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}

	LevelPlayer->SetGroundTexture("stage1_Col.bmp");

	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}