#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

// ����
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

class GameEngineSoundPlayer
{
	friend class GameEngineSound;

public:

	void SetVolume(float _Volume);
	void Stop();

	GameEngineSoundPlayer()
	{

	}

private:
	GameEngineSoundPlayer(FMOD::Channel* _Control)
		: Control(_Control)
	{
	}

	FMOD::Channel* Control = nullptr;
};

// ���� :
class GameEngineSound
{
	static float GlobalVolume;

	// Management

	friend class SoundSystemCreator;
	friend class GameEngineSoundPlayer;

private:
	static std::map<std::string, GameEngineSound*> AllSound;

public:
	static void SetGlobalVolume(float _Value)
	{
		GlobalVolume = _Value;
	}

	static float GetGlobalVolume()
	{
		return GlobalVolume;
	}

	static void SoundLoad(const std::string& _Path)
	{
		GameEnginePath Path = _Path;
		SoundLoad(Path.GetFileName(), _Path);
	}

	static GameEngineSound* FindSound(const std::string& _Name);


	static void SoundLoad(const std::string& _Name, const std::string& _Path);

	static GameEngineSoundPlayer SoundPlay(const std::string& _Name);

	static void Release();

	static void Update();


public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:

private:
	FMOD::Sound* SoundHandle = nullptr;

	FMOD::Channel* Play();
	void Load(const std::string& _Path);
};
