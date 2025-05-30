#include "Head.h"


int change_thing(string filename, string need_change_word, string new_word) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cerr << "�޷����ļ�" << endl;
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

            cout << "�޸ĳɹ���" << endl;
        }
        else {
            cerr << "�ļ���ʽ����δ�ҵ�����" << endl;
        }
    }
    else {
        cerr << "δ�ҵ�" << need_change_word << "�ֶ�" << endl;
    }
    return 0;
}



void removeLinesFromFile(const string& filename, const string& lineToRemove) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("�޷��������ļ�: " + filename);
    }

    string tempFilename = filename + ".tmp";
    ofstream outFile(tempFilename);
    if (!outFile) {
        inFile.close();
        throw runtime_error("�޷�����ʱ�ļ�: " + tempFilename);
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
        throw runtime_error("�޷�ɾ��ԭ�ļ�");
    }

    if (rename(tempFilename.c_str(), filename.c_str())) {
        throw runtime_error("�޷���������ʱ�ļ�");
    }

    cout << "ɾ���� " << removedCount << " ��ƥ������\n";
}