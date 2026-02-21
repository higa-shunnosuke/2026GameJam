#include "InGame.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/ResourceManager.h"
#include "../../System/Camera/Camera.h"

InGame::InGame()
	: m_map(nullptr)
	, m_player(nullptr)
	, m_groundImage()
	, m_back_buffer()
{
}

void InGame::Initialize()
{
	// 背景画像読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	m_groundImage = rm.GetImageResource("Assets/Textures/InGame/Ground.PNG")[0];
	m_skyImage[1] = rm.GetImageResource("Assets/Textures/InGame/Sky1.PNG")[0];

	// 各オブジェクトを生成
	ObjectManager& object = ObjectManager::GetInstance();
	// マップの初期化
	m_map = object.RequestSpawn<MapData>({ 0,0 });
	m_player = object.RequestSpawn<Player>(Vector2D(64.0f,448.0f));
	m_player->SetMap(m_map);

	// カメラを生成
	Camera& camera = Camera::GetInstance();
	camera.Initialize();

	m_back_buffer = MakeScreen(D_STAGE_WIDTH, D_STAGE_HEIGHT, TRUE);

	// 制限時間の初期化
	m_time = 60.0f;

}

// 更新処理
SceneType InGame::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	// リザルトシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::resutart;
	}

	// オブジェクトマネージャーのインスタンスを取得する
	ObjectManager& object = ObjectManager::GetInstance();

	// 生成するオブジェクトがあれば、オブジェクトリスト内に挿入する
	object.ProcessPendingCreates();

	// リスト内のオブジェクトを更新する
	for (ObjectBase* obj : object.GetObjects())
	{
		obj->Update(delta);
	}

	// オブジェクトの当たり判定を確認する
	object.CheckPlayerCollisions(dynamic_cast<ObjectBase*>(m_player));

	// 破棄待ちオブジェクトをm_objectsから削除する
	object.ProcessPendingDestroys();

	Camera& camera = Camera::GetInstance();
	// プレイヤーを追跡
	camera.SetCameraPos(m_player->GetLocation());
	//カメラの更新
	camera.Update();

	// タイマーの更新
	__super::Timer(delta);

	// 親クラスの更新処理
	return __super::Update(delta);
}

// 描画処理
void InGame::Draw() const
{
	//---------------
	// 仮想画面に描画
	//---------------
	SetDrawScreen(m_back_buffer);
	ClearDrawScreen();

	float imageSize = 0.222f;
	int offset = 582;

	// 背景画像の描画
	DrawRotaGraph(D_WIN_WIDTH / 2, D_WIN_HEIGHT / 2, imageSize, 0.0, m_skyImage[1], TRUE);
	DrawRotaGraph(D_WIN_WIDTH / 2, D_WIN_HEIGHT / 2 + offset, imageSize, 0.0, m_groundImage, TRUE);

	//	インゲーム表示
	DrawFormatString(10, 10, 0xffffff, "InGame");

	__super::Draw();

	//---------------
	// 表画面に描画
	//---------------
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// 仮想画面を描画
	Camera& camera = Camera::GetInstance();
	camera.Draw(m_back_buffer);

	SetFontSize(64);
	DrawFormatString(1100, 10, 0xffffff, "%.2f", m_time);
	SetFontSize(12);
}

// 終了処理
void InGame::Finalize()
{
	ObjectManager& object = ObjectManager::GetInstance();
	object.DestroyAllObjects();
}

// 現在のシーンタイプ取得
const SceneType InGame::GetNowSceneType() const
{
	// リザルト
	return SceneType::ingame;
}
