#include "Result.h"
#include "../../System/ResourceManager.h"
#include "../../System/InputManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <DxLib.h>

// コンストラクタ
Result::Result()
	:m_ranking(nullptr)
{
	
}

// 初期化
void Result::Initialize()
{
	// アニメーション
	m_animeTime = 0.0f;
	m_animeCount = 0;
	m_clickFlag = FALSE;

    m_haikeiTime = 0.0f;
	m_haikeiCount = 0;

	ResourceManager& rm = ResourceManager::GetInstance();

	m_haikeiImage[0] = rm.GetImageResource("Assets/Sprites/Result/背景１.PNG")[0];
	m_haikeiImage[1] = rm.GetImageResource("Assets/Sprites/Result/背景２.PNG")[0];
	m_backrockImage = rm.GetImageResource("Assets/Sprites/Title/Rock.PNG")[0];
	m_jewelImage = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald1.PNG")[0];
	m_scoreImage = rm.GetImageResource("Assets/Sprites/Result/スコア.PNG")[0];
	m_restartImage = rm.GetImageResource("Assets/Sprites/Result/リスタート.PNG")[0];
	m_rankingImage = rm.GetImageResource("Assets/Sprites/Title/RANKING.PNG")[0];
	m_titleImage = rm.GetImageResource("Assets/Sprites/Result/タイトル.PNG")[0];
	m_moguraImage = rm.GetImageResource("Assets/Sprites/Result/モグラ.PNG")[0];

	m_cursorNumber = 0;

	// サウンド
	m_resultBgm = rm.GetSoundResource("Assets/Sounds/BGM/Title.mp3");
	m_selectSe = rm.GetSoundResource("Assets/Sounds/SE/Select.mp3");
	m_decisionSe = rm.GetSoundResource("Assets/Sounds/SE/Click.mp3");

	// ランキング順位
	m_rank = 0;

	// ランキングデータを作成する
	m_ranking = new Ranking();
	m_ranking->Initialize();

	//今回の配列に追加、ソート、11位以下切り捨て
	if (m_ranking->AddAndSortRanking(m_currentData))
	{
		// csvに保存
		m_ranking->SaveRankingCsv();

		// 何位かを受け取る(0:圏外)
		m_rank = m_ranking->GetCurrentRank(m_currentData);
	}

	// BGM再生
	PlaySoundMem(m_resultBgm, DX_PLAYTYPE_LOOP);
}

// 更新
SceneType Result::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();

	// コントローラー
	bool decisionPressed = input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed;
	bool leftPressed = input.GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Pressed;
	bool rightPressed = input.GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Pressed;

#if _DEBUG
	// キー
	if (!decisionPressed)decisionPressed = (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed);
	if (!leftPressed)leftPressed = (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_A) == eInputState::Pressed);
	if (!rightPressed)rightPressed = (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_D) == eInputState::Pressed);
#endif

	if (m_rankingDraw)
	{
		if (decisionPressed)
		{
			m_rankingDraw = false;
			m_clickFlag = false;
		}
		// 親クラスの更新
		return __super::Update(delta);
	}

	if (m_clickFlag)
	{
		m_animeTime += delta;
		if (m_animeTime > 0.2)
		{
			m_animeTime = 0.0f;
			m_animeCount += 1;
		}

		if (m_animeCount > 2)
		{
			switch (m_cursorNumber)
			{
			case 0:
				// インゲームシーンに遷移する
				return SceneType::ingame;

			case 1:
				// ランキングを描画
				m_rankingDraw = true;
				break;

			case 2:
				// エンドシーンに遷移する
				return SceneType::title;
			}
		}
	}
	else
	{
		m_taikiTime += delta;
		if (m_taikiTime > 0.2)
		{
			m_taikiTime = 0.0f;
			m_taikiCount += 1;
		}

		if (leftPressed)
		{
			m_cursorNumber = (m_cursorNumber + 2) % 3; // 左へ

			// SEを再生
			PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
		}
		if (rightPressed)
		{
			m_cursorNumber = (m_cursorNumber + 1) % 3; // 右へ

			// SEを再生
			PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
		}
		if (decisionPressed)
		{
			// SEを再生
			PlaySoundMem(m_decisionSe, DX_PLAYTYPE_BACK);

			m_clickFlag = true;
			m_animeTime = 0.0f;
			m_animeCount = 0;
		}
	}
	m_haikeiTime += delta;
	if (m_haikeiTime > 0.6)
	{
		m_haikeiTime = 0.0f;
		m_haikeiCount += 1;
	}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void Result::Draw() const
{
	// ランキングを描画
	if (m_rankingDraw)
	{
		m_ranking->Draw();
		return;
	}

	// 背景
	DrawRotaGraph(640, 360, 0.5, 0, m_haikeiImage[m_haikeiCount % 2], TRUE);

	// RESULT SCORE
	DrawRotaGraph(620, 250, 0.2, 0, m_scoreImage, TRUE);

	//エメラルド描画
	DrawRotaGraph(550, 350, 0.06, 0, m_jewelImage, TRUE);

	// エメラルドの数
	SetFontSize(50);
	DrawFormatString(600, 330, 0xffffff, "×%d", m_currentData.score);
	SetFontSize(32);

	// リスタート
	DrawRotaGraph(340, 620, 0.15, 0, m_backrockImage, TRUE);	// 岩
	DrawRotaGraph(340, 620, 0.15, 0, m_restartImage, TRUE);		// 文字

	// ランキング
	DrawRotaGraph(650, 620, 0.15, 0, m_backrockImage, TRUE);	// 岩
	DrawRotaGraph(650, 615, 0.15, 0, m_rankingImage, TRUE);		// 文字

	// タイトル
	DrawRotaGraph(960, 620, 0.15, 0, m_backrockImage, TRUE);	// 岩背景描画
	DrawRotaGraph(960, 615, 0.15, 0, m_titleImage, TRUE);		// 文字

	// カーソル
	DrawRotaGraphF(340 + 310 * m_cursorNumber, 580 + ((m_clickFlag) ? 20 : 0), 0.07, 0.0, m_moguraImage, TRUE);

	// 入賞表示
	SetFontSize(70);
	if (m_rank != 0) DrawFormatString(640 - 2 * 32, 130, 0xffffff, "%d位！", m_rank);	
	SetFontSize(32);

}

// 終了
void Result::Finalize()
{
	if (m_ranking != nullptr)
	{
		delete m_ranking;
	}
	// BGM停止
	StopSoundMem(m_resultBgm);
}

// 現在のシーンタイプ取得
const SceneType Result::GetNowSceneType() const
{
	// リザルト
	return SceneType::resutart;
}

PlayData Result::TransitionData(const PlayData* prevdata)
{
	if (prevdata == nullptr) return PlayData();

	// データがあるなら受け取る
	m_currentData = *prevdata;

	return PlayData();
}