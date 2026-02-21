#include "MapData.h"

#include "../../Utilitys/ProjectConfig.h"
#include "../../System/ResourceManager.h"

#include "../../Utilitys/Random.h"

#include "../ObjectManager.h"
#include "../PotatoPlant/PotatoPlant.h"
#include "../Jewel/Jewel.h"
#include "../Rock/Rock.h"

#include <fstream>
#include <string>
#include <sstream>

#define JEWEL_RATE (40)		// 宝石の生成確率（％）
#define ROCK_RATE  (10)		// 岩の生成確率（％）

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
	m_soil[0] = rm.GetImageResource("Assets/Sprites/soil/soil0.PNG")[0];
	m_soil[1] = rm.GetImageResource("Assets/Sprites/soil/soil1.PNG")[0];
	m_soil[2] = rm.GetImageResource("Assets/Sprites/soil/soil2.PNG")[0];
	m_soil[3] = rm.GetImageResource("Assets/Sprites/soil/soil3.PNG")[0];

	// 道のzlayer
	m_zLayer = 2;
	 
	// マップデータの読み込み
	LoadMapCsv();
	// ランダムの種を設定
	Random::SetSeed();
	// プラントの生成
	SpawnPlant();
	// 宝石と岩の生成
	GenerateMapObjects();
}

