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
   https://github.com/higa-shunnosuke/2026GameJam.git

2. Visual Studio 2022 で .sln を開く
  
3. 構成を以下に設定  
    ・構成：Debug  
    ・プラットフォーム：x64

4. ビルド → ソリューションのビルド

---

## フォルダ構成

    ProjectRoot/  
    ├─ Source/  
    │  ├─ App/  
    │  ├─ GameObjects/  
    │  ├─ Scenes/  
    │  ├─ Systems/  
    │  ├─ Utilitys/         
    ├─ Assets/  
    │  ├─ Common/  
    │  ├─ Sprites/ ----- キャラクター・UI  
    │  ├─ Textures/ ---- 背景  
    │  ├─ Audio/ ------- BGM・SE  
    │  ├─ Fonts/  
    │  └─ LocalTest/  
    └─  Resources/  
       └─ data/  

---

## 命名規則（Naming Convention）

### 基本方針（全体ルール） 

英語のみ（ローマ字禁止）  
意味が分かる名前を優先  
略語は控える（HPなどは可）  
1単語で済むなら1単語  
スネークケースとキャメルケースを使い分ける  

### 変数名（ローカル変数）  

lowerCamelCase  
 ```bash
int playerHp;  
float moveSpeed;  
bool isAlive;
```
❌ NG
 ```bash
int PlayerHP;  
int a;  
int hp1;  
```

### メンバ変数（クラス内）  

lowerCamelCase + m_ プレフィックス  
 ```bash
class Player {  
    int m_hp;  
    float m_moveSpeed;  
    bool m_isAlive;  
};  
```
👉 「これはメンバだ」と一目で分かる  

### 定数（const / constexpr）  

UPPER_SNAKE_CASE
 ```bash
constexpr int MAX_PLAYER_HP = 100;  
const float GRAVITY = 9.8f;  
```

### 関数名  
 ```bash
UpperCamelCase（パスカルケース）  
void Update();  
void Draw();  
void TakeDamage(int damage);  
```

### クラス名  
UpperCamelCase  
 ```bash
class Player;  
class EnemyManager;  
class GetLocation;  
```

### enum
 ```bash
enum class EnemyType {  
    normal,  
    boss,  
    fly  
};  
```
