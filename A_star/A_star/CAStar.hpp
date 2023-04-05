//
//  CAStar.hpp
//  A_star
//
//  Created by xiaoR on 2023/4/5.
//

#ifndef CAStar_hpp
#define CAStar_hpp

#include <vector>
#include "CPathFinding.h"
#include "CNode.hpp"

using namespace std;

vector<vector<CNode>> NoMapTempArray;

// A_star算法类
class CAStar : public CPathFinding{
private:
    //    地图大小
    int m_iMapRow = 0, m_iMapCol = 0;
    vector<vector<int>> m_iMapArray;
public:
//    暂定为公有的
    vector<vector<CNode>> m_NoMapArray;
    CAStar(int iRow, int iCol);
    void set_map();
    void set_map(vector<vector<int>> & iMapArray);
    void set_NoMap();
    void set_NoMap(vector<vector<CNode>> & NoMapArray);
    vector<vector<CNode>> get_NoMap();
    vector<pair<int, int>> FindPath(const pair<int, int> iOriginPair, const pair<int, int> iDestinationPair);
    int ComputeDistance(pair<int, int> iOriginPair, pair<int, int> iDestinationPair);
    friend bool compare(pair<int, int> node1, pair<int, int> node2);
    ////    静态排序比较
//    static bool compare(pair<int, int> node1, pair<int, int> node2) {
////        通过比较节点的G值来排序
//        if ((static)get_NoMap()[node1.first][node1.second].get_G() < (static)get_NoMap()[node2.first][node2.second].get_G()) {
//            return true;
//        } else {
//            return false;
//        }
//    }
};
//    全局排序比较
bool compare(pair<int, int> node1, pair<int, int> node2) {
//        通过比较节点的G值来排序
    if (NoMapTempArray[node1.first][node1.second].get_G() < NoMapTempArray[node2.first][node2.second].get_G()) {
        return true;
    } else {
        return false;
    }
}

#endif /* CAStar_hpp */
