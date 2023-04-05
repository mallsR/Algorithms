//
//  CNode.cpp
//  A_star
//
//  Created by xiaoR on 2023/4/5.
//

#include "CNode.hpp"

//构造函数
CNode::CNode(int iG, int iH, int iF) {
    m_iG = iG;
    m_iH = iH;
    m_iF = iF;
    m_bVisited = false;
    m_paPointToNode = make_pair(-1, -1);
}

void CNode::set_G(int iG) {
    m_iG = iG;
}

int CNode::get_G() {
    return m_iG;
}

void CNode::set_F() {
    m_iF = m_iG + m_iH;
}

int CNode::get_F() {
    return m_iF;
}

void CNode::set_H(int iH) {
    m_iH = iH;
}

int CNode::get_H() {
    return m_iH;
}

void CNode::set_visited(bool bVisited) {
    m_bVisited = bVisited;
}

bool CNode::get_visited() {
    return m_bVisited;
}

// 设置和获取指向
void CNode::set_point(pair<int, int> iTargetPair) {
    m_paPointToNode = iTargetPair;
};

pair<int, int> CNode::get_point() {
    return m_paPointToNode;
};
