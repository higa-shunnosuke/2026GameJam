#include "End.h"
#include "../../Utilitys/ProjectConfig.h"

// コンストラクタ
End::End()
{
}

// 初期化
void End::Initialize()
{
	m_time = 3;
}

// 更新
SceneType End::Update(float delta)
{
	__super::Timer(delta);

	if (m_elapsedTime > m_time)
	{
		return SceneType::none;
	}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void End::Draw() const
{
	// エンドを表示
	DrawFormatString(10, 10, 0xffffff, "Thank you for Playing!!");
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
