# test_bgl

Boost Graph Library (BGL) で有向グラフを作り、Graphviz 用の `graph.dot` を出力する最小サンプル

## ファイル構成

- `main.cpp`: BGL でグラフを作って `graph.dot` を出力
- `Makefile`: ビルドと画像化
- `CMakeLists.txt`: CMake ビルド
- `setup_ubuntu.sh`: Ubuntu 向け依存インストール
- `Dockerfile`: 依存入りコンテナ環境

## 依存関係

- C++17 対応コンパイラ（`g++` など）
- Boost（`libboost-graph-dev`）
- Graphviz（`dot` コマンド）
- `make` または `cmake`

## Ubuntu で依存を入れる

```bash
cd test_bgl
./setup_ubuntu.sh
```

## 使い方（Makefile）

```bash
cd test_bgl
make png
```

上記で次が生成されます。

- `graph.dot`
- `graph.png`

## 使い方（CMake）

```bash
cd test_bgl
cmake -S . -B build
cmake --build build
./build/test_bgl
dot -Tpng graph.dot -o graph.png
```

## Docker で試す

```bash
cd test_bgl
docker build -t test-bgl .
docker run --rm -it -v "$PWD":/work -w /work test-bgl make png
```
