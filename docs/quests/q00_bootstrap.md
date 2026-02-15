# Quest 00: ブートストラップ（起動確認）

## 目的（Objective）
- 学習ラボの土台をローカルで再現し、GUI ループとヘッドレステストの両方が動作する状態を作る。

## ルール（Rules）
- 公開 API は `platform.h` / `game.h` / `engine.h` の既定範囲から増やさない。
- 1フレームごとの動的メモリ確保を禁止。
- C99 準拠で実装する。

## 制約（Constraints）
- WSL2 Ubuntu 22.04+ を優先。
- raylib が導入できない環境では、まずヘッドレステストを通す。

## 受け入れ条件（Definition of Done）
- `study_like_game` が起動し、以下を満たす:
  - 矩形がキー入力で移動
  - HUD に `FPS`, `dt(ms)`, `Player position` が表示
  - 1秒ごとに stdout へ timing 統計（avg/min/max dt）を出力
  - 5分間クラッシュせず動作
- `test_game_determinism` がヘッドレスで成功する。

## 実装ヒント
- 初期化関数を公開 API に追加せず、platform 側で遅延初期化を使う。
- `dt` の異常値（停止復帰直後の巨大値）はクランプする。
- HUD 文字列は固定長バッファで構築し、毎フレームの heap 確保を避ける。

## テスト計画（最低限）
1. GUI 起動テスト: 手動で 60 秒操作
2. 5分連続動作: 放置確認
3. ヘッドレス決定性テスト: 固定入力列で 2 回実行し同一結果を確認
4. CI で `ctest` を実行

## トラブルシュート（WSLg 含む）
- ウィンドウが出ない: `echo $DISPLAY`, `echo $WAYLAND_DISPLAY` を確認。
- `raylib not found`: `libraylib-dev` 導入または raylib ソースビルド。
- 入力が効かない: ウィンドウにフォーカスがあるか確認。
