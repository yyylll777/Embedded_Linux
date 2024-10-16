ctrl+alt+t打开终端

windows的绝对路径中，目录使用"\\"分隔；

在Linux的绝对路径中，目录使用"/"分隔。



Linux的目录是树状结构。

## 学习shell

### 什么是shell

#### 引言

当我们谈起命令行时，其实指的是Shell。Shell是一个程序，它接收由键盘输入的命令并将其传递给操作系统（简称系统）来执行。几乎所有的Linux发行版都提供了来自GNU项目的Shell程序Bash。

#### 终端仿真器(terminal emulator)

当使用图形用户界面（Graphical User Interface，GUI）时，我们需要
另一种叫作终端仿真器（terminal emulator）的程序与Shell进行交互。如果仔细查看桌面菜单，应该能在其中找到终端仿真器。在KDE下使用的是konsole，在GNOME下使用的是gnome-terminal，但是在菜单上很可能将它们简单地统称为终端（terminal）。Linux系统中可用的终端仿真器数目众多，不过基本上做的都是同样的事情：让用户访问Shell。

#### 简单命令(root)

如果提示符的最后一个字符是#，而非$，表明该终端会话具有超级用户权限。这就意味着要么我们是以超级用户（root用户）登录的，要么选用的终端仿真器提供了超级用户权限。

#### 光标移动

按上方向键，可以得到之前输入的命令，按下方向则相反。如果按左方向键和右方向键，能够将光标移动到命令行的任意位置。这可以让我们很容易地编辑命令。

虽然Shell与用户的交互全部是通过键盘来完成的，但是在终端仿真器中也可以使用鼠标。X Window系统（驱动GUI的底层系统）内建立了一种机制，支持快速“复制—粘贴”技术。如果按住鼠标左键，拖动鼠标选中部分文本（或者双击选中一个单词），这些文本会被复制到由X Window维护的缓冲区中。**按鼠标中键可以将复制好的文本粘贴到光标所在的位置。**

**在终端窗口使用ctrl+c和ctrl+快捷键是没用的。**

#### 几个简单命令

date命令，该命令可以显示当前的时间和日期

cal命令，默认显示当前月份的日历

查看磁盘的当前可用空间，输入df命令

查看可用内存容量，输入free命令

结束终端会话的方法不止一种，关闭终端仿真器窗口、在Shell提示符下
输入exit命令，或是按Ctrl-D组合键均可

### 导航

和Windows一样，类UNIX系统（如Linux）也是按照有层次的目录结构来组织文件的。这意味着文件是在树状的目录（在其他系统中有时称为文件夹）中组织的，目录中还可以有文件和其他目录。文件系统的第一个目录称为根目录，其中包含了文件和子目录，而子目录中还可以包含更多的文件和子目录，依此类推。

需要注意的是，在Windows系统中，每个存储设备都有各自独立的文件系统树。**而在类UNIX系统中（如Linux），不管计算机安装了多少存储设备，都只有一个文件系统树。**按照负责维护系统的超级用户的设置，存储设备将会连接（更准确地说是“挂载”）到文件系统树的不同位置。即，在linux系统中，没有windows系统的盘符(C盘，D盘)的概念，只有一个根目录(/)，所有文件都在根目录下面。

#### 当前工作目录

在任何时刻，我们都处在某个目录中，能够看到该目录中包含的文件、上级目录（父目录）以及下级目录（子目录）。我们所处的目录称为当前工作目录。可以使用pwd（print working directory，输出工作目录）命令将其显示出来：

当首次登录系统（或是启动终端仿真器）时，当前工作目录就是用户的主目录。**每个用户都有自己的主目录，这是普通用户唯一有权限写入文件的地方。**

#### 列出目录内容

ls命令能够列出当前工作目录中的文件和子目录,其实我们可以使用ls命令列出任意目录中的内容，并不局限于当前工作目录。

#### 更改当前工作目录

cd命令可以更改当前工作目录（我们当前所在的位置）。只需要在cd命令之后输入要更改的工作目录的路径名即可。路径名是沿着文件系统树的分支到达目标目录的路线。路径名分为两种：绝对路径名和相对路径名。

