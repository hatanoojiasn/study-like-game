# 開発ガイド（WSL2 + Ubuntu 想定）

## 1. 目的
このガイドは、Questを快適に進めるための最短セットアップを提供します。
詳細な世界観と進行順は `docs/roadmap.md`、各ミッション仕様は `docs/quests/` を参照してください。

## 2. 依存関係の導入
### 2.1 apt で導入（推奨）
```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build pkg-config libraylib-dev
```

### 2.2 aptで入らない場合（raylib最小ビルド）
```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build pkg-config libgl1-mesa-dev libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev
git clone --depth 1 https://github.com/raysan5/raylib.git
cmake -S raylib -B raylib/build -G Ninja -DBUILD_EXAMPLES=OFF
cmake --build raylib/build
sudo cmake --install raylib/build
```

## 3. ビルドとテスト
### 3.1 GUI + テスト
```bash
cmake -S . -B build -G Ninja
cmake --build build
```

### 3.2 ヘッドレステスト（CI同等）
```bash
cmake -S . -B build-test -G Ninja -DBUILD_HOST_APP=OFF
cmake --build build-test
ctest --test-dir build-test --output-on-failure
```

## 4. 実行
```bash
./build/study_like_game
```

## 5. WSLg トラブルシュート
1. `echo $DISPLAY` と `echo $WAYLAND_DISPLAY` を確認。
2. Windows側で `wsl --shutdown` 実行後に再起動。
3. GUI不可環境では `-DBUILD_HOST_APP=OFF` でQuestを先行。

## 6. 学習メトリクスの見方
- **安定度**: FPS
- **ストレス**: dtジッタ（min/max差）
- **監視健全性**: テレメトリ周期誤差
- **思考負荷**: VM命令実行数（将来Quest）

## 7. 固定公開インタフェース方針
公開APIは `platform.h` / `game.h` / `engine.h` の最小セットで固定し、Quest進行中に増やしません。
機能追加は内部実装で吸収し、移植性と学習一貫性を守ります。
