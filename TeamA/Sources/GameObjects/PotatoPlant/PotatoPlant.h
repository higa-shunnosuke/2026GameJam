#pragma once
#include "../ObjectBase.h"

#include "../../Utilitys/Vector2D.h"
#include <vector>

class PotatoPlant : public ObjectBase
{
private:
	int m_leavesnekkoImages[3]; //—t‚Á‚Ï‚Æª‚Á‚±‚Ì‰æ‘œ
	int m_rank;

public:
	PotatoPlant();
	~PotatoPlant();

public:

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// I—¹ˆ—
	/// </summary>
	void Finalize() override;

	void CreationPotato();

	void DecideSpawnPosition();

	void SpawnPotatoByType(Vector2D position);
};