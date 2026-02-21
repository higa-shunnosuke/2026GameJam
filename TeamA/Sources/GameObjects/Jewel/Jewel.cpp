#include "Jewel.h"

#include "../ObjectManager.h"
#include "../../System/ResourceManager.h"
#include <DxLib.h>

Jewel::Jewel()
	:m_animeTime()
	, m_animeCount()
	, m_animeTime_e()
	, m_animeCount_e()
	, m_emerald_image{}
, m_effect_image{}
{

}

Jewel::~Jewel()
{

}

void Jewel::Initialize()
{
	ResourceManager& rm = ResourceManager::GetInstance();
	m_emerald_image[0] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald1.PNG")[0];
	m_emerald_image[1] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald2.PNG")[0];
	m_emerald_image[2] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald3.PNG")[0];
	m_emerald_image[3] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald4.PNG")[0];

	m_effect_image[0] = rm.GetImageResource("Assets/Sprites/Jewel/effect/キラキラ１.PNG")[0];
	m_effect_image[1] = rm.GetImageResource("Assets/Sprites/Jewel/effect/キラキラ２.PNG")[0];
	m_effect_image[2] = rm.GetImageResource("Assets/Sprites/Jewel/effect/キラキラ３.PNG")[0];

	// zlayerの設定
	m_zLayer = 10;

	// 当たり判定の設定
	m_collision.m_type = e_ObjectType::jewel;
	m_collision.m_radius = 10;

	// アニメ変数の初期化
	m_animeTime = 0.0f;
	m_animeCount = 0;
	m_animeTime_e = 0.0f;
	m_animeCount_e = 0;
}

void Jewel::Update(float delta)
{
	m_animeTime += delta;
	if (m_animeTime > 0.2f)
	{
		m_animeTime = 0.0f;
		m_animeCount = (m_animeCount + 1) % 4;
	}

	m_animeTime_e += delta;
	if (m_animeTime_e > 0.13f)
	{
		m_animeTime_e = 0.0f;
		m_animeCount_e = (m_animeCount_e + 1) % 3;

	}
}

void Jewel::Draw() const
{
	// 宝石
	DrawRotaGraphF(m_location.x, m_location.y, 0.04f, 0.0f, m_emerald_image[m_animeCount], TRUE);
	// エフェクト
	DrawRotaGraphF(m_location.x, m_location.y, 0.04f, 0.0f, m_effect_image[m_animeCount_e], TRUE);

#if _DEBUG
	// 当たり判定を可視化
	DrawCircle(m_location.x, m_location.y,m_collision.m_radius, GetColor(255, 0, 0), FALSE);
#endif
}

void Jewel::Finalize()
{

}

void Jewel::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);
}