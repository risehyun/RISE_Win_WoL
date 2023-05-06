#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

class GameEngineActor : public GameEngineObject
{
public:
	GameEngineActor();
	~GameEngineActor();

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

	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	float4 GetPos() const
	{
		return Pos;
	}

	float4 GetScale() const
	{
		return Scale;
	}

protected:

private:
	float4 Pos;
	float4 Scale;
};