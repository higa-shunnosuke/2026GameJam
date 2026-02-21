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
	m_skyImage.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky3.PNG")[0]);
	m_skyImage.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky2.PNG")[0]);
	m_skyImage.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky1.PNG")[0]);

	// 各オブジェクトを生成
	ObjectManager& object = ObjectManager::GetInstance();
	// マップの初期化
	m_map = object.RequestSpawn<MapData>({ 0,0 });
	m_player = object.RequestSpawn<Player>(Vector2D(64.0f, D_BOX_SIZE * D_START_Y - D_BOX_SIZE / 2));
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
	// タイマーの更新
	__super::Timer(delta);

	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	// リザルトシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::resutart;
	}
	if (m_elapsedTime > m_time)
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



	// 親クラスの更新処理
	return __super::Update(delta);
}

// 描画処理
void InGame::Draw() const
{
	//--------------------
	// 仮想画面に描画
	//--------------------
	SetDrawScreen(m_back_buffer);
	ClearDrawScreen();

	// 背景
	{
		float imageSize = 0.222f;
		int offset;

		// 空
		offset = - 192;
		DrawExtendGraph(0, offset, D_STAGE_WIDTH, D_STAGE_HEIGHT / 2 + offset, m_skyImage[m_skyImage.size() - 1], TRUE);
		for (int i = 0; i < m_skyImage.size(); i++)
		{
			// フェード間隔
			float fadeInterval = m_time / m_skyImage.size();
			// フェード比率(20%)
			float fadeRatio = 0.2;
			// フェード時間
			float fadeTime = fadeInterval * fadeRatio;
			// フェード終了時間
			float fadeEnd = m_time - (fadeInterval * i);
			// フェード開始時間
			float fadeStart = fadeEnd - fadeTime;
			// アルファ
			int alpha = 255;

			if (m_elapsedTime >= fadeEnd) continue;

			// フェード経過時間を測定(InGameの経過時間 - フェード開始時間)
			float fadeElapsed = m_elapsedTime - fadeStart;

			// アルファを計算
			alpha -= 255 / fadeTime * fadeElapsed;

			// アルファブレンド
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			// 経過時間に応じて空を描画
			DrawExtendGraph(0, offset, D_STAGE_WIDTH, D_STAGE_HEIGHT / 2 + offset, m_skyImage[i], TRUE);
			// ブレンドモードを戻す
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		// 地面
		offset = 32;
		DrawExtendGraph(0, offset, D_STAGE_WIDTH, D_STAGE_HEIGHT + offset, m_groundImage, TRUE);

	}

	__super::Draw();

	//--------------------
	// 表画面に描画
	//--------------------
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// 仮想画面を描画
	Camera& camera = Camera::GetInstance();
	camera.Draw(m_back_buffer);

	SetFontSize(64);
	//	インゲーム表示
	DrawFormatString(10, 10, 0xff0000, "InGame");
	// タイマー描画
	DrawFormatString(1100, 10, 0xffffff, "%.2f", m_time - m_elapsedTime);
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
