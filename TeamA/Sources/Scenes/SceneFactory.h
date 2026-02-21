#pragma once
#include "SceneBase.h"

// 各シーンクラス
#include "Title/Title.h"
#include "InGame/InGame.h"
#include "Result/Result.h"
#include "End/End.h"

// シーン生成用クラス
class SceneFactory
{
public:
	/// <summary>
	/// シーン生成処理
	/// </summary>
	/// <param name="nextType">次のシーンタイプ</param>
	/// <returns>生成したシーンのポインタ</returns>
	static SceneBase* CreateScene(SceneType nextType)
	{
		// 各シーンの生成
		switch (nextType)
		{
		case SceneType::title:
			return dynamic_cast<SceneBase*>(new Title());
		case SceneType::ingame:
			return dynamic_cast<SceneBase*>(new InGame());
		case SceneType::resutart:
			return dynamic_cast<SceneBase*>(new Result());
		case SceneType::end:
			return dynamic_cast<SceneBase*>(new End());
		}

		return nullptr;
	}
};
