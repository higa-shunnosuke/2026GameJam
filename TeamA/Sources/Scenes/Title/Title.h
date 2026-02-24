#pragma once
#include "../SceneBase.h"


// タイトル
class Title : public SceneBase
{
private:

	// カーソル
	int m_cursorNumber;
	bool m_clickFlag;

	// アニメーション
	int m_animeCount;
	float m_animeTime;
	

	// 画像
	// タイトル画像
	int m_tutiImage[2];

	// モグラ画像
	int m_soilImage1;	//横向きのモグラ
	int m_drillImage;	//横向きのドリル
	int m_downImage[3];	//下向きのモグラ
	int m_effectImage[3];	//採掘エフェクト

	// その他オブジェクト画像
	int m_leaves_nekkoImage;//根と葉画像
	int m_potatoImage;		//ジャガイモ画像
	int m_jewelImage;		//エメラルド
	int m_jeweleffectImage;	//エメラルドキラキラ画像
	int m_rockImage;		//岩画像

	// タイトルロゴ画像
	int m_titlerogoImage;

	// 背景画像
	// 地下画像
	int m_groundImage;
	// 空画像
	int m_skyImage;


	// サウンド
	// タイトルBGM
	int m_titleBgm;
	// 選択SE
	int m_selectSe;
	// 決定SE
	int m_decisionSe;

	// 入力
	// 左
	eInputState m_left;
	// 右
	eInputState m_right;
	// 決定
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
};

