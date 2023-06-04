#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

// lib�� ������ ����ϰڴٴ� ��ó�����Դϴ�.
// lib�� �����̴�.
#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

////////////////////////////////////////////////// SoundPlayer

void GameEngineSoundPlayer::SetLoop(int _Count)
{
	Control->setLoopCount(_Count);
}

void GameEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * GameEngineSound::GlobalVolume);
}

void GameEngineSoundPlayer::Stop()
{
	Control->stop();
}


// FMOD�� ����ϱ� ���� �ڵ� �� ��ü
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		// �̷� �ܺ� �Լ��� ���ο��� new�� �ϰ� �ֽ��ϴ�.
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�.");
		}
	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

void GameEngineSound::Update()
{
	if (nullptr == SoundSystem)
	{
		MsgBoxAssert("Sound System�� �������� �ʾƼ� ���� ������Ʈ�� �������� �����ϴ�.");
	}

	SoundSystem->update();
}


SoundSystemCreator SoundInitObject = SoundSystemCreator();

float GameEngineSound::GlobalVolume = 1.0f;

std::map<std::string, GameEngineSound*> GameEngineSound::AllSound;

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
	if (nullptr != SoundHandle)
	{
		SoundHandle->release();
	}
}

GameEngineSound* GameEngineSound::FindSound(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllSound.find(UpperName);

	if (FindIter == AllSound.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSound::SoundLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineSound* NewSound = new GameEngineSound();

	NewSound->Load(_Path);

	AllSound.insert(std::make_pair(UpperName, NewSound));
}

GameEngineSoundPlayer GameEngineSound::SoundPlay(const std::string& _Name, int _Loop)
{
	GameEngineSound* FindSoundPtr = FindSound(_Name);

	if (nullptr == FindSoundPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineSoundPlayer Player = FindSoundPtr->Play();

	Player.SetVolume(1.0f);

	Player.SetLoop(_Loop);

	return Player;
}

void GameEngineSound::Release()
{
	for (std::pair<std::string, GameEngineSound*> Pair : GameEngineSound::AllSound)
	{
		if (nullptr == Pair.second)
		{
			return;
		}

		delete Pair.second;
	}
}


void GameEngineSound::Load(const std::string& _Path)
{
	std::string UTF8 = GameEngineString::AnsiToUTF8(_Path);

	SoundSystem->createSound(UTF8.c_str(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("���� �ε忡 �����߽��ϴ�.");
	}
}

FMOD::Channel* GameEngineSound::Play()
{
	FMOD::Channel* SoundControl = nullptr;

	SoundSystem->playSound(SoundHandle, nullptr, false, &SoundControl);

	return SoundControl;
}