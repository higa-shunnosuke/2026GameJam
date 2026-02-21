#pragma once

#include "../ObjectBase.h"
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

class MapData : public ObjectBase
{
private:

	/// <summary>
	/// グリッド座標を入れる構造体
	/// </summary>
	struct GridPos
	{
		int x;
		int y;
	};

	/// <summary>
	/// 画像情報
	/// </summary>
	struct TilePiece
	{
		int img;	// 画像ハンドル
		int rot90;	// 回転回数
	};

	/// <summary>
	/// タイル1マスの画像情報
	/// </summary>
	struct AutoTile4
	{
		TilePiece lu; // 左上
		TilePiece ru; // 右上
		TilePiece ld; // 左下
		TilePiece rd; // 右下
	};

	std::vector<std::vector<char>> m_mapData;	// マップ配列
	int m_soil[4];								// 道の画像

public:
	MapData();
	~MapData();

public:
	void Initialize() override;
	void Draw() const override;

public:

	/// <summary>
	/// 土を破壊する
	/// </summary>
	/// <param name="worldPos">現在の座標</param>
	/// <param name="derection">向いている方向</param>
	bool DestroySoil(const Vector2D& worldPos,const e_Direction& derection);

	/// <summary>
	/// 移動後のグリッド情報を返す関数
	/// </summary>
	/// <param name="location">移動後の座標</param>
	/// <returns>移動後の座標のグリッド情報</returns>
	e_TileType TileType(const Vector2D& worldPos) const;


	/// <summary>
	/// ワールド座標をグリッド中央に寄せる
	/// </summary>
	/// <param name="worldPos"></param>
	/// <returns></returns>
	Vector2D GetTileLocation(const Vector2D& worldPos);

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

	/// <summary>
	/// プラントを生成する処理
	/// </summary>
	void CreatePlant();

	/// <summary>
	/// 宝石を生成する処理
	/// </summary>
	void CreateJewel();

	/// <summary>
	/// 岩を生成する
	/// </summary>
	void CreateRock();


private:

	/// <summary>
	/// 上下左右に道があるかを確認する
	/// </summary>
	/// <param name="gridPos"></param>
	/// <returns></returns>
	int GetRoadMask(GridPos gridPos) const;

	/// <summary>
	/// maskから分割画像構造体を返す
	/// </summary>
	/// <param name="gridPos"></param>
	/// <param name="mask"></param>
	/// <returns></returns>
	AutoTile4 ConvertMaskToTile(GridPos gridPos, int mask) const;
};