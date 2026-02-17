#include "Application.h"
#include <algorithm>
#include "../Utilitys/ProjectConfig.h"
#include "../Scenes/SceneManager.h"


HINSTANCE g_hInst;
HWND g_hWnd = NULL;

// アプリケーションの起動
void Application::StartApp(const TCHAR* appName)
{
	// ウィンドウ生成
	InitWindow(appName);

	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{
		return;
	}

	// シーン初期化
	SceneManager& manager = SceneManager::GetInstance();
	manager.Initialize();

	// メイン処理ループ
	MainLoop();
}

// ウィンドウの生成
void Application::InitWindow(const TCHAR* appName)
{
	// ウィンドウモードで起動する
	ChangeWindowMode(TRUE);

	// ウィンドウサイズの設定
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// ウィンドウタイトルの設定
	SetWindowText(appName);

	// 垂直同期を行わない
	SetWaitVSyncFlag(FALSE);

	// Log.txtファイルの生成制御（Debugモードのみ生成する）
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dxライブラリの初期化
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dxライブラリの初期化に失敗しました！\n");
	}

	// 描画先を表画面に反映する
	SetDrawScreen(DX_SCREEN_BACK);

	// 非アクティブ状態でも動作させる
	SetAlwaysRunFlag(TRUE);
}

// メインループ
void Application::MainLoop()
{
	while (ProcessMessage() == D_SUCCESS)
	{
		// ESCキーで終了
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}

		// シーン管理
		SceneManager& manager = SceneManager::GetInstance();
		manager.Update();
	}

	DxLib_End();
}