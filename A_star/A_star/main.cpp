//
//  main.cpp
//  A_star
//
//  Created by xiaoR on 2023/4/5.
//

#include <iostream>
#include <vector>
#include "CAStar.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // 输入
    int M, N;
    cin >> M >> N;
//    构建AStar对象
    CAStar cAStar(M, N);
//    设置地图
    cAStar.set_map();
//    设置起点与终点
    pair<int, int> iOriginPair;
    pair<int, int> iDestinationPair;
    cin >> iOriginPair.first >> iOriginPair.second;
    cin >> iDestinationPair.first >> iDestinationPair.second;
//    寻找路径
    vector<pair<int, int>> path = cAStar.FindPath(iOriginPair, iDestinationPair);
//    输出路径
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i].first << path[i].second << endl;
    }
    return 0;
}
