#include "Player.h"
#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Bullet.h"

Player::Player()
{
}

Player::~Player()
{

}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");




		// sprite �ε�


		// ĳ���� �̵�


		// �̹� �ε��� ��������Ʈ�� �� 

		if (false == ResourcesManager::GetInst().IsLoadTexture("FRONT_COMPLETE.bmp"))
		{
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FRONT_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BACK_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LEFT_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RIGHT_COMPLETE.bmp"), 11, 7);
		}




		if(false == ResourcesManager::GetInst().IsLoadTexture("idle.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("idle.bmp"));
		}


		if (false == ResourcesManager::GetInst().IsLoadTexture("Fireball_0.Bmp"))
		{		
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Fireball_0.bmp"));
		}

		// UI �ӽ�
		if (false == ResourcesManager::GetInst().IsLoadTexture("HPBar.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_PLAYERBAR.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MONEY.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SKILLBAR.bmp"));
		}







		{
			MainRenderer = CreateRenderer(RenderOrder::Play);
			MainRenderer->SetRenderScale({ 100, 100 });

			MainRenderer->CreateAnimation("Idle_FRONT", "FRONT_COMPLETE.bmp", 0, 0, 0.1f, true);



			// RUN
			MainRenderer->CreateAnimation("Run_FRONT", "FRONT_COMPLETE.bmp", 12, 14, 0.1f, true);

			MainRenderer->CreateAnimation("Run_BACK", "BACK_COMPLETE.bmp", 12, 14, 0.1f, true);

			MainRenderer->CreateAnimation("Run_LEFT", "LEFT_COMPLETE.bmp", 12, 16, 0.1f, true);

			MainRenderer->CreateAnimation("Run_RIGHT", "RIGHT_COMPLETE.bmp", 12, 16, 0.1f, true);


			//		MainRenderer->SetRenderScaleToTexture();




			//		MainRenderer->ChangeAnimation("Idle");
		}


		{
			GameEngineRenderer* Ptr = CreateRenderer("UI_PLAYERBAR.bmp", RenderOrder::Play);
			Ptr->SetRenderPos({ -425, -320 });
			Ptr->SetRenderScale({ 328, 80 });
			Ptr->SetTexture("UI_PLAYERBAR.bmp");
		}

		{
			GameEngineRenderer* Ptr = CreateRenderer("UI_MONEY.bmp", RenderOrder::Play);
			Ptr->SetRenderPos({ 0, 340 });
			Ptr->SetRenderScale({ 16, 16 });
			Ptr->SetTexture("UI_MONEY.bmp");
		}

		{
			GameEngineRenderer* Ptr = CreateRenderer("UI_SKILLBAR.bmp", RenderOrder::Play);
			Ptr->SetRenderPos({ -425, 340 });
			Ptr->SetRenderScale({ 400, 100 });
			Ptr->SetTexture("UI_SKILLBAR.bmp");
		}
	}



	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	SetPos(WinScale.Half());


	ChanageState(PlayerState::Idle);

}

void Player::Update(float _Delta)
{

	StateUpdate(_Delta);

//
//	if (true == GameEngineInput::IsUp(VK_LBUTTON))
//	{
//		float4 Pos = GameEngineWindow::MainWindow.GetMousePos();
//
//		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
//		NewBullet->Renderer->SetTexture("Fireball_0.bmp");
//
//		NewBullet->SetDir(float4::RIGHT);
//		NewBullet->SetPos(GetPos());
////		NewBullet->SetPos(Pos);
//	}

//	AddPos(MovePos);
//	GetLevel()->GetMainCamera()->AddPos(MovePos);
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}