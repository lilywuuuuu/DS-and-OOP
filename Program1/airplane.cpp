#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

int flag;
int a_id = -1, b_id = -1, c_id = -1, d_id = -1;
int maxFuel = 10;
int maxLanding = 4;
int maxTakeoff = 4;
int timeUnit = 500;
float numOfLands = 0;
float numOfEmergencyLands = 0;
float numOfCrahes = 0;
float numOfTakeoff = 0;
float landingTime = 0;
float takeoffTime = 0;
float fuelSaved = 0;
unsigned seed;

typedef struct landing{
    int id;
    int fuel;
    int waitTime = 0;
    struct landing *next;
} Landing;

typedef struct takeoff{
    int id;
    int waitTime= 0;
    struct takeoff *next;
} Takeoff;

int random(int);
int randomFuel(int);
bool isEmptyLanding(landing *&);
void newLanding(landing *&, landing *&, int);
void normalLanding(landing *&);
void emergencyLanding(landing *&, landing *&, landing *&, landing *&, landing *&);
void addTimeLanding(landing *&);
void determineLanding(landing *&, landing *&, landing *&, landing *&, landing *&);
void deleteEmergencyLanding(landing *&);
bool isEmptyTakeoff(Takeoff *&);
void newTakeoff(Takeoff *&, Takeoff *&, int);
void addTimeTakeoff(Takeoff *&);
void normalTakeoff(Takeoff *&);
void deleteTakeoff(Takeoff *&head);
int runwayUsage(landing *, landing *, Takeoff *);
void printLanding(landing *);
void printTakeoff(Takeoff *);


