#include "Result.h"
#include "../../System/ResourceManager.h"
#include "../../System/InputManager.h"

// コンストラクタ
Result::Result()
{
	
}

// 初期化
void Result::Initialize()
{
	ResourceManager& rm = ResourceManager::GetInstance();

	m_background = rm.GetImageResource("Assets/Textures/InGame/Sky3.PNG")[0];

	m_jewelImage = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald1.PNG")[0];

	m_moguraImage[0] = rm.GetImageResource("Assets/Sprites/Player/Down3.PNG")[0]; //  下向きドリルモグラ読み込み

	m_moguraImage[1] = rm.GetImageResource("Assets/Sprites/Player/Down2.PNG")[0]; //  下向きドリルモグラ読み込み

	m_moguraImage[2] = rm.GetImageResource("Assets/Sprites/Player/Down1.PNG")[0]; //  下向きドリルモグラ読み込み
	m_cursorNumber = 0;
}

// 更新
SceneType Result::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();

	if (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_D) == eInputState::Pressed)
	{
		m_cursorNumber = (m_cursorNumber + 1) % 3; // 右へ
	}
	if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_A) == eInputState::Pressed)
	{
		m_cursorNumber = (m_cursorNumber + 2) % 3; // 左へ
	}
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)//エンターが押されたら
	{
		switch (m_cursorNumber)
		{
		case 0:
			return SceneType::ingame; //インゲームシーンに遷移する

		case 1:
			return SceneType::ingame;//後でランキングに変更,ランキングシーンに遷移する

		case 2:
			return SceneType::end;//エンドシーンに遷移する

		default:
			break;//error時
		}
	}
	// エンドシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::end;
	}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void Result::Draw() const
{
	//	リザルト表示

	DrawRotaGraph(640, 250, 0.25, 0, m_background, TRUE);

	DrawRotaGraph(390, 350, 0.05, 0, m_jewelImage, TRUE);

	SetFontSize(64);
	DrawFormatString(460, 200, 0xffffff, "ResultScore");

	SetFontSize(40);
	DrawFormatString(480, 330, 0xffffff, "獲得ジュエル表示");

	DrawFormatString(480, 390, 0xffffff, "スコア表示");

	SetFontSize(50);
	DrawFormatString(250, 600, 0xffffff, "RESTART");
	DrawFormatString(560, 600, 0xffffff, "RANKING");
	DrawFormatString(905, 600, 0xffffff, "END");

	int cursorx = 0;
	switch (m_cursorNumber)
	{
	case 0: cursorx = 340; break; // RESTART
	case 1: cursorx = 650; break; // RANKING
	case 2: cursorx = 950; break; // END
	}

	DrawRotaGraph(cursorx, 550, 0.07, 0, m_moguraImage[0], TRUE);//カーソルモグラ描画
}

// 終了
void Result::Finalize()
{

}

// 現在のシーンタイプ取得
const SceneType Result::GetNowSceneType() const
{
	// リザルト
	return SceneType::resutart;
}