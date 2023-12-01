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

For those who are not familiar with the Rust language environment, we have prepared a [pre-compiled binary for Windows](https://img.atcoder.jp/ahc025/tNvZmDfV_windows.zip).
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


The following options are available.

- `--dir=in2` Change the destination of the input files to the specified one instead of `in`.
- `--N=30` Fix the $N$ value of the generated inputs to the specified one.
- `--D=2` Fix the $D$ value of the generated inputs to the specified one.
- `--Q=100` Fix the $Q$ value of the generated inputs to the specified one.

## Local Tester
Let `in.txt` be an input file, `out.txt` be a file to which output of your program will be written, and `cmd` be a command to run your program.
You can test your program by executing the following command.
```
cargo run -r --bin tester cmd < in.txt > out.txt
```
The above command outputs the score to standard error.
You can specify arguments to your program by 
```
cargo run -r --bin tester cmd arg1 arg2 ... < in.txt > out.txt
```

If you use the precompiled binary for Windows, replace `cargo run -r --bin tester` with `./tester.exe`.
You can visualize the contents of the output file by pasting it into the [visualizer](https://img.atcoder.jp/ahc025/tNvZmDfV.html?lang=en).

### Examples
When executing a binary `a.out` which has been compiled in C++, etc. 
```
cargo run -r --bin tester ./a.out < in.txt > out.txt
```

When executing a program `main.py` using python3.
```
cargo run -r --bin tester python3 main.py < in.txt > out.txt
```

### When using Powershell on Windows
Because you cannot use `<` in the above examples, please execute as follows.
```
cat in.txt | cargo run -r --bin tester cmd > out.txt
```

For some execution commands, you may need to specify the full path, as in the following example.
```
cat in.txt | cargo run -r --bin tester C:\Users\myname\AppData\Local\Microsoft\WindowsApps\python3.exe main.py > out.txt
```
You can check the full path of a command by executing `gcm python3`.

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

You can also use a [web visualizer](https://img.atcoder.jp/ahc025/tNvZmDfV.html?lang=en) which is more rich in features.


# 使い方

## 実行環境
Rust言語のコンパイル環境が必要です。
https://www.rust-lang.org/ja を参考に各自インストールして下さい。
コンパイルエラーになった場合、コンパイラのバージョンが古い可能性があります。
以下のコマンド実行することで最新のコンパイラに更新が可能です。
```
rustup update
```

Rust言語の環境構築が面倒な方向けに、[Windows用のコンパイル済みバイナリ](https://img.atcoder.jp/ahc025/tNvZmDfV_windows.zip)も用意してあります。
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

以下のオプションが使用可能です

- `--dir=in2` 入力ファイルの出力先を `in` ではなく、指定されたものに変更
- `--N=30` 生成される入力の $N$ の値を指定されたものに固定
- `--D=2` 生成される入力の $D$ の値を指定されたものに固定
- `--Q=100` 生成される入力の $Q$ の値を指定されたものに固定

## ローカルテスタ
入力ファイル名を`in.txt`、出力結果を書き出す先のファイル名を`out.txt`、あなたのプログラムの実行コマンドを`cmd`としたとき、以下のコマンドを実行します。

```
cargo run -r --bin tester cmd < in.txt > out.txt
```
実行が終わると、スコアが標準エラーに出力されます。
引数が必要な場合には
```
cargo run -r --bin tester cmd arg1 arg2 ... < in.txt > out.txt
```
のようにします。

Windows用のコンパイル済バイナリを使用する場合は `cargo run -r --bin tester` の部分を `./tester.exe` に置き換えて下さい。
出力された`out.txt`の中身を[ビジュアライザ](https://img.atcoder.jp/ahc025/tNvZmDfV.html?lang=ja)に貼り付けると、ビジュアライズが可能です。

### 例
C++などでコンパイル済みの `a.out` というバイナリを実行する場合
```
cargo run -r --bin tester ./a.out < in.txt > out.txt
```

python3 で `main.py` というプログラムを実行する場合
```
cargo run -r --bin tester python3 main.py < in.txt > out.txt
```

### Windows で Powershell を使用する場合
上記の `<` が使えないため、以下のように実行して下さい。
```
cat in.txt | cargo run -r --bin tester cmd > out.txt
```

実行コマンドによっては以下の例のようにフルパスで指定する必要がある場合があります。
```
cat in.txt | cargo run -r --bin tester C:\Users\myname\AppData\Local\Microsoft\WindowsApps\python3.exe main.py > out.txt
```
コマンドのフルパスは `gcm python3` というコマンドを実行することで確認出来ます。

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

より機能が豊富な[ウェブ版のビジュアライザ](https://img.atcoder.jp/ahc025/tNvZmDfV.html?lang=ja)も利用可能です。
