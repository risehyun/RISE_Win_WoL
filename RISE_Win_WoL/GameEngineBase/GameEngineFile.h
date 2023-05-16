#pragma once
#include "GameEnginePath.h"
#include <string>

class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _path);
	~GameEngineFile();

protected:

private:

};