##### 绝对路径

绝对路径名从根目录开始，随后紧接着一个又一个分支，直到目标目录或文件。例如，系统里有一个目录，大多数系统程序安装在其中。该目录的路径名是/usr/bin。这就意味着根目录（在路径名中用/来表示）中有一个名为usr的目录，该目录包含一个bin目录

##### 相对路径

相对路径名则是从当前工作目录开始的。为此，用到了两种特殊表示法来描述目标在文件系统树中的相对位置：.（点号）和..（双点号）。.代表当前工作目录，..代表当前工作目录的父目录。

一般而言，如果没有指定路径名，则默认为当前工作目录。

以点号开头的文件名是隐藏的。这说明ls命令不会列出这些文件，除非使用ls-a。在创建账户时，主目录里会放置一些用于配置账户的隐藏文件。与UNIX一样，Linux中的文件名与命令也是区分大小写的。文件名File1和file1指向不同的文件。虽然Linux支持长文件名，其中可以包含嵌入的空格和标点符号，但是标点符号仅限于点号、半字线以及下画线。最重要的是，别在其中使用空格[1]。如果你想分隔文件名中的单词，可以使用下画线。不像其他操作系统，Linux并没有“文件扩展名”的概念。你想怎么命名文件都行。文件内容或用途是由其他方式来决定的。

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231019213726970.png" alt="image-20231019213726970" style="zoom:50%;" />



### 探索Linux系统

#### 再谈ls命令

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020144017676.png" alt="image-20231020144017676" style="zoom:50%;" />



<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020144220740.png" alt="image-20231020144220740" style="zoom:50%;" />

上图为常用的ls命令选项。

ls命令可能是用得最多的命令。有了它，就能够查看目录内容、确定各种重要文件和目录属性。只需输入ls命令，就可以得到当前工作目录包含的文件和子目录，除了当前工作目录，我们还可以指定要显示内容的目录：

```shell
ls /usr
```

甚至可以指定多个目录。在下面的例子中，我们同时列出了用 户主目录（由字符~代表）和/usr目录的内容:

```shell
ls ~/usr
```

#### 使用file命令确定文件类型

可以使用file命令来确定文件类型，Linux系统并不要求文件 名必须反映文件的内容。当我们看到picture.jpg时，通常会觉得该文件 是一张JPEG压缩图像，但是在Linux中未必如此。我们可以像下面这调用file命令：

```shell
file filename
```

file命令会输出文件内容的简要描述,例如：

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020144724344.png" alt="image-20231020144724344" style="zoom:50%;" />

**在类UNIX系统中（如Linux），存在一个普遍观念：万物皆文件（everything is a file ）**

#### 使用less命令查看文本文件

使用less命令可以查看文本文件。纵观Linux系统，有大量文件包含 的是人类可读的文本。less命令提供了一种查看这类文件的便捷方法。很多包含系统设置的文件（称 为“配置文件”）采用的都是文本格式，能够阅读这种文件可以让我们了解系统是如何工作的。除此之外，系统使用的某些程序（称为“脚本”） 也是文本格式的。

less命令的用法如下：

```shell
less filename
```

文本是字符与数字之间简单的一对一映射，它非常紧凑。50个文本字符可以转换为50字节的数字。要明白，文本只是字符与数字之间的简单映射，这一点非常重要。它不同于Microsoft Word或 OpenOffice.org Write所创建的字处理程序文档。与简单的ASCII文本文件相比，这些文件包含了很多用于描述文档结构和格式的非文本元素。而普通的ASCII文本文件仅包含字符本身和少数基本的控制代码，例如，制表符、回车符及换行符。

less命令允许我们前后翻看文本文件。例如，要想查看定义了系统 中所有用户的文件，可以输入下列命令：

```shell
less /etc/passwd
```

运行less命令之后，就能够查看文件内容了。如果文件内容多于一 页，则可以前后翻看。按Q键可退出less命令。

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020145225096.png" alt="image-20231020145225096" style="zoom:50%;" />

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020145357447.png" alt="image-20231020145357447" style="zoom:50%;" />

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020145410639.png" alt="image-20231020145410639" style="zoom:50%;" />

