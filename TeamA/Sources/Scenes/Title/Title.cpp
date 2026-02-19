#include "Title.h"


// コンストラクタ
Title::Title()
{

}

// 初期化
void Title::Initialize()
{
	
}

// 更新
SceneType Title::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	// インゲームシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::ingame;
	}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void Title::Draw() const
{
	// タイトルを表示
	DrawFormatString(10, 10, 0xffffff, "Title");
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