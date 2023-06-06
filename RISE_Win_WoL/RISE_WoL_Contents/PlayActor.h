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


	void CameraFocus();

	void SetGroundTexture(const std::string& _GroundTextureName);

	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	float4 ActorCameraPos();

protected:
	float	m_fMoveSpeed = 0.0f;
	float	m_fAttackSpeed = 0.0f;
	float	m_fAttackRange = 0.0f;
	int		m_iMaxHp = 0;
	int		m_iCurHp = 0;

	virtual void SetInitStat();

	virtual void OnDamaged();

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;



};