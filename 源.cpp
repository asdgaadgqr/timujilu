/*
https://www.hacker101.com/sessions/introduction.html
1.	本视频一开始介绍了哪两个工具，他们的作用分别是什么？为什么作者会推荐firefox，它的优点是什么？（5分）
Burp Proxy and Firefox

Burp Proxy allows me to watch all HTTP(S) conmmunication, intercept(拦截) and modify(修改) request, and replay existing request.
Burp Proxy可以监视http和http流量、抓包、改包、重复发包等操作。

Firefox allows me to set proxy settings specifically in the browser(浏览器), rather than system - wide.
火狐可以在浏览器里设置代理，就可以只查看我想查看的流量，而不是查看所有网络流量。系统还包括了非常好的开发人员工具。

2.本视频中体现了哪些攻防上的哲学观点？作者希望你养成什么样的思维？这些思维在帮助你挖掘漏洞的时候有什么帮助？结合你的经历与视频内容谈谈你的看法。（10分）

观点：要在其他人之前先找到漏洞，就可以在受到攻击之前修复漏洞。要做到这一点，就必须要了解黑客的攻击手法，以及他们的思考方式。要运行程序，了解程序的运行方式以及程序可能怎样崩溃。攻击者和防御者的负担不同，攻击者只用找到一个漏洞，但是防御者必须找到每一个。在实践中攻击者会比防御者更有优势。精力是有限的，所以要优先考虑高风险区域，这样才可以最大程度减少攻击影响或者猜测出攻击者实际上想要的是什么。要尽量弄清楚功能存在的意义，然后针对每个功能考虑攻击者的目标可能是什么，确定优先级，然后根据应用程序的位置对应用程序进行排名。

思维：换位思考，有针对性，提前预判

帮助：以后挖洞可以从开发人员不是特别重视的位置开始挖

看法：还没有挖过洞，以后可以多认识一些开发人员，研究他们一般比较重视哪些方面的防御，为以后挖洞做准备。

3.审计以下代码：
< ? php
	if (isset($_GET[' name '])) {
		echo "<h1>Hello {$_GET['name']} !</h1>";
	}
? >
<form method = "GET">
Enter your name : <input type = "input" name = "name"><br>
<input type = " submit">


本段代码涉及到客户端，服务端以及通信协议。
运行在客户端的代码主要有HTML以及javascript，由浏览器核心负责解释

通信协议为HTTP协议，有多种格式的请求包，常见的为POST与GET

运行在服务端的代码为php，由php核心负责解释。

用户端与服务端通过HTTP通信协议进行交互。

那么，以上代码中，哪些部分属于客户端的内容，哪些属于服务端的内容？（1分）
客户端：
<form method = "GET">
Enter your name : <input type = "input" name = "name"><br>
<input type = " submit">
服务端：
< ? php
	if (isset($_GET[' name '])) {
		echo "<h1>Hello {$_GET['name']} !</h1>";
	}
? >

客户端是通过传递什么参数来控制服务端代码的？（1分）
传递name

客户端通过控制该参数会对服务端造成什么影响，继而使得客户端本身收到影响，从而造成了什么漏洞？如果是xss漏洞，具体又是什么类型的xss漏洞，为什么？（3分）
XSS攻击通常指的是通过利用网页开发时留下的漏洞，通过巧妙的方法注入恶意指令代码到网页，使用户加载并执行攻击者恶意制造的网页程序。跨站脚本攻击是指恶意攻击者往Web页面里插入恶意Script代码，当用户浏览该页之时，嵌入其中Web里面的Script代码会被执行，从而达到恶意攻击用户的目的。
xss漏洞通常是通过php的输出函数将javascript代码输出到html页面中，通过用户本地浏览器执行的，所以xss漏洞关键就是寻找参数未过滤的输出函数。
大佬链接：https ://www.jianshu.com/p/4fcb4b411a66


反射型xss漏洞，在客户端输入以后就直接通过echo函数输出，没有储存进数据库，也没有对用户输入进行任何过滤。

4.思考：现实中如何利用xss漏洞实施攻击，我们应该如何预防？（1分）
直接输出的，在输出之前进行过滤。
要进入数据库的，在进入数据库之前过滤。
*/




