#include "Head.h"


bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

int createFile(string file_name) {
    string houzhui = ".txt";
    // 确保文件名以.txt结尾
    if (file_name.find(houzhui) == string::npos) {
        file_name += houzhui;
    }

    // 检查文件是否已存在
    bool existed = fileExists(file_name);

    ofstream file(file_name, ios::app);
    if (file.is_open()) {
        // 只有文件原本不存在时才打印创建成功
        if (!existed) {
            cout << file_name << "文件创建成功" << endl;
        }
        file.close();
    }
    else {
        cout << "无法打开文件" << endl;
        return -1;
    }
    return 0;
}
