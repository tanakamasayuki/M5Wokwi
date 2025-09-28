# 変更履歴

## [Unreleased]
- プロジェクトの初期ドキュメント（`AGENTS.md`、`README.md`、`CHANGELOG.md`）を整備。
- Arduino ライブラリ標準構成（`src/`, `examples/`, `library.properties`）を作成。
- `M5UnifiedW` スタブ実装と `examples/Button/Button.ino` を追加し、M5Unified の Button スケッチ互換をビルド検証可能に。
- M5GFX を利用した ILI9341 (320×240) ディスプレイ初期化処理を `M5.Display` に統合。
- M5UnifiedW API 表面の初期実装。
- デフォルトの M5Stack Core 用ディスプレイとボタンを定義した Wokwi diagram テンプレート。
- 基本的な描画処理とボタンポーリングを紹介するサンプルスケッチ。
