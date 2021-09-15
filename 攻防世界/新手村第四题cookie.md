新手村第四题cookie

X老师告诉小宁他在cookie里放了些东西，小宁疑惑地想：‘这是夹心饼干的意思吗？’

我先查一下cookie是什么。看菜鸟教程看了一下也没看怎么懂。还是决定打开题目先看一下。“你知道什么是cookie吗？”我当然不知道了。暴力抓包得到了

GET / HTTP/1.1
Host: 220.249.52.133:37708
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:83.0) Gecko/20100101 Firefox/83.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Connection: close
Cookie: look-here=cookie.php
Upgrade-Insecure-Requests: 1
Pragma: no-cache
Cache-Control: no-cache



Cookie: look-here=cookie.php这一句就很灵性，应该是个文件吧。输入/cookie.php界面变为See the http response看不太懂，直接搜索翻译为“查看http响应”，那试一下，重新抓包抓到了，再看一下response居然就写在那里cyberpeace{cc02b489321e14fcf73caeb7dd9a155d}

