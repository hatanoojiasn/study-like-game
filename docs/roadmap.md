# ロードマップ: 壊れた世界を修理して最終章へ

## 最終到達点
**同じゲームロジックを Host 実装と自作OS想定実装の両方で動かし、挙動差を測定して修復できる状態**へ到達する。

## Tier構成とアンロック
- **Tier0 観測基盤**（Q00〜Q02）
  - 解放: ログ観測、再現、時間安定化
- **Tier1 操作感修復**（Q03〜Q05）
  - 解放: 入力精度、移動手触り、HUD可観測性
- **Tier2 協調並行**（Q06〜Q08）
  - 解放: 周期監視、タスク分離、重処理分割
- **Tier3 物理整備**（Q09〜Q12）
  - 解放: 衝突検知、押し戻し、境界応答、決定性監査
- **Tier4 言語/VM**（Q13〜Q17）
  - 解放: 字句・構文・バイトコード・VM実行・敵AI制御
- **Tier5 数学/物理強化**（Q18〜Q19）
  - 解放: 数値積分比較、保存量監視
- **Tier6 OS移植導線**（Q20〜Q21）
  - 解放: platform差し替え訓練、OS起動ルート

## Quest一覧（難易度・時間・アンロック）
| Quest | 主題 | 難易度 | 目安時間 | 解放能力（アンロック） | まず触るファイル |
|---|---|---|---|---|---|
| Q00 | 起動と観測 | C | 30分〜1時間 | 観測コンソール | `src/main.c` |
| Q01 | リプレイ | C | 30分〜1時間 | リプレイ機能 | `tests/test_game_determinism.c` |
| Q02 | dt安定化 | C | 1〜2時間 | 時間安定化バフ | `src/main.c` |
| Q03 | 入力バッファ | B | 1〜2時間 | 操作精度アップ | `src/platform/host_raylib/platform_host.c` |
| Q04 | 操作感調律 | B | 1〜2時間 | チューニング機能 | `src/game/game.c` |
| Q05 | HUD拡張 | C | 30分〜1時間 | 可観測性強化 | `src/main.c` |
| Q06 | 250ms監視 | B | 1〜2時間 | 監視ネットワーク | `src/main.c` |
| Q07 | 協調スケジューラ | B | 半日 | タスク分離スロット | `src/engine/engine.c` |
| Q08 | ジョブ分割 | B | 半日 | フレーム安定化II | `src/engine/engine.c` |
| Q09 | AABB検知 | B | 1〜2時間 | 衝突検知 | `src/game/game.c` |
| Q10 | 押し戻し | B | 1〜2時間 | 空間整合性 | `src/game/game.c` |
| Q11 | 境界応答 | B | 1〜2時間 | 境界ルール | `src/game/game.c` |
| Q12 | 決定性監査 | A | 半日 | 再現性保証バッジ | `tests/test_game_determinism.c` |
| Q13 | 字句解析 | B | 半日 | 言語層Lv1 | `src/engine/engine.c` |
| Q14 | 構文解析 | A | 半日〜1日 | 言語層Lv2 | `src/engine/engine.c` |
| Q15 | バイトコード化 | A | 半日〜1日 | 言語層Lv3 | `src/engine/engine.c` |
| Q16 | VM実行核 | A | 1日 | AI稼働 | `src/engine/engine.c` |
| Q17 | AI適用 | A | 1日 | 敵AI編集 | `src/game/game.c` |
| Q18 | 数値積分比較 | B | 半日 | 物理解析モード | `src/game/game.c` |
| Q19 | 保存量監視 | B | 半日 | 物理健全性ゲージ | `src/game/game.c` |
| Q20 | platform差し替え | A | 1日 | 移植準備完了 | `src/platform/host_raylib/platform_host.c` |
| Q21 | OS起動導線 | S | 数日 | 最終章アクセス | `docs/roadmap.md` |

## 学べる概念マップ
- **OS**: Q20, Q21
- **エンジン**: Q00〜Q12
- **コンパイラ/VM**: Q13〜Q17
- **数学/物理**: Q09〜Q12, Q18, Q19

## 遊び方の指針
- 1Questごとに「症状→介入→報酬」を記録して進捗ログを作る。
- C難易度で観測力を上げ、B/Aで設計判断、Sで統合力を試す。
- 行き詰まったら前Tierへ戻って可観測性を強化してから再挑戦する。
