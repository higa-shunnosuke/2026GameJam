#include "End.h"

// コンストラクタ
End::End()
{
}

// 初期化
void End::Initialize()
{
}

// 更新
SceneType End::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	// タイトルシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::title;
	}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void End::Draw() const
{
	// エンドを表示
	DrawFormatString(10, 10, 0xffffff, "End");
}

// 終了
void End::Finalize()
{
}

// 現在のシーンタイプ取得
const SceneType End::GetNowSceneType() const
{
	return SceneType::end;
}
