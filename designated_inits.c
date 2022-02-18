/**
 * @file designated_inits.c
 * @author b1tg (https://b1tg.github.io)
 * @brief designated inits in C
 * @version 0.1
 * @date 2022-02-18
 * 
 */

// https://c.godbolt.org/
// https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html


#include <stdio.h>

#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

// basic:
// int a[6] = { [4] = 29, [2] = 15 };
// 等价于
// int a[6] = { 0, 0, 15, 0, 29, 0 };
// 未提到的默认初始化为 0

char *week[] = {
    [SUN] = "Sunday",
    [MON] = "Monday",
    [TUE] = "Tuesday",
    [WED] = "Wednesday",
    [FRI] = "Friday", // order not matters
    [THU] = "Thursday",
    [SAT] = "Saturday",
};

// 一个 unsigned char 的范围是 0-255，因此可用于字符分类
int whitespace[256] = {[' '] = 1, ['\t'] = 1, ['\h'] = 1, ['\f'] = 1, ['\n'] = 1, ['\r'] = 1};

int is_whitespace(unsigned char chr)
{
    return whitespace[chr];
}

struct point
{
    unsigned int x;
    unsigned int y;
};
int main()
{
    printf("%s\n", week[SUN]);

    for (int i = 0; i < 256; i++)
    {
        printf("%x ", whitespace[i]);
    }
    printf("\n");
    printf("%d %d\n", is_whitespace('\n'), is_whitespace('c'));

    // 初始化数组中的某个结构体
    struct point ptarray[3] = {[2].y = 0xbe, [2].x = 0xef, [0].x = 0xde};
    for (int i = 0; i < 3; i++)
    {
        printf("ptarray[%d] { x=0x%x, y=0x%x }\n", i, ptarray[i].x, ptarray[i].y);
    }
}

// Sunday
// 0 0 0 0 0 0 0 0 0 1 1 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 1 0
// ptarray[0] { x=0xde, y=0x0 }
// ptarray[1] { x=0x0,  y=0x0 }
// ptarray[2] { x=0xef, y=0xbe }
