#include <bits/stdc++.h>

#include "nlohmann/json.hpp"

#include"Users.h"

#include<fstream>

using namespace std;
using json = nlohmann::json;
void SaveConnections(int, string, string, map < string, vector < string >> & , set < string > & );
int readFiles(vector < Users * > & Database, map < string, vector < string >> & graph);
int main() {
    vector < Users * > Database;
    map < string, vector < string >> graph;
    set < string > Connections;
    string id;
    cin >> id;

    if (!readFiles(Database, graph)) { //Read The Information From "users.json" When Program Starts
        cout << "Can't Read File\n";
        exit(0);
    }
    SaveConnections(5, id, "-1", graph, Connections);//Get Connections Of Input ID (Till Degree 5 ) & Save It In A Set
    Connections.erase(id);

    for (const auto & x: Connections) cout << x << endl;
    return 0;
}

int readFiles(vector < Users * > & Database, map < string, vector < string >> & graph) {
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
            vector < string > tmp = tempUser -> Connections;
            graph.insert(pair < string, vector < string >> (tempUser -> id, tempUser -> Connections));
            Database.push_back(tempUser);

        }

        file.close();
        return 1;
    } else return 0;

}

void SaveConnections(int k, string node, string parent, map < string, vector < string >> & graph, set < string > & Connections) {

    if (k < 0)
        return;

    Connections.insert(node);

    for (const auto & i: graph[node]) {

        if (i != parent) {

            SaveConnections(k - 1, i, node, graph, Connections);
        }
    }
}
