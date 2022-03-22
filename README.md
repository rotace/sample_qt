# sample_qt
Qtのサンプルプログラム集


### フォルダ構成

| フォルダ | 内容 |
| --- | --- |
| EchoServer | マルチスレッドなTCP/UDP通信のサンプル |
| TargetSimulator | 目標模擬ライブラリ |



### EchoServer
以下のサイトを参考に、QTcpServer、QTcpSocket、QUdpSocketを使ってマルチスレッドサーバを作成
* [Qtのマルチスレッド機構](https://qiita.com/hermit4/items/f4f03a4533e8c332241b)
* [QThreadを使ってみよう](https://qiita.com/hermit4/items/b1eaf6132fb06a30091f)

### TargetSimulator
以下のサイトを参考に、QAbstractItemModel、QAbstractItemView、Qt3Dを使って目標模擬ライブラリを作成
* [QtのMVC系アーキテクチャ モデル/ビューアーキテクチャ 初めの１歩](https://qiita.com/argama147/items/79db67c058560909ec1c)
* [Qt3D Module](https://doc.qt.io/archives/qt-5.5/qt3d-index.html)