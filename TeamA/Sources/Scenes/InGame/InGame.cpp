#include "InGame.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/ResourceManager.h"
#include "../../System/MapData/MapData.h"

InGame::InGame()
	: camera(nullptr)
	, player(nullptr)
	, jewel(nullptr)
	, groundImage()
	, back_buffer()
{
}

void InGame::Initialize()
{
	// 背景画像読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	groundImage = rm.GetImageResource("Assets/Textures/InGame/BackGround/Ground.PNG")[0];

	// マップの初期化
	MapData& map = MapData::GetInstance();
	map.Initialize();

	// 各オブジェクトを生成
	ObjectManager& object = ObjectManager::GetInstance();
	player = object.RequestSpawn<Player>(Vector2D(580.0f,360.0f));
	jewel = object.RequestSpawn<Jewel>(Vector2D(700.0f, 360.0f));

	// カメラを生成
	Camera& camera = Camera::GetInstance();
	camera.Initialize();

	back_buffer = MakeScreen(D_STAGE_WIDTH, D_STAGE_HEIGHT, TRUE);

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
		obj->Update();
	}

	// オブジェクトの当たり判定を確認する
	object.CheckPlayerCollisions(dynamic_cast<ObjectBase*>(player));

	// 破棄待ちオブジェクトをm_objectsから削除する
	object.ProcessPendingDestroys();

	Camera& camera = Camera::GetInstance();
	// プレイヤーを追跡
	camera.SetCameraPos(player->GetLocation());
	//カメラの更新
	camera.Update();

	// 親クラスの更新処理
	return __super::Update(delta);
}

// 描画処理
void InGame::Draw() const
{
	//---------------
	// 仮想画面に描画
	//---------------
	SetDrawScreen(back_buffer);
	ClearDrawScreen();

	float imageSize = 0.222f;
	int offset = 400;

	// 背景画像の描画
	DrawRotaGraph(D_WIN_WIDTH / 2, D_WIN_HEIGHT / 2 + offset, imageSize, 0.0, groundImage, TRUE);

	// マップの描画
	MapData& map = MapData::GetInstance();
	map.Draw();

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
	camera.Draw(back_buffer);

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