#### 符号链接

在大多数类UNIX系统中，一个文件可以被多个名称引用。

### 操作文件和目录

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020145935637.png" alt="image-20231020145935637" style="zoom:50%;" />

命令可以使复杂的任务更加简单

#### 通配符

因为Shell要用到大量的文件名，所以它提供了一种特殊字符，帮助快速指定一组文件名。这种特殊字符叫作通配符(wildcard）。使用通配符的过程也称为“通配符匹配”（globbing）[1]，可以依据模式选择文件名

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020150139314.png" alt="image-20231020150139314" style="zoom:50%;" />

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020150157269.png" alt="image-20231020150157269" style="zoom:50%;" />

```shell
*.txt //代表名字以.txt结尾的所有文件，包括0长度的文件。
```

利用通配符，可以构建出复杂的文件名匹配条件。

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020150237648.png" alt="image-20231020150237648" style="zoom:50%;" />

*并不能匹配以点号开头的文件（隐藏文件）

#### mkdir--创建目录

mkdir命令可用于创建目录，用法如下:

```shell
mkdir directory...
```

下列命令：

```shell
mkdir dir1
```

可以创建单个目录dir1。再看下列命令：

```shell
mkdir dir1 dir2 dir3
```

可以分别创建3个目录——dir1、dir2、dir3。

-p选项可以创建嵌套目录

```shell
mkdir /tmp/dir1/dir2
```

此命令可以在dir1目录中创建dir2

rmdir命令可以用来删除目录，但是只能删除空目录。

#### cp--复制文件和目录

cp命令可用于复制文件和目录。该命令有两种不同的用法。下列形式可以将单个文件或目录item1复制到文件或目录item2：

```shell
cp item1 item2
```

而下列形式可以将多个文件或目录item复制到目录directory中：

```shell
cp item... directory
```

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020150928506.png" alt="image-20231020150928506" style="zoom:50%;" />

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020151012028.png" alt="image-20231020151012028" style="zoom:50%;" />

#### mv--移动和重命名文件

取决于具体用法，mv命令可以执行文件移动和文件重命名操作。不管是哪种情况，操作完成之后，原先的文件名都不再存在。mv命令的用法和cp命令大同小异：

```shell
mv item1 item2
```

该命令可以将文件或目录item1移动或重命名为item2。也可以像下面这样使用：

```shell
mv item... directory
```

该命令将一个或多个item从一个目录移动到另一个目录

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020153254194.png" alt="image-20231020153254194" style="zoom:50%;" />

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020153313846.png" alt="image-20231020153313846" style="zoom:50%;" />

#### rm--删除文件和目录

rm命令可用于删除文件和目录，如下所示

```shell
rm item...
```

其中，item可以是一个或多个文件/目录。

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020153628020.png" alt="image-20231020153628020" style="zoom:50%;" />

类UNIX系统（如Linux）并没有还原删除命令。使用rm命令删除的文件或目录，就再也找不回来了

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020153720001.png" alt="image-20231020153720001" style="zoom:50%;" />

#### ln--创建硬链接和符号链接

ln命令可用于创建硬链接或符号链接。该命令有两种不同的用法。 创建硬链接：

```shell
ln file link
```

创建符号链接：

```shell
ln -s item link
```

其中，item可以是文件或目录。

##### 硬链接

硬链接是最初UNIX创建链接的方式，相较于符号链接，硬链接要更现代。在默认情况下，每个文件只有一个硬链接，由其为文件赋予名称。当我们创建硬链接时，就为文件额外创建了一个目录项。硬链接有两个重要限制。

1.硬链接不能引用其所在文件系统之外的文件。这意味着如果文件与链接不在同一个磁盘分区内的话，是无法引用该文件的。 

2.硬链接不能引用目录。

你无法区分硬链接及其引用的文件。不同于符号链接，当你列出包含硬链接的目录内容时，你会发现硬链接并没有什么特别的指示说明。 如果删除了某个硬链接，则消失的只是该链接本身，而文件内容仍旧存在（也就是说，磁盘空间并未被释放），直到文件的所有硬链接全部被删除。

##### 符号链接

符号链接就是为了克服硬链接的限制而出现的。其工作原理是创建一种特殊类型的文件，内含一段指向被引用文件或目录的文本指针。就这方面而言，它和Windows的快捷方式非常类似。由符号链接指向的文件与符号链接本身几乎没有区别。例如，向符号链接写入内容，最终写入的是被引用的文件。当你删除符号链接时，删除的只是链接，而非文件。如果文件先于符号链接被删除，那么符号链接仍旧存在，但其指向就不再有效了。这种链接称为无效链接。在很多实现中，ls命令会用不同的颜色（如红色）来显示无效链接，告知用户其存在。当我们创建符号链接时，相当于用文本描述目标文件相对于符号链接的位置。

硬链接就是：一面墙上有一个洞，洞里放着一个苹果。从墙的这一面看是这个苹果，从墙的另一面看还是同一个苹果。

硬链接就是同一块数据但有两个不同的名字，读写的时候本质上都是修改的同一块数据。硬链接在删除的时候只是删除了一个名字。只有一块数据的所有名字都删除了的时候，数据才会被删除。（删除的时候相当于把墙的这一面糊上，但苹果本身不动，只有两面都糊上了，你才会看不到）

符号链接就是：我声称我有一个苹果，但是当你找我要的时候，我对你说，到某个建筑物的仓库就可以拿到那个苹果了。可见我并不真正拥有一个苹果，我只是拥有“某个地方有一个苹果”这个信息。但对于外部的观察者来说，这跟我实际上拥有一个苹果并无差异。

符号链接的删除：假设我死了，不会影响到原始数据。假设原始数据没了，那我这个符号链接就变成了一张空头支票，也就是悬空的符号链接。

快捷方式：本质上就是符号链接，只不过 Windows 的资源管理器可以直接管理这种文件。

junction points：可能跟符号链接的区别仅仅是能否使用相对路径。

复制：把一个苹果变成两个苹果。

链接都是为文件起别名（alias）的方式，跟复制有本质区别的。

### 和命令打交道

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020164247768.png" alt="image-20231020164247768" style="zoom:50%;" />

#### 命令究竟是什么？

符合下列4种情况之一的，都可以称之为命令。

1.可执行程序。就像我们在/usr/bin中见到的那些文件一样。在这一分类中，程序可以是由C和C++编写并经过编译生成的二进制可执行文件，也可以是由Shell、Perl、Python、Ruby等脚本语言编写的脚本。

2.在Shell中的内建命令。Bash支持大量内建命令，cd命令就是其中之一。

3.Shell函数。Shell函数是并入环境中的微型Shell脚本。在后文中，我们将介绍环境配置和Shell函数的编写，目前只需要知道两者的存在即可。

4.别名。别名是我们在其他命令的基础上自己定义的命令。

#### 识别命令

##### type--显示命令类型

type命令属于Shell内建命令，能够显示指定的命令属于哪种类型。 其用法如下：

```shell
type command
```

其中，command是想要检查的文件名。

##### which--显示可执行文件的位置

有时候，系统中安装的程序不止一个版本。尽管这种情况在桌面系统中并不常见，但在大型服务器上却是司空见惯的。为了确定某个程序的确切位置，可以使用which命令：

```shell
which command
```

which命令只适用于可执行文件，不适用于内建命令或代替实际可执行文件的别名。如果试图对Shell内建命令（例如cd命令）使用which命令，要么不会有任何输出结果，要么得到错误消息：

#### 获取命令文档

##### help--获取Shell内建命令的帮助信息

Bash自带的帮助功能可用于所有Shell内建命令。只需要输入help， 然后加上Shell内建命令的名称即可。

##### --help---显示用法信息

很多程序都支持--help选项，该选项可以显示命令所支持的语法和选项的相关描述。

##### man--显示命令的手册页

大多数用于命令行的程序会提供一份叫作手册（manual)或手册页（man page ）的正式文档。有一个特殊的分页程序man可以浏览这种文档。其用法如下：

