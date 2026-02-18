#pragma once
#include "../Utilitys/Singleton.h"
#include "ObjectBase.h"

#include <vector>

class ObjectManager : public Singleton<ObjectManager>
{
private:

	// ゲーム内で有効なオブジェクト一覧
	std::vector<ObjectBase*> m_objects;
	// 次のフレームで生成予定のオブジェクト一覧
	std::vector<ObjectBase*> m_pendingCreates;
	// 次のフレームで破棄予定のオブジェクト一覧
	std::vector<ObjectBase*> m_pendingDestroys;

public:
	ObjectManager();
	~ObjectManager();

public:

	/// <summary>
	/// 生成待ちオブジェクトをm_objectsに追加する
	/// </summary>
	void ProcessPendingCreates();

	/// <summary>
	/// 破棄待ちオブジェクトをm_objectsから削除する
	/// </summary>
	void ProcessPendingDestroys();

public:

	/// <summary>
	/// ゲーム内で有効なオブジェクト一覧を取得する
	/// </summary>
	/// <returns>m_objects</returns>
	const std::vector<ObjectBase*>& GetObjects() const;

	/// <summary>
	/// 全てのオブジェクトを削除する
	/// </summary>
	void DestroyAllObjects();

public:

	/// <summary>
	/// オブジェクトの生成を予約する
	/// </summary>
	/// <typeparam name="T">ObjectBaseを継承したクラス</typeparam>
	/// <param name="location">生成する座標</param>
	/// <returns>生成したオブジェクトのインスタンス</returns>
	template <class T>
	T* RequestSpawn(const Vector2D& location)
	{
		// 生成するオブジェクトクラスを動的確保
		T* instance = new T();

		// ObjectBaseを継承しているか確認
		ObjectBase* object = dynamic_cast<ObjectBase*>(instance);

		// エラーチェック
		if (object == nullptr)
		{
			delete instance;
			throw std::string("オブジェクトが生成できませんでした。");
		}

		// オブジェクトの初期化
		object->Initialize();

		// 位置情報設定
		object->SetLocation(location);

		// 生成予約を行う
		m_pendingCreates.push_back(object);

		return instance;
	}


	/// <summary>
	/// オブジェクトの破棄を予約する
	/// </summary>
	/// <param name="target">破棄するオブジェクト</param>
	void DestroyObject(ObjectBase* target)
	{
		// ヌルポチェック
		if (target == nullptr)
		{
			return;
		}

		// 既に予約されていれば追加しない
		for (ObjectBase* object : m_pendingDestroys)
		{
			if (object == target)
			{
				return;
			}
		}

		// 破棄予約を行う
		m_pendingDestroys.push_back(target);
	}
};

