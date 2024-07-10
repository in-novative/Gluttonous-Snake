开发平台: `Windows 10`
开发工具: `Qt Creator 13.0.2(Community)`

项目管理由`Qt`完成，简要概述封装:
`interface.*`实现绘制交互界面, 包括开始界面、游戏界面、排行榜界面、帮助界面(暂时)
`maze.*`实现地图的初始化&管理, 在地图初始化时加载图片以减少延迟
`snack.*`实现蛇的初始化&管理, 由`move`函数控制蛇的运动(使用的是4399经典键位)
`game.*`通过调用`maze.*`和`snack.*`实现游戏功能, 包括单人和双人(暂无)模式
`QtHeader.h`包括了所使用的大部分头文件、`define`、`extern`等等