```shell
man program
```

其中，program是待浏览的手册页对应的命令名称。 手册页的格式各不相同，不过一般都会包含下列部分。

标题（手册页的名称）。 

命令语法提要。 

命令作用描述。 

命名选项清单及其描述。 

不过，手册页中通常并不包含示例，其目的是作为参考，并非教程。

在大多数Linux系统中，man命令使用less命令显示手册页，所以在浏览的时候，熟悉的所有less命令都照样管用。 man命令显示的“手册页”被分为若干节（section），不仅涵盖用户命令，还包括系统管理命令、编程接口、文件格式等。

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020170511287.png" alt="image-20231020170511287" style="zoom:50%;" />

有时候我们需要参考手册页的某一节，从中查找所需的内容。当要查找的文件格式同时也是命令名称的时候，更是如此。如果没有指明节号，则显示最先匹配到的那一节（可能会是第1节）。为了指明节号， 可以像下面这样

```shell
man section search_term
```

##### apropos--显示适合的命令清单

关于apropos命令可以根据关键字在手册页列表中搜索可能的匹配项。这种方法比较粗糙，但有时倒也管用。注意，man命令的-k选项和apropos命令具有相同的功能。

##### whatis--显示手册页的简述

whatis命令会显示匹配指定关键字的手册页名称和单行描述：

