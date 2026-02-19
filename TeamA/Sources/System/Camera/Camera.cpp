#include "Camera.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/InputManager.h"
#include <cmath>

// コンストラクタ
Camera::Camera():
	location(),
	size(),
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
	size.x = D_WIN_WIDTH;
	size.y = D_WIN_HEIGHT;

	// カメラの初期座標を設定
	location.x = D_WIN_WIDTH / 2;
	location.y = D_WIN_HEIGHT / 2;

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
	float maxCameraX = D_STAGE_WIDTH - (D_STAGE_WIDTH / zoom);
	if (location.x < 0) location.x = 0.0f;
	if (location.x > maxCameraX) location.x = maxCameraX;
	float maxCameraY = D_STAGE_HEIGHT - (D_STAGE_HEIGHT / zoom);
	if (location.y < 0) location.y = 0.0f;
	if (location.y > maxCameraY) location.y = maxCameraY;
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
	if (input.GetKeyState(KEY_INPUT_S) == eInputState::Hold)
	{
		location.y += 2.0f;
	}
	if (input.GetKeyState(KEY_INPUT_W) == eInputState::Hold)
	{
		location.y -= 2.0f;
	}

	//location = player->GetLocation();
}

// 描画処理
void Camera::Draw(int back_buffer)
{
	// スケーリング後のサイズ
	int drawW = (int)(D_WIN_WIDTH * zoom);
	int drawH = (int)(D_WIN_HEIGHT * zoom);

	// 描画位置
	int drawX = -(int)(location.x * zoom);
	int drawY = -(int)(location.y * zoom);

	// 背景を拡大・縮小＋スクロールして描画
	DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, back_buffer, TRUE);
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