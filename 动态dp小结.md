# 动态dp小结

​	处理一类带修改dp的方法。

​	例子：noip2018 保卫王国，luogu 动态dp模板题，sdoi2017 切树游戏。

​	利用矩阵乘法的性质快速合并两段序列的dp值即，不过将矩阵乘法的加法改成取min/max，乘法改成加法，还可能是维护dp的系数（例子：切树游戏）。通过线段树维护区间的矩阵乘积，一般还会套上树剖。

​	时间复杂度：$O(n\log n)\to O(n\log^2n)$。（lct/全局平衡二叉树、树剖）

​	记录一个模板：

```c++
void gao(int x,int y)
{
	val[x]=y;
	update matrix of x
	while(x){
		int tp,l,r;
		Seg::qry f of tp
		if(fa[tp]){
			update fl of fa[tp]
		}
		Seg::qry f of tp
		if(fa[tp]){
			update fl of fa[tp]
			update matrix of fa[tp]
		}
		x=fa[tp]
	}
}
```

需要注意的点：

1.线段树上矩阵乘法的顺序为倒序。

2.如果一个询问要修改好几处的值，最好按dfn序来修改（例子：保卫王国）