#include "Title.h"
#include "../../System/ResourceManager.h"
#include "../../System/InputManager.h"
#include "../../Utilitys/ProjectConfig.h"

#define D_TIME (60.0f)

// コンストラクタ
Title::Title()
{

}

// 初期化
void Title::Initialize()
{
	// 画像う読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	// モグラ画像
	m_moleImg = rm.GetImageResource("Assets/Sprites/Player/Idle1.PNG")[0];
	// ドリル
	m_drillImg[0] = rm.GetImageResource("Assets/Sprites/Drill/Drill1.PNG")[0];
	m_drillImg[1] = rm.GetImageResource("Assets/Sprites/Drill/Drill2.PNG")[0];
	m_drillImg[2] = rm.GetImageResource("Assets/Sprites/Drill/Drill3.PNG")[0];
	// 採掘エフェクト
	m_effectImage[0] = rm.GetImageResource("Assets/Sprites/Effect/Effect1.PNG")[0];
	m_effectImage[1] = rm.GetImageResource("Assets/Sprites/Effect/Effect2.PNG")[0];
	m_effectImage[2] = rm.GetImageResource("Assets/Sprites/Effect/Effect3.PNG")[0];

	// 背景画像
	// 地下
	m_groundImg = rm.GetImageResource("Assets/Textures/InGame/Ground.PNG")[0];
	// 空
	m_skyImg.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky3.PNG")[0]);
	m_skyImg.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky2.PNG")[0]);
	m_skyImg.push_back(rm.GetImageResource("Assets/Textures/InGame/Sky1.PNG")[0]);

	// ロゴ
	m_logoImg = rm.GetImageResource("Assets/Sprites/Title/Title.PNG")[0];

	// ボタン
	m_buttonImage = rm.GetImageResource("Assets/Sprites/Title/Rock.PNG")[0];
	m_uiImage[0] = rm.GetImageResource("Assets/Sprites/Title/GAMESTART.PNG")[0];
	//m_uiImage[1] = rm.GetImageResource("Assets/Sprites/Title/RANKING.PNG")[0];
	m_uiImage[1] = rm.GetImageResource("Assets/Sprites/Title/END.PNG")[0];
	
	// サウンド
	m_titleBgm = rm.GetSoundResource("Assets/Sounds/BGM/Title.mp3");
	m_selectSe = rm.GetSoundResource("Assets/Sounds/SE/Select.mp3");
	m_decisionSe = rm.GetSoundResource("Assets/Sounds/SE/Click.mp3");

	// アニメーション
	m_animeTime = 0.0f;
	m_animeCount = 0;
	m_clickFlag = FALSE;

	m_cursorNumber = 0;

	m_time = D_TIME;
	m_elapsedTime = 0.0f;

	// BGM再生
	PlaySoundMem(m_titleBgm, DX_PLAYTYPE_LOOP);
}

// 更新
SceneType Title::Update(float delta)
{
	__super::Timer(delta);

	if (m_elapsedTime >= m_time)
	{
		m_time = D_TIME;
		m_elapsedTime = 0.0f;
	}

	//インスタンス取得
	InputManager& input = InputManager::GetInstance();

	input.TitleApplyInput(m_up, m_down, m_decision);

	if (m_clickFlag)
	{
		m_animeTime += delta;
		if (m_animeTime > 0.1)
		{
			m_animeTime = 0.0f;
			m_animeCount += 1;
		}

		if (m_animeCount > 2)
		{
			switch (m_cursorNumber)
			{
			case 0:
				return SceneType::ingame; //インゲームシーンに遷移する

			//case 1:
			//	return SceneType::ingame;//後でランキングに変更,ランキングシーンに遷移する

			case 1:
				return SceneType::end;//エンドシーンに遷移する

			default:
				break;//error時
			}
		}
	}
	else
	{
		if (m_down == eInputState::Pressed)
		{
			m_cursorNumber += 1;

			// SEを再生
			PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
		}

		if (m_up == eInputState::Pressed)
		{
			m_cursorNumber += 3;

			// SEを再生
			PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
		}
		m_cursorNumber %= 2;

		if (m_decision == eInputState::Pressed)//決定ボタンが押されたら
		{
			// SEを再生
			PlaySoundMem(m_decisionSe, DX_PLAYTYPE_BACK);

			m_clickFlag = TRUE;
			m_animeTime = 0.0f;
			m_animeCount = 0;
		}
	}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void Title::Draw() const
{
	// 画像サイズ
	float imageSize;

	// 背景
	{
		int offset;

		// 空
		offset = -256;
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
		offset = 128;
		DrawExtendGraph(0, offset, D_WIN_WIDTH, D_WIN_HEIGHT + offset, m_groundImg, TRUE);

	}

	// タイトル表示
	imageSize = 0.45;
	DrawRotaGraph(D_WIN_WIDTH / 2, D_WIN_HEIGHT / 4, imageSize, 0, m_logoImg, TRUE);	//タイトル描画


	// ボタン表示
	for (int i = 0; i < 2; i++)
	{
		if (m_cursorNumber == i)
		{
			imageSize = 0.16;
		}
		else
		{
			imageSize = 0.15;
		}

		DrawRotaGraph(D_WIN_WIDTH / 2, D_WIN_HEIGHT / 2 + 72 + i * 88, imageSize, 0.0, m_buttonImage,TRUE);

		if (i == 0)
		{
			imageSize -= 0.03;
		}
		DrawRotaGraph(D_WIN_WIDTH / 2, D_WIN_HEIGHT / 2 + 72 + i * 88, imageSize, 0.0, m_uiImage[i],TRUE);
	}

	int cursorY = D_WIN_HEIGHT / 2 + 72 + m_cursorNumber * 88;
	imageSize = 0.07;
	if (m_clickFlag)
	{

		DrawRotaGraph(440, cursorY, imageSize, 0.0, m_moleImg, TRUE, TRUE);
		DrawRotaGraph(440, cursorY, imageSize, 0.0, m_drillImg[m_animeCount % 3], TRUE, TRUE);
		DrawRotaGraph(440, cursorY, imageSize, 0.0, m_effectImage[m_animeCount % 3], TRUE, TRUE);
	}
	else
	{
		DrawRotaGraph(445, cursorY, imageSize, 0, m_moleImg, TRUE, TRUE);//カーソルモグラ描画
		DrawRotaGraph(445, cursorY, imageSize, 0, m_drillImg[0], TRUE, TRUE);//カーソルドリル描画
	}

}

// 終了
void Title::Finalize()
{
	// BGM停止
	StopSoundMem(m_titleBgm);
}

// 現在のシーンタイプ取得
const SceneType Title::GetNowSceneType() const
{
	// タイトル
	return SceneType::title;
}