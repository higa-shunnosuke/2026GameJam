#include "InGame.h"
#include "../../Utilitys/ProjectConfig.h"
#include "../../System/ResourceManager.h"

#include <fstream>
#include <string>
#include <sstream>

InGame::InGame()
	: player(nullptr)
	, jewel(nullptr)
	, groundImage()
{
}

void InGame::Initialize()
{
	// 背景画像読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	groundImage = rm.GetImageResource("Assets/Textures/InGame/BackGround/Ground.PNG")[0];

	ObjectManager& object = ObjectManager::GetInstance();
	player = object.RequestSpawn<Player>(Vector2D(580.0f,360.0f));
	jewel = object.RequestSpawn<Jewel>(Vector2D(700.0f, 360.0f));

	// マップデータの読み込み
	LoadMapCsv();
}

// 更新処理
SceneType InGame::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	// リザルトシーンに遷移する
	if (input.GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return SceneType::resutart;
	}

	// オブジェクトマネージャーのインスタンスを取得する
	ObjectManager& object = ObjectManager::GetInstance();

	// 生成するオブジェクトがあれば、オブジェクトリスト内に挿入する
	object.ProcessPendingCreates();

	// リスト内のオブジェクトを更新する
	for (ObjectBase* obj : object.GetObjects())
	{
		obj->Update();
	}

	// オブジェクトの当たり判定を確認する
	object.CheckPlayerCollisions(dynamic_cast<ObjectBase*>(player));

	// 破棄待ちオブジェクトをm_objectsから削除する
	object.ProcessPendingDestroys();

	// 親クラスの更新処理
	return __super::Update(delta);
}

// 描画処理
void InGame::Draw() const
{
	float imageSize = 0.222f;
	int offset = 400;

	// 背景画像の描画
	DrawRotaGraph(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2 + offset, imageSize, 0.0, groundImage, TRUE);

	//	インゲーム表示
	DrawFormatString(10, 10, 0xffffff, "InGame");

	//for (size_t y = 0; y < m_mapData.size(); ++y)
	//{
	//	for (size_t x = 0; x < m_mapData[y].size(); ++x)
	//	{
	//		const char& ch = m_mapData[y][x];

	//		Vector2D position = { 128.0f * x,128.0f * y };
	//		float size = 64.0f;
	//		switch (ch)
	//		{
	//		case '#':
	//			DrawBoxAA(position.x - size, position.y - size, position.x + size, position.y + size, GetColor(255, 0, 0), FALSE);
	//			break;
	//		case 'r':
	//			DrawBoxAA(position.x - size, position.y - size, position.x + size, position.y + size, GetColor(0, 255, 0), FALSE);
	//			break;
	//		case 'g':
	//			DrawBoxAA(position.x - size, position.y - size, position.x + size, position.y + size, GetColor(0, 0, 255), FALSE);
	//			break;

	//		}
	//		DrawFormatString(position.x, position.y, 0xffffff, "%c", ch);
	//	}
	//}

	__super::Draw();
}

// 終了処理
void InGame::Finalize()
{
	ObjectManager& object = ObjectManager::GetInstance();
	object.DestroyAllObjects();
}

// 現在のシーンタイプ取得
const SceneType InGame::GetNowSceneType() const
{
	// リザルト
	return SceneType::ingame;
}

void InGame::LoadMapCsv()
{
	// g : 土
	// r : 道
	// # : 天井の蓋

	m_mapData.clear();

	std::ifstream file("Resource/MapData/Map.csv");
	if (!file) return;

	std::vector<char> row;
	char ch;

	while (file.get(ch))
	{
		switch (ch)
		{
		case ',':
			continue;
			break;
		case '\n':
			m_mapData.push_back(row);
			row.clear();
			break;
		case '\r':
			// Windows対策（CRLFのRを無視）
			continue;
			break;
		default:
			// g,r,#を追加する
			row.push_back(ch);
			break;
		}
	}

	// 最終行の改行なし対策
	if (!row.empty())
	{
		m_mapData.push_back(row);
	}

}
