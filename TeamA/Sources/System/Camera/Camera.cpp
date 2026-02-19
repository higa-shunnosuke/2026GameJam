#include "Camera.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/InputManager.h"
#include <cmath>

// コンストラクタ
Camera::Camera():
	location(),
	sizeX(),
	sizeY(),
	player(nullptr)
{

}

// デストラクタ
Camera::~Camera()
{

}

// 初期化処理
void Camera::Initialize()
{
	// ズーム倍率を設定
	zoom = 1.0f;

	// スクリーンの初期サイズを設定
	GetDrawScreenSize(&sizeX, &sizeY);

	// カメラの初期座標を設定
	location.x = sizeX / 2;
	location.y = sizeY / 2;

}

// 更新処理
void Camera::Update()
{
	// ズーム変更前の値を記録
	float prevZoom = zoom;

	// ズーム
	Zoom();

	// スクロール
	Scroll();

	/// ステージ外にいかないようにする処理
	float maxCameraX = 1280 - (1280 / zoom);
	if (location.x < 0) location.x = 0.0f;
	if (location.x > maxCameraX) location.x = maxCameraX;
}

// 描画処理
void Camera::Draw(int back_buffer)
{
	// スケーリング後のサイズ
	int drawW = (int)(D_WIN_MAX_X * zoom);
	int drawH = (int)(D_WIN_MAX_Y * zoom);

	// 描画位置（X はスクロールに応じて、Y は下合わせ）
	int drawX = -(int)(location.x * zoom);
	int drawY = 720 - drawH;  // 画面下端に合わせる

	// 背景を拡大・縮小＋スクロールして描画
	DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, back_buffer, TRUE);
}

// ズーム処理
void Camera::Zoom()
{
	// マウス
	int wheel = GetMouseWheelRotVol();
	if (wheel != 0) 
	{
		// ズーム倍率を計算
		zoom += wheel * 0.1f;
	}
	// コントローラー
	InputManager& input = InputManager::GetInstance();
	if (input.GetLeftStick().y != 0.0f)
	{
		// 倍率を計算
		zoom += input.GetLeftStick().y * 0.005f;
	}

	if (zoom < ZOOM_MIN) zoom = ZOOM_MIN;
	if (zoom > ZOOM_MAX) zoom = ZOOM_MAX;
}

// スクロール処理
void Camera::Scroll()
{
	InputManager& input = InputManager::GetInstance();

	// 手動スクロール（キーボード）
	if (input.GetKeyState(KEY_INPUT_D) == eInputState::Hold)
	{
		location.x += 2.0f;
	}
	if (input.GetKeyState(KEY_INPUT_A) == eInputState::Hold)
	{
		location.x -= 2.0f;
	}

	location.x = player->GetLocation().x;
	location.y = player->GetLocation().y;
}

// カメラ座標設定処理
void Camera::SetCameraPos(Vector2D location)
{
	this->location = location;
}

// 巫女情報設定処理
void Camera::SetPlayer(Player* player)
{
	this->player = player;
}

void Camera::SetZoom(float zoom)
{
	this->zoom = zoom;
}

float Camera::GetZoom()
{
	return zoom;
}