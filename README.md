# iot-stand-test
## 基板のバージョンについて
このリポジトリには以下に示すように、基板実装されている部品の違いにより4つのバージョンの基板の動作試験用のコードが含まれる。
- 旧
    - 単数制御基板
    - 複数制御基板
- 新
    - 単数制御基板
    - 複数制御基板

単数基板のテストコードはSingleControl、複数基板のコードはMultipleControlという名前で新/旧それぞれのディレクトリ(NewBoard/OldBoard)に入っている。

## 動作試験の方法
### 用意するもの
- 部品実装済みの基板
- Raspberry Pi (実際の現場ではRaspberry Pi 3B+が使用されているが、ここでは基板が動くことを確認するのが目的のため、Raspberry Piのバージョンは問わないものとする。)
- 動作試験用リレー基板 (動作することが確認できているものを用意すること。)
- 5VのACアダプター (3A以上の電流を流せるものを推奨)
- テスタ (あるとよい)

### 動作試験手順
Raspberry PiのGUI環境を用いており、wiringPi、pigpioの各ライブラリがインストールされていることを前提とする。SSHやVNCを用いる場合は各自で工夫してほしい。  
また、環境構築は各自の好みがあると思うので、ここでは言及しない。
1. Raspberry PiのGPIOに基板のコネクタを刺す。(このとき、DCジャックがRaspberry PiのMicroUSBまたはType-C端子の真上に来るような向きにすること。)
1. (複数基板のみ)Hat基板と拡張基板を4極のリボンケーブルで接続する
1. Raspberry Piとモニターを接続し、電源を入れ、ログインする。
1. 対応する基板のディレクトリに移動する。
1. これより先、言語によって手順が変わる。動作は同じなのでC++とPython3のどちらか好きな方を選んでもらって構わない。
    <dl>
    <dt>5.1 Pythonを使用する場合</dt>
    <dd>ターミナルに `python3 test.py` で実行し、動作を見守る。</dd>
    <dt>5.2 C++を使用する場合</dt>
    <dd>ターミナルに `g++ test.cpp -o test.out -lwiringPi` と入力し、コンパイルが通ったら、`./test.out` で実行し、動作を見守る。</dd>
    </dl>
1. 基板がちゃんと動作することが確認できたら、SlackのProductionチャンネルかStandチャンネルで報告。
### 注意事項
- 金属の上でやらないこと。やらざるを得ない場合はプラスチックなどの不導体を基板との間に敷くか、スペーサー等を用いて接触しないようにすること。
- 基板が想定通りの動作をしない等の不具合が発生した場合は原因を特定し、修正すること。原因の特定ができない・修正不能の場合はすぐに報告。