##### info--显示程序的info条目

GNU项目为自家的程序提供了手册页的替代品：info。Info页使用名为info（恰如其分）的阅读器显示。info页中也包含超链接，和我们平时看到的网页颇为相像。nfo程序读取info文件，该文件按照树形结构组织成各个单独的节点，每个节点包含一个主题。info文件包含的超链接可以让你在节点之间跳转。超链接可以通过前置的星号来识别，将光标放在超链接上并按 Enter键即可激活。 输入info和程序名称（可选）就可以启动info程序

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020193939314.png" alt="image-20231020193939314" style="zoom:50%;" />



##### 文档文件

系统中安装的很多软件包都有自己的文档文件，它们被存放在/usr/share/doc目录中。其中大部分文档文件采用的是纯文本格式，可以使用less命令来查看。有些文件采用的是HTML格式，可以用Web浏览器来查看。我们可能会碰到一些以.gz扩展名结尾的文件。这表明它们是经过gzip压缩过的。gzip软件包中有一个特殊版本的less命令，它叫作zless，可以显示由gzip压缩的文档文件的内容。

#### 使用alias创建自己的命令

使用alias命令来创建自己的命令。但是在动手之前，我们需要展示一个命令行的小技巧：可以使用分 号作为分隔符，在命令行中一次性输入多个命令。就像下面这样：

```shell
command1; command2; command3...
```

使用alias创建别名，例如下列语句：

```shell
alias foo='cd /usr; ls; cd-'
```

alias命令的写法：

```shell
alias name='string'
```

在alias之后，我们指定了别名，紧接着（不允许出现空白字符[1]） 是等号，然后是单引号引用的字符串，包含着要赋给别名的内容。定义好的别名可以出现在Shell允许出现命令的任何地方。

unalias命令可以删除别名：

```shell
unalias foo
```

尽管我们有意避免使用已有的命令名称来为别名命名，但这种做法其实并不少见。其目的在于为常见命令添加惯用选项。例如，前面讲到的ls是如何通过别名来添加颜色支持的：

要想知道系统中定义的所有别名，使用不加任何参数的alias命令即可。

**在命令行定义别名还有一个小问题。当Shell会话结束时，这些别名也会随之消失**

### 重定向

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231020200224307.png" alt="image-20231020200224307" style="zoom:50%;" />

#### 标准输入、标准输出及标准错误

我们目前用过的很多程序能够产生某种形式的输出结果。这种输出结果通常有两种类型。 

1.程序的运行结果，也就是程序本就要产生的数据。 

2.表明程序运行情况的状态和错误消息。

