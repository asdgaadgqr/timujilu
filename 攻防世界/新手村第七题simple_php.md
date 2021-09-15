新手村第七题simple_php

小宁听说php是最好的语言,于是她简单学习之后写了几行php代码。

打开题目看到是一串代码

```
﻿<?php 
﻿show_source(__FILE__); 
﻿include("config.php");  
﻿$a=@$_GET['a']; 
﻿$b=@$_GET['b']; 
﻿if($a==0 and $a){   
﻿echo $flag1;
 } 
 if(is_numeric($b)){
 exit();
 } 
 if($b>1234){  
 echo $flag2; 
 } 
 ?> 
```

很显然是get传输，那直接在网址后面输入就行了。

要a和b同时输出才能得到flag。在PHP中如果a=d5421则a=0，如果b为数字或字符那么就会返回当b=1987s，则b=1987>1234且b不为数字或字符。所以输入/?a=d5421&b=1987s得到Cyberpeace{647E37C7627CC3E4019EC69324F66C7C}