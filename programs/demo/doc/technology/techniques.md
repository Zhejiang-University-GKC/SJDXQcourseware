## 开发语言

主要使用C++进行开发

## 项目管理

|      名称      |         工具         |
|:-------------:|:--------------------:|
|    版本控制    |      Git,fossil      |
|    持续集成    |   Jenkins,Appveyor   |
|    构建工具    |     CMake,QMake     |
|    规范检查    |       cpplint       |
|    静态分析    |       cppcheck      |
|   复杂度分析   |       cppncss       |
| 单元测试覆盖率 | OpenCppCoverage,gcov |


## 具体实现

1. 项目整体采用MVVM的模式
1. 绘图部分运用Windows DC
1. 公交的路线规划采用优化的Dijkstra算法，对抽象的公交站点地图运用Dijkstra算法，并根据总站点数、换乘次数等对应不同的公交方案