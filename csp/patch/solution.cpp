#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

// N为原文件最大行数，M为最大可能处理的行数（包含补丁行）
const int N = 2050, M = 500100;

int n; // 原文件总行数
string origin[M], patch[M], input; // origin存原文件，patch存过滤后的补丁文本

int modified_in_patch[M]; // 记录原文件的某一行属于哪个补丁块（用于最终输出时替换）
bool printed_patch[M];    // 记录某个补丁块是否已经输出过，防止重复输出

vector<int> out_patch[M]; // 存储每个补丁块最终需要应用到新文件的内容（即 + 和空格开头的行）

// 输出指定的补丁块内容
inline void print_outpatch(int i)
{
    printed_patch[i] = 1; // 标记该补丁块已输出
    // 遍历该补丁块提取出的新文件内容片段并输出
    for (size_t x = 0; x < out_patch[i].size(); ++x) cout << patch[out_patch[i][x]] << '\n';
}

// 最终的合并输出逻辑
inline void output_res()
{
    for (int i = 1; i <= n; ++i) 
    {
        // 如果原文件的第 i 行没有被任何补丁修改，原样输出
        if (!modified_in_patch[i]) cout << origin[i] << '\n';
        // 如果被修改了，且对应的补丁块还没输出过，则输出该补丁块的全部新内容
        else if (modified_in_patch[i] && !printed_patch[modified_in_patch[i]]) print_outpatch(modified_in_patch[i]);
    }
}

// 存储补丁头部信息的结构体：@@ -NN,MM +nn,mm @@
struct info 
{ 
    int NN, MM, nn, mm; 
    inline info(int a = 0, int b = 0, int c = 0, int d = 0) { NN = a, MM = b, nn = c, mm = d; }
};

pair<int, int> blk[M]; // 存储每个补丁块在 patch 数组中的起始和结束行号区间 [first, second]
info binfo[M];         // 存储每个补丁块解析出的 NN, MM, nn, mm 属性
int patch_sz, blk_sz;  // patch_sz: 补丁总有效行数, blk_sz: 补丁块总数

// 校验在给定的偏移位置 NN 下，补丁中要求删除/保留的行（ol）是否与原文件完全一致
inline bool judge(int NN, const vector<int>& ol)
{
    for (size_t i = 0; i < ol.size(); ++i) 
        if (origin[i + NN] != patch[ol[i]]) return 0; // 一旦有不匹配则返回 false
    return 1;
}

// 状态机：解析 @@ -NN,MM +nn,mm @@ 格式，严格要求空格、符号和数字的顺序
inline int nxt_status(int cur, char c) 
{
    switch(cur)
    {
        case 0 : return (c == ' ') ? 1 : -1;
        case 1 : return (c == '-') ? 2 : -1;
        case 2 : return ('1' <= c && c <= '9') ? 3 : -1;
        case 3 : return ('0' <= c && c <= '9') ? 3 : (c == ',') ? 4 : -1;
        case 4 : return ('1' <= c && c <= '9') ? 5 : -1;
        case 5 : return ('0' <= c && c <= '9') ? 5 : (c == ' ') ? 6 : -1;
        case 6 : return (c == '+') ? 7 : -1;
        case 7 : return ('1' <= c && c <= '9') ? 8 : -1;
        case 8 : return ('0' <= c && c <= '9') ? 8 : (c == ',') ? 9 : -1;
        case 9 : return ('1' <= c && c <= '9') ? 10 : -1;
        case 10 : return ('0' <= c && c <= '9') ? 10 : (c == ' ') ? 11 : -1;
        case 11 : return (c == '@') ? 12 : -1;
        default : return -1;
    }
    return -1;
}

// 调用状态机判断第 idx 行（补丁头）格式是否合法
inline bool judge_patch_head(int idx)
{
    string& s = patch[idx];
    if (s.size() <= 4) return 0;
    // 检查首尾是否为 @@
    if (!(s[0] == '@' && s[1] == '@' && s[s.size() - 1] == '@' && s[s.size() - 2] == '@')) return 0;
    int sta = 0, i = 2;
    // 从第3个字符开始送入状态机，直到倒数第3个字符
    for (; i <= s.size() - 2 && sta >= 0; ++i) sta = nxt_status(sta, s[i]);
    return (i == s.size() - 1) && sta == 12; // 必须全部解析完且停在接受状态 12
}

// 提取补丁头中的数字 NN, MM, nn, mm
inline info get_patch(int idx)
{
    string& s = patch[idx];
    // 将非数字字符全部替换为空格，方便后续使用 stringstream 自动按空格分割提取数字
    for (size_t i = 0; i < s.size(); ++i) if (s[i] < '0' || s[i] > '9') s[i] = ' ';
    stringstream ss(s);
    info ret;
    ss >> ret.NN >> ret.MM >> ret.nn >> ret.mm;
    return ret;
}

