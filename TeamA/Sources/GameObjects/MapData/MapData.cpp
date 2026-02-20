#include "MapData.h"

#include "../../Utilitys/ProjectConfig.h"
#include "../../System/ResourceManager.h"

#include "../../Utilitys/Random.h"

#include "..//ObjectManager.h"
#include "..//PotatoPlant/PotatoPlant.h"
#include "..//Jewel/Jewel.h"

#include <fstream>
#include <string>
#include <sstream>

MapData::MapData()
	:m_soil{}
{
}

MapData::~MapData()
{
}

void MapData::Initialize()
{
	// 画像の読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	m_soil[0] = rm.GetImageResource("Assets/Sprites/soil/soil1.PNG")[0];

	// 道のzlayer
	m_zLayer = 2;
	 
	// マップデータの読み込み
	LoadMapCsv();
	// ランダムの種を設定
	Random::SetSeed();
	// 宝石の生成
	CreateJewel();
	// プラントの生成
	CreatePlant();
}

void MapData::Draw() const
{
	for (size_t y = 0; y < m_mapData.size(); ++y)
	{
		for (size_t x = 0; x < m_mapData[y].size(); ++x)
		{
			const char& ch = m_mapData[y][x];

			float size = D_BOX_SIZE;
			Vector2D position = { size * x,size * y };

			Vector2D pos[4] = {
				{position.x + 32.0f,position.y + 32.0f},
				{position.x + 96.0f,position.y + 32.0f},
				{position.x + 32.0f,position.y + 96.0f},
				{position.x + 96.0f,position.y + 96.0f},
			};

			unsigned int debug_color = 0xffffff;

			switch (ch)
			{
			case 'r':
				DrawRotaGraphF(pos[0].x, pos[0].y, 1.0f, 0.0f, m_soil[0], TRUE);
				DrawRotaGraphF(pos[1].x, pos[1].y, 1.0f, 0.0f, m_soil[0], TRUE);
				DrawRotaGraphF(pos[2].x, pos[2].y, 1.0f, 0.0f, m_soil[0], TRUE);
				DrawRotaGraphF(pos[3].x, pos[3].y, 1.0f, 0.0f, m_soil[0], TRUE);
			
				debug_color = GetColor(0, 255, 0);
				break;
			case 's':
				debug_color = GetColor(255, 0, 0);
				break;
			case 'w':
				debug_color = GetColor(0, 0, 255);
				break;
			}

#if _DEBUG
			// デバッグ用
			DrawBoxAA(position.x, position.y, position.x + size, position.y + size, debug_color, FALSE);
			DrawFormatString(position.x, position.y, 0xffffff, "%c(%d,%d)", ch, x, y);
#endif
		}
	}
}

bool MapData::DestroySoil(const Vector2D& worldPos, const e_Direction& derection)
{
	GridPos grid = WorldToGrid(worldPos);

	switch (derection)
	{
	case e_Direction::up:
		grid.y--;
		break;
	case e_Direction::down:
		grid.y++;
		break;
	case e_Direction::left:
		grid.x--;
		break;
	case e_Direction::right:
		grid.x++;
		break;
	}

	// 配列範囲内か確認
	if (IsGridInBounds(grid))
	{
		// 土なら
		if (m_mapData[grid.y][grid.x] == 's')
		{
			// 道にする
			m_mapData[grid.y][grid.x] = 'r';

			return true;
		}
	}
	return false;
}

e_TileType MapData::TileType(const Vector2D& worldPos) const
{
	GridPos gridPos = WorldToGrid(worldPos);
	switch (m_mapData[gridPos.y][gridPos.x])
	{
	case 'r':
		return e_TileType::road;
		break;
	case 's':
		return e_TileType::soil;
		break;
	case 'w':
		return e_TileType::wall;
		break;
	}

	return e_TileType::none;
}

Vector2D MapData::GetTileLocation(const Vector2D& worldPos)
{
	return GridToWorld(WorldToGrid(worldPos));
}

MapData::GridPos MapData::WorldToGrid(const Vector2D& worldPos) const
{
	// ワールド座標をステージ内に収める
	Vector2D clampedWorld = ClampWorldPosition(worldPos);

	// グリッドに変換
	GridPos grid;
	grid.x = static_cast<int>(clampedWorld.x / D_BOX_SIZE);
	grid.y = static_cast<int>(clampedWorld.y / D_BOX_SIZE);

	// グリッドを範囲内に収めて返す
	return ClampGridPosition(grid);
}

Vector2D MapData::GridToWorld(const GridPos& gridPos) const
{
	// グリッド座標をワールド座標に変換
	Vector2D world = { static_cast<float>(gridPos.x * D_BOX_SIZE) , static_cast<float>(gridPos.y * D_BOX_SIZE) };
	// 中心に補正
	world += D_BOX_SIZE * 0.5f;
	// ワールド座標を範囲内に収めて返す
	return ClampWorldPosition(world);
}

