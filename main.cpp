#include <iostream>
#include "gameentry.h"
using namespace std;

int main()
{
    int opcion_principal, opcion_login, opcion_play, s;
    string n, p, p_confirm;
    GameEntry player, newplayer;
    Game G;
    cout<<"1- Login\n"<<"2- Show top 5 ranking by score\n"
       <<"3- Show top 5 ranking by times played\n"
      <<"4- Exit\n";
    cin>>opcion_principal;
    while(opcion_principal != 4){
        switch(opcion_principal){
        case 1:
            cout<<"1- Autenticate\n"<<"2- New player\n"<<"3- Back\n";
            cin>>opcion_login;
            while(opcion_login!=3){
                switch(opcion_login){
                case 1:
                    //To autenticate an existent player
                    cout<<"Name: ";
                    cin>>n;
                    cout<<"Password: ";
                    cin>>p;
                    player = newplayer;
                    player.SetName(n);
                    player.SetPassword(p);
                    try{
                        G.Login({p,player});
                    }catch(EmptyMultimap &empty){
                        cout<<"Runtime exception: "<<empty.what()<<endl;
                        break;
                    }catch(NotFound &notfound){
                        cout<<"Runtime exception: "<<notfound.what()<<endl;
                        break;
                    }//When both exceptions are thrown it goes back to Login menu
//once autenticated there's a new menu to play or not
                    cout<<"\n1- Play\n"<<"2- Back\n";
                    cin>>opcion_play;
                    while(opcion_play!=2){
                        switch(opcion_play){
                        case 1:
                            cout<<"What score did you get? ";
                            cin>>s;
                            G.Play({p,player},s);
                            break;
                        case 2:
                            //Return to login menu
                            break;
                        default:
                            cout<<"Incorrect input\n";
                        }
                        cout<<"\n1- Play\n"<<"2- Back\n";
                        cin>>opcion_play;
                    }
                    break;
                case 2:
                    //To add a new player
                    cout<<"Name: ";
                    cin>>n;
                    cout<<"Password: ";
                    cin>>p;
                    cout<<"Confirm your passoword: ";
                    cin>>p_confirm;
                    while(p!=p_confirm){
                        cout<<"Please type the confirmation of your password again: ";
                        cin>>p_confirm;
                    };
                    player = newplayer;
                    player.SetName(n);
                    player.SetPassword(p);
                    G.Add(player);
                    break;
                case 3:
                    //Return to main menu
                    break;
                default:
                    cout<<"Incorrect input\n";
                }
                cout<<"\n1- Autenticate\n"<<"2- New player\n"<<"3- Back\n";
                cin>>opcion_login;
            }
            break;
        case 2:
            try{
                G.PrintByScore();
            }catch(EmptyMultimap &empty){
                cout<<"Runtime excepetion: "<<empty.what()<<endl;
            }
            break;
        case 3:
            try{
                G.PrintByMatch();
            }catch(EmptyMultimap &empty){
                cout<<"Runtime excepetion: "<<empty.what()<<endl;
            }
            break;
        case 4:
            break;
        default:
            cout<<"Incorrent input\n";
            break;
        }
        cout<<"\n1- Login\n"<<"2- Show top 5 ranking by score\n"
           <<"3- Show top 5 ranking by times played\n"
          <<"4- Exit\n";
        cin>>opcion_principal;
    }
    cout<<"\nSuccesful quit\n";
    getchar();
    return 0;
}