// 核心逻辑：处理第 i 个补丁块，寻找偏移量并应用
inline bool solve_blk(int i)
{
    // 规则：当前块的起点必须不小于上一个块的终点（NN + MM）
    if (binfo[i].NN < binfo[i - 1].NN + binfo[i - 1].MM) return 0; 

    vector<int> tar_M, tar_m; // tar_M存原文件内容片段(行号)，tar_m存新文件内容片段(行号)
    
    // 遍历当前补丁块内的所有具体修改行
    for (int idx = blk[i].first; idx <= blk[i].second; ++idx)
    {
        string& s = patch[idx];
        // 规则：每一行必须以 -、+ 或空格开头
        if (s[0] != '-' && s[0] != '+' && s[0] != ' ') return 0; 
        
        if (s[0] != '+') tar_M.push_back(idx); // 非+号（即-或空格），属于原文件片段
        if (s[0] != '-') tar_m.push_back(idx); // 非-号（即+或空格），属于新文件片段
        
        s = s.substr(1, s.size() - 1); // 截掉开头的标记符（-, +, 空格），保留纯文本
    } 
    // 规则：提取出的片段行数必须与头部的 MM 和 mm 一致
    if (tar_M.size() != binfo[i].MM || tar_m.size() != binfo[i].mm) return 0; 

    vector<int> subans; // 存储所有能完美匹配原文件的合法偏移量 delta
    
    // 遍历绝对值小于 MM 的所有 delta
    for (int delta = -binfo[i].MM + 1; delta < binfo[i].MM; ++delta)
        // 确保偏移后的起始行加上 delta 后不与上一个补丁块重叠，并且文本能匹配 (judge)
        if (binfo[i].NN + delta >= std::max(1, binfo[i - 1].NN + binfo[i - 1].MM) && judge(binfo[i].NN + delta, tar_M))
            subans.push_back(delta);
    
    // 从所有合法的 delta 中选出绝对值最小的；绝对值相同选最小的（负数）
    int ans_delta = 1919810; // 设一个极大值作为初始值
    for (size_t x = 0; x < subans.size(); ++x)
        if ((abs(subans[x]) < abs(ans_delta)) || (abs(subans[x]) == abs(ans_delta) && subans[x] < ans_delta))
            ans_delta = subans[x];
    
    if (ans_delta == 1919810) return 0; // 如果没找到任何合法的 delta，补丁损坏

    out_patch[i] = tar_m; // 记录该块最终要输出的新文件内容片段
    
    // 标记原文件中被该补丁覆盖的行区间
    for (int x = binfo[i].NN + ans_delta; x < binfo[i].NN + ans_delta + tar_M.size(); ++x) 
        modified_in_patch[x] = i;

    // 当前块产生的偏移，会影响后续所有块的起始位置，所以要把后面的 NN 都加上该 delta
    for (int x = i; x <= blk_sz; ++x) binfo[x].NN += ans_delta;
    return 1;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 优化输入输出速度

    // 读取第一行，获取原文件总行数 n
    getline(cin, input); 
    stringstream ss(input);
    ss >> n;

    // 读取原文件内容
    for (int i = 1; i <= n; ++i) getline(cin, origin[i]);
    
    // 读取补丁文件内容并进行分块
    while (getline(cin, input))
    {
        if (input[0] == '#') continue; // 忽略注释行
        if (input.empty()) break;      // 遇到空行或结束

        patch[++patch_sz] = input; // 存入有效的补丁行
        
        if (input[0] == '@') // 发现新的补丁块头部
        {
            if (blk_sz) blk[blk_sz].second = patch_sz - 1; // 记录上一个补丁块的结束行号
            blk[++blk_sz].first = patch_sz + 1;            // 记录当前新补丁块的内容起始行号
        }
    }
    if (blk_sz) blk[blk_sz].second = patch_sz; // 收尾，记录最后一个补丁块的结束行号

    if (!blk_sz) cout << "Patch is damaged.", exit(0); // 没有任何补丁块，报错

    // 第一遍遍历：解析并校验所有补丁块的头部格式
    for (int i = 1; i <= blk_sz; ++i) 
    {
        if (!judge_patch_head(blk[i].first - 1)) cout << "Patch is damaged.", exit(0); 
        binfo[i] = get_patch(blk[i].first - 1);
    } 

    // 第二遍遍历：逐块进行内容校验并计算偏移量
    for (int i = 1; i <= blk_sz; ++i) 
        if (!solve_blk(i)) cout << "Patch is damaged.", exit(0);
        
    // 若中途未触发 exit(0)，说明全部校验通过，执行合并输出
    output_res(); 
}