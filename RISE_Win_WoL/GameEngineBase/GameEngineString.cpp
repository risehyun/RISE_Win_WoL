#include "GameEngineString.h"
#include "GameEngineDebug.h"
#include <Windows.h>

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

// ""(��Ƽ����Ʈ) => L""(���̵����Ʈ)�� ��ȯ
std::wstring GameEngineString::AnsiToUnicode(const std::string& _Text)
{
	// CP_ACP : �ü���� ����ϴ� ��
	// �ƹ��͵� ���� ������ _Text.c_str()�� �����Ʈ�� �Ǿ�� widebyte�� ��ȯ�� �� �������� �����Ѵ�.
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ����� 0�̿��� ��ȯ�� �� �����ϴ�.");

		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ����� 0�̿��� ��ȯ�� �� �����ϴ�.");

		return L"";
	}

	return Result;
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ����� 0�̿��� ��ȯ�� �� �����ϴ�.");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ����� 0�̿��� ��ȯ�� �� �����ϴ�.");
		return "";
	}

	return Result;
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ����� 0�̿��� ��ȯ�� �� �����ϴ�.");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ����� 0�̿��� ��ȯ�� �� �����ϴ�.");
		return "";
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(const std::string& _Text)
{
	std::wstring UniCode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(UniCode);
}