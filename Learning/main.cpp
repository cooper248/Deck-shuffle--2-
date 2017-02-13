//  main.cpp
//  Deck_Shuffle
//  Created by Cooper Richardson on 2/5/17.
//  Copyright © 2017 Cooper Richardson. All rights reserved.

// THIS CODE IS A REPEAT OF THE SHUFFLED PROGRAM BUT ALL FUNCTIONS ARE EXTERNAL OF THE MAIN

// include all necessary libraries
#include <iostream>
#include <fstream>
#include <assert.h>
#include <random>
#include <vector>
#include <ctime>
using namespace std;

//create variables
int numCards = 14;
int startValue = 0;
int numSuites = 4;
int iteration = 1;

//Create class for cards
class card
{
public:
    int cardValue;
    int suiteValue;
    
    void createCard(int,int);
    void printDecks(long,vector<card>);
};

void card::createCard(int value,int suite){
    suiteValue=suite;
    cardValue=value;
};

void createDecks(int *x, int *y, vector<card> *allDecks){
    // Function to create decks
    cout<<"How many decks would you like to use? "; cin>>*x;;
    for(int i=0;i<*x;i++)
    {
        for(int value=1;value<numCards;value++)
        {
            for(int suite=startValue;suite<numSuites;suite++)
            {
                card A;
                A.createCard(value, suite);
                allDecks->push_back(A);
            };
        };
    };
    // check that deck size is correct before moving on
    *y=allDecks->size();
    assert(*y==*x*52);
};

void printDecks(int *sizeDeck, vector<card> *allDecks){
    /// Prove to user that proper deck was created
    cout<<"You created "<< *sizeDeck<< " cards. Congrats!" <<endl;
    cout<<"Here are the cards that you created: " << endl <<endl;
    for(int i=0;i<*sizeDeck;i++){
        cout<< allDecks->at(i).card::cardValue;
        if(allDecks->at(i).card::suiteValue==0){
            cout<<" of hearts"<< endl;
        }
        if(allDecks->at(i).card::suiteValue==1){
            cout<<" of clubs"<< endl;
        }
        if(allDecks->at(i).card::suiteValue==2){
            cout<<" of spades"<< endl;
        }
        if(allDecks->at(i).card::suiteValue==3){
            cout<<" of diamonds"<< endl;
        }
    }
    cout<< endl; //readability
};

void shuffle (int *sizeDeck, int *numDecks, vector<card>* allDecks){
    // Shuffle created deck
    // Create location to use for swapping cards during shuffle
    vector<card> hold;
    card B;
    B.createCard(NULL,NULL);
    hold.push_back(B);

    
    srand(time(NULL));
    for(int i=0; i<*sizeDeck;i++){
        int pullLocation1 = rand()% *sizeDeck;
        int pullLocation2 = rand()% *sizeDeck;
        if(pullLocation1==52||pullLocation2==52){
            cout<< "we got max!!"<<endl;
        }
              //  cout << "here" << *sizeDeck<< endl;
        
        hold[0]=allDecks->at(pullLocation1);
        
        allDecks->at(pullLocation1)=allDecks->at(pullLocation2);
        allDecks->at(pullLocation2)=hold[0];
    }
    // Display shuffled Deck
    cout<<"Here is your shuffled set of " << *numDecks << " deck(s)"<<endl <<endl;
    for(int i=0;i<*sizeDeck;i++){
        cout<< allDecks->at(i).card::cardValue;
        if(allDecks->at(i).card::suiteValue==0){
            cout<<" of hearts"<< endl;
        }
        if(allDecks->at(i).card::suiteValue==1){
            cout<<" of clubs"<< endl;
        }
        if(allDecks->at(i).card::suiteValue==2){
            cout<<" of spades"<< endl;
        }
        if(allDecks->at(i).card::suiteValue==3){
            cout<<" of diamonds"<< endl;
        }
    }
};

void testA(int *numDecks, int* sizeDeck, vector<card> *allDecks){
    // Test A
    int check =1;
    if(*numDecks==1){
        for (int i=0; i<*sizeDeck;i++)
        {
            for (int j=0; j<*sizeDeck;j++)
            {
                if(i!=j)
                {
                    if(allDecks->at(i).card::cardValue==allDecks->at(j).card::cardValue && allDecks->at(i).card::suiteValue==allDecks->at(j).card::suiteValue)
                    {
                        check=check-1;
                        cout<<"ERROR: Repeat of a card has been created. Check your code again.";
                    }
                }
            }
        }
        cout<< endl << "No duplicate cards were created during the shuffle! Booya!" << endl;
        assert(check==1);
    }
};

void testB(int *numDecks, int* sizeDeck, vector<card> *allDecks){
    // Test B
    int test = 0;
    if(*numDecks>1)
    {
        for(int i =1;i<*sizeDeck;i++)
        {
            if(allDecks->at(i).card::cardValue==allDecks->at(0).card::cardValue && allDecks->at(i).card::suiteValue==allDecks->at(0).card::suiteValue)
            {
                test=test+1;
                if(test>*numDecks)
                {
                    cout<<"Whelp, you screwed something up. Too many repeats exist in this deck.";
                }
            }
        }
        assert(test=*numDecks);
        cout<<endl<<"Congratulations " << test << " repeats found in " << *numDecks << " decks. AKA perfection. Yahoo buckwheat!!"<<endl<<endl;
    }
};


int main() {
    vector<card> allDecks;
    int sizeDeck;
    int numDecks;
    
    createDecks(&numDecks, &sizeDeck, &allDecks);
    printDecks(&sizeDeck, &allDecks);
    shuffle(&sizeDeck, &numDecks, &allDecks);
    
    //Test deck
    testA(&numDecks,&sizeDeck, &allDecks);
    testB(&numDecks,&sizeDeck, &allDecks);
    
    // Write shuffled deck to file
    // NOTE TO USER, IF ON A MAC, MAKE SURE TO SEARCH LIBRARY FOR FILE OR SHOW HIDDEN FILES, OTHERWISE, YOU WILL NOT BE ABLE TO SEE THE CREATED .TXT FILE
    ofstream shuffledDeck;
    shuffledDeck.open("SHUFFLED.txt");
    for(int i =0;i<sizeDeck;i++){
        shuffledDeck << allDecks[i].card::cardValue << " of " << allDecks[i].card::suiteValue <<"\n";
    }
    shuffledDeck.close();
    return 0;
}