/*
https://www.hacker101.com/sessions/pentest_owasp
1.目前owasp的十大web安全漏洞是哪些？这些漏洞排名是按照漏洞的严重程度排序的还是按照漏洞的常见程度排序的？（2分）
owasp的十大web安全漏洞会逐年变化，如今可以查到2017年的
injection
broken authentication
sensitive data exposure
XML external entities（XXE）
broken access control
security misconfiguration
cross site scripting XSS
insecure deserialization
using components with know vulnerabilities
insufficient logging & monitoring
排名是按照漏洞的严重程度排序

2.请翻译一下credential stuffing（1分）
凭证填充攻击

3.为什么说不充分的日志记录(insufficient logging)也算owasp十大漏洞的一种？他的危害性如何（2分）
攻击者可以进一步攻击系统，维持持久性，转向更多系统以及篡改，提取或破坏数据。
危害性很大

4.请翻阅一下owasp testing guide，以及owasp testing guide check-list，视频说怎么结合这两个文档来学习渗透测试？ 结合你平时渗透过程中的经验，谈谈你的感想。（3分）
owasp testing guide里面有书，owasp testing guide check-list相当于一个索引，通过这个表格可以查漏洞在书上的位置，然后就可以在书上去查漏洞的具体信息。平时做题写的wp也可以写一个类似的文档，在下一次遇到类似的题的时候就可以看以前的笔记找思路。

5.you are only as good as you notes
   you are only as good as things you can refer to
结合这两句话谈谈你的感想。（2分）
只有想做才能做好，只有积累才能变强
*/



/*
https://www.hacker101.com/sessions/web_in_depth.html
1.http报文的结构是什么？（1分）
无论是请求包还是响应包都拥有一个起始行（start line）和头部（header），只有响应包具有一个主体（body）
在查资料的时候找到了一个很厉害的大佬的，写的很详细贴个链接https://www.huaweicloud.com/articles/795b0d40dab18a6e317c1db547c3d153.html


2.什么是crlf？在http报文的哪个位置。（1分）
回车换行，和enter好像差不多。在请求报文请求行、请求头的末尾和空行中，在响应报文状态行、响应头的末尾和空行中。


3.解释下这几个头的含义（5分）：

图片: https://uploader.shimo.im/f/g5F6pOxn3T93mirM.png
Host: 所请求服务器主机ip地址
Accept: 告诉服务器能够发送哪些媒体类型
Cookie:传送cookie数据到服务器
Referer: 告诉服务器该网页是从哪个页面链接过来的
Authorization：请求消息头含有服务器用于验证用户代理身份的凭证


4.cookie具有哪些特点，不同的域名和子域名对cookie有怎样的权限？Cookie的Secure和 HTTPOnly这两个flag分别有什么作用？请结合xss攻击来进行说明（3分）
cookie是从服务器发送的数据的关键部分，在客户机上驻留一段时间；每个cookie都有一个应用于域模式，并且他们与主机客户端发出的每个请求一起传递给匹配的主机。
为域名添加的cookie可以被其任意的子域名读取；为子域名添加的cookie不能被该域名读取，但是可以被子域名的子域名读取；子域可以为自己和父域设置cookie，但是不能为兄弟域设置cookie。
Secure：cookie将只能访问HTTPS页面
HTTPOnly：JavaScript无法读取cookie
这样就不能在网页中植入恶意代码了

5.简述本视频提到的xss绕过web防火墙的方案（5分）
实际用另一组尖括号包裹脚本标签通过网络应用防火墙

6.内容嗅探是什么？主要有哪些类型？请分别举例，主要用途是什么？在什么情况下可以利用这些漏洞？。为什么facebook等网站需要使用不同的域名来存储图片？（5分）
内容嗅探，也被称为媒体类型嗅探或MIME嗅探，是检查一个字节流的内容，试图推断其中数据的文件格式的做法。内容嗅探通常用在媒体类型没有被准确指定的情况，用于补偿元数据信息。
MIME types：长得像HTML会被解析为HTML，可以以存储的方式获得跨站点脚本
编码嗅探：没有为HTML文档指定编码，浏览器将用试探法来确定他，如果能够控制浏览器对文本进行编码的方式，则可以更改解析，而且还可以绕过过滤器。
如果该文件包含足够的HTML来触发嗅探，攻击者就可以上传一张图片，然后将其链接到受害者。


7.同源策略是什么？限制是什么？浏览器在遇到哪两种情况的时候会用到同源策略？如何放松SOP限制？放松SOP限制会对浏览器插件安全造成怎样的破坏？
无法在子域间移动数据，不会在单独的域之间拥有锁，增强浏览器的安全性
限制了对dom访问
阻止跨域发出请求，防止我破坏网络
开发人员可以通过更改文档来放松控制
始终能将附加信息发布到这些扩展程序中，很容易受到跨站点脚本攻击，可以通过扩展程序从一个网页跳到另一个网页



8.csrf是什么？如何设计规避csrf？视频中提到的错误的csrf配置方法是什么？
跨站点请求伪造是指攻击者诱使受害者进入攻击者控制的页面，然后攻击者将数据作为受害者提交到目标站点
使用CSRF令牌：这是绑定到用户会话的随机令牌，可以嵌入到生成的每个表单中
发送回代码的js文件每一页上都有<script src="/crsf.js">然后将csrf令牌烘焙到表单中

附加题：5、6两点主要利用的是由于服务端和客户端对同一信息的处理方式不同造成的漏洞，你还能举出相似的例子么？（1分）

*/