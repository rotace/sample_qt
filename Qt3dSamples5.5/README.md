# Qt3dSamples5.5
Qt3Dサンプル(Qt5.5)


## 動作環境

* Ubuntu16.04 32bit
* Qt5.5
* Qt3D


## 開発環境

以下の手順による。

``` bash
$ sudo apt install qt5-default
$ sudo apt install qtcreator
$ sudo apt install qtdeclarative5-dev
$ sudo apt install qt3d5-dev
$ sudo apt install qml-module-qt3d
$ sudo apt install qml-module-qtqml*
$ sudo apt install qml-module-qtquick*
```

## フォルダ構成

| フォルダ | 内容 |
| --- | --- |
| qt3d-gallery | Qt3Dの各Mesh/各Material/各Transform のビューワ |
| simple-cpp | C++ベースのQt3Dサンプル |
| simple-qml | QMLベースのQt3Dサンプル |
| simple-hybrid | C++とQMLで双方向に通信するQt3Dサンプル |
| simple-viewport | Viewportのサンプル |
| simple-scene3d | Scene3Dのサンプル |


### simple-cpp
以下のサイトを参考
* [Qt3D: C++Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-cpp-example-example.html)
* [Qt3D: Simple C++ Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-simple-cpp-example.html)
* [Github Qt3D](https://github.com/qt/qt3d/tree/5.5/examples/qt3d/common)

### simple-qml
以下のサイトを参考
* [Qt3D: Simple QML Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-simple-qml-example.html)
* [Github Qt3D](https://github.com/qt/qt3d/tree/5.5/examples/qt3d/common)

### simple-hybrid
以下のサイトを参考
* [Qt3D: C++Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-cpp-example-example.html)
* [Qt3D: Simple C++ Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-simple-cpp-example.html)
* [Qt3D: Simple QML Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-simple-qml-example.html)
* [Github Qt3D](https://github.com/qt/qt3d/tree/5.5/examples/qt3d/common)
* [QMLで記述したウィンドウをC++から制御する](https://theolizer.com/cpp-school4/cpp-school4-4/)

### simple-viewport
以下のサイトを参考
* [Qt3D: Multi Viewport QML Example](https://doc.qt.io/archives/qt-5.5/qt3drenderer-multiviewport-example.html)