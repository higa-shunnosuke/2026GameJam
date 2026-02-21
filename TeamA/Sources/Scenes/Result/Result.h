#pragma once
#include "../SceneBase.h"

class Result : public SceneBase
{
private:
		int m_background;

		int m_jewelImage;
		
		int m_cursorNumber;
		
		int m_moguraImage[3];

		float m_animeTime;

		int m_animeCount;

public:
	// コンストラクタ
	Result();

	// デストラクタ
	virtual ~Result() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual SceneType Update(float delta) override;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// 現在のシーンタイプを取得
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const SceneType GetNowSceneType() const override;
};

