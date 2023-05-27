#pragma once
#include <string>

class GameEngineString
{
public:
	GameEngineString();
	~GameEngineString();

	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(const GameEngineString&& _Other) = delete;

	static std::string ToUpperReturn(const std::string& _Value)
	{
		std::string UpperString = _Value;

		for (size_t i = 0; i < UpperString.size(); i++)
		{
			UpperString[i] = toupper(UpperString[i]);
		}

		return UpperString;
	}

	// Ansi == 멀티바이트 인코딩
	static std::wstring AnsiToUnicode(const std::string& _Text);
	static std::string UnicodeToAnsi(const std::wstring& _Text);
	static std::string UnicodeToUTF8(const std::wstring& _Text);
	static std::string AnsiToUTF8(const std::string& _Text);

protected:

private:
	
};