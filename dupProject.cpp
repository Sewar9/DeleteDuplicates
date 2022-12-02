#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>
#include <algorithm>
using namespace std;

void getFiles_w(string path, vector<string>& files) { //gets paths of the all the files in the folder (and subfolders)
    intptr_t hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles_w(p.assign(path).append("/").append(fileinfo.name), files);
            }
            else {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
    }
}

void reverseStr(string& str)
{
    int n = str.length();

    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

void removetillDot(string& str) //remove file extention
{
    size_t lastindex = str.find_last_of(".");
    str = str.substr(0, lastindex);
}

void delete_duplicates(vector<string>& files){ //deletes all files which their names end with "(number)",
                                               //but first checks if the original copy still exists in the folder.
    string str2, str4, str5;
    vector <string> fileCopy, files2;
    for (int i=0; i<files.size(); i++){
        fileCopy.push_back(files[i]);
    }
    for (int i=0; i<files.size(); i++){
        str5 = files[i];
        removetillDot(str5);
        int n = str5.length();
        if (str5.at(n-3) == '('){
            if (49 < str5.at(n-2) < 57){
                if (str5.at(n-1) == ')'){
                        continue;
                }
            }
        }
        files2.push_back(str5);
    }


    for(size_t i = 0; i < fileCopy.size(); ++i) {
        removetillDot(files[i]);
        str4 = files[i];
        int n = str4.length();
        if (str4.at(n-3) == '('){
            if (49 < str4.at(n-2) < 57){
                if (str4.at(n-1) == ')'){
                    str2 = files[i];
                    for (int i=0; i<4; i++){
                        str2.pop_back();
                    }

                    if(find (files2.begin(), files2.end(), str2.c_str())== files2.end()){
                        files2.push_back(str2);

                    }
                    else{
                        remove(fileCopy[i].c_str());
                    }
                }
            }
        }
    }


 }


template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
    out << "{";
    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", "<< endl;
    }
    out << "}";
    return out;
}
int main(){

    vector<string> files;
    getFiles_w("c:\\Apps\\se", files);

    for (int i=0; i<files.size(); i++){
        for(auto pos = files[i].find('\\'); pos != string::npos; pos = files[i].find('\\', ++pos))
            files[i].insert(++pos, 1, '\\');
    }

    delete_duplicates(files);

    return 0;

}
