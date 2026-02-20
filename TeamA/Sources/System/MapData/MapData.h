#pragma once
#include "../../Utilitys/Singleton.h"

#include "../../Utilitys/Vector2D.h"
#include "Direction.h"

#include <vector>

enum class e_TileType
{
	none,		// 空
	road,		// 道
	soil,		// 土
	wall,		// 壁

};

class MapData : public Singleton<MapData>
{
private:

	struct GridPos
	{
		int x;
		int y;
	};

	std::vector<std::vector<char>> m_mapData;	// マップ配列
	int m_soil;

public:
	MapData();
	~MapData();

public:
	void Initialize();
	void Draw() const;

public:

	/// <summary>
	/// 土を破壊する
	/// </summary>
	/// <param name="worldPos">現在の座標</param>
	/// <param name="derection">向いている方向</param>
	void DestroySoil(const Vector2D& worldPos,const e_Direction& derection);

	/// <summary>
	/// 移動後のグリッド情報を返す関数
	/// </summary>
	/// <param name="location">移動後の座標</param>
	/// <returns>移動後の座標のグリッド情報</returns>
	e_TileType TileType(const Vector2D& worldPos) const;

private:
	/// <summary>
	/// 座標をグリッドに変換する
	/// </summary>
	MapData::GridPos WorldToGrid(const Vector2D& worldPos) const;

	/// <summary>
	/// グリッドを二次元座標に変換する
	/// </summary>
	Vector2D GridToWorld(const GridPos& gridPos) const;


	/// <summary>
	/// ワールド座標を収める
	/// </summary>
	/// <param name="worldPos"></param>
	/// <returns></returns>
	Vector2D ClampWorldPosition(const Vector2D& worldPos) const;


	/// <summary>
	/// グリッド座標を収める
	/// </summary>
	/// <param name="gridPos"></param>
	/// <returns></returns>
	MapData::GridPos ClampGridPosition(const GridPos& gridPos) const;

	bool IsWorldInBounds(const Vector2D& worldPos) const;

	bool IsGridInBounds(const GridPos& gridPos) const;

private:

	/// <summary>
	/// マップcsvの読み込み
	/// </summary>
	void LoadMapCsv();
};