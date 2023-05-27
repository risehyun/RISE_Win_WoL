#include "GameEngineString.h"
#include "GameEngineDebug.h"
#include <Windows.h>

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

// ""(멀티바이트) => L""(와이드바이트)로 변환
std::wstring GameEngineString::AnsiToUnicode(const std::string& _Text)
{
	// CP_ACP : 운영체제가 사용하는 것
	// 아무것도 넣지 않으면 _Text.c_str()이 몇바이트가 되어야 widebyte로 변환할 수 있을지를 리턴한다.
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열의 사이즈가 0이여서 변환할 수 없습니다.");

		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("문자열의 사이즈가 0이여서 변환할 수 없습니다.");

		return L"";
	}

	return Result;
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열의 사이즈가 0이여서 변환할 수 없습니다.");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("문자열의 사이즈가 0이여서 변환할 수 없습니다.");
		return "";
	}

	return Result;
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열의 사이즈가 0이여서 변환할 수 없습니다.");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("문자열의 사이즈가 0이여서 변환할 수 없습니다.");
		return "";
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(const std::string& _Text)
{
	std::wstring UniCode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(UniCode);
}