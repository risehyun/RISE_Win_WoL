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


		if (false == ResourcesManager::GetInst().IsLoadTexture("FRONT_COMPLETE.bmp"))
		{
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FRONT_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BACK_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LEFT_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RIGHT_COMPLETE.bmp"), 11, 7);



			// 스킬 테스트
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PLAYER_NORMAL_ATTACK.bmp"), 8, 8);
		}

		if(false == ResourcesManager::GetInst().IsLoadTexture("idle.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("idle.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("Fireball_0.Bmp"))
		{		
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Fireball_0.bmp"));
		}

		// UI 임시
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

			MainRenderer->CreateAnimation("Left_Idle", "LEFT_COMPLETE.bmp", 0, 0, 0.1f, true);

			MainRenderer->CreateAnimation("Right_Idle", "RIGHT_COMPLETE.bmp", 0, 0, 0.1f, true);

			MainRenderer->CreateAnimation("Attack_NORMAL", "PLAYER_NORMAL_ATTACK.bmp", 0, 8, 0.1f, true);

			// RUN
			MainRenderer->CreateAnimation("Front_Run", "FRONT_COMPLETE.bmp", 12, 14, 0.1f, true);

			MainRenderer->CreateAnimation("Back_Run", "BACK_COMPLETE.bmp", 12, 14, 0.1f, true);

			MainRenderer->CreateAnimation("Left_Run", "LEFT_COMPLETE.bmp", 12, 16, 0.1f, true);

			MainRenderer->CreateAnimation("Right_Run", "RIGHT_COMPLETE.bmp", 12, 16, 0.1f, true);


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
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);

	case PlayerState::Run:
		return RunUpdate(_Delta);
	
	//case PlayerState::Attack:
	//	return AttackUpdate(_Delta);

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

		//case PlayerState::Attack:
		//	AttackStart();
		//	break;

		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}
}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName
	std::string AnimationName;
	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;
	CurState = _StateName;
	MainRenderer->ChangeAnimation(AnimationName);
}