如果观察ls命令，就能发现它会在屏幕上显示运行结果和错误消 息。 秉承“万物皆文件”的UNIX主旨，程序（例如ls命令）实际上将运行结果和状态消息分别发送到了名为stdout（标准输出，standard output 的 缩写）和stdeer（标准错误，standard error 的缩写）的特殊文件。

在默认情况下，标准输出和标准错误与显示器屏幕相关联，并不会保存为磁盘文件。 另外，许多程序从stdin（标准输入，standard input 的缩写)中获取输入，默认情况下，标准输入与键盘相关联。 I/O重定向允许我们修改输出结果的去处和输入的来源。通常来说，输出结果会显示在屏幕，输入则来自键盘，但有了I/O重定向，两者我们都可以改变。

#### 标准输出重定向

I/O重定向功能可以重新定义标准输出的去处。要想把标准输出重定向到其他文件，而非出现在屏幕上，可以使用重定向操作符>，后面跟上文件名即可。为什么我们要这样做？因为通常需要把命令的输出结果保存在文件中。例如，我们想让Shell将ls命令的输出结果保存在lsoutput.txt中：

```shell
ls -l /usr/bin > ls-output.txt
```

这里，我们生成了/usr/bin目录的长格式列表并将其发送到lsoutput.txt。

当使用重定向符>对标准输出进行重定向时，会完全重写目标文件。由于ls命令除了一条错误消息外没有产生任何输出结果，因此重定向操作一开始准备重写该文件，出现错误后停止了写入操作，最终导致了该文件内容被截断（truncation）。事实上，如果我们打算截断某个文件（或者创建一个新的空文件），就可以利用这个技巧：

```shell
> ls-output.txt
```

只需使用不加任何命令的重定向操作符，就可以截断现有文件或者创建一个新的空文件

那么，该怎样才能把重定向的标准输出追加到文件尾部，而不是将其从头覆盖呢？为此，可以使用重定向操作符>>来实现：

```shell
ls -l /usr/bin >> ls-output.txt
```

使用重定向操作符>>会将标准输出追加到文件尾部。如果指定的文件不存在，则像操作符>一样，新建该文件。

#### 标准错误重定向

标准错误重定向缺少专门的重定向操作符。要想重定向标准错误， 必须引用其文件描述符。程序可以在任意经过编号的文件流（numbered file stream ）上生成输出结果。虽然我们将前3个文件流称为标准输入、 标准输出及标准错误，但在Shell内部分别是用文件描述符0、1及2引用 它们的。Shell提供了使用文件描述符编号来重定向文件的写法。由于标准错误对应的文件描述符为2，因此可以用下列写法来重定向标准错误：

```shell
ls -l /bin/usr 2> ls-error.txt
```

文件描述符2紧靠在重定向操作符之前，将标准错误重定向到ls-error.txt。

##### 将标准输出和标准错误重定向到同一个文件中

有时候，我们可能想将命令的所有输出结果全都保存到一个文件 中。为此，必须同时重定向标准输出和标准错误。有两种实现方法。先来看传统方法，适用于旧版Shell：

```shell
ls -l /bin/usr > ls-output.txt 2>&1
```

我们执行了两次重定向。先将标准输出重定向到ls-output.txt，然后 使用2>&1将文件描述符2（标准错误）重定向到文件描述符1（标准输出）。

标准错误的重定向操作必须在标准输出重定向之后执行，否则无法奏效。

较新版本的Bash提供了另一种更流畅的方法来实现这种联合重定向：

```shell
ls -l /bin/usr &> ls-output.txt
```

我们使用&>将标准输出和标准错误重定向到ls-output.txt。你也许想将标准输出和标准错误追加到单个文件中，可以这样做：

```shell
ls -l /bin/usr &>> ls-output.txt
```

##### 丢弃用不着的输出结果

有时候你并不需要命令的输出结果，而希望将其丢弃掉，尤其是那些错误和状态消息。系统提供了一种解决方法：将输出结果重定向到名为/dev/null的特殊文件。该文件是一个系统设备，通常称作位桶（bit bucket ），能够接收输入结果但不做任何处理。下列命令可以丢弃命令的错误消息：

