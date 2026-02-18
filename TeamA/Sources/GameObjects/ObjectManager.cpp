#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::ProcessPendingCreates()
{
	// 生成予約があれば処理をする
	if (!m_pendingCreates.empty())
	{
		// 生成予約されたオブジェクトを順に追加する
		for (ObjectBase* object : m_pendingCreates)
		{
			// 追加するオブジェクトのzレイヤーを取得
			int z_layer = object->GetZLayer();

			// 現在のオブジェクト一覧の先頭から走査
			std::vector<ObjectBase*>::iterator itr = m_objects.begin();

			// zレイヤー順を維持する挿入位置を探す
			for (; itr != m_objects.end(); itr++)
			{
				// 自分より大きいzレイヤーが見つかればそこに挿入
				if (z_layer < (*itr)->GetZLayer())
				{
					break;
				}
			}

			// 見つかった位置に挿入
			m_objects.insert(itr, object);
		}

		// 生成予約リストをクリア
		m_pendingCreates.clear();

	}
}

void ObjectManager::ProcessPendingDestroys()
{
	// 破棄予約があれば処理する
	if (!m_pendingDestroys.empty())
	{
		// 予約されたオブジェクトを順に削除する
		for (ObjectBase* object : m_pendingDestroys)
		{
			// 現在のオブジェクト一覧の先頭から走査
			std::vector<ObjectBase*>::iterator itr = m_objects.begin();

			// 破棄予約されたオブジェクトを探す
			for (; itr != m_objects.end(); itr++)
			{
				// 見つかったら、削除する
				if ((*itr) == object)
				{
					m_objects.erase(itr);
					object->Finalize();
					delete object;
					break;
				}
			}
		}
	}
}

const std::vector<ObjectBase*>& ObjectManager::GetObjects() const
{
	return m_objects;
}

void ObjectManager::DestroyAllObjects()
{
	// 全オブジェクトを削除する
	for (ObjectBase* object : m_objects)
	{
		object->Finalize();
		delete object;
	}

	// 配列をクリアする
	m_objects.clear();
	m_pendingCreates.clear();
	m_pendingDestroys.clear();
}

