## 基本信息

> 考虑游戏性与博弈主题相关性的权衡：  
> 过度复杂的游戏不会有趣
> 
> 附带：动态难度控制系统

- 名称：勇士和魔王/Soldiers and Demons
- 游戏方式：人人/`人机`
- 基本背景：勇者斗魔王
- 可供操作角色：勇者、魔王
- 形式：角色与文字(字/词)交互，字词形成的意义被实现
	- （可选）增加节奏元素：节奏地牢
		- 随音乐节拍进行移动
- 来源：文字游戏

- 输赢判断：
	1. 一个界面+两个人固定初始血量，彼此攻击防御，同时剧情推进，剧情结尾处比较两人血量，血量更高者胜
	2. ✅无限时间，血量先归零一方判定为输

## 角色

- 移动方式：WASD移动
	1. 四向间断移动
	2. 八向平滑移动

- 角色属性：
	- 攻击（影响语句效果，需要对应防御语句，防御语句或许可以以添加限时护盾）
		- 物理
		- 法术
	- 血量
	- 回复（影响语句效果）
	- 移动速度（对八向平滑有效）

- 勇者
	- 骑士：
		- 攻击
			- 物理 高
			- 法术 低
		- 血量 中
		- 回复 中
		- 移动速度 高

	- 法师：
		- 攻击
			- 物理 低
			- 法术 高
		- 血量 低
		- 回复 高
		- 移动速度 中

	- 魔剑士：
		- 攻击
			- 物理 中
			- 法术 中
		- 血量 中
		- 回复 中
		- 移动速度 中

- 魔王
	- 撒旦：
		- 攻击
			- 物理 高
			- 法术 低
		- 血量 中
		- 回复 中
		- 移动速度 高

	- 洛基：
		- 攻击
			- 物理 低
			- 法术 高
		- 血量 低
		- 回复 高
		- 移动速度 中

	- 路西法：
		- 攻击
			- 物理 中
			- 法术 中
		- 血量 中
		- 回复 中
		- 移动速度 中

## 文字

> 成句或许不必合理  
> Example：勇者拼出了（魔王愣在原地）

- 名词
	- 角色
	- 各类装备
	- 各类食物
- 动词
	- 攻击（需要扩展类型）
	- 防御（需要扩展类型）
	- 使用（需要扩展，考虑过多扩展可能使游戏过于复杂）
- 修饰词？
	- 否定
	- 程度副词
	- 量词
- 特殊符号
- 成句判定
	1. 用户手动结束
	2. 程序自动判定

## 交互

- 角色移动：方向键
- 角色文本交互：
	1. 遇到文本就输入指令框
 	2. 遇到文本+使用按键输入指令框

## 难度设置

- 增大控制台面积
- 节奏更快
- 限制语句拼写的时长
- 撤销词块

## 界面（陶其航）

> 考虑界面间动画？

- 包含：菜单、游戏、介绍、`设置`

### 显示

- 基本
	- 以格为单位
	- 每人物游戏区域：？x？格

- 人物（考虑与 角色-移动方式的关系）
	- 游戏区域
		1. 不显示
		2. ✅占一格
	- 血量（？显示位置）
	- 指令行（？显示位置）
	- 历史行为（？显示位置）
	- 装备？

- 字词
	1. 按字数占格
	2. 压缩为一格

## 数据&结构

- 角色的指令行：数组
- 角色的各类数值：
	保存于文件，定义C++结构角色，以角色类型新建变量存储
- 角色的历史纪录（输出）：字符串数组-动态
- 游戏区域内字符：二维数组
- 字词：
	- 名词：枚举
	- 动词：函数（利用指针/函数重载）

## 算法

- 随机生成字词
	- 考虑分布是否使游戏更有趣/更符合博弈
	- 速度
	- 单次数量
	- 真/伪随机（？我认为伪随机）

- 成句判定？
- 动词
	- 类型：（待定）
	- 函数重载&继承
