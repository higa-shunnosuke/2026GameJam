#pragma once
#include <Windows.h>

// アプリケーション管理クラス
class Application
{
private:
	LONGLONG m_nowTime;
	LONGLONG m_oldTime;
	float m_delta;
public:

	Application()
		:m_nowTime(0)
		, m_oldTime(0)
		, m_delta(0)
	{

	}
	~Application();

public:
	/// <summary>
	/// アプリケーションを起動
	/// </summary>
	/// <param name="appName">アプリケーション名</param>
	void StartApp(const TCHAR* appName);

private:
	/// <summary>
	/// ウィンドウの生成
	/// </summary>
	/// <param name="appName">ウィンドウのタイトル</param>
	static void InitWindow(const TCHAR* appName);

	/// <summary>
	/// メインループ
	/// </summary>
    void MainLoop();

	/// <summary>
	/// デルタタイムの更新
	/// </summary>
	void UpDateDeltaTime();
};
