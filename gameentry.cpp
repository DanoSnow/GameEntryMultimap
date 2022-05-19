#include "gameentry.h"
#include <iomanip>
#include <algorithm>

GameEntry::GameEntry(string n, int s, string p) : name(n), score(s), password(p){timesPlayed = 0;}

GameEntry::GameEntry(const GameEntry &G){
    name = G.GetName();
    score = G.GetScore();
    timesPlayed = G.GetTimesPlayed();
    password = G.GetPassword();
}

GameEntry &GameEntry::operator=(const GameEntry &G){
    name = G.GetName();
    score = G.GetScore();
    timesPlayed = G.GetTimesPlayed();
    password = G.GetPassword();
    return *this;
}

bool GameEntry::operator<(const GameEntry &G)const{
    if(password<G.password){
        return true;
    }else{
        return false;
    }
}

bool GameEntry::operator>(const GameEntry &G)const{
    if(password>G.password){
        return true;
    }else{
        return false;
    }
}

void GameEntry::Print() const{
    cout<<left<<setw(20)<<GetName()<<setw(25)<<GetScore()<<GetTimesPlayed()<<endl;
}

void GameEntry::Play(int s){
    if(s>score){
        score = s;
    }
    timesPlayed++;
}

void Game::Add(GameEntry &G){
    scoresMap.insert(pair<string,GameEntry>(G.GetPassword(),G));
}

void Game::PrintByScore(){
    if(!scoresMap.empty()){
        multisetSort scoresSet;
        for(multimap<string,GameEntry>::iterator it=scoresMap.begin();it!=scoresMap.end();it++){
            scoresSet.insert(it->second);
        }
        cout<<"Top 5 ranking by score"<<endl
           <<left<<setw(20)<<"Name"<<setw(20)<<"Score"<<setw(20)<<"Times played"<<endl;
        int count = 0;
        multisetSort::iterator it_s = scoresSet.begin();
        while(count<5 && it_s!=scoresSet.end()){
            it_s->Print();
            count++;
            it_s++;
        }
        cout<<endl;
    }else{
        throw EmptyMultimap();
    }
}

void Game::PrintByMatch(){
    if(!scoresMap.empty()){
        SortCriteria criteria(SortCriteria::match);
        multisetSort matchSet(criteria);
        for(multimap<string,GameEntry>::iterator it=scoresMap.begin();it!=scoresMap.end();it++){
            matchSet.insert(it->second);
        }
        cout<<"Top 5 ranking by score"<<endl
            <<left<<setw(20)<<"Name"<<setw(20)<<"Score"<<setw(20)<<"Times played"<<endl;
        int count = 0;
        multisetSort::iterator it_m = matchSet.begin();
        while(count<5 && it_m!=matchSet.end()){
            it_m->Print();
            count++;
            it_m++;
        }
        cout<<endl;
    }else{
        throw EmptyMultimap();
    }
}

void Game::Login(pair<string, GameEntry> G){
    if(scoresMap.empty()){
        throw EmptyMultimap();
    }
    multimap<string,GameEntry>::iterator it = find_if(scoresMap.begin(),scoresMap.end(),
                                                      [=](pair<string,GameEntry> G1){
        return G.second.GetName()==G1.second.GetName() && G.first==G1.first;
    });
    if(it!=scoresMap.end()){
        cout<<"Welcome back "<<G.second.GetName()<<endl;
    }else{
        throw NotFound();
    }
}

void Game::Play(pair<string,GameEntry> G, int s){
    multimap<string,GameEntry>::iterator it = find_if(scoresMap.begin(),scoresMap.end(),
                                                      [=](pair<string,GameEntry> G1){
        return G.second.GetName()==G1.second.GetName() && G.first==G1.first;
    });
    it->second.Play(s);
}

EmptyMultimap::EmptyMultimap() : runtime_error ("Empty multimap"){}

NotFound::NotFound() : runtime_error("Player not found"){}
