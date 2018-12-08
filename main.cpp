
/**
 * 原博客地址
 * https://blog.csdn.net/u011000290/article/details/51066338
 */

#include <iostream>
#include "HexLexer.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    freopen("./in.txt", "r", stdin);
    freopen("./out.txt", "w", stdout);

    Hex hex(':');
    char ch;
    while (cin >> ch) {
        hex.ParseRecord(ch);
    }
    fclose(stdout);
    fclose(stdin);

    return 0;
}