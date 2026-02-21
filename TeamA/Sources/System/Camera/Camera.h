#pragma once

#include "../../Utilitys/Singleton.h"
#include "../../Utilitys/Vector2D.h"


class Camera : public Singleton<Camera>
{
private:
	Vector2D location;	// カメラ座標（スクリーンの左上）
	Vector2D size;		// スクリーンサイズ

public:
	// コンストラクタ
	Camera();
	// デストラクタ
	~Camera();

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	///  実行処理
	/// </summary>
	void Update();

	/// <summary>
	/// スクリーン描画
	/// </summary>
	/// <param name="back_buffer">表示する画面</param>
	void Draw(int back_buffer);

	/// <summary>
	///	カメラ座標設定処理
	/// </summary>
	/// <param name="location">座標</param>
	void SetCameraPos(Vector2D location);
};
