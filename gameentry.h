#ifndef GAMEENTRY_H
#define GAMEENTRY_H
#include <iostream>
#include <map>
#include <set>
#include <stdexcpt.h>
using namespace std;

class GameEntry{
private:
    string name;        //Player's name
    int score;          //Player's Score
    int timesPlayed;    //Number of times that the player played
    string password;    //Player's password
public:
    GameEntry(string="", int=0, string="");
    GameEntry(const GameEntry &);
    GameEntry &operator=(const GameEntry &);
    bool operator<(const GameEntry &)const;
    bool operator>(const GameEntry &)const;
    string GetName() const {return name;}
    void SetName(string n) {name = n;}
    int GetScore() const {return score;}
    void SetScore(int s) {score = s;}
    int GetTimesPlayed() const {return timesPlayed;}
    void SetTimesPlayed(int t) {timesPlayed = t;}
    string GetPassword() const {return password;}
    void SetPassword(string p) {password = p;}
    void Print() const;
    void Play(int);
};

class Game{
private:
    multimap<string, GameEntry> scoresMap;
public:
    void Add(GameEntry &);
    void PrintByScore();
    void PrintByMatch();
    void Login(pair<string,GameEntry>);
    void Play(pair<string,GameEntry>, int);
};

class SortCriteria{
public:
    enum criteria {score, match};
private:
    criteria crit;
public:
    SortCriteria(criteria c = score) : crit(c){}
    bool operator() (const GameEntry &G1, const GameEntry &G2)const{
        if(crit == score){
            return G1.GetScore()>G2.GetScore();
        }else{
            return G1.GetTimesPlayed()>G2.GetTimesPlayed();
        }
    }
};
typedef multiset<GameEntry,SortCriteria> multisetSort;

class EmptyMultimap : public runtime_error {
public:
    EmptyMultimap();
};

class NotFound : public runtime_error{
public:
    NotFound();
};

#endif // GAMEENTRY_H
