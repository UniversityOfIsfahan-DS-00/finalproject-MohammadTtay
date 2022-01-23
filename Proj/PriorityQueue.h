#include<iostream>

#include<Users.h>

using namespace std;

class PQEntry {
public:
    string id;
    int degree;
    int score;
    PQEntry * next;
    PQEntry * prev;

    PQEntry() {
        id = "";
        score = 0;
        next = nullptr;
        prev = nullptr;
    }
    PQEntry(string id, int degree) {
        this -> id = id;
        this -> degree = degree;
        score = 0;
        this -> next = nullptr;
        this -> prev = nullptr;
    }
    void CalcScore(Users * input, vector < Users * > & Database) {
        Users * temp = new Users;
        for (auto x: Database) {
            if (x -> id == this -> id) {
                temp = x;
                break;
            }
        }
        for (auto x: input -> Skills) {
            for (auto y: temp -> Skills) {
                if (x == y) this -> score += 100;
            }
        }
        if (input -> FOStudy == temp -> FOStudy) this -> score += 50;
        if (input -> University == temp -> University) this -> score += 25;
        if (input -> Workplace == temp -> Workplace) this -> score += 12;

        this ->score += degree;

    }

};

class prirityQueue {
public:
    PQEntry * header;
    PQEntry * trailer;
    int size = 0;

    prirityQueue() {
        this -> header = new PQEntry();
        this -> trailer = new PQEntry();
        this -> header -> next = this -> trailer;
        this -> trailer -> prev = this -> header;
    }

    void Enqueue(PQEntry * entry) {

        if (size == 0) {
            entry -> next = trailer;
            entry -> prev = header;

            header -> next = entry;
            trailer -> prev = entry;
        } else {
            PQEntry * walk = trailer -> prev;
            while (walk != header) {
                if (entry -> score < walk -> score) {
                    entry -> next = walk -> next;
                    entry -> prev = walk;

                    walk -> next = entry;
                    entry -> next -> prev = entry;
                    break;
                }
                walk = walk -> prev;
            }
            if (walk == header) {
                entry -> next = walk -> next;
                entry -> prev = walk;

                walk -> next = entry;
                entry -> next -> prev = entry;
            }

        }
        size++;

    }
    string Dequeue() {
        if (size == 0) return "";
        string temp = header -> next -> id;
        header -> next = header -> next -> next;
        header -> next -> prev = header;

        size--;

        return temp;
    }
    int frontScore() {
        if (size == 0) return NULL;
        return header -> next -> score;
    }

};
