//MarcAnthony Williams
//9/19/2024
//First Edition of the Warrior's Game using Structs.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Warrior creates warrior object
// Battle battles two warriors
//Status OUTPUTS the important info

struct Warrior{
   // Warrior(const string& name, int power) : name(name), power(power) {}
    string name;
    int power;
    
};


void commence_war(ifstream& ifs, vector<Warrior>& warriors);
void add_warrior(ifstream& ifs, vector<Warrior>& warriors);
void battle(ifstream& ifs, vector<Warrior>& warriors);
void battle_power_system(const string& warrior_one, const string& warrior_two, vector<Warrior>& warriors, size_t location_one, size_t location_two);
void display_status(vector<Warrior>& warriors);
bool check_existance(const string& name, vector<Warrior>& warriors);


int main(){
    ifstream ifs;
    vector<Warrior> warriors;
    commence_war(ifs, warriors);

}

//Additional Notes Reqs
bool check_existance(const string& name, vector<Warrior>& warriors){
    for(Warrior warrior : warriors){
        if(warrior.name == name){
            // warrior of same name already exists
            return true;
        }
    }
    //doesnt exist so add
    return false;
}

void add_warrior(ifstream& ifs, vector<Warrior>& warriors){
    string name;
    int power;
    ifs >> name >> power;

    if(check_existance(name, warriors) == true){
        cerr << "Cannot add warrior. Already exists in roster." << endl;
    }
    else{ //have to change cause no constructor. Just make obj then edit
        Warrior contestant;
        contestant.name = name;
        contestant.power = power;
        warriors.push_back(contestant);
    }
    

}
void battle_power_system(const string& warrior_one, const string& warrior_two, vector<Warrior>& warriors, size_t location_one, size_t location_two){
    //Handles all power cases. Maybe make battle output func? --> Yup 
        if(warriors[location_one].power > 0 && warriors[location_two].power > 0){
            if(warriors[location_one].power > warriors[location_two].power){
                // One > Two -> One reduces, two goes to 0
                cout << warrior_one << " defeats " << warrior_two << endl;
                warriors[location_one].power -= warriors[location_two].power;
                warriors[location_two].power = 0;
            }
            else if(warriors[location_one].power == warriors[location_two].power && warriors[location_one].power != 0 && warriors[location_two].power != 0){
                //Same power, both lose (BUT NOT 0) -> no power
                cout << "Mutual Annihilation: " << warrior_one << " and " << warrior_two << " die at each other's hands." << endl;
                warriors[location_one].power = 0;
                warriors[location_two].power = 0;
            }
            else if(warriors[location_one].power < warriors[location_two].power){
                //Opposite of first case
                cout << warrior_two << " defeats " << warrior_one << warriors[location_two].power << endl;
                warriors[location_two].power -= warriors[location_one].power;
                warriors[location_one].power = 0;
            }
        }
        else if(warriors[location_one].power > 0 && warriors[location_two].power == 0){
            cout << "He's dead " << warrior_one << endl;
        }
        else if(warriors[location_one].power == 0 && warriors[location_two].power > 0){
            cout << "He's dead " << warrior_two << endl;
        }
        else{
            //Both have no strength
            cout << "Oh NO! They're both dead! Yuck!" << endl;
        }
}
void battle(ifstream& ifs, vector<Warrior>& warriors){
    size_t location_one;
    size_t location_two;
    string warrior_one;
    string warrior_two;

    ifs >> warrior_one >> warrior_two;
    if(check_existance(warrior_one, warriors) == false || check_existance(warrior_two, warriors) == false){
        cerr << "One or both warriors do not exist within roster. Cannot commence battle.";
    }
    else if(check_existance(warrior_one, warriors) == true && check_existance(warrior_two, warriors) == true){
        cout << warrior_one << " battles " << warrior_two << endl;

        for(size_t i = 0; i < warriors.size(); i++){
            if(warriors[i].name == warrior_one){
                location_one = i;
            }
            else if(warriors[i].name == warrior_two){
                location_two = i;
            }
        }
        battle_power_system(warrior_one, warrior_two, warriors, location_one, location_two);
    }
    
}

void display_status(vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(Warrior warrior : warriors){
        cout << "Warrior: " << warrior.name <<", strength: " << warrior.power << endl;
    }
}

void commence_war(ifstream& ifs, vector<Warrior>& warriors){
    string command;
    

    do{
        ifs.open("warriors.txt");
        if(!ifs){
            cerr << "Could not open the file.\n";
            exit(1);
        }
    }while(!ifs);

    while(ifs >> command){
        if(command == "Warrior"){
            //make add warrior func
            add_warrior(ifs, warriors);
        }
        else if(command == "Battle"){
            //make battle func
            battle(ifs, warriors);

        }
        else if(command == "Status"){
            //make display/status func
            display_status(warriors);
        }
    }

}