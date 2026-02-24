#include "Result.h"
#include "../../System/ResourceManager.h"
#include "../../System/InputManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <DxLib.h>

// デバッグ出力用
#include <iostream>

#define D_RANKING_MAX_COUNT (10)	// ランキング10位まで

// コンストラクタ
Result::Result()
{
	
}

// 初期化
void Result::Initialize()
{
	ResourceManager& rm = ResourceManager::GetInstance();

	m_background = rm.GetImageResource("Assets/Textures/InGame/Sky3.PNG")[0];

	m_jewelImage = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald1.PNG")[0];

	m_moguraImage[0] = rm.GetImageResource("Assets/Sprites/Player/Down3.PNG")[0]; //  下向きドリルモグラ読み込み

	m_moguraImage[1] = rm.GetImageResource("Assets/Sprites/Player/Down2.PNG")[0]; //  下向きドリルモグラ読み込み

	m_moguraImage[2] = rm.GetImageResource("Assets/Sprites/Player/Down1.PNG")[0]; //  下向きドリルモグラ読み込み
	m_cursorNumber = 0;

	// サウンド
	m_resultBgm = rm.GetSoundResource("Assets/Sounds/BGM/Title.mp3");
	m_selectSe = rm.GetSoundResource("Assets/Sounds/SE/Click2.mp3");
	m_decisionSe = rm.GetSoundResource("Assets/Sounds/SE/Click1.mp3");

	// ファイルパス
	const std::string path = "Resource/RankingData/Ranking.csv";

	// ファイルの読み込み
	LoadRankingCsv(path);

	// 配列に追加、ソート、11位以下切り捨て
	if (AddAndSortRanking(m_currentData))
	{
		// csvに保存
		//SaveRankingCsv(path);
		if (!SaveRankingCsv(path))
		{
			// ここが出たら「開けていない」
			// DxLibならログや表示
			int a = 0;
			a = 1;
		}
	}

	std::cout << "\nスコア,yyyy-mm-dd hh:mm:ss" << std::endl;
	for (int i = 0; i < (int)m_ranking.size(); i++)
	{
		std::cout << m_ranking[i].score << "," << m_ranking[i].date << std::endl;
	}

	// BGM再生
	PlaySoundMem(m_resultBgm, DX_PLAYTYPE_LOOP);
}

// 更新
SceneType Result::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();

	input.TitleApplyInput(m_left, m_right, m_decision);

	if (m_right == eInputState::Pressed)
	{
		m_cursorNumber = (m_cursorNumber + 1) % 3; // 右へ

		// SEを再生
		PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
	}
	if (m_left == eInputState::Pressed)
	{
		m_cursorNumber = (m_cursorNumber + 2) % 3; // 左へ

		// SEを再生
		PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
	}
	if (m_decision == eInputState::Pressed)//決定が押されたら
	{
		// SEを再生
		PlaySoundMem(m_decisionSe, DX_PLAYTYPE_BACK);

		switch (m_cursorNumber)
		{
		case 0:
			return SceneType::ingame; //インゲームシーンに遷移する

		case 1:
			return SceneType::ingame;//後でランキングに変更,ランキングシーンに遷移する

		case 2:
			return SceneType::title;//タイトルシーンに遷移する

		default:
			break;//error時
		}
	}
	// エンドシーンに遷移する
	if (m_decision == eInputState::Pressed)
	{
		return SceneType::end;
	}

	// 親クラスの更新
	return __super::Update(delta);
}

// 描画
void Result::Draw() const
{
	//	リザルト表示

	DrawRotaGraph(640, 250, 0.25, 0, m_background, TRUE);

	DrawRotaGraph(390, 350, 0.05, 0, m_jewelImage, TRUE);

	SetFontSize(64);
	DrawFormatString(460, 200, 0xffffff, "ResultScore");

	SetFontSize(40);
	DrawFormatString(480, 330, 0xffffff, "獲得ジュエル表示");

	DrawFormatString(480, 390, 0xffffff, "スコア表示");

	SetFontSize(50);
	DrawFormatString(250, 600, 0xffffff, "RESTART");
	DrawFormatString(560, 600, 0xffffff, "RANKING");
	DrawFormatString(905, 600, 0xffffff, "TITLE");

	int cursorx = 0;
	switch (m_cursorNumber)
	{
	case 0: cursorx = 340; break; // RESTART
	case 1: cursorx = 650; break; // RANKING
	case 2: cursorx = 950; break; // END
	}

	DrawRotaGraph(cursorx, 550, 0.07, 0, m_moguraImage[0], TRUE);//カーソルモグラ描画
}

// 終了
void Result::Finalize()
{
	// BGM停止
	StopSoundMem(m_resultBgm);
}

// 現在のシーンタイプ取得
const SceneType Result::GetNowSceneType() const
{
	// リザルト
	return SceneType::resutart;
}

PlayData Result::TransitionData(const PlayData* prevdata)
{
	if (prevdata == nullptr) return PlayData();

	// データがあるなら受け取る
	m_currentData = *prevdata;

	return PlayData();
}

bool Result::LoadRankingCsv(const std::string& path)
{
	m_ranking.clear();

	std::ifstream file("Resource/RankingData/Ranking.csv");
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

bool Result::CompareRanking(const PlayData& a, const PlayData& b)
{
	// スコアを比較
	if (a.score != b.score) return a.score > b.score;
	// 同点なら日付が新しい順
	return a.date > b.date;
}

bool Result::AddAndSortRanking(const PlayData& newData)
{
	// 変更前の状態を保持
	std::vector<PlayData> before = m_ranking;

	// 追加
	m_ranking.push_back(newData);

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

bool Result::SaveRankingCsv(const std::string& path)
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
