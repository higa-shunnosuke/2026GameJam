#include "InGame.h"

InGame::InGame()
	: player(nullptr)
	, jewel(nullptr)
{

}

void InGame::Initialize()
{
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