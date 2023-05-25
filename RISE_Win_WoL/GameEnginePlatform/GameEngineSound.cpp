#include "GameEngineSound.h"

#ifdef  _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#endif //  _DEBUG

// FMOD를 사용하기 위한 핸들 및 객체

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

// 1번의 재생을 하고 조금 특별 관리 된다.
void GameEngineSound::PlayBgm(std::string& _Name)
{

}

// 특별 관리되는 사운드 재생을 멈춘다.
void GameEngineSound::StopBgm()
{

}