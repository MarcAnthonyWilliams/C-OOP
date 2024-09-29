//MarcAnthony Williams
//9/24/2024
//Second Edition of the Warrior's Game using classes, data hiding, and encapsulation.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Warrior creates warrior object
// Battle battles two warriors
//Status OUTPUTS the important info

class Warrior{
    class Weapon;
    public:
        friend ostream& operator<<(ostream& os, const Warrior& warrior);
        friend ostream& operator<<(ostream& os, const Warrior::Weapon& warrior);


        Warrior(const string& name, const string& weapon_name, int weapon_power) : name(name), weapon(weapon_name, weapon_power){}

        string get_warrior_name() const{
            return name;
        }
        // bool is_alive() const{
        //     return alive;
        // }
        // bool die(){
        //     alive = false;
        // }

        void assign_weapon(const string& weapon_name, int weapon_power){
            weapon = Weapon(weapon_name, weapon_power);
        }

        int get_strength() const{
            return weapon.get_power();
        }

        void set_strength(int x) {
            weapon.set_power(x);
        }

        string get_weapon_name() const{
            return weapon.get_name();
        }
        
    private:
        class Weapon{
            public:
                Weapon(const string& name, int power) : name(name), power(power){}
                
                int get_power() const{
                    return power;
                }
                string get_name() const{
                    return name;
                }

                void set_power(int x){
                    power = x;
                }
            private:
                string name;
                int power;
        };
        string name;
        //bool alive = true; want to keep this but not really necessary
        Weapon weapon;
};


void commence_war(ifstream& ifs, vector<Warrior>& warriors);
void add_warrior(ifstream& ifs, vector<Warrior>& warriors);
void battle(ifstream& ifs, vector<Warrior>& warriors);
void battle_power_system(const string& warrior_one, const string& warrior_two, vector<Warrior>& warriors, size_t location_one, size_t location_two);
void display_status(const vector<Warrior>& warriors);
bool check_existance(const string& name, const vector<Warrior>& warriors);

//Ostream operators for warriors and their weapons
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon){
    cout << weapon.get_name() << ", " << weapon.get_power();
    return os;
}
ostream& operator<<(ostream& os, const Warrior& warrior){
    cout << "Warrior: " << warrior.name << ", weapon: " << warrior.weapon;
    return os;
}


int main(){
    ifstream ifs;
    vector<Warrior> warriors;
    commence_war(ifs, warriors);

}



//Existence check for pre-existing warriors to ensure no duplicates
bool check_existance(const string& name, const vector<Warrior>& warriors){
    for(const Warrior& warrior : warriors){
        if(warrior.get_warrior_name() == name){
            // warrior of same name already exists
            return true;
        }
    }
    //doesnt exist so false
    return false;
}
// Adds warriors (and their weapons) to the fighting/battle roster.
void add_warrior(ifstream& ifs, vector<Warrior>& warriors){ // need to change for weapon
    string name;
    string weapon_name;
    int power;
    ifs >> name >> weapon_name >> power;

    if(check_existance(name, warriors) == true){
        cerr << "Cannot add warrior. Already exists in roster." << endl;
    }
    else{
        warriors.emplace_back(name, weapon_name, power);
    }
    

}
//Handles all Warrior to Warrior battle logic and outputs (Mutual Anihhilation, Defeats/Victories)
void battle_power_system(const string& warrior_one, const string& warrior_two, vector<Warrior>& warriors, size_t location_one, size_t location_two){
        if(warriors[location_one].get_strength() > 0 && warriors[location_two].get_strength() > 0){
            if(warriors[location_one].get_strength() > warriors[location_two].get_strength()){
                // One > Two -> One reduces, two goes to 0
                cout << warrior_one << " defeats " << warrior_two << endl;
               warriors[location_one].set_strength(warriors[location_one].get_strength() -  warriors[location_two].get_strength());
               warriors[location_two].set_strength(0);
               //warriors[location_two].die();
            }
            else if(warriors[location_one].get_strength() == warriors[location_two].get_strength() && warriors[location_one].get_strength() != 0 && warriors[location_two].get_strength() != 0){
                //Same power, both lose (BUT NOT 0) -> no power
                cout << "Mutual Annihilation: " << warrior_one << " and " << warrior_two << " die at each other's hands." << endl;
                warriors[location_one].set_strength(0);
                warriors[location_two].set_strength(0);
                //warriors[location_one].die();
                //warriors[location_two].die();
            }
            else if(warriors[location_one].get_strength() < warriors[location_two].get_strength()){
                //Opposite of first case
                cout << warrior_two << " defeats " << warrior_one << warriors[location_two].get_strength() << endl;
                warriors[location_two].set_strength(warriors[location_two].get_strength() - warriors[location_one].get_strength());
                warriors[location_one].set_strength(0);
                //warriors[location_one].die();
            }
        }
        //LocOne alive and other dead
        else if(warriors[location_one].get_strength() > 0 && warriors[location_two].get_strength() == 0){
            cout << "He's dead " << warrior_one << endl;
        }
        //LocTwo alive and other dead
        else if(warriors[location_one].get_strength() == 0 && warriors[location_two].get_strength() > 0){
            cout << "He's dead " << warrior_two << endl;
        }
        else{
            //Both have no strength/dead
            cout << "Oh NO! They're both dead! Yuck!" << endl;
        }
}
//Finds the warriors meant to battle, passing those locations to battle_power_system.
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
            if(warriors[i].get_warrior_name() == warrior_one){
                location_one = i;
            }
            else if(warriors[i].get_warrior_name() == warrior_two){
                location_two = i;
            }
        }
        battle_power_system(warrior_one, warrior_two, warriors, location_one, location_two);
    }
    
}
//Displays the status of each warrior in vector utilizing ostream
void display_status(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(const Warrior& warrior : warriors){
        cout << warrior << endl;
    }
}
//Utilizes every other function created to enact the war dynamic between warrior objects.
void commence_war(ifstream& ifs, vector<Warrior>& warriors){
    string command;

    ifs.open("warriors.txt");
    if(!ifs){
        cerr << "Could not open the file.\n";
        exit(1);
    }

    while(ifs >> command){
        if(command == "Warrior"){
            //Add a warrior to roster
            add_warrior(ifs, warriors);
        }
        else if(command == "Battle"){
            //Battle two warriors
            battle(ifs, warriors);

        }
        else if(command == "Status"){
            //Display state of the war
            display_status(warriors);
        }
    }

}