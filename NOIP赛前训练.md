$\newcommand{ssm}[2]{#1^{\overline{#2}}}$$\newcommand{sf}[2]{\begin{bmatrix}#1\\#2\end{bmatrix}}$$\newcommand{ss}[2]{\begin{Bmatrix}#1\\#2\end{Bmatrix}}$$\newcommand{xjm}[2]{#1^{\underline{#2}}}$

## 9.25

​	搞了一套comet 11。

​	学到一个技巧：$F=\Sigma_if_ix^i\times \xjm i m​$可以转成$F^{(m)}​$的形式

​	学了[DAG计数](G:\blogs\Blog-s-Writings\一些技巧.md)。

​	[cometXR 3C](https://cometoj.com/contest/64/problem/C?problem_id=3520)

​	肯定是把直径中点当根最优，二分数数就行了。

​	[cometXR 3D](https://cometoj.com/contest/64/problem/D?problem_id=3526)

​	一个技巧：把每个点到根的路径上的排名hash起来，问题变成动态维护序列的hash值，再用map或hsh查答案就行了。线段树二分可以一个log

​	[cometXR 3E](https://cometoj.com/contest/64/problem/E?problem_id=3535)

​	一个节点的有d个叶子的树，所有点到根路径的与的和权值个数是$O(d\log V)$的。

​	因为n*d小于1e6所以每个lca可以暴力合并。

## 9.26

​	[最小值](http://192.168.102.138/JudgeOnline/problem.php?cid=1321&pid=0)

​	随机，最小值被覆盖的期望次数为1

​	[字符串](http://192.168.102.138/JudgeOnline/problem.php?cid=1321&pid=1)

​	$F_{i,j}$表示s串用到前i位，匹配了t串前j位。

​	注意到相邻交换的位置不会再被删去或替换，那就有：

​	$cmin(F_{i,j},F_{k-1,l-1}+d+a*(j-l-1)+b*(i-k-1))$

​	[序列](http://192.168.102.138/JudgeOnline/problem.php?cid=1321&pid=2)

​	维护$pre_i$表示上一个颜色是$a_i$的位置。$nxt_i$同理。

​	一段区间的答案就是区间内pre值小于l的个数。

​	修改就是暴力把修改区间内的点暴力删去，然后把这个区间缩成一个点。注意到每次修改操作最多增加一个区间，所以修改次数是线性的。

​	对于询问，就是一个矩形数点，可以分治加扫描线，或者直接树套树。

​	分治：对于一段区间，用前半段的修改求对后半段询问的贡献，然后按左端点排序。

​	**注意：对于一个区间的分裂，加入一个区间，删除一个区间，尽量用函数封装，会好写/调很多！**

## 9.27

​	[Eclipse](http://192.168.102.138/JudgeOnline/problem.php?cid=1320&pid=0)

​	循环节的大小不超过$P^2$，相当于求$A*M^k=B$，其中A，M，B都是矩阵，B的第一位是C，第二位可以枚举，在用bsgs求解，复杂度是$O(\frac{P^2}{B}+BP)$，B为根号P时最优。

​	还要求循环节大小，同样用bsgs求，复杂度是$O(\frac{P^2}{B}+B)$，B取P时最优。

​	注意到BSGS的前提条件是矩阵M可逆，所以要把Y=0的情况判掉，这种情况的循环节大小是$O(P)$的，暴力即可。

​	[Emerald](http://192.168.102.138/JudgeOnline/problem.php?cid=1320&pid=1)

​	用一个结构维护一段区间的答案，要维护：

​	lmx,rmx: 从左边、右边进入能到达的最大值。

​	al[],ar[]: 能到区间左边、右边，且每个权值没有被匹配的个数。

​	pos: 能同时到达左边和右边的位置

​	dl,dr: 区间中的边是不是全部都是往左、右。

​	复杂度：$O(Vn\log n)$

​	[Entropy](http://192.168.102.138/JudgeOnline/problem.php?cid=1320&pid=2)

​	乱搞。

