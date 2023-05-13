#include <iostream>
#include <GameEngineCore/GameEngineCore.h>
#include <RISE_WoL_Contents/ContentCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart<ContentCore>("Wizard of Legend", hInstance);
	return 0;
}