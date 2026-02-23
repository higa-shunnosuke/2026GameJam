#include "InGame.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/ResourceManager.h"
#include "../../System/Camera/Camera.h"

// ボード位置
#define D_BOARD_POS_X (D_BOX_SIZE * 8 + 48)
#define D_BOARD_POS_Y (D_BOX_SIZE - 80)

// タイマー位置
#define D_TIMER_POS_X (D_BOX_SIZE * 7 + 72)
#define D_TIMER_POS_Y (D_BOX_SIZE - 16)

// スタミナ位置
#define D_STAMINA_POS_X (D_BOX_SIZE * 3 - 32)
#define D_STAMINA_POS_Y (D_BOX_SIZE / 2)


InGame::InGame()
	: m_map(nullptr)
	, m_player(nullptr)
	, m_groundImg()
	, m_boardImg()
	, m_timerImg()
	, m_staminaBarImg()
	, m_staminaFlameImg()
	, m_moleIconImg()
	, m_back_buffer()
{
}

void InGame::Initialize()
{
	// 背景画像読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	m_groundImg = rm.GetImageResource("Assets/Textures/InGame/Ground.PNG")[0];
	m_skyImg.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky3.PNG")[0]);
	m_skyImg.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky2.PNG")[0]);
	m_skyImg.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky1.PNG")[0]);
	m_boardImg = rm.GetImageResource("Assets/Sprites/UI/Board.PNG")[0];
	m_timerImg = rm.GetImageResource("Assets/Sprites/UI/Timer.PNG")[0];
	m_staminaBarImg[0] = rm.GetImageResource("Assets/Sprites/UI/Stamina1.PNG")[0];
	m_staminaBarImg[1] = rm.GetImageResource("Assets/Sprites/UI/Stamina2.PNG")[0];
	m_staminaBarImg[2] = rm.GetImageResource("Assets/Sprites/UI/Stamina3.PNG")[0];
	m_staminaFlameImg[0] = rm.GetImageResource("Assets/Sprites/UI/Frame1.PNG")[0];
	m_staminaFlameImg[1] = rm.GetImageResource("Assets/Sprites/UI/Flame2.PNG")[0];
	m_moleIconImg[0] = rm.GetImageResource("Assets/Sprites/UI/Mole1.PNG")[0];
	m_moleIconImg[1] = rm.GetImageResource("Assets/Sprites/UI/Mole2.PNG")[0];
	m_moleIconImg[2] = rm.GetImageResource("Assets/Sprites/UI/Mole3.PNG")[0];

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
#ifndef _DEBUG
	__super::Timer(delta);
#endif

	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	// リザルトシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::resutart;
	}
	if (m_elapsedTime > m_time || m_player->GetStamina() <= 0)
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
	//	インゲーム表示
	DrawFormatString(10, 10, 0xff0000, "InGame");

	// 画像サイズ
	float imageSize = 0.222f;


	//------------------------------
	// 背景 ＆ オブジェクトを描画
	//------------------------------
	SetDrawScreen(m_back_buffer);
	ClearDrawScreen();

	// 背景
	{
		int offset;

		// 空
		offset = - 192;
		DrawExtendGraph(0, offset, D_STAGE_WIDTH, D_STAGE_HEIGHT / 2 + offset, m_skyImg[m_skyImg.size() - 1], TRUE);
		for (int i = 0; i < m_skyImg.size(); i++)
		{
			// フェード間隔
			float fadeInterval = m_time / m_skyImg.size();
			// フェード比率(20%)
			float fadeRatio = 0.2f;
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
			alpha -= static_cast<int>(255 / fadeTime * fadeElapsed);

			// アルファブレンド
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			// 経過時間に応じて空を描画
			DrawExtendGraph(0, offset, D_STAGE_WIDTH, D_STAGE_HEIGHT / 2 + offset, m_skyImg[i], TRUE);
			// ブレンドモードを戻す
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		// 地面
		offset = 32;
		DrawExtendGraph(0, offset, D_STAGE_WIDTH, D_STAGE_HEIGHT + offset, m_groundImg, TRUE);

	}

	// オブジェクト描画
	__super::Draw();

	//------------------------------
	// ＵＩを描画
	//------------------------------
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// バックバッファを描画(
	Camera& camera = Camera::GetInstance();
	camera.Draw(m_back_buffer);

	// タイマー
	{
		// ボード
		imageSize = 0.35f;
		DrawRotaGraph(D_BOARD_POS_X, D_BOARD_POS_Y, imageSize, 0, m_boardImg, TRUE);

		// 時計
		imageSize = 0.11f;
		DrawRotaGraph(D_TIMER_POS_X, D_TIMER_POS_Y, imageSize, 0, m_timerImg, TRUE);
	}

	// スタミナ
	{
		// 枠（背面）
		imageSize = 0.22f;
		DrawRotaGraph(D_STAMINA_POS_X, D_STAMINA_POS_Y, imageSize, 0, m_staminaFlameImg[0], TRUE);

		// バー
		int stamina = m_player->GetStamina();
		int staminaMax = m_player->GetStaminaMax();
		float rate = static_cast<float>(stamina) / static_cast<float>(staminaMax);
		int drawWidth;
		int drawHeight;
		GetGraphSize(m_staminaBarImg[0], &drawWidth, &drawHeight);
		drawWidth = static_cast<int>(drawWidth * imageSize);
		int staminaBarPosX = static_cast<int>(D_STAMINA_POS_X - drawWidth + drawWidth * rate);

		SetDrawArea(64, 0, 64 + D_BOX_SIZE * 5, D_BOX_SIZE);
		if (rate > 0.6f) {
			DrawRotaGraph(staminaBarPosX, D_STAMINA_POS_Y, imageSize, 0, m_staminaBarImg[0], TRUE);		}
		else if (rate > 0.3f) {
			DrawRotaGraph(staminaBarPosX, D_STAMINA_POS_Y, imageSize, 0, m_staminaBarImg[1], TRUE);		}
		else {
			DrawRotaGraph(staminaBarPosX, D_STAMINA_POS_Y, imageSize, 0, m_staminaBarImg[2], TRUE);
		}
		SetDrawArea(0, 0, D_STAGE_WIDTH, D_STAGE_HEIGHT);

		// 枠（前面）
		DrawRotaGraph(D_STAMINA_POS_X, D_STAMINA_POS_Y, imageSize, 0, m_staminaFlameImg[1], TRUE);

		//// アイコン	
		//imageSize = 0.065f;
		//if (rate > 0.6f) {
		//	DrawRotaGraph(64, D_STAMINA_POS_Y, imageSize, 0, m_moleIconImg[0], TRUE);
		//} else if (rate > 0.3f) {
		//	DrawRotaGraph(64, D_STAMINA_POS_Y, imageSize, 0, m_moleIconImg[1], TRUE);
		//} else {
		//	DrawRotaGraph(64, D_STAMINA_POS_Y, imageSize, 0, m_moleIconImg[2], TRUE);
		//}
	}

	SetFontSize(64);
	DrawFormatString(D_TIMER_POS_X + 44, D_TIMER_POS_Y - 48, 0xffffff, "%.2f", m_time - m_elapsedTime);
	SetFontSize(32);

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


PlayData InGame::TransitionData(const PlayData* prevdata)
{
	PlayData nextData{};

	nextData.score = 0;
	nextData.date = GetCurrentDate();

	return nextData;
}


std::string InGame::GetCurrentDate()
{
	DATEDATA date;
	GetDateTime(&date);

	char buffer[32];
	sprintf_s(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
		date.Year,
		date.Mon,
		date.Day,
		date.Hour,
		date.Min,
		date.Sec
	);

	return std::string(buffer);
}