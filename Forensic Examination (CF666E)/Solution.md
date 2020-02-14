# Forensic Examination

Abstract: You are given a string $S$, and several strings $Ti$, you are to answer in which string $T_x(l\leq x\leq r)$, the substring $S[a,b]$ appeared the most times.

Ideas: Firstly, without hesitation, construct the generalized suffix automaton. To count the appeared time of every substring of $S$, we need to maintain the $Right$ set of each node on SAM with a segment tree. If we can know which node the substring of $S$ corresponds, we will be able to get the answer just by asking the seg-tree. To know that, we can pre-calculate the corresponding nodes of each prefix of $S$. If one prefix doesn't appear in T, we chose the corresponding node of the longest suffix of the prefix. When getting the answer of a substring, we start from a prefix which have the same ending as it. Then we jump the fail link to the node it corresponds and answer the question. There is a few details to consider.

# Something to Notice

- 利用线段树合并，如果查询区间内没有任何元素，可能会返回\{0,0\}，此时必须特判，将答案放进查询区间内。
- 如果询问的串在后缀自动机内没有对应节点(即没有出现过)，应该立即停止，直接输出0，而不应该向上跳fail.
- 匹配时跳到1号节点停止，注意需要维护当前最长匹配长度。