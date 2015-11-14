#include <iostream>
#include <limits.h>
#include <cstdio>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <string>
#define LIMIT 5

int chromosomes[LIMIT];
int iteration;
int minCost = INT_MAX;

using namespace std;


void cross_mutation();
int costEvaluation(int , char *);

int main()
{
    int i;
    cout << "Enter the five distinct numbers (range 1 to 2000)  :  ";
    for(i=0; i<LIMIT; i++) {
        cin >> chromosomes[i];
    }

    cout << "Enter maximum number of iterations : ";
    cin >> iteration;

    cout << "The Initial Permutation was ";
    for(i=0; i<LIMIT; i++) {
        cout << chromosomes[i] << " ";
    } cout << endl;

    cross_mutation();

    cout << "After " << iteration << " iterations the Final Permutation : ";
    for(i=0; i<LIMIT; i++) {
        cout << chromosomes[i] << " ";
    }
    cout << endl;

    return 0;
}


void cross_mutation() {
    int i, j;
    int times;

    for(times=1; times<=iteration; times++) {

        /* Iteration Counter  */
        cout << "Iteration Number :: " << times << endl << endl;
        int temp[LIMIT];
        int hold;


        /* Print first parent */
        cout << "Parent A : ";
        for(i=0; i<LIMIT; i++) {
            cout << chromosomes[i] << " ";
        } cout << endl;

        /* Cost of initial parent */
        int beforeMut = 0;
        int beforeMax = INT_MIN;
        for(i=0; i<LIMIT; i++) {
            char filename[11] = "DB_0";
            sprintf(filename, "%s%i.csv", filename, i+1);
            hold = costEvaluation(chromosomes[i], filename);
            //cout << "Cost :: " << hold << endl;
            beforeMut += hold;
            if(hold > beforeMax) {
                beforeMax = hold;
            }
        }
        beforeMut += beforeMax;
        cout << "Parent A Cost : " << beforeMut << endl;


        /* Second parent selection  */
        int index[LIMIT] = {0};
        bool visited[LIMIT] = {0};

        for(i=0; i<LIMIT; i++) {
            int temp = rand()%LIMIT;
            while(visited[temp] == true) {
                temp = rand()%LIMIT;
            }

            visited[temp] = true;
            index[i] = temp;
        }

        int parent[LIMIT];
        for(i=0; i<LIMIT; i++) {
            parent[i] = chromosomes[index[i]];
        }

        /* Print second parent */
        cout << "Parent B : ";
        for(i=0; i<LIMIT; i++) {
            cout << parent[i] << " ";
        } cout << endl;


        /* Cost of second parent */
        int beforeMutB = 0;
        int beforeMaxB = INT_MIN;
        for(i=0; i<LIMIT; i++) {
            char filename[11] = "DB_0";
            sprintf(filename, "%s%i.csv", filename, i+1);
            hold = costEvaluation(parent[i], filename);
            //cout << "Cost :: " << hold << endl;
            beforeMutB += hold;
            if(hold > beforeMaxB) {
                beforeMaxB = hold;
            }
        }
        beforeMutB += beforeMaxB;
        cout << "Parent B Cost : " << beforeMutB << endl;


        /*   Child generation  */
        int childA[LIMIT] = {0};
        int childB[LIMIT] = {0};

        for(i=0; i<=LIMIT/2; i++) {
            childA[i] = chromosomes[i];
        }

        for(i=0; i<=LIMIT/2; i++) {
            childB[i] = parent[i];
        }

        /*   Cross - over for child A  */
        for(i=0; i<LIMIT; i++) {
            j = 0;
            while(j<LIMIT) {
                if(childA[j] == parent[i]) {
                    break;
                } else if(childA[j] == 0) {
                    childA[j] = parent[i];
                    break;
                } else {
                    j++;
                }
            }
        }

        /*   Cross - over for child B  */
        for(i=0; i<LIMIT; i++) {
            j = 0;
            while(j<LIMIT) {
                if(childB[j] == chromosomes[i]) {
                    break;
                } else if(childB[j] == 0) {
                    childB[j] = chromosomes[i];
                    break;
                } else {
                    j++;
                }
            }
        }

        /* print child A */
        cout << "Child A : ";
        for(i=0; i<LIMIT; i++) {
            cout << childA[i] << " ";
        } cout << endl;


        /*   Calculate the cost of the first child */
        int costA = 0;
        int costAMax = INT_MIN;
        for(i=0; i<LIMIT; i++) {
            char filename[11] = "DB_0";
            sprintf(filename, "%s%i.csv", filename, i+1);
            hold = costEvaluation(childA[i], filename);
            //cout << "CostA :: " << hold << endl;
            costA += hold;
            if(hold > costAMax) {
                costAMax = hold;
            }
        }
        costA += costAMax;
        cout << "Cost of Child A : " << costA << endl;


        /* print child B */
        cout << "Child B : ";
        for(i=0; i<LIMIT; i++) {
            cout << childB[i] << " ";
        } cout << endl;


        /*   Calculate the cost of the second child */
        int costB = 0;
        int costBMax = INT_MIN;
        for(i=0; i<LIMIT; i++) {
            char filename[11] = "DB_0";
            sprintf(filename, "%s%i.csv", filename, i+1);
            hold = costEvaluation(childB[i], filename);
            //cout << "CostA :: " << hold << endl;
            costB += hold;
            if(hold > costBMax) {
                costBMax = hold;
            }
        }
        costB += costBMax;
        cout << "Cost of Child B : " << costB << endl;

        /* Comparison and Elimination */
        if(costA <= costB) {
            if(costA < beforeMut) {
                beforeMut = costA;
                for(i=0; i<LIMIT; i++) {
                    chromosomes[i] = childA[i];
                }
            }
        } else {
            if(costB < beforeMut) {
                beforeMut = costB;
                for(i=0; i<LIMIT; i++) {
                    chromosomes[i] = childB[i];
                }
            }
        }

        /* After Cross-over*/
        cout << endl << "After cross- over the premutation we got : ";
        for(i=0; i<LIMIT; i++) {
            cout << chromosomes[i] << " ";
        } cout << endl;


        for(i=0; i<LIMIT; i++) {
            temp[i] = chromosomes[i];
        }

        /*   Mutation  */
        int tempVal;

        int index1 = rand()%LIMIT;
        int index2 = rand()%LIMIT;
        while(index1 == index2) {
            index2 = rand()%LIMIT;
        }

        //cout << index1 << " " << index2 << endl;

        tempVal      = temp[index1];
        temp[index1] = temp[index2];
        temp[index2] = tempVal;

        /*    Calculate the cost after mutation  */
        cout << "After Mutation the permutation : ";
        for(i=0; i<LIMIT; i++) {
            cout << temp[i] << " ";
        } cout << endl;

        int afterMut = 0;
        int afterMax = INT_MIN;
        for(i=0; i<LIMIT; i++) {
            char filename[11] = "DB_0";
            sprintf(filename, "%s%i.csv", filename, i+1);
            hold = costEvaluation(temp[i], filename);
            //cout << "Cost :: " << hold << endl;
            afterMut += hold;
            if(hold > afterMax) {
                afterMax = hold;
            }
        }
        afterMut += afterMax;
        cout << "Mutated cost " << afterMut << endl;

        if(afterMut < beforeMut) {
            beforeMut = afterMut;

            for(i=0; i<LIMIT; i++) {
                chromosomes[i] = temp[i];
            }
        }
        minCost =  beforeMut;
        cout << "Final, survival chromosome (permutation) after " << times << " iteration : ";
        for(i=0; i<LIMIT; i++) {
            cout << chromosomes[i] << " ";
        } cout << endl;

        cout << "Final Cost ::" << minCost;

        cout << endl;
        for(j=0; j<80; j++) {
            cout << "*" ;
        } cout << endl << endl;
    }
}


int stoi(string str) {
    int num = 0;
    for(unsigned int i=0; i<str.length(); i++) {
        num = 10*num + (str[i] - '0');
    }

    return num;
}

int costEvaluation(int id, char filename[11]) {
    int counter = 0;
    string line;

    ifstream  fin;
    fin.open(filename,ios::in);

    if(fin.is_open()) {
        while(getline(fin, line)) {
            counter++;
            istringstream s(line);
            string temp;
            getline(s, temp,',');
            if(id == stoi(temp)) {
                /*cout << id << " | ";
                getline(s, temp, ',');
                cout << temp << " | ";
                getline(s, temp, ',');
                cout << temp << " | ";*/
                break;
            }
        }
    } else {
        cout << " Sorry !!! Error Occured while reading in the Database : " << filename << endl;
        exit(1);
    }
    fin.close();

    return counter;
}
