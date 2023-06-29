#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include <string>
#include <list>

class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;

class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;

public:
	GameEngineActor();
	virtual ~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	float4 GetPos() const
	{
		return Pos;
	}

	int GetAttackPower() const
	{
		return m_iAttackPower;
	}

	// ÀÌ¸§ÀÌ ¾ø´Â ºó ·»´õ·¯¸¦ ¸¸µì´Ï´Ù.
	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(EnumType _Order)
	{
		return CreateRenderer("", static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(int _Order = 0)
	{
		return CreateRenderer("", static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, EnumType _Order)
	{
		return CreateRenderer(_ImageName, static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, int _Order);

	template<typename EnumType>
	GameEngineRenderer* CreateUIRender(EnumType _Order)
	{
		return CreateUIRenderer("", static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateUIRenderer(int _Order = 0)
	{
		return CreateUIRenderer("", static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRenderer* CreateUIRenderer(const std::string& _ImageName, EnumType _Order)
	{
		return CreateUIRenderer(_ImageName, static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateUIRenderer(const std::string& _ImageName, int _Order);



	template<typename EnumType>
	GameEngineCollision* CreateCollision(EnumType _Order)
	{
		return CreateCollision(static_cast<int>(_Order));
	}

	GameEngineCollision* CreateCollision(int _Order = 0);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

	bool IsLevelOver()
	{
		return IsOverValue;
	}

	void OverOn()
	{
		IsOverValue = true;
	}

	void OverOff()
	{
		IsOverValue = false;
	}


protected:
	virtual void LevelStart() {}
	virtual void LevelEnd() {}



	float	m_fMoveSpeed = 0.0f;
	float	m_fAttackSpeed = 0.0f;
	float	m_fAttackRange = 0.0f;

	int		m_iAttackPower = 0;
	int		m_iMaxHp = 0;
	int		m_iCurHp = 0;

private:
	bool IsOverValue = false;

	GameEngineLevel* Level;

	float4 Pos = float4::ZERO;
	float4 Scale = float4::ZERO;

	std::list<GameEngineRenderer*> AllRenderer;
	std::list<GameEngineCollision*> AllCollision;


	void ActorRelease();
};