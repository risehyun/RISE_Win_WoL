#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineWindowTexture.h"

// ���� :
class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	HDC GetHDC()
	{
		return Hdc;
	}

	HWND GetHWND()
	{
		return hWnd;
	}

	float4 GetScale()
	{
		return Scale;
	}

	GameEngineWindowTexture* GetWindowBuffer()
	{
		return WindowBuffer;
	}

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	float4 GetMousePos();

	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

	static void WindowLoopOff()
	{
		IsWindowUpdate = false;
	}

	void ClearBackBuffer();

	void DoubleBuffering();

	void CursorOff();

	static bool IsFocus()
	{
		return IsFocusValue;
	}

protected:

private:
	static bool IsWindowUpdate;
	static bool IsFocusValue;
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;


	float4 Scale;
	GameEngineWindowTexture* WindowBuffer = nullptr;

	GameEngineWindowTexture* BackBuffer = nullptr;

	HDC Hdc = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass(HINSTANCE hInstance);
};

