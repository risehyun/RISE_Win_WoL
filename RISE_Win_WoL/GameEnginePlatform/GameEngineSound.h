#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

// 선언
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

class GameEngineSoundPlayer
{
	friend class GameEngineSound;

public:
	void Stop()
	{
		Control->stop();
	}

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

// 설명 :
class GameEngineSound
{
	// Management

	friend class SoundSystemCreator;

private:
	static std::map<std::string, GameEngineSound*> AllSound;

public:
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
