#include "GameEngineSound.h"

#ifdef  _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#endif //  _DEBUG

// FMOD�� ����ϱ� ���� �ڵ� �� ��ü

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
}

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
	
	}

	~SoundSystemCreator()
	{
	
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();

void GameEngineSound::SoundLoad(std::string& _Name, std::string& _Path)
{

}

void GameEngineSound::SoundPlay(std::string& _Name)
{

}

// 1���� ����� �ϰ� ���� Ư�� ���� �ȴ�.
void GameEngineSound::PlayBgm(std::string& _Name)
{

}

// Ư�� �����Ǵ� ���� ����� �����.
void GameEngineSound::StopBgm()
{

}