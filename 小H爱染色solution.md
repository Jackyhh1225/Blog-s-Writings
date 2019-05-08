推式子题。

 先考虑$F[x]=x^c$。

 设编号最小的黑球编号为$g$。那么，这个式子的意义就是在$0$到$g-1$随意放$c$个球。

 那么就有：
$$
 Ans=\Sigma_{i=0}^m S(c,i)i!\Sigma_{j=m}^{2m}C_j^m C_m^{m-(j-m)}C_n^{i+j}
$$
 意思就是枚举有$i$个箱子不是空的，枚举$j$表示两次共选了$j$个球，$C_j^m C_m^{m-(j-m)}$表示方案数，$C_n^{i+j}$表示选出$i+j$个位置，前$i$个位置表示$c$个球要放的地方。

 一般地就有：
$$
 \begin{aligned}
 Ans&=\Sigma_{j=m}^{2m}C_j^mC_m^{2m-j}\Sigma_{i=0}^mC_n^{i+j}\Sigma_{k=0}^mi!S(k,i)f_k\\
 &=\Sigma_{j=m}^{2m}C_j^mC_m^{2m-j}\Sigma_{i=0}^mC_n^{i+j}\Sigma_{k=0}^iC_i^k(-1)^{i-k}F(k)
 \end{aligned}
$$
 $\Sigma_{k=0}^iC_i^k(-1)^{i-k}F(k)$可以一遍卷积求，再用一遍卷积合并，统计答案。