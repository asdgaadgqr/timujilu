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