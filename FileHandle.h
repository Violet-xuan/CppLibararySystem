#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#pragma once
bool removeIdFromFile(const string& filename, const int& targetId) {
    // 1. 读取文件内容到 vector
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    vector<string> lines;
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    string tmpstr=std::to_string(targetId);
    // 2. 查找并删除目标 ID
    auto it = find(lines.begin(), lines.end(),tmpstr);
    if (it == lines.end()) {
        cerr << "ID " << targetId << " not found in " << filename << endl;
        return false;
    }
    lines.erase(it);

    // 3. 重新写入文件
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return false;
    }

    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();
    return true;
}