int main(void){
    
    landing *headA1 = NULL;
    landing *headB1 = NULL, *tailB1 = NULL, *headB2 = NULL, *tailB2 = NULL;
    landing *headC1 = NULL, *tailC1 = NULL, *headC2 = NULL, *tailC2 = NULL;
    Landing *headD1 = NULL, *tailD1 = NULL, *headD2 = NULL, *tailD2 = NULL;

    Takeoff *headA = NULL, *tailA = NULL, *headB = NULL, *tailB = NULL;
    Takeoff *headC = NULL, *tailC = NULL, *headD = NULL, *tailD = NULL;

    int landingRunway = 1;
    int takeoffRunway = 1;
    int idLanding = 1;
    int idTakeoff = 0;
    int tempTime = 0;
    
    seed = (unsigned) time (0);
    srand(seed);

    while(tempTime < timeUnit){
        flag = 0;
        
        tempTime++;
        // Prints the initial states in the queues
        cout << "\n\n-------------------\nSimulation time: " << tempTime << endl;
        cout << "\nRunwayA(-1)";
        cout << "\nLane 1: ";
        printLanding(headA1);
        cout << "\nLane 2: ";
        cout << "\nTakeoff: ";
        printTakeoff(headA);
        cout << "\n\nRunwayB(-1)";
        cout << "\nLane 1: ";
        printLanding(headB1);
        cout << "\nLane 2: ";
        printLanding(headB2);
        cout << "\nTakeoff: ";
        printTakeoff(headB);
        cout << "\n\nRunwayC(-1)";
        cout << "\nLane 1: ";
        printLanding(headC1);
        cout << "\nLane 2: ";
        printLanding(headC2);
        cout << "\nTakeoff: ";
        printTakeoff(headC);
        cout << "\n\nRunwayD(-1)";
        cout << "\nLane 1: ";
        printLanding(headD1);
        cout << "\nLane 2: ";
        printLanding(headD2);
        cout << "\nTakeoff: ";
        printTakeoff(headD);

        // Add waiting time to the planes in the takeoff queue
        addTimeTakeoff(headA);
        addTimeTakeoff(headB);
        addTimeTakeoff(headC);
        addTimeTakeoff(headD);
        
        // Add waiting time to the planes in the landing queue
        addTimeLanding(headB1);
        addTimeLanding(headC1);
        addTimeLanding(headD1);
        addTimeLanding(headB2);
        addTimeLanding(headC2);
        addTimeLanding(headD2);

        // Randomly generate landing planes and put them in designated runways
        int generatedLand = random(maxLanding);

        cout << "\n\n----\nStep 1\n";
        cout << "Landing plane: ";

        for(int i=0; i<generatedLand; i++){
            if(landingRunway % 6 == 1) newLanding(headB1, tailB1, idLanding);
            else if(landingRunway % 6 == 2) newLanding(headC1, tailC1, idLanding);
            else if(landingRunway % 6 == 3) newLanding(headD1, tailD1, idLanding);
            else if(landingRunway % 6 == 4) newLanding(headB2, tailB2, idLanding);
            else if(landingRunway % 6 == 5) newLanding(headC2, tailC2, idLanding);
            else  newLanding(headD2, tailD2, idLanding);
            landingRunway++;
            idLanding += 2;
        }
        // Prints the handling of the landing queues
        cout << "\n\nRunwayA(-1)";
        cout << "\nLane 1: ";
        printLanding(headA1);
        cout << "\nLane 2: ";
        cout << "\nTakeoff: ";
        printTakeoff(headA);
        cout << "\n\nRunwayB(-1)";
        cout << "\nLane 1: ";
        printLanding(headB1);
        cout << "\nLane 2: ";
        printLanding(headB2);
        cout << "\nTakeoff: ";
        printTakeoff(headB);
        cout << "\n\nRunwayC(-1)";
        cout << "\nLane 1: ";
        printLanding(headC1);
        cout << "\nLane 2: ";
        printLanding(headC2);
        cout << "\nTakeoff: ";
        printTakeoff(headC);
        cout << "\n\nRunwayD(-1)";
        cout << "\nLane 1: ";
        printLanding(headD1);
        cout << "\nLane 2: ";
        printLanding(headD2);
        cout << "\nTakeoff: ";
        printTakeoff(headD);

        // Randomly generate takeoff planes and put them in designated runways
        int generatedTakeoff = random(maxTakeoff);
        cout << "\n\n----\nStep 2\n";
        cout << "Takeoff plane: ";
        
        for(int i=0; i<generatedTakeoff; i++){
            if(takeoffRunway % 4 == 1) newTakeoff(headA, tailA, idTakeoff);
            else if(takeoffRunway % 4 == 2) newTakeoff(headB, tailB, idTakeoff);
            else if(takeoffRunway % 4 == 3) newTakeoff(headC, tailC, idTakeoff);
            else if(takeoffRunway % 4 == 0) newTakeoff(headD, tailD, idTakeoff);
            takeoffRunway++;
            idTakeoff +=2;
        }
        // Prints the handling of the takeoff queues
        cout << "\n\nRunwayA(-1)";
        cout << "\nLane 1: ";
        printLanding(headA1);
        cout << "\nLane 2: ";
        cout << "\nTakeoff: ";
        printTakeoff(headA);
        cout << "\n\nRunwayB(-1)";
        cout << "\nLane 1: ";
        printLanding(headB1);
        cout << "\nLane 2: ";
        printLanding(headB2);
        cout << "\nTakeoff: ";
        printTakeoff(headB);
        cout << "\n\nRunwayC(-1)";
        cout << "\nLane 1: ";
        printLanding(headC1);
        cout << "\nLane 2: ";
        printLanding(headC2);
        cout << "\nTakeoff: ";
        printTakeoff(headC);
        cout << "\n\nRunwayD(-1)";
        cout << "\nLane 1: ";
        printLanding(headD1);
        cout << "\nLane 2: ";
        printLanding(headD2);
        cout << "\nTakeoff: ";
        printTakeoff(headD);

        // Determines which plane to use the runway
        int b = runwayUsage(headB1, headB2, headB);
        int c = runwayUsage(headC1, headC2, headC);
        int d = runwayUsage(headD1, headD2, headD);
        a_id = -1;
        b_id = -1;
        c_id = -1;
        d_id = -1;
        
        cout << "\n\n----\nStep 3\n";
        cout << "Emergency Plane: ";
        
        // Determines if any of the planes needs emergency landing
        determineLanding(headA1, headA1, headB1, headC1, headD1);
        determineLanding(headB1, headA1, headB1, headC1, headD1);
        determineLanding(headC1, headA1, headB1, headC1, headD1);
        determineLanding(headD1, headA1, headB1, headC1, headD1);
        determineLanding(headB2, headA1, headB1, headC1, headD1);
        determineLanding(headC2, headA1, headB1, headC1, headD1);
        determineLanding(headD2, headA1, headB1, headC1, headD1);
        
        // Prints the handle of emergency landing
        cout << "\n\nRunwayA(-1)";
        cout << "\nLane 1: ";
        printLanding(headA1);
        cout << "\nLane 2: ";
        cout << "\nTakeoff: ";
        printTakeoff(headA);
        cout << "\n\nRunwayB(-1)";
        cout << "\nLane 1: ";
        printLanding(headB1);
        cout << "\nLane 2: ";
        printLanding(headB2);
        cout << "\nTakeoff: ";
        printTakeoff(headB);
        cout << "\n\nRunwayC(-1)";
        cout << "\nLane 1: ";
        printLanding(headC1);
        cout << "\nLane 2: ";
        printLanding(headC2);
        cout << "\nTakeoff: ";
        printTakeoff(headC);
        cout << "\n\nRunwayD(-1)";
        cout << "\nLane 1: ";
        printLanding(headD1);
        cout << "\nLane 2: ";
        printLanding(headD2);
        cout << "\nTakeoff: ";
        printTakeoff(headD);
        
        // Put everything in place for landing/ emergency landing/ takeoff
        if(headA != NULL && flag == 0){
            a_id = headA->id;
            headA = headA->next;
        }

        if(flag < 2){
            deleteEmergencyLanding(headA1);
            if(b == 0);
            else if(headB1 != NULL && b == 1) {
                b_id = headB1->id;
                normalLanding(headB1);
            }
            else if(headB2 != NULL && b == 2) {
                b_id = headB2->id;
                normalLanding(headB2);
            }
            else if (headB != NULL && b == 3){
                b_id = headB->id;
                normalTakeoff(headB);
            }
        }

        if(flag < 3){
            deleteEmergencyLanding(headA1);
            deleteEmergencyLanding(headB1);
            if(c == 0);
            else if(headC1 != NULL && c == 1) {
                c_id = headC1->id;
                normalLanding(headC1);
            }
            else if(headC2 != NULL && c == 2) {
                c_id = headC2->id;
                normalLanding(headC2);
            }
            else if (headC != NULL && c == 3){
                c_id = headC->id;
                normalTakeoff(headC);
            }
        }

        if(flag < 4){
            deleteEmergencyLanding(headA1);
            deleteEmergencyLanding(headB1);
            deleteEmergencyLanding(headC1);
            if(d == 0);
            else if(headD1 != NULL && d == 1) {
                d_id = headD1->id;
                normalLanding(headD1);
            }
            else if(headD2 != NULL && d == 2) {
                d_id = headD2->id;
                normalLanding(headD2);
            }
            else if (headD != NULL && d == 3){
                d_id = headD->id;
                normalTakeoff(headD);
            }
        }
        
        if(flag == 4){
            deleteEmergencyLanding(headA1);
            deleteEmergencyLanding(headB1);
            deleteEmergencyLanding(headC1);
            deleteEmergencyLanding(headD1);
        }
        
        // Prints the handle of all planes
        cout << "\n\n----\nStep 4\n";
        cout << "\nRunwayA(" << a_id << ")";
        cout << "\nLane 1: ";
        printLanding(headA1);
        cout << "\nLane 2: ";
        cout << "\nTakeoff: ";
        printTakeoff(headA);
        cout << "\n\nRunwayB(" << b_id << ")";
        cout << "\nLane 1: ";
        printLanding(headB1);
        cout << "\nLane 2: ";
        printLanding(headB2);
        cout << "\nTakeoff: ";
        printTakeoff(headB);
        cout << "\n\nRunwayC(" << c_id << ")";
        cout << "\nLane 1: ";
        printLanding(headC1);
        cout << "\nLane 2: ";
        printLanding(headC2);
        cout << "\nTakeoff: ";
        printTakeoff(headC);
        cout << "\n\nRunwayD(" << d_id << ") ";
        cout << "\nLane 1: ";
        printLanding(headD1);
        cout << "\nLane 2: ";
        printLanding(headD2);
        cout << "\nTakeoff: ";
        printTakeoff(headD);
    }
    // Prints the statistics 
    cout << "\n\n---------\nThe number of time unit you want to stimulate is " << timeUnit << ".";
    cout << "\nThe number of crashed planes is " << numOfCrahes << ".";
    cout << "\nThe number of emergency landings is " << numOfEmergencyLands << ".";
    cout << fixed << setprecision(2);
    cout << "\nThe average landing time is " << landingTime/numOfLands << " units.";
    cout << "\nThe average takeoff time is " << takeoffTime/numOfTakeoff << " units.";
    cout << "\nThe average fuel saved is " << fuelSaved/numOfLands << " units.";
    cout << endl << endl;
    return 0;
}

