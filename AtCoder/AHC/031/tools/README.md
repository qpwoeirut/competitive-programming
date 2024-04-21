- [Usage](#usage)
  - [Requirements](#requirements)
  - [Input Generation](#input-generation)
  - [Visualization](#visualization)
- [使い方](#%E4%BD%BF%E3%81%84%E6%96%B9)
  - [実行環境](#%E5%AE%9F%E8%A1%8C%E7%92%B0%E5%A2%83)
  - [入力生成](#%E5%85%A5%E5%8A%9B%E7%94%9F%E6%88%90)
  - [ビジュアライザ](#%E3%83%93%E3%82%B8%E3%83%A5%E3%82%A2%E3%83%A9%E3%82%A4%E3%82%B6)

# Usage

## Requirements
Please install a compiler for Rust language (see https://www.rust-lang.org).
If a compile error occurs, the compiler version may be old.
You can update to the latest compiler by executing the following command.
```
rustup update
```

For those who are not familiar with the Rust language environment, we have prepared a [pre-compiled binary for Windows](https://img.atcoder.jp/ahc031/PJcas1sL_windows.zip).
The following examples assume that you will be working in the directory where this README is located.

## Input Generation
The `in` directory contains pre-generated input files for seed=0-99.
If you want more inputs, prepare `seeds.txt` which contains a list of random seeds (unsigned 64bit integers) and execute the following command.
```
cargo run -r --bin gen seeds.txt
```
This will output input files into `in` directory.
When using the precompiled binary for Windows, execute the following command.
```
./gen.exe seeds.txt
```
If you use the command prompt instead of WSL, use `gen.exe` instead of `./gen.exe`.


The following options are available.

- `--dir=in2` Change the destination of the input files to the specified one instead of `in`.
- `--D=10` Fix the $D$ value of the generated inputs to the specified one.
- `--N=10` Fix the $N$ value of the generated inputs to the specified one.
- `--E=10000` Fix the $E$ value of the generated inputs to the specified one.


## Visualization
Let `in.txt` be an input file and `out.txt` be an output file.
You can visualize the output by executing the following command.
```
cargo run -r --bin vis in.txt out.txt
```
When using the precompiled binary for Windows,
```
./vis.exe in.txt out.txt
```

The above command writes a visualization result to `vis.html`.
It also outputs the score to standard output.

You can also use a [web visualizer](https://img.atcoder.jp/ahc031/PJcas1sL.html?lang=en) which is more rich in features.

# 使い方

## 実行環境
Rust言語のコンパイル環境が必要です。
https://www.rust-lang.org/ja を参考に各自インストールして下さい。
コンパイルエラーになった場合、コンパイラのバージョンが古い可能性があります。
以下のコマンド実行することで最新のコンパイラに更新が可能です。
```
rustup update
```

Rust言語の環境構築が面倒な方向けに、[Windows用のコンパイル済みバイナリ](https://img.atcoder.jp/ahc031/PJcas1sL_windows.zip)も用意してあります。
以下の実行例では、このREADMEが置かれているディレクトリに移動して作業することを想定しています。

## 入力生成
`in` ディレクトリに予め生成された seed=0~99 に対する入力ファイルが置かれています。
より多くの入力が欲しい場合は、`seeds.txt` に欲しい入力ファイルの数だけ乱数seed値(符号なし64bit整数値)を記入し、以下のコマンドを実行します。
```
cargo run -r --bin gen seeds.txt
```
生成された入力ファイルは `in` ディレクトリに出力されます。
Windows用のコンパイル済バイナリを使用する場合は以下のようにします。
```
./gen.exe seeds.txt
```
WSLではなくコマンドプロンプトを使用する場合は `./gen.exe` ではなく `gen.exe` として下さい。

以下のオプションが使用可能です

- `--dir=in2` 入力ファイルの出力先を `in` ではなく、指定されたものに変更
- `--D=10` 生成される入力の $D$ の値を指定されたものに固定
- `--N=10` 生成される入力の $N$ の値を指定されたものに固定
- `--E=10000` 生成される入力の $E$ の値を指定されたものに固定

## ビジュアライザ
入力ファイル名を`in.txt`、出力ファイル名を`out.txt`としたとき、以下のコマンドを実行します。
```
cargo run -r --bin vis in.txt out.txt
```
Windows用のコンパイル済バイナリを使用する場合は以下のようにします。
```
./vis.exe in.txt out.txt
```

出力のビジュアライズ結果は `vis.html` というファイルに書き出されます。
標準出力にはスコアを出力します。

より機能が豊富な[ウェブ版のビジュアライザ](https://img.atcoder.jp/ahc031/PJcas1sL.html?lang=ja)も利用可能です。
