#include "Head.h"


bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

int createFile(string file_name) {
    string houzhui = ".txt";
    // ȷ���ļ�����.txt��β
    if (file_name.find(houzhui) == string::npos) {
        file_name += houzhui;
    }

    // ����ļ��Ƿ��Ѵ���
    bool existed = fileExists(file_name);

    ofstream file(file_name, ios::app);
    if (file.is_open()) {
        // ֻ���ļ�ԭ��������ʱ�Ŵ�ӡ�����ɹ�
        if (!existed) {
            cout << file_name << "�ļ������ɹ�" << endl;
        }
        file.close();
    }
    else {
        cout << "�޷����ļ�" << endl;
        return -1;
    }
    return 0;
}
