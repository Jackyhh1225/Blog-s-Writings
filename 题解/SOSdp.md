# SOSdp

​	

​	在CF上做题遇到了一道SOSdp，研究了一下，发现这其实是高维前后缀和，一般可以用fwt来加速这一过程。这里就记几道例题。

​	1.[CF1208F](https://codeforces.com/contest/1208/problem/F)

​	考虑枚举i,那么要求的就是高维后缀和。要动态加入，记忆化就行了。

​	2.[E. Compatible Numbers](https://codeforces.com/contest/165/problem/E)

​	高维前缀和，记录一下从哪来的就行了。

​	3.[E - Vowels ](https://codeforces.com/contest/383/problem/E)

​	容斥后做高维后缀和。

​	4.[Covering Sets CodeChef - COVERING](https://vjudge.net/problem/CodeChef-COVERING)

​	求和，那就计算A(i)*B(j)\*C(i)的贡献，做fwt或卷积就行了。

​	5.[D. Jzzhu and Numbers](https://codeforces.com/problemset/problem/449/D)

​	与卷积

​	6.[COCI 2011/2012 Problem KOSARE](http://hsin.hr/coci/archive/2011_2012/contest6_tasks.pdf)

​	或卷积

​	7.[hackrank subsets](https://www.hackerrank.com/contests/countercode/challenges/subset/problem)

​	分块，加枚举子集

​	8.[Jersey Number](https://www.codechef.com/problems/AMR14F/)

​	状压，预处理每个区间的值，容斥后跟3一样

​	9.[Beautiful Sandwich](https://www.codechef.com/SNFL16MR/problems/BEAUTY)

​	跟上一题有点像，预处理删掉每个单词后的贡献，做高维前缀和就行了。计算贡献就是对每一个a，加上2*下一段a的长度。

​	10.[Uchiha Brothers and Two Products ](https://www.hackerearth.com/problem/algorithm/uchiha-brothers-and-two-products-circuit/)

​	高维前缀和，把加法改一下就行了，在高维前缀差分。

​	12.[Strange Functions](https://www.codechef.com/IPC15P2B/problems/STR_FUNC)

​	这题不能fwt，要SOSDP。

​	维护$\Sigma G$和$\Sigma F^2$

​	13.[D. Varying Kibibits](https://codeforces.com/contest/800/problem/D)

​	维护子集完全平方和的和。高维后缀和。

​	设集和的大小为n，集合元素和为S，集合元素平方和为T，子集完全平方和的和为$2^{n-2}(S^2+T)$。证明大概就是对每个元素单独考虑，把枚举出来的子集合补成大集合。

