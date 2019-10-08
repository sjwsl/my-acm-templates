1.Trick
①I\O优化
快速读入与快速输出。

②STL优化
e.g. map、set
手写/pbds

③少调用函数

④使用define优化？道听途说，不准。
2.循环优化

①循环展开
for(int i=1;i<=n;i+=4)
{
    ++a[i];
    ++a[i+1];
    ++a[i+2];
    ++a[i+3];   
}
//处理mod 4剩余部分

②while代替for
应该是有用的。但是大部分时候，for和while的思想也不太一样。不太能直接替换。

③前置++
i++ -> ++i

3.运算优化

①取模优化
可以搭配三目运算符，ret=ret+a>=mod?ret+a-mod:ret+a;

②位运算

4.存储优化：
把循环次数较多的放在后面的维数。把较大的一维放在前面。
因为存储空间是连续的。不断跳一大段也是费时费力的。
矩阵乘法就可以用这个优化。

5.利用系统自带优化
①手动O2，O3，Ofast优化
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")

会CE，但是本地打表可以。

②register
对于大量的for中的i可以变成register

③inline

6.实力卡常数

①zkw线段树

7.用空间优化时间

①如果要对int取模，那么数组可以都用int，运算的时候可以强制转化。
可以省空间省时间。

8.O2
　不开O2：NTT比FFT快 
　开O2：FFT比NTT快

9.常数尽量声明成常量

10.避免使用步长为较大的2的幂的访问模式
　　避免缓存冲突。
　　在状压DP、使用高位数组时很重要
　　解决方法：把数组稍微开大一些