```shell
ls -l /bin/usr 2> /dev/null
```

#### 标准输入重定向

##### Cat--拼接文件

cat命令读取一个或多个文件并将其复制到标准输出:

```shell
cat filename
```

在大多数情况下，你可以将cat命令等同于DOS中的type命令，能够以不分页的形式显示文件内容。例如，下列命令将显示ls-output.txt的内容：

```shell
cat ls-output.txt
```

cat命令常用于显示比较短的文本文件。因为cat命令能够接收多个文件作为参数，所以还可用于将文件拼接在一起。假设我们下载了一个被分割成好几部分的文件（Usenet上的多媒体文件多采用这种方式）， 希望能将其组合还原。如果这些文件的命名方式如下：

```shell
movie.mpeg.001 movie.mpeg.002 ... movie.mpeg.099
```

我们可以用下列命令将其恢复原状：

```shell
cat movie.mpeg.0* > movie.mpeg
```

因为通配符会按照顺序扩展，所以cat命令的参数排列也不会出错

如果输入没有任何参数的cat命令会怎样？什么都没发生，就是停在那里，像是被卡住了。看起来似乎如此， 但其实这正是cat命令应该做的事情。如果没有为cat命令指定任何参数，它就从标准输入中读取。又因为标准输入默认和键盘关联，所以cat命令一直在等着我们从键盘输入！输入下面的文本，然后按Enter键：

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231021165658300.png" alt="image-20231021165658300" style="zoom:50%;" />

接着，按Ctrl-D组合键（也就是按住Ctrl键，再按D键），告诉cat命令已经到达了标准输入的文件末尾（End Of File，EOF）：

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231021165727071.png" alt="image-20231021165727071" style="zoom:50%;" />

在缺少文件名参数的情况下，因为cat命令会将标准输入复制到标准输出，所以我们看到了重复显示的文本行。利用这种行为，可以创建短小的文本文件。假设我们想要创建一个名为lazy_dog.txt的文件，其中包含先前示例中的文本内容。

现在我们知道除文件名参数之外，cat是如何接收标准输入的，让我们尝试重定向标准输入：

<img src="C:\Users\22364\AppData\Roaming\Typora\typora-user-images\image-20231021170137505.png" alt="image-20231021170137505" style="zoom:50%;" />

通过重定向操作符<，我们将标准输入方式从键盘改为文件 lazy_dog.txt。可以看到，结果和传递文件参数一模一样。相较于传递文件参数，重定向标准输入也并未显得特别有用，这里只表明可以使用文件作为标准输入而已。

#### 管道

Shell的管道特性利用了命令能够从标准输入读取数据并将数据发送到标准输出的能力。通过管道操作符|，可以将一个命令的标准输出传给另一个命令的标准输入：

```shell
command1 | command2
```

对于那些将结果发往标准输出的命令，我们都可以使用less命令将其输出结果逐页显示出来

```shell
ls -l /usr/bin | less
```

对任何能够产生标准输出的命令，我们都可以利用这个方法检查其输出结果。 管道往往用来执行复杂的数据操作。我们也可以把多个命令组合在一起形成管道，这种方式中用到的命令通常被称为过滤器（filter）。过滤器获取输入，对其做出改动，然后输出。

##### 排序列表

我们先来试一试sort命令。假设要把/bin和/usr/bin目录下的所有可执行文件合并成一个列表，然后排序，并查看最终结果。

```shell
ls /bin /usr/bin | sort | less
```

因为我们指定了两个目录（/bin和/usr/bin），所以ls命令的输出结果包含了两个排序列表，分别对应每个目录。在管道中加入sort命令， 就可以修改ls命令的输出结果，生成单个有序列表。

乍一看，很难理解管道操作符|与重定向操作符>执行的重定向有什么不同之处。简单来说，重定向操作符将命令与文件连接在一起， 而管道操作符将一个命令的输出结果与另一个命令的输出结果连接在 一起：

## vim

centos中使用su root命令进入root

vim中删除和剪切操作是等价的

























