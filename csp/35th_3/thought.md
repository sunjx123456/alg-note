### 包装性
不要都放在main函数中，学会拆分逻辑
### 数据污染问题
erase不是直接得到字符串，而是把原字符串删了，直接得到用substr
substr(起始位置，len（默认为到头）)erase一样
while读入时，最后一个是空的，所以后续不能管最后一个了
### f(const vector<>& v)
前面是类型，引用加在类型后
### 一些感悟
这个题其实也没有难度，只是按照说的做即可，不用像一开始那样绞尽脑汁想为什么意思，按图索骥就行 

函数变量不要用i影响函数里面的循环

在大模拟中，如果需要频繁对超长文本进行切片（例如提取某段长文本的中间一部分进行高频比对），使用 string::substr() 会导致严重的性能问题。
痛点： s.substr(L, len) 每次调用都会在堆内存中重新 new 出一块空间，并把原字符复制过去。如果在大循环里调用，很容易 TLE（超时）。
解法： 使用 std::string_view。他只相当于一个指针加长度
模板代码：
string text = "Patch is damaged. Please check the format.";
// 建立视图（几乎没有任何开销）
string_view sv = text; 
// 切片操作，同样没有任何内存分配
string_view sub_sv = sv.substr(9, 7); // 提取出 "damaged"

