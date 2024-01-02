# 配置

1. root目录：laravel的public目录，入口文件位/public/index.php

2. nginx中配置

   ``` nginx
   // 功能类似鱼将访问地址修改
   # 源地址：http://localhost/index.php
   # 修改后：http://localhost
   location / {
       try_files $uri $uri/ /index.php?$query_string;
   }
   
   location ~ \.php {
       fastcgi_pass 127.0.0.1;
       fastcgi_index index.php;
   }
   ```

   