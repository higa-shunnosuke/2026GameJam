#pragma once
#include <Windows.h>

// アプリケーション管理クラス
class Application
{
public:
	/// <summary>
	/// アプリケーションを起動
	/// </summary>
	/// <param name="appName">アプリケーション名</param>
	static void StartApp(const TCHAR* appName);

private:
	/// <summary>
	/// ウィンドウの生成
	/// </summary>
	/// <param name="appName">ウィンドウのタイトル</param>
	static void InitWindow(const TCHAR* appName);

	/// <summary>
	/// メインループ
	/// </summary>
	static void MainLoop();
};

