#include "study_in_pink1.h"

bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Task 1
int firstMeet(int & exp1, int & exp2, int e1) {
    // TODO: Complete this function
    int D;
    float P; // The probability that Sherlock finds the suitcase.
    if (exp1 > 600 || exp2 > 600) {
            if (exp1 > 600) { 
                exp1 = 600;
            } else {
                exp2 = 600;
            }
        } 
    if (exp1 < 0 || exp2 < 0) {
            if (exp1 < 0) { 
                exp1 = 0;
            } else {
                exp2 = 0;
            }
        }

    if (e1 >= 0 && e1 <= 3) {    

        switch (e1) {
            case 0: // Information 1
                exp2 += 29;
                break;
            case 1: // Information 2
                exp2 += 45;
                break;
            case 2: // Information 3
                exp2 += 75;
                break;
            case 3: // Information 4
                exp2 += 29 + 45 + 75;
        }

        D = e1 * 3 + exp1 * 7;

        if (D % 2 == 0) {  
            exp1 += ceil((float)D/200);
        } else {
            exp1 -= ceil((float)D/100);
        }
    }else if(e1 >= 4 && e1 <= 99){
        if(e1 >= 4 && e1 <= 19){ // Information 1
            exp2 += ceil((float)e1/4 + 19);
        }
        else if(e1 >= 20 && e1 <= 49){ // Information 2
            exp2 += ceil((float)e1/9 + 21);
        }
        else if(e1 >= 50 && e1 <= 65){ // Information 3
            exp2 += ceil((float)e1/16 + 17);
        }
        else if(e1 >= 66 && e1 <= 79){ // Information 4
            exp2 += ceil((float)e1/4 + 19);
            if(exp2 > 200){
                exp2 += ceil((float)e1/9 + 21);
            }
        }
        else if(e1 >= 80 && e1 <= 99){ // Information 5
            exp2 += ceil((float)e1/4 + 19);
            exp2 += ceil((float)e1/9 + 21);
            if(exp2 > 400){
                exp2 += ceil((float)e1/16 + 17);
                exp2 = ceil((float)exp2 * 1.15);
            }
        }

    if (exp1 > 600 || exp2 > 600) {
            if (exp1 > 600) { 
                exp1 = 600;
            } else {
                exp2 = 600;
            }
        } 
    if (exp1 < 0 || exp2 < 0) {
            if (exp1 < 0) { 
                exp1 = 0;
            } else {
                exp2 = 0;
            }
        }

        return exp1 + exp2;
    }else{
        return -99;
    }
}

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    // TODO: Complete this function
    if(E2 >= 0 && E2 <= 99){
    // Check HP and Money condition
    if (HP1 > 600 || M1 > 3000) {
        if(HP1 > 600){
            HP1 = 600;
        }
        else{M1 = 3000;}
        } 
    if (HP1 < 0 || M1 < 0) {
        if(HP1 < 0){
            HP1 = 0;
        }
        else{M1 = 0;}
        }

    // Road 1:
    int S; // the nearest perfect square to the value EXP1
    int temp1;
    int temp2;
    float P1; /*the probability for Sherlock to find the suitcase on
    this route*/ 
    
    // The probability P1 of finding the suitcase on this route.
    temp1 = floor(sqrt(EXP1));
    temp2 = ceil(sqrt(EXP1));
    if((EXP1 - temp1*temp1) > (temp2*temp2 - EXP1)){
        S = temp2*temp2;
        P1 = 1;
    }
    else{
        S = temp1*temp1;
        P1 = ((float)EXP1/S + 80)/123;
    }

    // Road 2:
    // FOOD or DRINK:
    int m = 0; // MONEY SPENT.
    if(E2 % 2 != 0){
    while(m <= ceil(M1/2)){
    // Need to write another function to check m valid??
    // (provide continue and break at the end )
    /*if(m <= ceil(M1/2)){
        break;
    }*/
    if(HP1 < 200){ //Food
        HP1 = HP1 + ceil(HP1*0.3);
        m = 150; //Food
        if(m <= ceil(M1/2)){
            break;
        }
    }else{ //Beverage
        HP1 = HP1 + ceil(HP1*0.1);
        m = 70; //Drink
        if(m <= ceil(M1/2)){
            break;
        }
    }

    // RENTAL TRANSPORTATION:
    EXP1 += ceil(EXP1*0.13); /*EXP1 after performing 1 of the 2 
    actions below*/
    if(EXP1 < 400){ //Sherlock will choose to take a taxi
        m += 200; // The price to rent a taxi
        if(m <= ceil(M1/2)){
            break;
        }   
    }else{ //Sherlock will choose to take a horse-drawn carriage
        m += 120; // The price to rent a horse-drawn carriage
        if(m <= ceil(M1/2)){
            break;
        }    
    }
   
    // SHERLOCK MET A HOMELESS PERSON:
    EXP1 -= ceil(EXP1*0.1); /*EXP1 After the homeless person mistook it 
    for another empty suitcase.*/
    if(EXP1 < 300){ //Listen to a homeless person's instructions.
        m += 100;       
        if(m <= ceil(M1/2)){
            break;
        }  
    }else{ //Ask this person to lead the way
        m += 120; 
        if(m <= ceil(M1/2)){
            break;
        }  
    }
    }

    HP1  -= floor(HP1*0.17); 
    EXP1 += ceil(EXP1*0.17);
    }else{

    // FOOD or DRINK:
    if(HP1 < 200){ //Food
        HP1 = HP1 + ceil(HP1*0.3);
        m = 150; //Food
    }else{ //Beverage
        HP1 = HP1 + ceil(HP1*0.1);
        m = 70; //Drink
    }

    if(m <= M1){ 
    // RENTAL TRANSPORTATION:   
    EXP1 += ceil(EXP1*0.13);/*EXP1 after performing 1 of the 2 
    actions below*/
    if(EXP1 < 400){ //Sherlock will choose to take a taxi
        m += 200; // The price to rent a taxi  
    }else{ //Sherlock will choose to take a horse-drawn carriage
        m += 120; // The price to rent a horse-drawn carriage  
    }
    }

    if(m <= M1){
    // SHERLOCK MET A HOMELESS PERSON:
    EXP1 -= ceil(EXP1*0.1); /*EXP1 After the homeless person mistook it 
    for another empty suitcase.*/ 
    if(EXP1 < 300){ //Listen to a homeless person's instructions.
        m += 100;         
    }else{ //Ask this person to lead the way
        m += 120;  
    }
    }

    HP1  -= floor(HP1*0.17); 
    EXP1 += ceil(EXP1*0.17);
    }
    M1 -= m; // How much money is left?, and restore if needed
    // The probability P2 of finding the suitcase on this route.
    temp1 = floor(sqrt(EXP1));
    temp2 = ceil(sqrt(EXP1));
    if((EXP1 - temp1*temp1) > (temp2*temp2 - EXP1)){
        S = temp2*temp2;
        P2 = 1;
    }
    else{
        S = temp1*temp1;
        P2 = ((float)EXP1/S + 80)/123;
    }

    //Road 3:
    float P[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    int P3;
    int i;
    if(E2 >= 0 && E2 < 10){
        int i = E2;
        P3 = P[i];
    }else{
        if((E2/10 + E2%10) >= 10){
            int i = (E2/10 + E2%10) -10;
            P3 = P[i];
        }else{
            int i = E2/10 + E2%10;
            P3 = P[i];
        }        
    }

    //Average probability:
    P = (P1*100 + P2*100 + P3)/3;

    if(P == 100){
        EXP1 -= floor(EXP1*0.25);
    }else if(P < 50){
        HP1 -= floor(HP1*0.15);
        EXP1 += ceil(EXP*0.15);
    }else{
        HP1 -= floor(HP1*0.1);
        EXP1 += ceil(EXP*0.2);        
    } 

    // Check HP and Money condition
    if (HP1 > 600 || M1 > 3000) {
        if(HP1 > 600){
            HP1 = 600;
        }
        else{M1 = 3000;}
        } 
    if (HP1 < 0 || M1 < 0) {
        if(HP1 < 0){
            HP1 = 0;
        }
        else{M1 = 0;}
        }
    
    return HP1 + EXP1 + M1;
}else
return -99;
}

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    // TODO: Complete this function
    
    return -1;
}

// Task 4
int checkPassword(const char * s, const char * email) {
    // TODO: Complete this function

    return -99;
}

// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    // TODO: Complete this function

    return -1;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////