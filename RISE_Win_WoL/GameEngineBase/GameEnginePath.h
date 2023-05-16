#pragma once
#include <string>
#include <filesystem>

class GameEnginePath
{
public:
	GameEnginePath();
	GameEnginePath(const std::string& _path);
	~GameEnginePath();

	std::string GetFileName();

	void SetCurrentPath();
	void MoveParent();
	void MoveParentToExistsChild(const std::string& _ChildPath);
	void MoveChild(const std::string& _ChildPath);
	std::string PlusFilePath(const std::string& _ChildPath);

	std::string GetStringPath()
	{
		return Path.string();
	}

	bool IsDirectory();

protected:
	std::filesystem::path Path;

private:

};

