使用pbds库
```c++
#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef long long tp;
typedef tree<tp, null_type, less<tp>, rb_tree_tag, tree_order_statistics_node_update> pbds;
```
`insert(x)`：插入x
`erase(x)`：删除x
`find_by_order(k)`：返回排名为k的的元素是什么（k从0开始）
`order_of_key(x)`：返回元素x的排名（从0开始）
`lower_bound(x)`：求大于等于x的最小值的元素
`upper_bound(x)`：求大于x的最小值的元素
