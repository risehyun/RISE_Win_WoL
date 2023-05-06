#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

class GameEngineTexture;

class ResourcesManager
{
public:
	ResourcesManager(const ResourcesManager& _Other) = delete;
	ResourcesManager(ResourcesManager&& _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(ResourcesManager&& _Other) noexcept = delete;

	static ResourcesManager& GetInst()
	{
		return Inst;
	}
	
	// ���ϸ��� ����Ͽ� ã���� �ϴ� �ؽ��ĸ� �ε��մϴ�.
	void TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		TextureLoad(LoadPath.GetFileName(), _Path);
	}

	void TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineTexture* FindTexture(const std::string& _Name);

	bool IsLoadTexture(const std::string& _Image);


protected:

private:
	static ResourcesManager Inst;

	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineTexture*> AllTexture;
};