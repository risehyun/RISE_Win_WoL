#include "Player.h"

#pragma region Headers

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"

#include <GameEnginePlatform/GameEngineWindow.h>

#include "SKILL_PlayerNormalAttack.h"
#include "SKILL_PlayerWindBoomerang.h"
#include "SKILL_EarthenAegis.h"
#include "SKILL_SnowflakeChakrams.h"
#include "SKILL_Tornado.h"
#include "SKILL_Fireball.h"

#include <GameEngineCore/GameEngineCore.h>

#pragma endregion

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}

void Player::DashStart()
{
	ChangeAnimationState("Dash");
}

void Player::AttackStart()
{
	DirCheck();
	ChangeAnimationState("Attack");
}

void Player::DeathStart()
{
	EffectPlayer = GameEngineSound::SoundPlay("PLAYER_DIE.mp3");
	EffectPlayer.SetVolume(10.0f);
	ChangeAnimationState("Death");
}

void Player::Skill_EarthenAegis_Start()
{
	ChangeAnimationState("Attack");
}

void Player::Skill_SnowflakeChakrams_Start()
{
	ChangeAnimationState("Attack");
}

void Player::Skill_Tornado_Start()
{
	ChangeAnimationState("Attack");
}

void Player::Skill_Fireball_Start()
{
	ChangeAnimationState("Attack");
}

void Player::OnDamagedStart()
{
	EffectPlayer = GameEngineSound::SoundPlay("PLAYER_HITED.mp3");
	EffectPlayer.SetVolume(10.0f);
	ChangeAnimationState("Damage");
}

void Player::SetTotalGold(int _GoldCount)
{
	m_iTotalGold += _GoldCount;
}

void Player::IdleUpdate(float _Delta)
{


	// 자신의 위치에 해당하는 픽셀의 색상을 체크하기 위해 가져온다.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) == Color)
	{

	}

	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			AddPos(float4::UP);
		}

		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
			AddPos(float4::DOWN);
		}
	}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}

}

void Player::RunUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) == Color)
	{

	}

	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			AddPos(float4::UP);
		}

		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
			AddPos(float4::DOWN);
		}
	}

	DirCheck();

	float Speed = 400.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		CheckPos = LeftCheck;
		MovePos = { -Speed * _Delta, 0.0f };
	}

	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		CheckPos = RightCheck;
		MovePos = { Speed * _Delta, 0.0f };
	}

	else if (true == GameEngineInput::IsPress('W') && Dir == PlayerDir::Up)
	{
		CheckPos = UpCheck;
		MovePos = { 0.0f, -Speed * _Delta };
	}

	else if (true == GameEngineInput::IsPress('S') && Dir == PlayerDir::Down)
	{
		CheckPos = DownCheck;
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

	if (true == GameEngineInput::IsUp(VK_SPACE))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

}

void Player::DashUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) == Color)
	{

	}

	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			AddPos(float4::UP);
		}

		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
			AddPos(float4::DOWN);
		}

	}

	//	DirCheck();

	float Speed = 500.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (Dir == PlayerDir::Left)
	{
		CheckPos = { -15.0f, -30.0f };
		MovePos = { -Speed * _Delta, 0.0f };
	}

	else if (Dir == PlayerDir::Right)
	{
		CheckPos = { 15.0f, -30.0f };
		MovePos = { Speed * _Delta, 0.0f };
	}

	else if (Dir == PlayerDir::Up)
	{
		CheckPos = { -15.0f, 30.0f };
		MovePos = { 0.0f, -Speed * _Delta };
	}

	else if (Dir == PlayerDir::Down)
	{
		CheckPos = { 15.0f, 30.0f };
		MovePos = { 0.0f, Speed * _Delta };
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

	if (1.5f <= GetLiveTime())
	{

		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('W') ||
			true == GameEngineInput::IsPress('S') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(PlayerState::Run);
		}

		else
		{
			ChangeState(PlayerState::Idle);
		}

		ResetLiveTime();
	}

	return;
}

// 수정 필요
void Player::AttackUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		DirCheck();
		ChangeState(PlayerState::Idle);

	}

	return;
}

void Player::OnDamagedUpdate(float _Delta)
{
	//	DirCheck();

	if (true == IsDeath()) {
		ChangeState(PlayerState::Death);
	}

	else if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		ChangeState(PlayerState::Run);
		return;
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::DeathUpdate(float _Delta)
{
	// 추후 페이드아웃 추가

	EffectPlayer.Stop();

	Player::MainPlayer->OverOff();

	if (true == MainRenderer->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}
}

void Player::Skill_EarthenAgis_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}

}

void Player::Skill_SnowflakeChakrams_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::Skill_Tornado_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::Skill_Fireball_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}