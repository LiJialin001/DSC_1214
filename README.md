# DSC_1214
Digital Signal Generator by MCU &amp; LPF

## 规范

### 命名注释

- 变量采用[匈牙利命名法](https://zh.m.wikipedia.org/zh-hans/匈牙利命名法)
- 引脚号必须使用label代替

### 平台

暂时采用 ESP-IDF

### 文件树

### Git规范

#### 不得push编译相关文件(放入.gitignore)

#### 功能修改/更新

先pull主分支，再merge新分支，更改都在自己开的分支中进行，主分支仅用于merge操作，确认不需要修改后及时删除开的分支。

#### commit - m

格式为[%type] - %msg type： 本次操作类别

- New 新增
- Del 删除
- Fix 修正
- Mix 多种操作
- msg：附加的说明信息，务必是能让其他人看懂

### log规范

使用串口实现log输出，打印的Log的级别是能真实反映此Log对应的级别，标签、Log内容具有很好的可读性

#### 各个Log等级的使用

Debug

> 用于调试的信息，编译进产品，但可以在运行时关闭

Info

> 例如一些运行时的状态信息，这些状态信息在出现问题的时候能提供帮助

Warning

> 警告系统出现了异常，即将出现错误

Error

> 系统已经出现了错误







# **电子系统设计与实验设计分析报告**

**通信三班**

**李佳林 3020234369	王宝琨 3020234366	姜晨亮 3020234357**



## 1 需求分析

▲ 设计要求的简单阐述，概括性的讲（例如频率可变、幅度可调）

▲ 谈谈你的总体思路，或者你所理解的设计中要考虑的因素（这里并非具体设计方案）：系统构成涉及都的系统繁简程度、可实现性、成本等，以及软件任务分工是否可行



## 2 总体设计

▲ 硬件：系统框图

▲ 软件：流程图、代码的组织架构（实例程序里已经有所体现，学习和改进）

设计重点、难点



## 3 详细设计及仿真

▲ 硬件，各部分电路的分析（讲解电路原理）、仿真的运用

（1）DAC信号的参数特点：交流还是直流？信号电压范围是什么？

（2）模拟有源低通滤波器设计，filterpro工具，sallen-key/ multiple-feedback两者之一，运算放大器的选用LM358，选择的依据，比如358适合单电源供电、输入输出电压范围、增益带宽乘积、压摆率指标都是什么，有什么作用

（3）单管功率放大器（电流放大器，射极跟随器），偏置电路，仿真环境中，可以对偏置进行调节，图表。隔直流电容，容值？仿真，图表。输出电压范围、阻抗等

（4）电源

▲ 软件对重点模块进行分析说明，包括你采用的某些***数据结构，f，A，\***如果有代码，要用等宽字体



## 4 设计总结及心得

【每小组交一份，组内分工协作】