void MapData::Draw() const
{
	// ラムダ式（無名関数）を作成
	auto DrawPiece = [&](const TilePiece& p, const Vector2D& center)
		{
			const float angle = (float)p.rot90 * DX_PI_F * 0.5f;
			DrawRotaGraphF(center.x, center.y, 1.0f, angle, p.img, TRUE);
		};

	for (size_t y = 0; y < m_mapData.size(); ++y)
	{
		for (size_t x = 0; x < m_mapData[y].size(); ++x)
		{
			const char ch = m_mapData[y][x];

			const float size = D_BOX_SIZE;
			const Vector2D position = { size * (float)x, size * (float)y };

			// 4分割（64x64想定）を中央座標で描く
			const Vector2D pos[4] = {
				{ position.x + 32.0f, position.y + 32.0f }, // LU
				{ position.x + 96.0f, position.y + 32.0f }, // RU
				{ position.x + 32.0f, position.y + 96.0f }, // LD
				{ position.x + 96.0f, position.y + 96.0f }, // RD
			};

			if (ch == 'r')
			{
				const int mask = GetRoadMask(GridPos{ (int)x, (int)y });
				const AutoTile4 tile = ConvertMaskToTile(GridPos{ (int)x,(int)y }, mask);

				DrawPiece(tile.lu, pos[0]);
				DrawPiece(tile.ru, pos[1]);
				DrawPiece(tile.ld, pos[2]);
				DrawPiece(tile.rd, pos[3]);
			}

#if _DEBUG
			// デバッグ
			//unsigned int debug_color = 0xffffff;
			//if (ch == 'r') debug_color = GetColor(0, 255, 0);
			//else if (ch == 's') debug_color = GetColor(255, 0, 0);
			//else if (ch == 'w') debug_color = GetColor(0, 0, 255);

			//DrawBoxAA(position.x, position.y, position.x + size, position.y + size, debug_color, FALSE);
			//DrawFormatString(position.x, position.y, 0xffffff, "%c(%d,%d)", ch, (int)x, (int)y);
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
	// s : 土
	// r : 道
	// w : 天井の蓋

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
			// g,r,wを追加する
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

void MapData::SpawnPlant()
{
	ObjectManager& om = ObjectManager::GetInstance();

	om.RequestSpawn<PotatoPlant>({ 192.0f,260.0f });
	om.RequestSpawn<PotatoPlant>({ 640.0f,260.0f });
	om.RequestSpawn<PotatoPlant>({ 1152.0f,260.0f });
}

void MapData::GenerateMapObjects()
{
	const int start_y = D_BOX_OFFSET;
	const int end_y = D_BOX_OFFSET + D_BOX_COUNT;

	// 生成中だけ使う岩占有配列（ローカル）
	std::vector<std::vector<bool>> rockOcc(m_mapData.size());
	for (size_t y = 0; y < m_mapData.size(); ++y)
		rockOcc[y].assign(m_mapData[y].size(), false);

	// 到達判定の基準地点（※あなたのゲームの「開始地点」に合わせて設定）
	// 例：生成範囲の左上を基準にする（仮）
	const GridPos startGrid{ 0, start_y };

	for (int y = start_y; y < end_y && y < (int)m_mapData.size(); ++y)
	{
		for (int x = 0; x < (int)m_mapData[y].size(); ++x)
		{
			GridPos grid{ x, y };
			const int r = (int)(Random::GetRand() % 100);

			if (r < JEWEL_RATE)
			{
				SpawnJewel(grid);
			}
			else if (r < JEWEL_RATE + ROCK_RATE)
			{
				if (CanPlaceRock(grid, rockOcc, startGrid))
				{
					rockOcc[y][x] = true;
					SpawnRock(grid);
				}
			}
		}
	}
}

void MapData::SpawnJewel(const GridPos& gridPos)
{
	// 5層以上は見ない
	if (gridPos.y < 5)
		return;

	// 宝石の数5
	int value = 0;
	// 深さに応じて最低、最大出現数を増やす
	int current_min = 0;
	int current_max = 1;
	if (gridPos.y > 7)
	{
		current_min = 1;
		current_max = 2;
	}
	if (gridPos.y > 9)
	{
		current_min = 1;
		current_max = 3;
	}
	if (gridPos.y > 12)
	{
		current_min = 2;
		current_max = 3;
	}
	if (gridPos.y > 15)
	{
		current_min = 3;
		current_max = 4;
	}

	// 最低値から最大値までの間でランダム
	int range = current_max - current_min + 1;
	value = current_min + (Random::GetRand() % range);

	ObjectManager& om = ObjectManager::GetInstance();
	// 中心座標
	Vector2D pos = GridToWorld({ static_cast<int>(gridPos.x), static_cast<int>(gridPos.y) });

	switch (value)
	{
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

void MapData::SpawnRock(const GridPos& gridPos)
{
	// 範囲外
	if (!IsGridInBounds(gridPos)) return;

	// 深さ制限
	if (gridPos.y < 5) return;

	ObjectManager& om = ObjectManager::GetInstance();
	Vector2D pos = GridToWorld({ static_cast<int>(gridPos.x), static_cast<int>(gridPos.y) });

	om.RequestSpawn<Rock>(pos);
	m_mapData[gridPos.y][gridPos.x] = 'w';
}

int MapData::GetRoadMask(GridPos gridPos) const
{
	int mask = 0;

	// 上,右,下,左
	const GridPos dir[4] = { {0,-1}, {1,0}, {0,1}, {-1,0} };
	const int bit[4] = { 1,2,4,8 };

	for (int i = 0; i < 4; ++i)
	{
		GridPos n = { gridPos.x + dir[i].x, gridPos.y + dir[i].y };

		// 配列外なら見ない
		if (!IsGridInBounds(n)) continue;

		if (m_mapData[n.y][n.x] == 'r')
		{
			mask |= bit[i];
		}
	}

	return mask;
}

MapData::AutoTile4 MapData::ConvertMaskToTile(GridPos gridPos, int mask) const
{
	AutoTile4 result;
	const bool up = (mask & 1) != 0;
	const bool right = (mask & 2) != 0;
	const bool down = (mask & 4) != 0;
	const bool left = (mask & 8) != 0;

	// 斜めチェック
	// ラムダ式（無名関数）を作成
	auto IsRoad = [&](int x, int y)
		{
			GridPos p{ x, y };
			return IsGridInBounds(p) && m_mapData[p.y][p.x] == 'r';
		};

	const bool nw = !IsRoad(gridPos.x - 1, gridPos.y - 1);
	const bool ne = !IsRoad(gridPos.x + 1, gridPos.y - 1);
	const bool sw = !IsRoad(gridPos.x - 1, gridPos.y + 1);
	const bool se = !IsRoad(gridPos.x + 1, gridPos.y + 1);

	// -------------------------
	// LU（左上）：上 & 左
	// -------------------------
	if (!up && !left)
		result.lu = { m_soil[2],3 };
	else if (up && !left)
		result.lu = { m_soil[1],3 };
	else if (!up && left)
		result.lu = { m_soil[1],0 };
	else
	{
		if (nw)
			result.lu = { m_soil[3],3 };
		else
			result.lu = { m_soil[0],0 };
	}


	// -------------------------
	// RU（右上）：上 & 右
	// -------------------------
	if (!up && !right)
		result.ru = { m_soil[2],0 };
	else if (up && !right)
		result.ru = { m_soil[1],1 };
	else if (!up && right)
		result.ru = { m_soil[1],0 };
	else
	{
		if (ne)
			result.ru = { m_soil[3],0 };
		else
			result.ru = { m_soil[0],0 };
	}

	// -------------------------
	// LD（左下）：下 & 左
	// -------------------------
	if (!down && !left)
		result.ld = { m_soil[2],2 };
	else if (down && !left)
		result.ld = { m_soil[1],3 };
	else if (!down && left)
		result.ld = { m_soil[1],2 };
	else
	{
		if (sw)
			result.ld = { m_soil[3],2 };
		else
			result.ld = { m_soil[0],0 };
	}

	// -------------------------
	// RD（右下）：下 & 右
	// -------------------------
	if (!down && !right)
		result.rd = { m_soil[2],1 };
	else if (down && !right)
		result.rd = { m_soil[1],1 };
	else if (!down && right)
		result.rd = { m_soil[1],2 };
	else
	{
		if (se)
			result.rd = { m_soil[3],1 };
		else
			result.rd = { m_soil[0],0 };
	}

	return result;
}

bool MapData::IsWalkableTerrain(const GridPos& gridPos) const
{
	const char t = m_mapData[gridPos.y][gridPos.x];

	// 通れない地形
	if (t == 'w') return false;

	// 通れる地形（必要なら条件を追加/制限）
	return true;
}

int MapData::CountReachableCells(const GridPos& start,const std::vector<std::vector<bool>>& rockOcc,const GridPos* extraRock) const
{
	const int h = (int)m_mapData.size();
	if (h == 0) return 0;

	const int w = (int)m_mapData[0].size();

	auto inBounds = [&](const GridPos& p) -> bool
		{
			return (0 <= p.x && p.x < w && 0 <= p.y && p.y < h);
		};

	auto isBlocked = [&](const GridPos& p) -> bool
		{
			if (!inBounds(p)) return true;
			if (!IsWalkableTerrain(p)) return true;

			// 仮置き岩（指定があるときだけ）
			if (extraRock && p.x == extraRock->x && p.y == extraRock->y) return true;

			// 既に確定した岩（GenerateMapObjects内のローカル配列）
			if (rockOcc[p.y][p.x]) return true;

			return false;
		};

	if (isBlocked(start)) return 0;

	std::vector<std::vector<uint8_t>> visited(h);
	for (int y = 0; y < h; ++y)
		visited[y].assign(w, 0);

	std::vector<GridPos> q;
	q.reserve((size_t)w * (size_t)h);

	visited[start.y][start.x] = 1;
	q.push_back(start);

	const GridPos dir4[4] = { {0,-1},{1,0},{0,1},{-1,0} };

	int count = 0;
	for (size_t qi = 0; qi < q.size(); ++qi)
	{
		const GridPos cur = q[qi];
		++count;

		for (int i = 0; i < 4; ++i)
		{
			GridPos nxt{ cur.x + dir4[i].x, cur.y + dir4[i].y };

			if (!inBounds(nxt)) continue;
			if (visited[nxt.y][nxt.x]) continue;
			if (isBlocked(nxt)) continue;

			visited[nxt.y][nxt.x] = 1;
			q.push_back(nxt);
		}
	}

	return count;
}

bool MapData::CanPlaceRock(const GridPos& rockPos,const std::vector<std::vector<bool>>& rockOcc,const GridPos& start) const
{
	// 範囲チェック
	if (rockPos.y < 0 || rockPos.y >= (int)m_mapData.size()) return false;
	if (rockPos.x < 0 || rockPos.x >= (int)m_mapData[rockPos.y].size()) return false;

	// 既に岩なら不可
	if (rockOcc[rockPos.y][rockPos.x]) return false;

	// 地形的に置けない場所は不可（必要に応じて条件調整）
	if (!IsWalkableTerrain(rockPos)) return false;

	// start が歩けないと探索が0になるので、必ず歩ける場所を渡すこと
	if (!IsWalkableTerrain(start)) return false;
	if (rockOcc[start.y][start.x]) return false;

	// rockPos を除いた「本来到達できるべきマス総数」を数える
	int total = 0;
	for (int y = 0; y < (int)m_mapData.size(); ++y)
	{
		for (int x = 0; x < (int)m_mapData[y].size(); ++x)
		{
			if (x == rockPos.x && y == rockPos.y) continue; // 候補マスは除外
			if (!IsWalkableTerrain(GridPos{ x, y })) continue;
			if (rockOcc[y][x]) continue;
			++total;
		}
	}

	// rockPos を「仮に岩」にした状態で到達可能数を数える
	const int reach = CountReachableCells(start, rockOcc, &rockPos);

	// 全て到達できるなら分断なし
	return (reach == total);
}