#include <bits/stdc++.h>

#include<vector>

#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Users {
public:
    string id;
    string Name;
    string Birthday;
    string University, FOStudy, Workplace;
    vector < string > Skills;
    vector < string > Connections;

    Users(json temp) {

        this -> id = temp["id"];
        this -> Name = temp["name"];
        this -> Birthday = temp["dateOfBirth"];
        this -> University = temp["universityLocation"];
        this -> FOStudy = temp["field"];
        this -> Workplace = temp["workplace"];
        vector < string > a = temp["specialties"];
        this -> Skills = a;
        vector < string > b = temp["connectionId"];
        this -> Connections = b;

    }

    Users() {}
    void printData() {
        cout << "ID:" << this -> id << endl;
        cout << "Name:" << this -> Name << endl;
        cout << "Birthday:" << this -> Birthday << endl;
        cout << "University:" << this -> University << endl;
        cout << "Field Of Study:" << this -> FOStudy << endl;
        cout << "Workplace:" << this -> Workplace << endl;

        cout << "Skills:" << endl;
        for (auto y: this -> Skills) cout << y << " ";
        cout << endl;

        cout << "Connections:" << endl;
        for (auto y: this -> Connections) cout << y << " ";
        cout << "\n\n";
    }

};
