#include "Title.h"
#include "../../System/ResourceManager.h"
#include "../../System/InputManager.h"


// コンストラクタ
Title::Title()
{

}

// 初期化
void Title::Initialize()
{

	ResourceManager& rm = ResourceManager::GetInstance();
	m_animeTime = 0.0f;

	m_animeCount = 0;

	m_tutiImage[0] = rm.GetImageResource("Assets/Sprites/soil/soil1.PNG")[0];

	m_tutiImage[1] = rm.GetImageResource("Assets/Sprites/soil/soil2.PNG")[0];

	m_groundImage = rm.GetImageResource("Assets/Textures/InGame/Ground.PNG")[0]; // 地下背景読み込み

	m_skyImage = rm.GetImageResource("Assets/Textures/InGame/Sky1.PNG")[0]; //　空背景読み込み

	m_soilImage1 = rm.GetImageResource("Assets/Sprites/Player/Idle1.PNG")[0]; //  待機モグラ読み込み

	m_drillImage = rm.GetImageResource("Assets/Sprites/Drill/Drill1.PNG")[0]; //  待機モグラに着けるドリル読み込み

	m_soilImage2 = rm.GetImageResource("Assets/Sprites/Player/Down3.PNG")[0]; //  下向きドリルモグラ読み込み

	m_jewelImage = rm.GetImageResource("Assets/Sprites/jewel/emerald/emerald1.PNG")[0]; //エメラルド読み込み

	m_jeweleffectImage = rm.GetImageResource("Assets/Sprites/jewel/effect/キラキラ１.PNG")[0]; //エメラルド読み込み7

	m_effectImage = rm.GetImageResource("Assets/Sprites/Effect/Effect1.PNG")[0]; // 採掘エフェクト読み込み

	m_rockImage = rm.GetImageResource("Assets/Sprites/Rock/Rock.PNG")[0]; // 岩読み込み

	m_potatoImage = rm.GetImageResource("Assets/Sprites/Potato/NormalPotato.PNG")[0]; //  ジャガイモ読み込み

	m_leaves_nekkoImage = rm.GetImageResource("Assets/Sprites/Potato/Leaves_Nekko1.PNG")[0]; //  根と葉画像読み込み

	m_titlerogoImage = rm.GetImageResource("Assets/Sprites/Title/Title.PNG")[0]; // タイトル画像読み込み

	//  ジャガイモ読み込み

	m_cursorNumber = 0;
}

