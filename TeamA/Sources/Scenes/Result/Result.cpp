#include "Result.h"

// コンストラクタ
Result::Result()
{
	
}

// 初期化
void Result::Initialize()
{
	
}

// 更新
SceneType Result::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
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
	DrawFormatString(10, 10, 0xffffff, "Result");
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