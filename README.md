# Run instruction:

命令行程序仅支持文件输入，同时把输出打印到-o [file name]指定的文件中；

**具体使用的命令如下**：

| 参数                      | 参数意义                                           | 用法示例                                 |
| ------------------------- | -------------------------------------------------- | ---------------------------------------- |
| -i < path to input file>  | 带一个参数，表示输入文件的路径（绝对或者相对路径） | intersect.exe -i input.txt -o output.txt |
| -o < path to output file> | 带一个参数，表示输出文件的路径（绝对或者相对路径） | intersect.exe -i input.txt -o output.txt |

输入：

- 首行代表有多少个几何图形
- 支持直线（直线、射线、线段）和圆
  - 直线输入格式：L x1 y1 x2 y2
  - 射线输入格式：R x1 y1 x2 y2
  - 线段输入格式：S x1 y1 x2 y2
  - 圆输入格式：C x y r

输出：（输出到 -o 指定的文件中）

- 所有几何图形的交点数，行末没有换行符。



# UI使用说明

UI.exe位于项目主页的**UI/**文件夹内。

按钮使用方法如下

**1.文件导入**：选择文件并从文件导入几何对象的描述。

**2.添加**：在按钮左侧文本框内输入几何对象的描述后点击即可。

**3.删除**：在按钮左侧复选框内选择想要删除的几何对象后点击即可。

**4.绘制**：直接点击即可，会在按钮下方绘制现有几何对象及交点，在按钮右侧显示交点数目及查看交点坐标

****

### Appendix：

开发工具： VS2019 企业版 C/C++项目

直接打开sln后进行如下配置：

#### 配置

1. core项目**属性**中**C/C++** 的**预编译头**，选择**不使用**

2. core项目**属性**中**C/C++**的的**预处理器**，预处理器定义添加"**DLL_EXPORTS**"（很重要）

3. 命令行项目pair_wzb的项目**属性**的**链接器**，**输入**的附加依赖项添加"**core生成的.lib路径**"
4. 命令行项目pair_wzb的项目**属性**的**调试**，添加**命令行参数** -i < filename > -o < fielname >

以上配置后应该可以正常编译项目并且运行！

附：test项目与命令行项目类似，需要在**引用**中引用core项目，以及test项目也不适用**预编译头**

（这里的命令行操作本质上应该是使用的lib，如果真正的使用dll，应该是使用LoadLibrary库导入对应的函数）

*****

UI：**使用C#开发**

在vs中新建c#Windows 窗体应用项目，将UI文件夹下除UI.exe 和 core.dll文件之外的所有文件添加进项目，然后将core.dll复制至新建项目的bin/Debug/  目录下即可