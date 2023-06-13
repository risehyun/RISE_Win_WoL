#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>
#include "resource.h"

HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;
bool GameEngineWindow::IsWindowUpdate = true;

bool GameEngineWindow::IsFocusValue = false;

GameEngineWindow::GameEngineWindow()
{

}

GameEngineWindow::~GameEngineWindow()
{
	if (nullptr != BackBuffer)
	{
		delete BackBuffer;
		BackBuffer = nullptr;
	}


	if (nullptr != WindowBuffer)
	{
		delete WindowBuffer;
		WindowBuffer = nullptr;
	}
}

void GameEngineWindow::ClearBackBuffer()
{
	Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
}

void GameEngineWindow::DoubleBuffering()
{
	WindowBuffer->BitCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale());
}

void GameEngineWindow::Open(const std::string& _Title, HINSTANCE _hInstance)
{
	Instance = _hInstance;
	Title = _Title;

	if (nullptr == Instance)
	{
		MsgBoxAssert("HInstance없이 윈도우를 만들수는 없습니다.");
		return;
	}

	MyRegisterClass(Instance);
	InitInstance();
}


void GameEngineWindow::InitInstance()
{
	hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

	if (!hWnd)
	{
		MsgBoxAssert("윈도우 생성에 실패했습니다.");
		return;
	}

	Hdc = ::GetDC(hWnd);

	WindowBuffer = new GameEngineWindowTexture();
	WindowBuffer->ResCreate(Hdc);

	// 더플버퍼링을 하기 위해 이미지를 담을 버퍼 준비
	BackBuffer = new GameEngineWindowTexture();

	// 윈도우에 그릴 수 있는 스케일로 생성
	BackBuffer->ResCreate(WindowBuffer->GetScale());

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_SETFOCUS:
	{
		IsFocusValue = true;
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_KILLFOCUS:
	{
		IsFocusValue = false;
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		IsWindowUpdate = false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameEngineWindow::MyRegisterClass(HINSTANCE hInstance)
{
	static bool Check = false;

	if (true == Check)
	{
		return;
	}

	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GameEngineWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Instance;
	wcex.hIcon = nullptr;
//	wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "DefaultWindow";
	wcex.hIconSm = nullptr;

	if (false == RegisterClassExA(&wcex))
	{
		MsgBoxAssert("윈도우 클래스 동록에 실패했습니다.");
		return;
	}

	Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
	// 윈도우가 뜨기전에 로딩해야할 이미지나 사운드 등등을 처리하는 단계
	if (nullptr != _Start)
	{
		_Start(_Inst);
	}

	MSG msg;

	while (IsWindowUpdate)
	{

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (nullptr != _Update)
			{
				_Update();
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		if (nullptr != _Update)
		{
			_Update();
		}

	}

	if (nullptr != _End)
	{
		_End();
	}

	return;
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
	Scale = _Scale;

	if (nullptr != BackBuffer)
	{
		delete BackBuffer;
		BackBuffer = new GameEngineWindowTexture();
		BackBuffer->ResCreate(Scale);
	}

	RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };

	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);

}

float4 GameEngineWindow::GetMousePos()
{
	POINT MoniterPoint;
	GetCursorPos(&MoniterPoint);
	ScreenToClient(hWnd, &MoniterPoint);
	return float4{ static_cast<float>(MoniterPoint.x), static_cast<float>(MoniterPoint.y) };
}

void GameEngineWindow::CursorOff()
{
	ShowCursor(FALSE);
}