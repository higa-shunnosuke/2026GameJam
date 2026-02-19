#include "MapData.h"

#include "../../Utilitys/Vector2D.h"

#include <fstream>
#include <string>
#include <sstream>

MapData::MapData()
{
}

MapData::~MapData()
{
}

void MapData::Initialize()
{
	// マップデータの読み込み
	LoadMapCsv();
}

void MapData::Draw() const
{
	for (size_t y = 0; y < m_mapData.size(); ++y)
	{
		for (size_t x = 0; x < m_mapData[y].size(); ++x)
		{
			const char& ch = m_mapData[y][x];

			float size = 128.0f;
			Vector2D position = { size * x,size * y };
			switch (ch)
			{
			case '#':
				DrawBoxAA(position.x, position.y, position.x + size, position.y + size, GetColor(255, 0, 0), FALSE);
				break;
			case 'r':
				DrawBoxAA(position.x, position.y, position.x + size, position.y + size, GetColor(0, 255, 0), FALSE);
				break;
			case 'g':
				DrawBoxAA(position.x, position.y, position.x + size, position.y + size, GetColor(0, 0, 255), FALSE);
				break;

			}
			DrawFormatString(position.x, position.y, 0xffffff, "%c", ch);
		}
	}
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
