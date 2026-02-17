# プロジェクト名（仮）

## 概要
本プロジェクトは、C++ を用いて制作する **2Dゲーム**です。  
Visual Studio 2022 を使用し、チーム制作での開発を前提としています。

---

## 開発環境
- OS：Windows 10 / 11
- IDE：Visual Studio 2022
- 言語：C++
- プロジェクト種別：2Dゲーム

---
## ビルド手順
1. リポジトリを clone
   ```bash
   git clone <リポジトリURL>

2. Visual Studio 2022 で .sln を開く
  
3. 構成を以下に設定  
    ・構成：Debug  
    ・プラットフォーム：x64

4. ビルド → ソリューションのビルド

---

フォルダ構成

ProjectRoot/  
├─ Source/          # ゲームロジック  
|  ├─ App/          # アプリケーション管理  
|  ├─ GameObjects/  # オブジェクト管理  
|  ├─ Scenes/       # シーン管理  
|  ├─ Systems/    　# 入力 & 読み込み管理  
|  ├─ Utilitys/       
├─ Assets/          # ゲームで使用する素材  
│  ├─ Common/  
│  ├─ Sprites/  
│  ├─ Textures/  
│  ├─ Audio/  
│  ├─ Fonts/  
│  └─ LocalTest/    # 個人用（Git管理外）  
├─ Resources/  
   └─ data/         # スコア・ランキング（Git管理外）  
