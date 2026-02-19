#include "InGame.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/ResourceManager.h"

InGame::InGame()
	: player(nullptr)
	, jewel(nullptr)
{

}

void InGame::Initialize()
{
	// 背景画像読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	groundImage = rm.GetImageResource("Assets/Textures/InGame/BackGround/Ground.PNG")[0];

	ObjectManager& object = ObjectManager::GetInstance();
	player = object.RequestSpawn<Player>(Vector2D(580.0f,360.0f));
	jewel = object.RequestSpawn<Jewel>(Vector2D(700.0f, 360.0f));
}

// 更新処理
SceneType InGame::Update()
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	// リザルトシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::resutart;
	}

	// 親クラスの更新
	return __super::Update();
}

// 描画処理
void InGame::Draw() const
{
	// 背景画像の描画
	DrawRotaGraph(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, 1.0, 0.0, groundImage, TRUE);

	//	インゲーム表示
	DrawFormatString(10, 10, 0xffffff, "InGame");

	__super::Draw();
}

// 終了処理
void InGame::Finalize()
{
	
}

// 現在のシーンタイプ取得
const SceneType InGame::GetNowSceneType() const
{
	// リザルト
	return SceneType::ingame;
}