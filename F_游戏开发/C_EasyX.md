# EasyX使用

## 图形加载

``` c
#include <
int main(){
    initgraph(400, 800); // 窗口400*800
    IMAGE bk; //图片变量
    loadimage(&bk, "./bk.bmp"); // 加载图片
    putimage(0,0, &bk); // 画图
}
```

