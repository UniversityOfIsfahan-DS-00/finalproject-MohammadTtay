#include <bits/stdc++.h>

#include "nlohmann/json.hpp"

#include"Users.h"

#include<fstream>

using namespace std;
using json = nlohmann::json;

int readFiles(vector < Users * > & Database);
int main() {
    vector < Users * > Database;

    if (!readFiles(Database)) { //Read The Information From "users.jason" When Program Starts
        return 0;
    }

    for (auto x: Database) x -> printData();

    return 0;
}

int readFiles(vector < Users * > & Database) {
    ifstream file("../users.json");
    if (file.is_open()) {
        char temp;
        string tempLine;
        while (true) {
            file >> temp;
            if (temp == ']') break;
            getline(file, tempLine, '}');
            tempLine.push_back('}');

            Users * tempUser = new Users(json::parse(tempLine));
            Database.push_back(tempUser);

        }

        file.close();
        return 1;
    } else return 0;

}
