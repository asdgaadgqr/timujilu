```php
 <?php
    error_reporting(0);
    highlight_file(__FILE__);
    include_once 'flag.php';
    $fir = $_GET['fir'];//get传参给fir
    if (isset($_GET['fir'])){//判断是否给fir传值
        if ($fir == md5($fir)){//fir的原值和md5加密后的值相等
            echo $flag1;//前两个条件都成立回显flag1
        }
    } 
```

$fir == md5($fir)查到fir的值为0e215962017

http://10.1.114.1:20000/?fir=0e215962017

得到` `TheFlagFi1e.php

访问该文件

需要输入正确的密码

使用字典爆破没有试出密码

sqlmap跑不出来

甚至于找不到注入点

f12在注释中发现<!--        md5加密，很安全！-->

查到ffifdyop和129581926211651571912466741651878684928

在经过md5加密以后会组成sql语句

select password from xxxx where password =' ' or 'xxx'

就可以成功绕过

nice, give you the flag!

# flag{74f3002433d36d6465fddecd52af9422}                    