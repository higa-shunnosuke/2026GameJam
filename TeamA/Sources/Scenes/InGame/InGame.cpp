#include "InGame.h"

InGame::InGame()
{

}

void InGame::Initialize()
{
	
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