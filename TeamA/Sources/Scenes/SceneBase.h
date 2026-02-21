#pragma once
#include "DxLib.h"
#include "../System/InputManager.h"
#include "../GameObjects/ObjectManager.h"

/// <summary>
/// シーンタイプ
/// </summary>
enum class SceneType
{
	title,
	ingame,
	resutart,
	end
};

// シーン基底クラス
class SceneBase
{
protected:
	float m_time;			// 制限時間
	float m_elapsedTime;	// 経過時間

public:
	// コンストラクタ
	SceneBase()
		: m_time()
	{

	}

	// デストラクタ
	virtual ~SceneBase() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize()
	{
		
	}

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="delta">デルタタイム</param>
	/// <returns>現在のシーン情報</returns>
	virtual SceneType Update(float delta)
	{
		// 現在のシーン情報を返す
		return GetNowSceneType();
	}

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const
	{
		ObjectManager& object = ObjectManager::GetInstance();

		// リスト内のオブジェクトを描画する
		for (ObjectBase* obj : object.GetObjects())
		{
			obj->Draw();
		}
	}

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize()
	{

	}

	/// <summary>
	/// 現在のシーンタイプを取得
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const SceneType GetNowSceneType() const = 0;

	/// <summary>
	/// タイマー
	/// </summary>
	/// <param name="delta">デルタタイム</param>
	virtual void Timer(float delta)
	{
		// 経過時間が制限時間を超えるまでdeltaを加算
		if (m_elapsedTime < m_time) {
			m_elapsedTime += delta;
		}
		else {
			m_elapsedTime = m_time;
		}
	}
};