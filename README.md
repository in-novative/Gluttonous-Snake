开发平台: `Windows 10`
<br>开发工具: `Qt Creator 13.0.2(Community)`

项目管理由`Qt`完成，简要概述封装:
<br>`interface.*`实现绘制交互界面, 包括开始界面、游戏界面、排行榜界面、帮助界面
<br>`maze.*`实现地图的初始化&管理, 在地图初始化时加载图片以减少延迟
<br>`snack.*`实现蛇的初始化&管理, 由`move`函数控制蛇的运动(使用的是4399经典键位)
<br>`game.*`通过调用`maze.*`和`snack.*`实现游戏功能, 包括单人和双人(暂无)模式
<br>`QtHeader.h`包括了所使用的大部分头文件、`define`、`extern`等等
<br>`star.*`蛇可以吃`star`增加长度和得分, `star`在一定时间内未被吃掉则会变成墙, 刷新和存在时间随机

蛇（包括头、身、尾）使用`deque`结构进行管理，每次移动时根据移动方向从`front`执行压入，并弹出`back`元素；根据头部的位置执行不同的操作，并更新蛇的位置
<br>读取移动方向，在`mainWindow`中使用`QString keyText`进行记录，重写`keyPressEvent`函数，将键盘操作`append`到`keyText`末尾；间隔一定时间从`keyText`读取第一个有效字符（无效字符包括`wasd`以外的字符、与蛇头方向相反的移动字符），若为空则保持之前的移动方向
<br>贴图，使用`QVector<QPair<QPixmap, QRect>> images`管理图片，`first`为图片资源，`second`为贴图位置、尺寸信息，每次调用`paintImage`时向`images`末尾`append`图片信息，并重写`paintEvent`函数在`update`后执行贴图操作；同时在加载游戏界面时从image文件夹读取图片，并在后续贴图时进行复用，减小延迟
<br>`star`的随机刷新和消失，交替使用两个`timer`，分别执行刷新和消失功能；使用`QRandomGenerator`生成随机的操作时间间隔；`star`的倒计时闪烁功能，通过对指定位置交替画原图和`BLANK`图片来实现
<br>`crash`功能（在撞到墙体或者蛇身时触发，弹出`crash`窗口，可选择退回到游戏或者是初始界面），通过`interface->game->maze&snack&star`（`->`代表类的包含关系）对资源进行管理，`crash`后执行`delete game`并触发析构函数释放资源，同时保留`interface`并再次调用相应界面