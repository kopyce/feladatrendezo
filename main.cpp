//includeok
#include <iostream>
#include <fstream>
#include "single_include/nlohmann/json.hpp"

//konnyebben hashznaljak neveket
using json = nlohmann::json;
using namespace std;

//valtozok
const int max_task = 50;
int loadedTasks;
int hova=0;
int indexe;
bool on;
int selection;
int delindexe;
string thing;
string todolist[max_task][2];
ofstream outputFile;
json jsonTodoList; 

//egyetlen funkciom my beloved
int lookfor(string cucc){
    for (int index=0; index< max_task; index++) {
        if(todolist[index][0]==cucc){
            return index; 
        }
    }
    return -1;
}


//main
int main() {
    //feltolteni semmivel a listat
    for (int i = 0; i < max_task; i++) {
        todolist[i][0] = "";
        todolist[i][1] = ""; 
    }
    //elozetes baszakodasok
    hova=0;
    cout << "konpany feladat beosztokaja";
    on=true;
    ifstream inputFile; 
    //baszott nagy while loop
    while(on){
    
    cout << "\n 0 kilepeshez, 1 hozzaadashoz, 2 hogy kesznek jelold, 3 hogy torold, 4 hogy listazd, 5 a betolteshez \n";

    try {
    selection = 0;
    cin >> selection;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Invalid input. Please enter a number.");
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //megnezni mit tehetek
    switch (selection)
    {
    //kilepes es mentes
    case 0:
    jsonTodoList;
    for (int i = 0; i < max_task; i++) {
        json item;
        item["task"] = todolist[i][0];
        item["status"] = todolist[i][1];
        jsonTodoList.push_back(item);
    }

    outputFile.open("feladatok.json");
    outputFile << jsonTodoList.dump(4); 
    outputFile.close();

    on = false;
    break;
    //hozza adasa a cuccnak
    case 1:
        cout << "hozzaadando feladat neve: ";
        getline(cin, thing);
        if (!thing.empty()) {
        if (hova < max_task) {
            todolist[hova][0] = thing;
            todolist[hova][1] = "nemkesz";
            hova++; 
        } else {
            cout << "tele van a lista." << endl;
        }
        } else {
            cout << "adj nevet is neki." << endl;
        }
        break;
    //feladat kesznek jelolese
    case 2:
        cout<<"kesznek jelolendo feladat neve\n";
        getline(cin, thing);
        indexe= lookfor(thing);
        if(indexe!=-1){
            if(todolist[indexe][1]=="nemkesz"){
                todolist[indexe][1]="kesz";
            }else{
                todolist[indexe][1]="nemkesz";
            }
            cout << "allapot frissitve.";
        }else{
            cout << "nincs megtalalva";
        }
        break;
    //feladat torlese
    case 3:
        cout << "torolni valo feladat: ";
                getline(cin, thing);
                delindexe = lookfor(thing);
                if (delindexe != -1) {
                    for (int i = delindexe; i < max_task - 1; i++) {
                        todolist[i][0] = todolist[i + 1][0];
                        todolist[i][1] = todolist[i + 1][1];
                    }
                    hova--;
                    cout << "torolve.\n";
                } else {
                    cout << "nincs megtalalva\n";
                }
                break;
    //feladatok kiirasa (csak azok amikbe van is valami)
    case 4:
    for(int i = 0; i < max_task; i++){
        if(todolist[i][0]!=""){
        cout << "feladat: " << todolist[i][0] << ", keszvan-e: " << todolist[i][1] << endl;
    }
    }
    cout << hova << "/" << max_task;
    break;
    //feladatok betoltese
    case 5:
        inputFile.open("feladatok.json");
        if (!inputFile.is_open()) {
            cout << "nem tudtam megnyitni :(" << endl;
        } else {
            try {
                json jsonTodoList;
                inputFile >> jsonTodoList;
                loadedTasks=0;
                for (int i = 0; i < max_task && i < jsonTodoList.size(); i++) {
                    todolist[i][0] = jsonTodoList[i]["task"];
                    todolist[i][1] = jsonTodoList[i]["status"];
                    if (!todolist[i][0].empty()) {
                    loadedTasks++; // Increment the count of loaded tasks
                }
                }
                hova = loadedTasks;
                cout << "betoltve." << endl;
            } catch (const json::parse_error& e) {
                cout << "hiba. " << e.what() << endl;
            }
            inputFile.close();
        }
        break;
    //apa
    case 1971:
        cout<<"szia apa!";
        break;        
    //anya
    case 1970:
        cout<< "szia anya!";
        break;
    //balfasz es rosszat ir be
    default:
        cout<<"nemjo opciot irtal :(";
        break;
    }
    //nemtudom mi
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
  }
  return 0;
}