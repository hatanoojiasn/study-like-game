# 開発ガイド（WSL2 + Ubuntu 想定）

## 1. 前提
- 推奨環境: Windows + WSL2 Ubuntu 22.04 以上
- ビルドツール: `cmake`, `ninja-build`（または `make`）, `gcc`/`clang`
- GUI: `raylib`

## 2. 依存関係の導入

### 2.1 apt で導入（まずはこちら）
```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build pkg-config libraylib-dev
```

> 環境によっては `libraylib-dev` が存在しない場合があります。その場合は次節を利用してください。

### 2.2 raylib を最小構成でソースビルド
```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build pkg-config libgl1-mesa-dev libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev

git clone --depth 1 https://github.com/raysan5/raylib.git
cmake -S raylib -B raylib/build -G Ninja -DBUILD_EXAMPLES=OFF
cmake --build raylib/build
sudo cmake --install raylib/build
```

## 3. ビルド

### 3.1 GUIアプリ + テスト
```bash
cmake -S . -B build -G Ninja
cmake --build build
```

### 3.2 テストのみ（CI と同等）
```bash
cmake -S . -B build-test -G Ninja -DBUILD_HOST_APP=OFF
cmake --build build-test
ctest --test-dir build-test --output-on-failure
```

## 4. 実行
```bash
./build/study_like_game
```

期待される挙動:
- ウィンドウが開く
- WASD / 矢印キーで矩形プレイヤーが移動
- HUD に FPS / dt / 座標が表示される
- 標準出力に 1 秒ごとの `avg/min/max dt` が出る
- 5 分経過で正常終了

## 5. WSLg でウィンドウが出ない場合

1. `echo $DISPLAY` と `echo $WAYLAND_DISPLAY` を確認
   - どちらかが空なら、WSLg が有効な WSL2 か確認
2. Windows 側を再起動し、WSL を再起動
```bash
wsl --shutdown
```
3. Ubuntu 側で X11/Wayland 関連ライブラリが不足していないか確認
4. リモート環境や Headless VM では GUI 表示不可の可能性があるため、`-DBUILD_HOST_APP=OFF` でテスト中心に進行

## 6. 固定公開インタフェース方針
このリポジトリは API 成長を抑制します。
- `platform/platform.h`: 入力状態 + 描画/時間関数のみ
- `game/game.h`: `init/step/draw`
- `engine/engine.h`: `init/step/draw`

新機能は公開 API を増やさず、内部実装だけで拡張してください。
