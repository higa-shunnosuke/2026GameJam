#pragma once
#include "../SceneBase.h"


// タイトル
class Title : public SceneBase
{
private:
	int m_animeCount;

	float m_animeTime;

	int m_groundImage;//地下背景

	int m_skyImage;//空背景

	int m_soilImage1;//横向きモグラ

	int m_soilImage2;//下向きドリルモグラ

	int m_tutiImage[2];

	int m_jewelImage;//エメラルド

	int m_effectImage;//採掘エフェクト

	int m_rockImage;//岩画像

	int m_leaves_nekkoImage;//根と葉画像

	int m_potatoImage; //ジャガイモ画像

	int m_drillImage; //横向きモグラに着けるドリル

	int m_jeweleffectImage;//エメラルドキラキラ画像

	int m_cursorNumber;

	int m_titlerogoImage;

	eInputState m_left;
	eInputState m_right;
	eInputState m_decision;
public:
	// コンストラクタ
	Title();

	// デストラクタ
	virtual ~Title() = default;

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

private:
	void ApplyInput();
};

