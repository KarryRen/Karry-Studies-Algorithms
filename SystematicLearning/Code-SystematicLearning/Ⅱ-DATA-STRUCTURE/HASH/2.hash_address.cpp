/*
    @author Karry 
    @date on 2023/8/20.
    @comment Day 20 开放寻址法实现 hash 表
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 200003; // 大于 2 * 1e5 的第一个质数
const int null = 0X3f3f3f3f; // 用一个不可能出现的数标识 hash 表的坑是空的

int h[N]; // hash 表数组

/*
 * 在 hash 表中找到数 x
 * 如果 x 存在就返回 x 的下标
 * 如果 x 不存在就返回 x 应该存储的下标
 */
bool find(int x) {
    // 先求出来映射值
    int k = (x % N + N) % N;

    // 从头开始在单链表中进行寻找
    while (h[k] != null && h[k] != x) {
        k++; // 如果不是空而且还不相等，说明没有找到，那就继续往后面找
        if (k == N) k = 0; // 如果找到了尾部，就回到开头
        // 直到找到目的下标
    }

    return k;
}

int main() {
    int n;
    cin >> n;

    // 初始化哈希表，让每一个坑都为空
    // memset这个函数是按字节来赋值的，int 有 4 个字节，所以把每个字节都赋值成 0x3f 以后就是 0x3f3f3f3f
    memset(h, 0x3f, sizeof(h));

    string op; // 操作符
    int x; // 操作数
    while (n--) {
        cin >> op >> x;
        int k = find(x);
        if (op == "I") h[k] = x; // 插入操作：如果之前没有插入过 x 那么直接在应该插入的位置赋值即可；如果之前已经插入过 x 了，再赋值一遍也无所谓
        else if (op == "Q") {
            if (h[k] != null) cout << "Yes" << endl; // 如果存在返回的就应该是之前插入的位置
            else cout << "No" << endl; // 否则该插入的位置的数值一定是空
        } else cout << "Wrong Input" << endl;
    }

    return 0;
}
