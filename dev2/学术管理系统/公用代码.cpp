#include "Head.h"


int change_thing(string filename, string need_change_word, string new_word) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cerr << "无法打开文件" << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();


    size_t pos = content.find(need_change_word + "=");
    if (pos != string::npos) {

        pos += need_change_word.length() + 1;


        size_t comma_pos = content.find(',', pos);
        if (comma_pos != string::npos) {

            content.replace(pos, comma_pos - pos, new_word);


            ofstream outFile(filename);
            outFile << content;
            outFile.close();

            cout << "修改成功！" << endl;
        }
        else {
            cerr << "文件格式错误：未找到逗号" << endl;
        }
    }
    else {
        cerr << "未找到" << need_change_word << "字段" << endl;
    }
    return 0;
}



void removeLinesFromFile(const string& filename, const string& lineToRemove) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("无法打开输入文件: " + filename);
    }

    string tempFilename = filename + ".tmp";
    ofstream outFile(tempFilename);
    if (!outFile) {
        inFile.close();
        throw runtime_error("无法打开临时文件: " + tempFilename);
    }

    string line;
    size_t removedCount = 0;
    while (getline(inFile, line)) {
        if (line != lineToRemove) {
            outFile << line << "\n";
        }
        else {
            removedCount++;
        }
    }

    inFile.close();
    outFile.close();

    if (remove(filename.c_str())) {
        throw runtime_error("无法删除原文件");
    }

    if (rename(tempFilename.c_str(), filename.c_str())) {
        throw runtime_error("无法重命名临时文件");
    }

    cout << "删除了 " << removedCount << " 行匹配内容\n";
}