int random(int max){
    int x = 0;
    x = rand() % max;
    return x;
}

int randomFuel(int maxFuel){
    int x = 0;
    x = rand() % maxFuel + 1;
    return x;
}

bool isEmptyLanding(landing *&head){
    if(head == NULL) return true;
    else return false;
}

void newLanding(landing *&head, landing *&tail, int id_){
    landing *temp = new landing;
    temp->id = id_;
    temp->fuel = randomFuel(maxFuel);
    temp->next = NULL;
    cout << "(" << temp->id << ", " << temp->fuel << "), ";
    if(isEmptyLanding(head)) head = temp;
    else tail->next = temp;
    tail = temp;
}


void normalLanding(landing *&head){
    landingTime += head->waitTime;
    fuelSaved += head->fuel;
    numOfLands++;
    landing *temp = head;
    head = head->next;
    delete temp;
}

void emergencyLanding(landing *&current, landing *&headA1, landing *&headB1, landing *&headC1, landing *&headD1){
    landing *tempCurrent = new landing;
    tempCurrent->id = current->id;
    tempCurrent->fuel = current->fuel;
    
    if(flag == 1){
        a_id = tempCurrent->id;
        landing *temp = headA1;
        tempCurrent->next = temp;
        headA1 = tempCurrent;
    }
    else if(flag == 2){
        b_id = tempCurrent ->id;
        landing *temp = headB1;
        tempCurrent->next = temp;
        headB1 = tempCurrent;
    }
    else if(flag == 3){
        c_id = tempCurrent ->id;
        landing *temp = headC1;
        tempCurrent->next = temp;
        headC1 = tempCurrent;
    }
    else if(flag == 4){
        d_id = tempCurrent ->id;
        landing *temp = headD1;
        tempCurrent->next = temp;
        headD1 = tempCurrent;
    }
    else {
        cout << "Plane " << current->id << " ran out of fuel and crashed." << endl;
        numOfCrahes++;
    }
    
    landingTime += current->waitTime;
    numOfEmergencyLands++;
    cout << "(" << current->id << ", " << current->fuel << "), ";

    if(current->next == NULL) {
        current = NULL;
    }
    else {
        landing *temp = current;
        current = temp->next;
        delete temp;
    }
    
}

