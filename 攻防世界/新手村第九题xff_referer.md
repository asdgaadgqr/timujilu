新手村第九题xff_referer

X老师告诉小宁其实xff和referer是可以伪造的。

这道题多半是要伪造xff和referer，以前伪造过本地IP这次也应该是差不多的做法。打开题目要求是ip地址必须为123.123.123.123，抓包发送给重发器，然后伪造一个**X-Forwarded-For: 123.123.123.123放在中间发送得到一个新的界面。或者是直接使用插件伪造。显示必须来自https://www.google.com继续进行伪造Referer:https://www.google.com发送得到答案。

cyberpeace{790aed5b3e4167414434be6ba5091280}