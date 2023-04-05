//
//  CNode.hpp
//  A_star
//
//  Created by xiaoR on 2023/4/5.
//

#ifndef CNode_hpp
#define CNode_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class CNode{
private:
    int m_iG = INT_MAX, m_iH = INT_MAX, m_iF = INT_MAX;
    bool m_bVisited = false;
    pair<int, int> m_paPointToNode;
public:
    CNode(int iG = INT_MAX, int iH = INT_MAX, int iF = INT_MAX);
    void set_G(int iG);
    int get_G();
//    m_iF = m_iG + m_iH
    void set_F();
    int get_F();
    void set_H(int iH);
    int get_H();
    void set_visited(bool bVisited);
    bool get_visited();
//    设置和获取指向
    void set_point(pair<int, int> iTargetPair);
    pair<int, int> get_point();
};
#endif /* CNode_hpp */
