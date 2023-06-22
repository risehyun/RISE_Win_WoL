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
		ChanageState(PlayerState::Run);
		return;
	}

	// 일반 공격
	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		ChanageState(PlayerState::Attack);

		SKILL_PlayerNormalAttack* NewAttack = GetLevel()->CreateActor<SKILL_PlayerNormalAttack>();

		DirCheck();

		if (Dir == PlayerDir::Left)
		{
			NewAttack->SetDir(float4::LEFT);
			NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_LEFT");
		}

		if (Dir == PlayerDir::Right)
		{
			NewAttack->SetDir(float4::RIGHT);
			NewAttack->SetPos(GetPos() + float4{ 100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_RIGHT");
		}

		if (Dir == PlayerDir::Up)
		{
			NewAttack->SetDir(float4::UP);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, -100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_UP");
		}


		if (Dir == PlayerDir::Down)
		{
			NewAttack->SetDir(float4::DOWN);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, 100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_DOWN");
		}

		return;
	}

	if (true == GameEngineInput::IsDown(VK_RBUTTON))
	{

		float4 MovePos = float4::ZERO;

		DirCheck();

		ChanageState(PlayerState::Attack);

		SKILL_Tornado* NewAttack = GetLevel()->CreateActor<SKILL_Tornado>();
		NewAttack->SetPos({ GetPos() });

		return;
	}

	if (true == GameEngineInput::IsDown('Q'))
	{
		ChanageState(PlayerState::Skill_EarthenAegis);
		SKILL_EarthenAegis* NewAttack = GetLevel()->CreateActor<SKILL_EarthenAegis>();
		NewAttack->SetPos(GetPos() + float4{ 0.0f, 0.0f, 0.0f, 0.0f });
		return;
	}

	if (true == GameEngineInput::IsDown('E'))
	{
		ChanageState(PlayerState::Skill_SnowflakeChakrams);
		SKILL_SnowflakeChakrams* NewAttack = GetLevel()->CreateActor<SKILL_SnowflakeChakrams>();
		NewAttack->SetPos(GetPos() + float4{ 0.0f, 0.0f, 0.0f, 0.0f });
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChanageState(PlayerState::Skill_ExplodingFireball);
		SKILL_Fireball* NewAttack = GetLevel()->CreateActor<SKILL_Fireball>();
		DirCheck();

		if (Dir == PlayerDir::Left)
		{
			NewAttack->SetDir(float4::LEFT);
			NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Left");
		}

		if (Dir == PlayerDir::Right)
		{
			NewAttack->SetDir(float4::RIGHT);
			NewAttack->SetPos(GetPos() + float4{ 100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Right");
			NewAttack->Renderer->SetRenderScale({ 120, 80 });
		}

		if (Dir == PlayerDir::Up)
		{
			NewAttack->SetDir(float4::UP);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, -100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Up");
			NewAttack->Renderer->SetRenderScale({ 160, 120 });
		}

		if (Dir == PlayerDir::Down)
		{
			NewAttack->SetDir(float4::DOWN);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, 100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Down");
			NewAttack->Renderer->SetRenderScale({ 160, 120 });
		}

		return;
	}

	if (true == GameEngineInput::IsUp(VK_SPACE))
	{
		ChanageState(PlayerState::Dash);
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
		ChanageState(PlayerState::Idle);
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChanageState(PlayerState::Attack);

		SKILL_PlayerNormalAttack* NewAttack = GetLevel()->CreateActor<SKILL_PlayerNormalAttack>();

		DirCheck();

		if (Dir == PlayerDir::Left)
		{
			NewAttack->SetDir(float4::LEFT);
			NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_LEFT");
		}

		if (Dir == PlayerDir::Right)
		{
			NewAttack->SetDir(float4::RIGHT);
			NewAttack->SetPos(GetPos() + float4{ 100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_RIGHT");
		}

		if (Dir == PlayerDir::Up)
		{
			NewAttack->SetDir(float4::UP);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, -100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_UP");
		}


		if (Dir == PlayerDir::Down)
		{
			NewAttack->SetDir(float4::DOWN);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, 100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_DOWN");
		}

		return;
	}

	if (true == GameEngineInput::IsUp(VK_SPACE))
	{
		ChanageState(PlayerState::Dash);
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

	DirCheck();

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
			ChanageState(PlayerState::Run);
		}

		else
		{
			ChanageState(PlayerState::Idle);
		}

		ResetLiveTime();
	}

	return;
}

// 수정 필요
void Player::AttackUpdate(float _Delta)
{
	if (1.5f <= GetLiveTime())
	{
		DirCheck();
		ChanageState(PlayerState::Idle);

		ResetLiveTime();
	}

	return;
}

void Player::OnDamagedUpdate(float _Delta)
{
	DirCheck();

	if (true == IsDeath()) {
		ChanageState(PlayerState::Death);
	}

	else if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		ChanageState(PlayerState::Run);
		return;
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChanageState(PlayerState::Idle);
	}
}

void Player::DeathUpdate(float _Delta)
{
	// 추후 페이드아웃 추가
	if (true == MainRenderer->IsAnimationEnd())
	{
		EffectPlayer.Stop();
		GameEngineCore::ChangeLevel("EndingLevel");
	}
}

void Player::Skill_EarthenAgis_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChanageState(PlayerState::Idle);
	}

}

void Player::Skill_SnowflakeChakrams_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChanageState(PlayerState::Idle);
	}
}

void Player::Skill_Tornado_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChanageState(PlayerState::Idle);
	}
}

void Player::Skill_Fireball_Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChanageState(PlayerState::Idle);
	}
}