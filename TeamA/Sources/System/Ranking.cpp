#include "Ranking.h"

#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>

#include <iostream>

#define D_RANKING_MAX_COUNT (10)	// ランキング10位まで

void Ranking::Initialize()
{
	ResourceManager& rm = ResourceManager::GetInstance();

	m_backrockImage = rm.GetImageResource("Assets/Sprites/Title/Rock.PNG")[0];
	m_jewelImage = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald1.PNG")[0];
	m_rankingImage = rm.GetImageResource("Assets/Sprites/Title/RANKING.PNG")[0];
	m_rankingBackGround = rm.GetImageResource("Assets/Textures/InGame/Ground.PNG")[0];

	// ファイルパス
	path = "Resource/RankingData/Ranking.csv";

	// ファイルの読み込み
	LoadRankingCsv();

#if _DEBUG

	std::cout << "\nスコア,yyyy-mm-dd hh:mm:ss" << std::endl;
	for (int i = 0; i < (int)m_ranking.size(); i++)
	{
		std::cout << m_ranking[i].score << "," << m_ranking[i].date << std::endl;
	}

#endif
}

void Ranking::Draw() const
{
	// 背景
	DrawExtendGraph(0, -128, 1280, 720, m_rankingBackGround, TRUE);

	// ランキング文字
	DrawRotaGraph(640, 50, 0.15, 0, m_backrockImage, TRUE);	// 岩
	DrawRotaGraph(640, 45, 0.15, 0, m_rankingImage, TRUE);	// 文字

	// 順位
	for (int i = 0; i < (int)m_ranking.size(); i++)
	{
		int x = ((i < 5) ? 420 : 860);
		int y = 150 + 115 * (i % 5);
		DrawRotaGraph(x, y, 0.2, 0, m_backrockImage, TRUE);
		DrawFormatString(x - 140, y - 15, 0xffffff, "%d位", i + 1);
		DrawRotaGraph(x - 40, y, 0.032, 0.0, m_jewelImage, TRUE);
		SetFontSize(40);
		DrawFormatString(x - 5, y - 20, 0xffffff, "×%d", m_ranking[i].score);
		SetFontSize(20);
		DrawFormatString(x - 20, y + 20, 0xffffff, "%.14s", m_ranking[i].date.c_str());
		SetFontSize(32);
	}
}

bool Ranking::LoadRankingCsv()
{
	m_ranking.clear();

	std::ifstream file(path);
	if (!file.is_open())
		return false;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::stringstream ss(line);

		std::string scoreStr;
		std::string dateStr;

		// score,date の2列を読む
		if (!std::getline(ss, scoreStr, ','))
			continue;
		if (!std::getline(ss, dateStr))
			continue;

		// WindowsのCRLF対策（末尾に '\r' が付くことがある）
		if (!dateStr.empty() && dateStr.back() == '\r')
			dateStr.pop_back();

		// score を int に変換（不正ならその行は捨てる）
		int score = 0;
		try
		{
			score = std::stoi(scoreStr);
		}
		catch (...)
		{
			continue;
		}

		m_ranking.push_back(PlayData{ score, dateStr });
	}

	return true;
}

bool Ranking::CompareRanking(const PlayData& a, const PlayData& b)
{
	// スコアを比較
	if (a.score != b.score) return a.score > b.score;
	// 同点なら日付が新しい順
	return a.date > b.date;
}

bool Ranking::AddAndSortRanking(const PlayData& playdata)
{
	// 変更前の状態を保持
	std::vector<PlayData> before = m_ranking;

	// 追加
	m_ranking.push_back(playdata);

	// ソート
	std::sort(m_ranking.begin(), m_ranking.end(),
		[this](const PlayData& a, const PlayData& b)
		{
			return CompareRanking(a, b);
		});

	// 上位制限
	if (m_ranking.size() > D_RANKING_MAX_COUNT)
		m_ranking.resize(D_RANKING_MAX_COUNT);

	// 変更があったか判定
	return m_ranking != before;
}

bool Ranking::SaveRankingCsv()
{
	// 既存を消して書き直す
	std::ofstream file(path, std::ios::trunc);

	if (!file.is_open())
		return false;

	// ヘッダ無し（必要なら書く：file << "Score,Date\n";）
	for (const auto& r : m_ranking)
	{
		// score,date
		file << r.score << "," << r.date << "\n";
	}

	return true;
}

int Ranking::GetCurrentRank(const PlayData& playdata)
{
	// 順位検索
	for (size_t i = 0; i < m_ranking.size(); ++i)
	{
		if (m_ranking[i] == playdata)
		{
			return static_cast<int>(i) + 1;
		}
	}
}
