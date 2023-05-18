#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayActor : public GameEngineActor
{
public:
	PlayActor();
	~PlayActor();

	PlayActor(const PlayActor& _Other) = delete;
	PlayActor(PlayActor&& _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor& _Other) = delete;
	PlayActor& operator=(PlayActor&& _Other) noexcept = delete;

	void Gravity(float _Delta);

	void CameraFocus();

	void GravityOff()
	{
		IsGravity = false;
	}

	void GravityOn()
	{
		IsGravity = true;
	}

	void SetGroundTexture(const std::string& _GroundTextureName);

protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool IsGravity = false;

	float GravityPower = 10.0f;
	float4 GravityVector = float4::ZERO;
};