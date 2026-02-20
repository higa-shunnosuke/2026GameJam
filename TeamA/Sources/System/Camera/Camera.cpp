#include "Camera.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/InputManager.h"
#include <cmath>

// コンストラクタ
Camera::Camera():
	location(),
	size()
{

}

// デストラクタ
Camera::~Camera()
{

}

// 初期化処理
void Camera::Initialize()
{
	// スクリーンのサイズを設定
	size.x = D_WIN_WIDTH / 2;
	size.y = D_WIN_HEIGHT / 2;

	// カメラの初期座標を設定
	location.x = 0.0f;
	location.y = 0.0f;

}

// 更新処理
void Camera::Update()
{
	/// ステージ外にいかないようにする処理
	float maxCameraX = D_STAGE_WIDTH - D_WIN_WIDTH;
	if (location.x < 0.0f) location.x = 0.0f;
	if (location.x > maxCameraX) location.x = maxCameraX;
	float maxCameraY = D_STAGE_HEIGHT - D_WIN_HEIGHT;
	if (location.y < 0.0f) location.y = 0.0f;
	if (location.y > maxCameraY) location.y = maxCameraY;
}

// 描画処理
void Camera::Draw(int back_buffer)
{
	// スケーリング後のサイズ
	int drawW = (int)(D_STAGE_WIDTH);
	int drawH = (int)(D_STAGE_HEIGHT);

	// 描画位置
	int drawX = -(int)(location.x);
	int drawY = -(int)(location.y);

	// 背景を拡大・縮小＋スクロールして描画
	DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, back_buffer, TRUE);
}

// カメラ座標設定処理
void Camera::SetCameraPos(Vector2D location)
{
	this->location = location - size;
}