Vector2D MapData::ClampWorldPosition(const Vector2D& worldPos) const
{
	Vector2D clamped = worldPos;
	// xを0から最大座標に収める
	if (clamped.x < 0)  clamped.x = 0;
	if (clamped.x > D_STAGE_WIDTH)  clamped.x = D_STAGE_WIDTH;
	// yを0から最大座標に収める
	if (clamped.y < 0)  clamped.y = 0;
	if (clamped.y > D_STAGE_HEIGHT)  clamped.y = D_STAGE_HEIGHT;

	return clamped;
}

MapData::GridPos MapData::ClampGridPosition(const GridPos& gridPos) const
{
	// 空チェック
	if (m_mapData.empty() || m_mapData[0].empty())
		return GridPos{ 0, 0 };

	// 最大インデックスを取得
	GridPos clamped = gridPos;
	const int maxX = static_cast<int>(m_mapData[0].size()) - 1;
	const int maxY = static_cast<int>(m_mapData.size()) - 1;

	// xを0から最大インデックスに収める
	if (clamped.x < 0) clamped.x = 0;
	if (clamped.x > maxX) clamped.x = maxX;
	// yを0から最大インデックスに収める
	if (clamped.y < 0) clamped.y = 0;
	if (clamped.y > maxY) clamped.y = maxY;

	return clamped;
}

bool MapData::IsWorldInBounds(const Vector2D& worldPos) const
{
	return worldPos.x >= 0 &&
		worldPos.x <= D_STAGE_WIDTH &&
		worldPos.y >= 0 &&
		worldPos.y <= D_STAGE_HEIGHT;
}

bool MapData::IsGridInBounds(const GridPos& gridPos) const
{
	// 空チェック
	if (m_mapData.empty() || m_mapData[0].empty())
		return false;

	const int maxX = static_cast<int>(m_mapData[0].size()) - 1;
	const int maxY = static_cast<int>(m_mapData.size()) - 1;

	return gridPos.x >= 0 &&
		gridPos.x <= maxX &&
		gridPos.y >= 0 &&
		gridPos.y <= maxY;
}

void MapData::LoadMapCsv()
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

void MapData::CreatePlant()
{
	ObjectManager& om = ObjectManager::GetInstance();

	om.RequestSpawn<PotatoPlant>({ 192.0f,192.0f });
	om.RequestSpawn<PotatoPlant>({ 640.0f,192.0f });
	om.RequestSpawn<PotatoPlant>({ 1152.0f,192.0f });
}

void MapData::CreateJewel()
{

	// 各マスに宝石を生成する数を決める処理

	// 宝石の生成数を入れる配列
	std::vector<std::vector<int>> jewel;

	// 要素数を同じにする
	jewel = std::vector<std::vector<int>>(
		m_mapData.size(),
		std::vector<int>(m_mapData[0].size(), 0)
	);

	for (size_t y = 0; y < jewel.size(); ++y)
	{
		for (size_t x = 0; x < jewel[y].size(); ++x)
		{
			int value = 0;

			// 深さ 5～14 のときのみ生成率を上げる
			if (y >= 5 && y <= 3 + D_BOX_COUNT)
			{
				// 0.0 ～ 1.0 の乱数に正規化
				float r = static_cast<float>(Random::GetRand())
					/ static_cast<float>(UINT_MAX);

				// 生成するかしないかを決める処理
				// 深くなるほど確率を上げる（5 → 0%、14 → 100%）
				float depthRate = static_cast<float>(y - 5) / 10.0f;

				if (r < depthRate)
				{
					// 0～5 のランダム個数
					value = static_cast<int>(Random::GetRand() % 5);
				}
			}

			jewel[y][x] = value;
		}
	}


	// 生成する処理
	ObjectManager& om = ObjectManager::GetInstance();

	constexpr int kMaxOffset = 64;

	for (size_t y = 0; y < jewel.size(); ++y)
	{
		for (size_t x = 0; x < jewel[y].size(); ++x)
		{
			const int spawnNum = jewel[y][x];

			// 中心座標
			Vector2D pos = GridToWorld({ static_cast<int>(x), static_cast<int>(y) });

			switch (spawnNum)
			{
			case 0:

				break;
			case 1:
				om.RequestSpawn<Jewel>(pos);

				break;
			case 2:
				// 左上と右下
				om.RequestSpawn<Jewel>(pos - 32.0f);
				om.RequestSpawn<Jewel>(pos + 32.0f);

				break;
			case 3:
				// 上と左下と右下
				om.RequestSpawn<Jewel>({ pos.x,pos.y - 24.0f });
				om.RequestSpawn<Jewel>({ pos.x - 24.0f,pos.y + 24 });
				om.RequestSpawn<Jewel>({ pos.x + 24.0f,pos.y + 24 });

				break;
			case 4:
				// 左上と右上と左下と右下
				om.RequestSpawn<Jewel>(pos - 32.0f);
				om.RequestSpawn<Jewel>({ pos.x + 32.0f,pos.y - 32 });
				om.RequestSpawn<Jewel>({ pos.x - 32.0f,pos.y + 32 });
				om.RequestSpawn<Jewel>(pos + 32.0f);
				break;
			}
		}
	}
}
