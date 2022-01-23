#include <bits/stdc++.h>

#include "nlohmann/json.hpp"

#include<fstream>

#include<PriorityQueue.h>

#include <conio.h>

using namespace std;
using json = nlohmann::json;
void SaveConnections(int, string, string, map < string, vector < string >> & , set < string > & );
int readFiles(vector < Users * > & Database, map < string, vector < string >> & graph);
prirityQueue * buildPQ(string, vector < Users * > & , set < string > & );
void printSuggestions(prirityQueue * & , vector < Users * > & );
int main() {
    vector < Users * > Database;
    map < string, vector < string >> graph;

    if (!readFiles(Database, graph)) { //Read The Information From "users.json" When Program Starts
        cout << "Can't Read File\n";
        exit(0);
    }
    while (true) {
        system("cls");
        string id;
        cout << "Enter The ID:";
        cin >> id;
        set < string > Connections;

        SaveConnections(5, id, "-1", graph, Connections); //Get Connections Of Input ID (Till Degree 5 ) & Save It In A Set
        Connections.erase(id);

        prirityQueue * List = buildPQ(id, Database, Connections);

        printSuggestions(List, Database);

        cout << "\nESC--->Finish\nReturn--->Back";
        char c = getch();

        if (c == 27) return 0;
        if (c == 13) continue;
    }

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

prirityQueue * buildPQ(string inputID, vector < Users * > & Database, set < string > & Connections) {
    prirityQueue * tmpPQ = new prirityQueue;
    Users * inputUser = new Users;
    for (auto x: Database) {
        if (x -> id == inputID) {
            inputUser = x;
            break;
        }
    }
    for (const auto & x: Connections) {
        PQEntry * tmpEntry = new PQEntry(x);
        tmpEntry -> CalcScore(inputUser, Database);
        tmpPQ -> Enqueue(tmpEntry);
    }
    return tmpPQ;
}

void printSuggestions(prirityQueue * & List, vector < Users * > & Database) {
    cout <<"\n.:Suggestions:.\n\n";
    for (int i = 0; i < 20; i++) {
        int score = List -> frontScore();
        string tmpID = List -> Dequeue();
        for (auto x: Database) {
            if (x -> id == tmpID) {
                x -> printData();
                cout << "Score:" << score << "\n\n";
                break;
            }
        }
    }
}
