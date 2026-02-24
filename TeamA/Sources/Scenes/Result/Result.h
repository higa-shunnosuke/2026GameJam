#pragma once
#include "../SceneBase.h"

#include <string>
#include <vector>

class Result : public SceneBase
{
private:

	int m_background;
	int m_jewelImage;
	int m_cursorNumber;
	int m_moguraImage[3];
	int m_effectImage[3];

	//アニメーション
	float m_animeTime;
	int m_animeCount;
	bool m_clickFlag;

	// ランキング
	std::vector<PlayData> m_ranking;	// ランキング格納配列
	PlayData m_currentData;				// 今回のプレイデータ

	// サウンド
	// リザルトBGM
	int m_resultBgm;
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

	/// <summary>
	/// データの受け渡し
	/// </summary>
	/// <param name="data">受け取るデータ</param>
	/// <returns>渡すデータ</returns>
	virtual PlayData TransitionData(const PlayData* prevdata) override;

private:

	/// <summary>
	/// csvファイルの読み込み
	/// </summary>
	/// <param name="path">ファイルパス</param>
	/// <returns>true:成功</returns>
	bool LoadRankingCsv(const std::string& path);

	/// <summary>
	/// データa,bを比較する
	/// </summary>
	/// <param name="a">1つ目のデータ</param>
	/// <param name="b">2つ目のデータ</param>
	/// <returns>true:aが大きい</returns>
	bool CompareRanking(const PlayData& a, const PlayData& b);

	/// <summary>
	/// 配列にデータを挿入してソートする
	/// </summary>
	/// <param name="newData">追加するデータ</param>
	/// <returns>true:変更あり</returns>
	bool AddAndSortRanking(const PlayData& newData);

	/// <summary>
	/// csvを上書きする
	/// </summary>
	/// <param name="path">ファイルパス</param>
	/// <returns>true:成功</returns>
	bool SaveRankingCsv(const std::string& path);

};