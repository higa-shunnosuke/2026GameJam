#pragma once

#include "../../Utilitys/Singleton.h"
#include "../../Utilitys/Vector2D.h"
#include "../../GameObjects/Player/Player.h"


class Camera : public Singleton<Camera>
{
private:
	Vector2D location;	// カメラ座標
	Vector2D size;		// スクリーンサイズ
	float zoom = 1.0f;	// ズーム倍率

	Player* player;		// プレイヤーのポインタ

	// ズーム倍率の範囲
	const float ZOOM_MIN = 1.0f;
	const float ZOOM_MAX = 2.0f;

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
	/// ズーム処理
	/// </summary>
	void Zoom();

	/// <summary>
	/// スクロール処理
	/// </summary>
	void Scroll();

	/// <summary>
	///	カメラ座標指定処理
	/// </summary>
	/// <param name="location">指定座標</param>
	void SetCameraPos(Vector2D location);

	/// <summary>
	/// プレイヤー情報設定処理
	/// </summary>
	/// <param name="player">プレイヤーのポインタ</param>
	void SetPlayer(Player* player);

	/// <summary>
	/// カメラ拡大率指定処理
	/// </summary>
	/// <param name="zoom">ズーム倍率</param>
	void SetZoom(float zoom);

	/// <summary>
	/// カメラ拡大率取得処理
	/// </summary>
	/// <returns></returns>
	float GetZoom();
};