void addTimeLanding(landing *&head){
    if (!isEmptyLanding(head)){
        landing *current = head;
        while(current != NULL){
            current->waitTime++;
            current->fuel--;
            current = current->next;
        }
    }
}

void determineLanding(landing *&head, landing *&headA1, landing *&headB1, landing *&headC1, landing *&headD1){
    if (!isEmptyLanding(head)){
        // Determine if the head is on lowfuel
        while (head != NULL && head->fuel == 0){
            flag++;
            emergencyLanding(head, headA1, headB1, headC1, headD1);
        }
        // Determine if the rest of the plane is on lowfuel
        if (head != NULL){
            landing* current = head->next;
            while (current != NULL){
                current->fuel--;
                current->waitTime++;
                if (current->fuel == 0){
                    flag++;
                    emergencyLanding(current, headA1, headB1, headC1, headD1);
                }
                else current = current->next;
            }
        }
    }
}

void deleteEmergencyLanding(landing *&head){
    landing * temp = head;
    if(head != NULL) head = head->next;
    else head = NULL;
    delete temp;
}

bool isEmptyTakeoff(Takeoff *&head){
    if(head == NULL) return true;
    else return false;
}

void newTakeoff(Takeoff *&head, Takeoff *&tail, int id_){
    Takeoff *temp = new Takeoff;
    temp->id = id_;
    temp->next = NULL;
    cout << "(" << temp->id << "), ";

    if(isEmptyTakeoff(head)) head = temp;
    else tail->next = temp;
    tail = temp;
}

void addTimeTakeoff(Takeoff *&head){
    if (!isEmptyTakeoff(head)){
        takeoff* current = head;
        while(current != NULL){
            current->waitTime++;
            current = current->next;
        }
    }
}

void normalTakeoff(Takeoff *&head){
    takeoffTime += head->waitTime;
    numOfTakeoff ++;
    Takeoff *temp = head;
    head = head->next;
    delete temp;
}

int runwayUsage( landing *head1, landing *head2, Takeoff *head){
    if(head1 != NULL && head2 != NULL && head != NULL){
        if(head1->id < head2->id && head1->id < head->id) return 1;
        else if (head2->id < head1->id && head2->id < head->id) return 2;
        else return 3;
    }

    else if(head1 != NULL && head2 != NULL){
        if(head1->id < head2->id) return 1;
        else return 2;
    }

    else if(head1 != NULL && head != NULL){
        if(head1->id < head->id) return 1;
        else return 3;
    }

    else if(head2 != NULL && head != NULL){
        if(head2->id < head->id) return 2;
        else return 3;
    }

    else if(head1 != NULL) return 1;

    else if(head2 != NULL) return 2;

    else if(head != NULL) return 3;

    else return 0;

}

void printLanding( landing *current ) {
    while( current != NULL ) {
        cout << "(" << current->id << ", " << current->fuel << "), ";
        current = current->next;
    }
}


void printTakeoff( Takeoff *current ) {
    while( current != NULL ) {
        cout << "(" << current->id << ")";
        current = current->next;
    }
}
