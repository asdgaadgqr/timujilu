新手村第二题robots

X老师上课讲了Robots协议，小宁同学却上课打了瞌睡，赶紧来教教小宁Robots协议是什么吧。

打开一看毫无头绪，F12也没有什么有用的东西。百度一下得到

**robots协议也叫****robots.txt**（统一小写）是一种存放于[网站](https://baike.baidu.com/item/网站)根目录下的[ASCII](https://baike.baidu.com/item/ASCII)编码的[文本文件](https://baike.baidu.com/item/文本文件)，它通常告诉网络[搜索引擎](https://baike.baidu.com/item/搜索引擎)的漫游器（又称[网络蜘蛛](https://baike.baidu.com/item/网络蜘蛛)），此网站中的哪些内容是不应被搜索引擎的漫游器获取的，哪些是可以被漫游器获取的。因为一些系统中的URL是大小写敏感的，所以robots.txt的文件名应统一为小写。robots.txt应放置于网站的根目录下。如果想单独定义搜索引擎的漫游器访问子目录时的行为，那么可以将自定的设置合并到根目录下的robots.txt，或者使用robots[元数据](https://baike.baidu.com/item/元数据)（Metadata，又称元数据）。robots协议并不是一个规范，而只是约定俗成的，所以并不能保证网站的隐私。

直接在网址后面加上/Robots.txt发现没有查到，robots协议统一小写所以用/robots.txt查询文本文件。查询到

```
User-agent: *
Disallow: 
Disallow: f1ag_1s_h3re.php
```

f1ag_1s_h3re.php也是一个文件将/robots.txt删掉输入/f1ag_1s_h3re.php进行查询得到cyberpeace{10f729c2e1e8def0a30d8e874d115334}