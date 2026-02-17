#include <iostream>
#include "App/Application.h"


// メイン関数
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{

#ifdef _DEBUG
	// コンソールを生成
	AllocConsole();

	// 標準出力 & エラー出力をコンソールに接続
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	printf("デバックモード");
#endif

	// アプリケーション起動
	Application::StartApp("ここにゲームタイトルを入力");

	return 0;
}