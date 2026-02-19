#pragma once
#include "../../Utilitys/Singleton.h"

#include <vector>

class MapData : public Singleton<MapData>
{
private:

	std::vector<std::vector<char>> m_mapData;

public:
	MapData();
	~MapData();

public:
	void Initialize();
	void Draw() const;

private:

	/// <summary>
	/// ƒ}ƒbƒvcsv‚Ì“Ç‚İ‚İ
	/// </summary>
	void LoadMapCsv();
};