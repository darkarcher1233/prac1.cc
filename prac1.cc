#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <cstring> // Para strcpy(), strcat() y strcmp()

using namespace std;

const int kTEAMNAME=40; // Máximo tamaño del nombre de un equipo
const int kPLAYERNAME=50; // Máximo tamaño del nombre de un jugador
const int kPLAYERS=5; // Número de jugadores por equipo
const int kMAXTEAMS=20; // Número máximo de equipos
const int kMINTEAMS=2; // Número mínimo de equipos

// Registro para los jugadores
struct Player{
    char name[kPLAYERNAME];
    unsigned int goals;
    bool best;
};

// Registro para los equipos
struct Team{
    unsigned int id;
    char name[kTEAMNAME];
    unsigned int wins;
    unsigned int losses;
    unsigned int draws;
    unsigned int points;
    Player players[kPLAYERS];
    //nuevas adaptaciones:
    int totalGoals = 0;
    int receivedGoals = 0;
};


// Tipos de error posibles
enum Error{
    ERR_EMPTY,
    ERR_MAX_TEAMS,
    ERR_NO_LEAGUE,
    ERR_NO_TEAMS,
    ERR_NOT_EXIST,
    ERR_NUM_TEAMS,
    ERR_OPTION
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada 
*/
void error(Error e){
    switch(e){
        case ERR_EMPTY: cout << "ERROR: empty string" << endl;
            break;
        case ERR_MAX_TEAMS: cout << "ERROR: maximum number of teams reached" << endl;
            break;
        case ERR_NO_LEAGUE: cout << "ERROR: there are no standings" << endl;
            break;
        case ERR_NO_TEAMS: cout << "ERROR: there are no teams" << endl;
            break;
        case ERR_NOT_EXIST: cout << "ERROR: team does not exist" << endl;
            break;
        case ERR_NUM_TEAMS: cout << "ERROR: wrong number of teams" << endl;
            break;
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
    }
}

/* Función que simula los goles marcados por los jugadores
team: equipo para el que vamos a simular los goles marcados
return: número de goles totales del equipo
*/

int simulateGoals(Team &team){
    int goals=0;
    
    for(int i=0;i<kPLAYERS;i++){
        int goal=rand()%2;
        team.players[i].goals+=goal;
        goals+=goal;
    }

    return goals;
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu(){
    cout << "1- Add team" << endl
         << "2- Add all teams" << endl
         << "3- Delete team" << endl
         << "4- Show teams" << endl
         << "5- Play league" << endl
         << "6- Show standings" << endl
         << "7- Show best players" << endl
         << "8- Edit players" << endl
         << "q- Quit" << endl
         << "Option: ";
}
//NEW

int searchTeam(Team equipos[], int numTeams, char name[kTEAMNAME]){
    bool found = false;
    int teamId = -1;
    for(int i = 0; i < numTeams && found == false; i++){
        if(strcmp(name, equipos[i].name) == 0){
            teamId = equipos[i].id;
            found = true;
        }
    }

    return teamId;
}

void addPlayers(Team &equipo){

    for(int i = 0; i < kPLAYERS; i++){ 
        sprintf(equipo.players[i].name, "%s-R%d", equipo.name, i + 1);
        equipo.players[i].goals = 0;
        equipo.players[i].best = false; 
    }

}
void addTeam(Team equipos[], int &numTeams, int &nextId){

    equipos[numTeams].id = nextId;

    bool keepGoing = true;
    do{
        if(numTeams >= kMAXTEAMS){
            error(ERR_MAX_TEAMS);
            keepGoing = false;
        }

        else{
            cout << "Enter team name:";
            cin.getline(equipos[numTeams].name, kTEAMNAME);

            if(strlen(equipos[numTeams].name) == 0){
                sprintf(equipos[numTeams].name, "Team_%d", equipos[numTeams].id);
            }
            equipos[numTeams].wins = 0;
            equipos[numTeams].losses = 0;
            equipos[numTeams].draws = 0;
            equipos[numTeams].points = 0;
            equipos[numTeams].totalGoals = 0;
            equipos[numTeams].receivedGoals = 0;

            addPlayers(equipos[numTeams]);

            numTeams ++;
            nextId++;

            keepGoing = false;

        }

    }while(keepGoing);

}

void addAllTeams(Team equipos[], int &numTeams, int &nextId, bool &played){

    bool keepGoing = true;
    char option = 'Y';
    int num;

    do{

        if(numTeams > 0){
            do{
                cout << "Do you want to delete existing teams (y/n)? ";
                cin >> option;
                cin.ignore();
                
            }while(option != 'y' && option != 'Y' && option != 'n' && option != 'N');

            if(option == 'n' || option == 'N'){
                keepGoing = false;
            }
            else{
                do{
                    nextId = 0;
                    played = false;

                    cout << "Enter number of teams: ";
                    cin >> num;
                    cin.ignore();

                    if(num < 2 || num > kMAXTEAMS){
                        error(ERR_NUM_TEAMS);
                    }
                }while(num < 2 || num > kMAXTEAMS);

                numTeams = num;

                for(int i = 0; i < numTeams; i++){
    
                    equipos[i].id = nextId;
                    sprintf(equipos[i].name, "Team_%d" , equipos[i].id);
    
                    equipos[i].wins = 0;
                    equipos[i].losses = 0;
                    equipos[i].draws = 0;
                    equipos[i].points = 0;
                    equipos[i].totalGoals = 0;
                    equipos[i].receivedGoals = 0;

                    addPlayers(equipos[i]);
    
                    nextId++;
    
                }
                keepGoing = false;
            }     
        }

        else{

            nextId = 0;
            do{
                cout << "Enter number of teams: ";
                cin >> num;
                if(num < 2 || num > kMAXTEAMS){
                    error(ERR_NUM_TEAMS);
                }
            }while(num < 2 || num > kMAXTEAMS);

            numTeams = num;

            for(int i = 0; i < numTeams; i++){

                equipos[i].id = nextId;
                sprintf(equipos[i].name, "Team_%d" , equipos[i].id);

                equipos[i].wins = 0;
                equipos[i].losses = 0;
                equipos[i].draws = 0;
                equipos[i].points = 0;

                addPlayers(equipos[i]);

                nextId++;

            }
            keepGoing = false;
        }
    }while(keepGoing);
}

void deleteTeam(Team equipos[], int &numTeams){
    bool keepGoing = true;
    char name[kTEAMNAME];
    int pos = -1;

    do{
        if(numTeams == 0){
            error(ERR_NO_TEAMS);
            keepGoing = false;
        }
        else{

            cout << "Enter team name: ";
            cin.getline(name, kTEAMNAME);

            if (strlen(name) == 0){
                error(ERR_EMPTY);
                keepGoing = false;
            } 
            else{
                pos = searchTeam(equipos, numTeams, name);

                if(pos == -1){
                    error(ERR_NOT_EXIST);
                } 
                
                else {
                    // Eliminar desplazando a la izquierda
                    for (int i = pos; i < numTeams - 1; i++){
                        equipos[i] = equipos[i + 1];
                    }
                    numTeams = numTeams - 1;
                    keepGoing = false;
                }
            }
        }
    } while (keepGoing);
}


void showTeams(Team equipos[], int numTeams){
    
    bool keepGoing = true, exists;
    char name[kTEAMNAME];
    int id;

    do{
        if(numTeams == 0){
            error(ERR_NO_TEAMS);
            keepGoing = false;
        }

        else{
            do{
                cout << "Enter team name: ";
                cin.getline(name, kTEAMNAME);

                
                id = searchTeam(equipos, numTeams, name);
                

                if(id == -1 && strlen(name) != 0){
                    exists = false;
                    error(ERR_NOT_EXIST);
                }
                else{
                    exists = true;
                }
            }while(!exists);

            if(strlen(name) == 0){
                for(int i = 0; i < numTeams; i++){

                    cout << "Name: " << equipos[i].name << endl
                         << "Wins: " << equipos[i].wins << endl
                         << "Losses: " << equipos[i].losses << endl
                         << "Draws: " << equipos[i].draws << endl
                         << "Points: " << equipos[i].points << endl;
    
                    //print players:
                    for(int j = 0; j < kPLAYERS; j++){
                        cout << equipos[i].players[j].name << ": " 
                             << equipos[i].players[j].goals << " goals" << endl;
                    }
                }
                keepGoing = false;
            }

            else{

                cout << "Name: " << equipos[id].name << endl
                << "Wins: " << equipos[id].wins << endl
                << "Losses: " << equipos[id].losses << endl
                << "Draws: " << equipos[id].draws << endl
                << "Points: " << equipos[id].points << endl;

                //print players:
                for(int i = 0; i < kPLAYERS; i++){
                    cout << equipos[id].players[i].name << ": " 
                         << equipos[id].players[i].goals << " goals" << endl;
                }
                keepGoing = false;
            }
            
            
        }
    }while(keepGoing);
}

void setTeamValues(Team equipos[], int numTeams){ // !!!
    for(int i = 0; i < numTeams; i++){
        equipos[i].wins = 0;
        equipos[i].losses = 0;
        equipos[i].draws = 0;
        equipos[i].points = 0;

        // NEW
        equipos[i].totalGoals = 0;
        equipos[i].receivedGoals = 0;

        //Players
        for(int j = 0; j < kPLAYERS; j++){
            equipos[i].players[j].goals = 0;
            equipos[i].players[j].best = false;
        }
    }
}

void bestPlayer(Team &equipo){
    int best = 0; 

    for(int i=0; i < kPLAYERS; i++){

        if(equipo.players[i].goals > equipo.players[best].goals){
            best = i; 
        }
    }
    equipo.players[best].best=true;
}


void playLeague(Team equipos[], int numTeams, bool &played){

    bool keepGoing = true;
    do{
        if (numTeams < kMINTEAMS) {
            error(ERR_NUM_TEAMS);
            keepGoing = false;
        }
        
        else{

            played = true;
            setTeamValues(equipos, numTeams); // Reiniciar todos los valores (incluyendo totalGoals y receivedGoals)

            for(int i = 0; i < numTeams; i++) {
                for(int j = i + 1; j < numTeams; j++) {
                    int golesEquipo1 = simulateGoals(equipos[i]);
                    int golesEquipo2 = simulateGoals(equipos[j]);

                    // Actualizar totalGoals y receivedGoals (goles recibidos)
                    equipos[i].totalGoals += golesEquipo1;
                    equipos[i].receivedGoals += golesEquipo2;
                    equipos[j].totalGoals += golesEquipo2;
                    equipos[j].receivedGoals += golesEquipo1;


                    // Lógica de puntos (wins/losses/draws)
                    if (golesEquipo1 > golesEquipo2) {
                        equipos[i].wins++;
                        equipos[i].points += 3;
                        equipos[j].losses++;
                    } else if (golesEquipo1 < golesEquipo2) {
                        equipos[j].wins++;
                        equipos[j].points += 3;
                        equipos[i].losses++;
                    } else {
                        equipos[i].draws++;
                        equipos[i].points++;
                        equipos[j].draws++;
                        equipos[j].points++;
                    }
                }
                bestPlayer(equipos[i]);
            }
            keepGoing = false;
        }
    }while(keepGoing);
}

void copyTeamStrings(Team copy[kMAXTEAMS], Team original[kMAXTEAMS], int numTeams){
    
    for(int i = 0; i < numTeams; i++) {
        strcpy(copy[i].name, original[i].name);
        copy[i].wins = original[i].wins;
        copy[i].draws = original[i].draws;
        copy[i].losses = original[i].losses;
        copy[i].points = original[i].points;
        //NEW
        copy[i].totalGoals = original[i].totalGoals;
        copy[i].receivedGoals = original[i].receivedGoals;
        // Copiar jugadores 
        for(int j = 0; j < kPLAYERS; j++) {
            strcpy(copy[i].players[j].name, original[i].players[j].name);
            copy[i].players[j].goals = original[i].players[j].goals;
            copy[i].players[j].best = original[i].players[j].best;
        }
    
    }
}

void sorterName(Team equipos[], int numTeams){

    Team orderedTeams[kMAXTEAMS];
    copyTeamStrings(orderedTeams, equipos, numTeams);


    for(int i = 0; i < numTeams - 1; i++){
        for(int j = 0; j < numTeams - i - 1; j++){
            if(strcmp(orderedTeams[j].name, orderedTeams[j + 1].name) < 0){

                Team temp = orderedTeams[j];
                orderedTeams[j] = orderedTeams[j + 1];
                orderedTeams[j + 1] = temp;
            }
        }
    }
    for(int i = 0; i < numTeams; i++){
        cout << orderedTeams[i].name << "|"
             << orderedTeams[i].wins << "|"
             << orderedTeams[i].draws << "|"
             << orderedTeams[i].losses << "|"
             << orderedTeams[i].totalGoals << "|";

            // print símbolo +/- :
        if((orderedTeams[i].totalGoals -  orderedTeams[i].receivedGoals) < 0){
                cout << "-";
        }
        
        if((orderedTeams[i].totalGoals -  orderedTeams[i].receivedGoals) > 0){
                cout << "+";
        }
        cout << orderedTeams[i].totalGoals -  orderedTeams[i].receivedGoals<< "|"
             << orderedTeams[i].points << endl;
    }
    
}

void sorterWins(Team equipos[], int numTeams){

    Team orderedTeams[kMAXTEAMS];

    copyTeamStrings(orderedTeams, equipos, numTeams);
    int diff;

    for(int i = 0; i < numTeams - 1; i++){
        for(int j = 0; j < numTeams - i - 1; j++){
            if(orderedTeams[j].wins < orderedTeams[j + 1].wins){

                Team temp = orderedTeams[j];
                orderedTeams[j] = orderedTeams[j + 1];
                orderedTeams[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < numTeams; i++){
        cout << orderedTeams[i].name << "|"
             << orderedTeams[i].wins << "|"
             << orderedTeams[i].draws << "|"
             << orderedTeams[i].losses << "|"
             << orderedTeams[i].totalGoals << "|";

        diff = orderedTeams[i].totalGoals -  orderedTeams[i].receivedGoals;

            // print símbolo +/- (el '-' ya se pone solo al ser una varable no unsingned):
        
        if(diff > 0){
                cout << "+";
        }
        cout << diff << "|" << orderedTeams[i].points << endl;
    }
}

void sorterDraws(Team equipos[], int numTeams){

    Team orderedTeams[kMAXTEAMS];

    copyTeamStrings(orderedTeams, equipos, numTeams);
    int diff;

    for(int i = 0; i < numTeams - 1; i++){
        for(int j = 0; j < numTeams - i - 1; j++){
            if(orderedTeams[j].draws < orderedTeams[j + 1].draws){

                Team temp = orderedTeams[j];
                orderedTeams[j] = orderedTeams[j + 1];
                orderedTeams[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < numTeams; i++){
        cout << orderedTeams[i].name << "|"
             << orderedTeams[i].wins << "|"
             << orderedTeams[i].draws << "|"
             << orderedTeams[i].losses << "|"
             << orderedTeams[i].totalGoals << "|";

        diff = orderedTeams[i].totalGoals -  orderedTeams[i].receivedGoals;

            // print símbolo +/- (el '-' ya se pone solo al ser una varable no unsigned):
        
        if(diff > 0){
                cout << "+";
        }
        cout << diff << "|" << orderedTeams[i].points << endl;
    }
}

void sorterLosses(Team equipos[], int numTeams){

    Team orderedTeams[kMAXTEAMS];

    copyTeamStrings(orderedTeams, equipos, numTeams);
    int diff;

    for(int i = 0; i < numTeams - 1; i++){
        for(int j = 0; j < numTeams - i - 1; j++){
            if(orderedTeams[j].losses < orderedTeams[j + 1].losses){

                Team temp = orderedTeams[j];
                orderedTeams[j] = orderedTeams[j + 1];
                orderedTeams[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < numTeams; i++){
        cout << orderedTeams[i].name << "|"
             << orderedTeams[i].wins << "|"
             << orderedTeams[i].draws << "|"
             << orderedTeams[i].losses << "|"
             << orderedTeams[i].totalGoals << "|";

        diff = orderedTeams[i].totalGoals -  orderedTeams[i].receivedGoals;

            // print símbolo +/- (el '-' ya se pone solo al ser una varable no unsingned):
        
        if(diff > 0){
                cout << "+";
        }
        cout << diff << "|" << orderedTeams[i].points << endl;
    }
}

void sorterPoints(Team equipos[], int numTeams){

    Team orderedTeams[kMAXTEAMS];

    copyTeamStrings(orderedTeams, equipos, numTeams);
    int diff;

    for(int i = 0; i < numTeams - 1; i++){
        for(int j = 0; j < numTeams - i - 1; j++){
            if(orderedTeams[j].points < orderedTeams[j + 1].points){

                Team temp = orderedTeams[j];
                orderedTeams[j] = orderedTeams[j + 1];
                orderedTeams[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < numTeams; i++){
        cout << orderedTeams[i].name << "|"
             << orderedTeams[i].wins << "|"
             << orderedTeams[i].draws << "|"
             << orderedTeams[i].losses << "|"
             << orderedTeams[i].totalGoals << "|";

        diff = orderedTeams[i].totalGoals -  orderedTeams[i].receivedGoals;

            // print símbolo +/- (el '-' ya se pone solo al ser una varable no unsingned):
        
        if(diff > 0){
                cout << "+";
        }
        cout << diff << "|" << orderedTeams[i].points << endl;
    }
}



void showStandings(Team equipos[], int numTeams, bool played){

    bool keepGoing = true;
    Team orderedTeams[kMAXTEAMS];
    char criterion;
    

    //COpiar el vector de equipos en el vector orderedTeams
    copyTeamStrings(orderedTeams, equipos, numTeams); 

    do{
        if(!played){
            error(ERR_NO_LEAGUE);
            keepGoing = false;
        }

        else{
            do{
                cout << "Enter sorting criterion (N/W/D/L/P):";
                cin.get(criterion);

                if(criterion == '\n'){
                    criterion = 'P';
                }

               if(criterion != 'N' && criterion != 'n' 
                    && criterion != 'W' && criterion != 'w' 
                    && criterion != 'D' && criterion != 'd'
                    && criterion != 'L' && criterion != 'l'
                    && criterion != 'P' && criterion != 'p'){
                        error(ERR_OPTION);
                    }

            }while(criterion != 'N' && criterion != 'n' 
                   && criterion != 'W' && criterion != 'w' 
                   && criterion != 'D' && criterion != 'd'
                   && criterion != 'L' && criterion != 'l'
                   && criterion != 'P' && criterion != 'p');

            switch(criterion){
                case 'P':
                case 'p':
                    sorterPoints(equipos, numTeams);
                    break;
                case 'N':
                case 'n':
                    sorterName(equipos, numTeams);
                    break;
                case 'W':
                case 'w':
                    sorterWins(equipos, numTeams);
                    break;
                case 'D':
                case 'd':
                    sorterDraws(equipos, numTeams);
                    break;

                case 'L':
                case 'l':
                    sorterLosses(equipos, numTeams);
                    break;
            }
            keepGoing = false;

        }

    }while(keepGoing);

}

void showBestPlayers(Team equipos[], int numTeams, bool played){

    bool keepGoing = true;
    do{
        if(!played){
            error(ERR_NO_LEAGUE);
            keepGoing = false;
        }
        else{
            for(int i = 0; i < numTeams; i++){

                cout << equipos[i].name << "|";

                for(int j = 0; j < kPLAYERS; j++){
                    if(equipos[i].players[j].best == true){
                        cout << equipos[i].players[j].name << "|" 
                             << equipos[i].players[j].goals << endl;
                    }
                }
            }
            keepGoing = false;
        }

    }while(keepGoing);
}

void editPlayers(Team equipos[], int &numEquipos){
    char nombreEquipo[kTEAMNAME];
    char changedName[kPLAYERNAME];
    bool keepGoing = true, foundTeam = false;
    
    do{
        if(numEquipos == 0){
            error(ERR_NO_TEAMS);
            keepGoing = false;
        }
        else{
            cout << "Enter team name: ";
            cin.getline(nombreEquipo, kTEAMNAME);
            
            if(strlen(nombreEquipo) == 0){

                error(ERR_EMPTY);
                keepGoing = false;
            }
            

            else{
                for(int i = 0; i < numEquipos && !foundTeam; i++){

                    if(strcmp(equipos[i].name, nombreEquipo) == 0){
                        foundTeam = true;

                        for(int j = 0; j < kPLAYERS; j++){
                            cout << equipos[i].players[j].name << endl
                                 << "New name:";

                            cin.getline(changedName, kPLAYERNAME);
                        
                            strncpy(equipos[i].players[j].name, changedName, kPLAYERNAME);

                            //Agregar null al final del string
                            equipos[i].players[j].name[kPLAYERNAME-1] = '\0';
                            
                        }
                    }
                }
                if(!foundTeam){

                    error(ERR_NOT_EXIST);
                }
                else{

                    keepGoing = false;
                }
            }
        }
    }while(keepGoing);
}
// Función principal. Tendrás que añadir más código tuyo
int main(){

    Team teams[kMAXTEAMS]; //ADDED: vector de Team

    char option;
    int numTeams = 0, nextId = 0;
    bool played = false;

    srand(888); // Fija la semilla del generador de números aleatorios. ¡NO TOCAR!
    
    do{
        showMenu();
        cin >> option;
        cin.ignore(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función "addTeam" para añadir un nuevo equipo
                addTeam(teams, numTeams, nextId);
                break;
            case '2': // Llamar a la función "addAllTeams" para añadir todos los equipos de una vez
                addAllTeams(teams, numTeams, nextId, played);
                break;
            case '3': // Llamar a la función "deleteTeam" para borrar un equipo
            deleteTeam(teams, numTeams);
                break;
            case '4': // Llamar a la función "showTeams" para mostrar los datos de los equipos
                showTeams(teams, numTeams);
                break;
            case '5': // Llamar a la función "playLeague" para simular los resultados de la competición
                playLeague(teams, numTeams, played);
                break;
            case '6': // Llamar a la función "showStandings" para mostrar la clasificación final
            showStandings(teams, numTeams, played);
                break;
            case '7': // Llamar a la función "showBestPlayers" para mostrar los mejores jugadores de cada equipo
            showBestPlayers(teams, numTeams, played);
                break;
            case '8':
                editPlayers(teams, numTeams);
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
