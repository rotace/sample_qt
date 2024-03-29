# sample_qt
Qtのサンプルプログラム集


## フォルダ構成

| フォルダ | 内容 | Qt Version |
| --- | --- | --- |
| EchoServer | マルチスレッドなTCP/UDP通信のサンプル | 5.15 |
| SocketTester | ソケットテストプログラム | 5.2-5.15 |
| Qt3dSamples5.5 | Qt3Dサンプル | 5.5 |
| TargetSimulator5.5 | 目標模擬ライブラリ | 5.5 |
| TreeViewer | ツリー表示のサンプル | 5.15 |

## EchoServer
以下のサイトを参考に、QTcpServer、QTcpSocket、QUdpSocketを使ってマルチスレッドサーバを作成
* [Qtのマルチスレッド機構](https://qiita.com/hermit4/items/f4f03a4533e8c332241b)
* [QThreadを使ってみよう](https://qiita.com/hermit4/items/b1eaf6132fb06a30091f)

## SocketTester

以下のサイトを参考に、QUdpSocketを使ってマルチキャストクライアントを作成
* [QUdpSocket](https://doc.qt.io/qt-5/qudpsocket.html)

## Qt3DSamples5.5
以下のサイトを参考に、Qt3Dのサンプルプログラムを作成
* [Qt3D: C++Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-cpp-example-example.html)
* [Qt3D: Simple C++ Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-simple-cpp-example.html)
* [Qt3D: Simple QML Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-simple-qml-example.html)
* [Github Qt3D](https://github.com/qt/qt3d/tree/5.5/examples/qt3d/common)
* [QMLで記述したウィンドウをC++から制御する](https://theolizer.com/cpp-school4/cpp-school4-4/)

## TargetSimulator5.5
以下のサイトを参考に、QAbstractItemModel、QAbstractItemView、Qt3Dを使って目標模擬ライブラリを作成
* [QtのMVC系アーキテクチャ モデル/ビューアーキテクチャ 初めの１歩](https://qiita.com/argama147/items/79db67c058560909ec1c)
* [Qt3D Module](https://doc.qt.io/archives/qt-5.5/qt3d-index.html)

## TreeViewer
以下のサイトを参考に、QtSql、QTreeWidgetを使ってツリー表示のサンプルプログラムを作成
* [QTreeWidget](https://doc.qt.io/qt-5/qtreewidget.html)
* [再帰SQL -図解-](https://qiita.com/Shoyu_N/items/f1786f99545fa5053b75)