// 更新
SceneType Title::Update(float delta)
{
	ApplyInput();

	m_animeTime += delta;
	if (m_animeTime > 0.2)
	{
		m_animeTime = 0.0f;
		m_animeCount += 1;
	}

	//インスタンス取得
	InputManager& input = InputManager::GetInstance();

	if (m_right == eInputState::Pressed) 
	{
		m_cursorNumber += 1; // 右へ
	}

	if (m_left == eInputState::Pressed )
	{
		m_cursorNumber +=2; // 左へ
	}
	m_cursorNumber %= 3;

	if (m_decision == eInputState::Pressed)//決定ボタンが押されたら
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
	//// インゲームシーンに遷移する
	//if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	//{
	//	return SceneType::ingame;
	//}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void Title::Draw() const
{
	int soilx = 250;
	int soily = 400;

	int emeraldx = 500;
	int emeraldy = 600;

	int nekkox = 690;
	int nekkoy = 150;

	DrawRotaGraph(640, 300, 0.25, 0, m_skyImage, TRUE);//空描画

	DrawRotaGraph(640, 880, 0.23, 0, m_groundImage, TRUE);//地下描画

	DrawRotaGraph(soilx - 40 , soily - 70, 2, 0, m_tutiImage[0], TRUE, TRUE);//道土描画

	DrawRotaGraph(soilx - 40, soily + 50, 2, 3.15, m_tutiImage[0], TRUE, TRUE);//道土描画

	DrawRotaGraph(soilx - 110, soily - 70, 2, 0, m_tutiImage[0], TRUE, TRUE);//道土描画

	DrawRotaGraph(soilx - 110, soily + 50, 2, 3.15, m_tutiImage[0], TRUE, TRUE);//道土描画
	
	DrawRotaGraph(soilx - 170, soily - 70, 2, 0, m_tutiImage[0], TRUE, TRUE);//道土描画

	DrawRotaGraph(soilx - 170, soily + 50, 2, 3.15, m_tutiImage[0], TRUE, TRUE);//道土描画

	DrawRotaGraph(soilx - 230, soily - 70, 2, 0, m_tutiImage[0], TRUE, TRUE);//道土描画

	DrawRotaGraph(soilx - 230, soily + 50, 2, 3.15, m_tutiImage[0], TRUE, TRUE);//道土描画

	DrawRotaGraph(soilx + 85, soily - 70, 2, 0, m_tutiImage[1], TRUE, FALSE);//行き止まり土描画

	DrawRotaGraph(soilx + 85 ,soily + 50, 2, 3.15, m_tutiImage[1], TRUE, TRUE);//行き止まり土描画

	DrawRotaGraph(soilx, soily, 0.13, 0, m_soilImage1, TRUE,TRUE);//横向きモグラ描画

	DrawRotaGraph(soilx, soily, 0.1, 0, m_drillImage, TRUE, TRUE);//ドリル描画

	DrawRotaGraph(soilx, soily, 0.1, 0, m_effectImage, TRUE,TRUE);//ドリルエフェクト描画

	DrawRotaGraph(nekkox, nekkoy, 0.3, 0, m_leaves_nekkoImage, TRUE);//真ん中根と葉描画

	DrawRotaGraph(nekkox + 40, nekkoy + 210, 0.03, 0, m_potatoImage, TRUE);//真ん中ジャガイモ描画

	DrawRotaGraph(nekkox + 410, nekkoy, 0.3, 0, m_leaves_nekkoImage, TRUE);//右端根と葉描画
	
	DrawRotaGraph(nekkox + 450, nekkoy + 210, 0.03, 0, m_potatoImage, TRUE);//右ジャガイモ描画

	DrawRotaGraph(emeraldx, emeraldy, 0.06, 0, m_jeweleffectImage, TRUE);//左エメラルドキラキラ描画

	DrawRotaGraph(emeraldx, emeraldy, 0.06, 0, m_jewelImage, TRUE);//左エメラルド描画

	DrawRotaGraph(emeraldx + 640, emeraldy + 50, 0.06, 0, m_jeweleffectImage, TRUE);//右エメラルドキラキラ描画

	DrawRotaGraph(emeraldx + 640, emeraldy + 50, 0.06, 0, m_jewelImage, TRUE);//右エメラルド描画

	DrawRotaGraph(800, 500, 0.12, 0, m_rockImage, TRUE);//岩描画
	
	// タイトルを表示
	DrawRotaGraph(240, 100, 0.2, 0, m_titlerogoImage, TRUE);//タイトル描画

	SetFontSize(40);

	SetFontSize(50);
	DrawFormatString(130, 600, 0xffffff, "GAMESTART");
	DrawFormatString(565, 600, 0xffffff, "RANKING");
	DrawFormatString(920, 600, 0xffffff, "END");

	int cursorx = 0;
	switch (m_cursorNumber)
	{
	case 0: cursorx = 270; break; // RESTART
	case 1: cursorx = 670; break; // RANKING
	case 2: cursorx = 970; break; // END
	}

	DrawRotaGraph(cursorx, 550, 0.07, 0, m_soilImage2, TRUE);//カーソルモグラ描画

}

// 終了
void Title::Finalize()
{
	
}

// 現在のシーンタイプ取得
const SceneType Title::GetNowSceneType() const
{
	// タイトル
	return SceneType::title;
}

void Title::ApplyInput()
{
	InputManager& input = InputManager::GetInstance();

	int getInput[3];

	getInput[0] = KEY_INPUT_RIGHT;
	getInput[1] = KEY_INPUT_D;
	getInput[2] = XINPUT_BUTTON_DPAD_RIGHT;
	m_right = input.ApplyOneInput(getInput, 3);

	getInput[0] = KEY_INPUT_LEFT;
	getInput[1] = KEY_INPUT_A;
	getInput[2] = XINPUT_BUTTON_DPAD_LEFT;
	m_left = input.ApplyOneInput(getInput, 3);

	getInput[0] = KEY_INPUT_SPACE;
	getInput[1] = XINPUT_BUTTON_A;
	m_decision = input.ApplyOneInput(getInput, 2);
}
