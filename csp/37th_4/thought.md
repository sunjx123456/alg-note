### const
struct block
{
	int val; int l, r;
	int cal()const
	{
		return (l + r) * (r - l + 1) / 2%mod;
	}
};
调用函数也会改变，所以要在函数上写const
### 合并元素
合并数组之间相邻的元素，双指针写法，不需要额外的空间，最后resize(k+1);从k+1开始把元素都销毁，size变成K+1
### reserve
改变vector的物理容量capacity，不用扩容停顿了，扩容需要消耗
### vector的赋值
用swap O(1)时间
