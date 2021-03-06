/*
 把询问[l,r]抽象成一个点(l,r)，题目就转化为求n个点的最小曼哈顿哈密尔顿路；由于这是个NP问题，所以我们希望找到一个稍微劣一点又不是很劣的但是能快速求得方案。莫涛大神在他的论文里使用了二维曼哈顿距离最小生成树
 二维曼哈顿距离最小生成树可以用区域划分法+树状数组/线段树维护区间极值在nlogn的时间复杂度内完成构图，并用Kruskal在n log n时间内求得，但是代码比较繁琐。
 这里介绍一个优美的替代品——分块
 将n个数分成sqrt(n)块
 按区间排序，以左端点所在块内为第一关键字，右端点为第二关键字，进行排序
 也就是以( pos [l],r )排序
 搞得过程是这样的：
 一、i与i+1在同一块内，r单调递增，所以r是O(n)的。由于有n^0.5块,所以这一部分时间复杂度是n^1.5。
 二、i与i+1跨越一块，r最多变化n，由于有n^0.5块，所以这一部分时间复杂度是n^1.5
 三、i与i+1在同一块内时变化不超过n^0.5，跨越一块也不会超过2*n^0.5，不妨看作是n^0.5。由于有n个数，所以时间复杂度是n^1.5
 于是就变成了O(n^1.5)了
*/
