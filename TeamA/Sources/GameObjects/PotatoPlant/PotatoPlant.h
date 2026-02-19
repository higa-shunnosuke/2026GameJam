#pragma once
#include "../ObjectBase.h"

#include "../../Utilitys/Vector2D.h"
#include <vector>

class PotatoPlant : public ObjectBase
{
private:
	int m_leavesImages[3]; //—t‚Á‚Ï‚Ì‰æ‘œ
	int m_nekkoImages[3]; //ª‚Á‚±‚Ì‰æ‘œ
	int m_rank;
	std::vector<Vector2D> m_potatolocation;

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

};