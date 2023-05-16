#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}

GameEngineDirectory::GameEngineDirectory(const std::string& _path)
	:GameEnginePath(_path)
{
	if (false == IsDirectory())
	{
		MsgBoxAssert("���丮 ��ΰ� �ƴմϴ�." + _path);
	}
}