//
//  CAStar.cpp
//  A_star
//
//  Created by xiaoR on 2023/4/5.
//

#include <iostream>
#include "CAStar.hpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include "CNode.hpp"

using namespace std;

// 构造函数
CAStar::CAStar(int iRow, int iCol) {
    m_iMapRow = iRow;
    m_iMapCol = iCol;
    for (int i = 0; i < m_iMapRow; ++i) {
        m_iMapArray.emplace_back(vector<int> (m_iMapCol, 0));
        m_NoMapArray.emplace_back(vector<CNode> (m_iMapCol, CNode()));
    }
}

//设置地图
void CAStar::set_map() {
    for (int i = 0; i < m_iMapRow; ++i) {
//        vector<int> temp(m_iMapCol, 0);
        for (int j = 0; j < m_iMapCol; ++j) {
            cin >> m_iMapArray[i][j];
        }
//        m_iMapArray.emplace_back(temp);
    }
}

void CAStar::set_map(vector<vector<int>> & iMapArray) {
    m_iMapArray = iMapArray;
}

//设置节点
void CAStar::set_NoMap() {
//    for (int i = 0; i < m_iMapRow; ++i) {
//        vector<int> temp(m_iMapCol, 0);
//        for (int j = 0; j < m_iMapCol; ++j) {
//
//        }
//        m_NoMapArray.emplace_back(temp);
//    }
}
void CAStar::set_NoMap(vector<vector<CNode>> & NoMapArray) {
    m_NoMapArray = NoMapArray;
}

vector<vector<CNode>> CAStar::get_NoMap() {
    return m_NoMapArray;
}

//计算两个点的距离
int CAStar::ComputeDistance(pair<int, int> iOriginPair, pair<int, int> iDestinationPair) {
    return fabs(iOriginPair.first - iDestinationPair.first) * 10 + fabs(iOriginPair.second - iDestinationPair.second) * 10;
}

//bool CAStar::compare(pair<int, int> node1, pair<int, int> node2) {
//    
//}

//根据给定起点和终点查找路径
vector<pair<int, int>> CAStar::FindPath(const pair<int, int> iOriginPair, const pair<int, int> iDestinationPair) {
//    设置9个位置的坐标offset
    vector<pair<int, int>> paCoordinateOffsetVec = {{-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 0}, {0, 1},
        {1, -1}, {1, 0}, {1, 1},
    };
//    保存最终路径
    vector<pair<int, int>> paPathVec;
//    开放列表：用于存储可能需要探索的点
    vector<pair<int, int>> paOpenListVec;
//    封闭队列：用于存储已经探索过，不需要再关注的点
    vector<pair<int, int>> paCloseListVec;
//    初始设置
    paOpenListVec.emplace_back(iOriginPair);
    m_NoMapArray[iOriginPair.first][iOriginPair.second].set_visited(true);
    m_NoMapArray[iOriginPair.first][iOriginPair.second].set_G(0);
    m_NoMapArray[iOriginPair.first][iOriginPair.second].set_H(ComputeDistance(iOriginPair, iDestinationPair));
    m_NoMapArray[iOriginPair.first][iOriginPair.second].set_F();
    pair<int, int> iCurrPos(-1, -1);
//  当OpenList不空，且当前位置不是Destination，则需要一直迭代；
    while (iCurrPos != iDestinationPair && !paOpenListVec.empty()) {
        iCurrPos = paOpenListVec.front();
//        paPathVec.emplace_back(paOpenListVec.begin());
//        已经访问到终点，可以返回路径信息
        if (iCurrPos == iDestinationPair) {
            return paPathVec;
        }
//        遍历当前节点的周围节点
//        保证依据周围节点的G值，从小到大入队
        for(int i = 0; i < 9; ++i) {
            pair<int, int> paOffset = paCoordinateOffsetVec[i];
            pair<int, int> paNextPos(iCurrPos.first + paOffset.first, iCurrPos.second + paOffset.second);
//            超出边界
            if (paNextPos.first < 0 || paNextPos.first >= m_iMapRow || paNextPos.second < 0 || paNextPos.second >= m_iMapCol){
                continue;
            }
//            是否为路障
            if (m_iMapArray[paNextPos.first][paNextPos.second] == 1) {
                continue;
            }
//            如果已经在CloseList中，则跳过
            if (find(paCloseListVec.begin(), paCloseListVec.end(), paNextPos) != paCloseListVec.end()) {
                continue;
            }
//                已经访问过
            if (m_NoMapArray[paNextPos.first][paNextPos.second].get_visited()) {
//                通过计算G判断，是否需要更新G、F值
                int iCurrG = m_NoMapArray[iCurrPos.first][iCurrPos.second].get_G();
                if ((i + 1) & 1 == 1) {
                    iCurrG += 14;
                } else {
                    iCurrG += 10;
                }
//                通过这个当前点，计算得到的G小于之前的G，则进行更新
                if (m_NoMapArray[paNextPos.first][paNextPos.second].get_G() > iCurrG) {
                    m_NoMapArray[paNextPos.first][paNextPos.second].set_G(iCurrG);
                    m_NoMapArray[paNextPos.first][paNextPos.second].set_F();
//                    NextPos 指向 CurrPos
                    m_NoMapArray[paNextPos.first][paNextPos.second].set_point(iCurrPos);
//                   ⚠️改变已经在OpenList中节点的G，需要重新队OpenList中节点，按从小到大进行排序
//                    但此处有点问题，快排的compare必须是全局函数或者静态成员函数，其无法访问，非静态数据成员m_NoMapArray;
//                    所以采用随时拷贝的方式。
                    NoMapTempArray = get_NoMap();
                    sort(paOpenListVec.begin(), paOpenListVec.end(), compare);
                }
                continue;
            }
//            是否已经在paOpenListQue中
//            if (find(paOpenListVec.begin(), paOpenListVec.end(), paNextPos)!= paOpenListVec.end()) {
//                continue;
//            }
//            直接设置G、H、F
            if ((i + 1) & 1 == 1) {
                m_NoMapArray[paNextPos.first][paNextPos.second].set_G(m_NoMapArray[iCurrPos.first][iCurrPos.second].get_G() + 14);
            } else {
                m_NoMapArray[paNextPos.first][paNextPos.second].set_G(m_NoMapArray[iCurrPos.first][iCurrPos.second].get_G() + 10);
            }
            m_NoMapArray[paNextPos.first][paNextPos.second].set_H(ComputeDistance(iCurrPos, iDestinationPair));
            m_NoMapArray[paNextPos.first][paNextPos.second].set_F();
//            设置为已经访问
            m_NoMapArray[paNextPos.first][paNextPos.second].set_visited(true);
//            NextPos 值向 CurrPos
            m_NoMapArray[paNextPos.first][paNextPos.second].set_point(iCurrPos);
            paOpenListVec.emplace_back(paNextPos);
            NoMapTempArray = get_NoMap();
            sort(paOpenListVec.begin(), paOpenListVec.end(), compare);
        }
//         出队
        paCloseListVec.emplace_back(paOpenListVec.begin());
        paOpenListVec.erase(paOpenListVec.begin());
    }
//    通过所指方向，计算路径
    if (iCurrPos == iDestinationPair) {
        cout << "find path." << endl;
    } else {
        cout << "not find path" << endl;
    }
    while (iCurrPos != iOriginPair) {
        paPathVec.emplace_back(iCurrPos);
        iCurrPos = m_NoMapArray[iCurrPos.first][iCurrPos.second].get_point();
    }
    return paPathVec;
}
