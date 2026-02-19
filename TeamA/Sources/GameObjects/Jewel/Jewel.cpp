#include "Jewel.h"

#include <DxLib.h>

Jewel::Jewel()
{

}

Jewel::~Jewel()
{

}

void Jewel::Initialize()
{
	m_animeTime = 0.0f;
	m_animeCount = 0;
}

void Jewel::Update()
{
	m_animeTime += 0.01f;
	if (m_animeTime > 1.0f)
	{
		m_animeTime = 0.0f;
		m_animeCount += 1;
	}
}

void Jewel::Draw() const
{
	DrawCircle(m_location.x, m_location.y, 10, GetColor(255, 0, 0), TRUE);
}

void Jewel::Finalize()
{

}

void Jewel::OnHitCollision(ObjectBase& other)
{

}