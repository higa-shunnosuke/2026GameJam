#pragma once

#include "../Scenes/SceneBase.h"
#include "../System/Ranking.h"

#include <string>
#include <vector>

class Ranking
{
public:

	std::vector<PlayData> m_ranking{};	// ランキング格納配列
	std::string path;					// ファイルパス

	// 画像
	int m_jewelImage;		// 宝石
	int m_backrockImage;	// ボタン背景
	int m_rankingImage;		// RANKING文字
	int m_rankingBackGround;	// ランキング背景

public:
	void Initialize();
	void Draw() const;

public:

	/// <summary>
	/// csvファイルの読み込み
	/// </summary>
	/// <param name="path">ファイルパス</param>
	/// <returns>true:成功</returns>
	bool LoadRankingCsv();

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
	bool AddAndSortRanking(const PlayData& data);

	/// <summary>
	/// csvを上書きする
	/// </summary>
	/// <param name="path">ファイルパス</param>
	/// <returns>true:成功</returns>
	bool SaveRankingCsv();

	/// <summary>
	/// 何位かを返す
	/// </summary>
	/// <param name="data">今回のプレイデータ</param>
	/// <returns>0:圏外</returns>
	int GetCurrentRank(const PlayData& data);
};