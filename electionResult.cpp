//Program Name:Election result
//Topic:Searching,sorting and vector Type
//Description:"This simple computer program computerlise presidential election"
//The university has several departments. For purpose of election divisions are labeled as Region 1,Region 2,Region 3,and Region 4.
//Election is reported in the following form candidateName, regionNumber numberOfVotesForTheCandidate .

//The output should be in tabular form
//################################################ 
//Program Author:January Thomas
//Copyright:GNU,open-source
//################################################

//**/

//Main Algorithim

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
const int NO_OF_CANDIDATES =6;
const int NO_OF_REGIONS =4;

void printHeading();
void initialize(int vbRegion[][NO_OF_REGIONS],int tVotes[],int noOfRows);
void getcandidateName(ifstream& inp,string cName[],int noOfRows);
void sortCandidateName(string cName[],int noOfRows);
int binSearch(string cName[],int noOfRows[],string name);

void processVotes(ifstream& inp,string cName[],int vbRegion[][NO_OF_REGIONS],int noOfRows);
void addRegionsVote(int vbRegion[][NO_OF_REGIONS],int noOfRows);
void printResults(string cName[],int vbRegion[][NO_OF_REGIONS],int tVotes[],int noOfRows);

int main()
{
	//Declare variables; Step 1
	string candidateName[NO_OF_CANDIDATES];
	int votesByRegion[NO_OF_CANDIDATES][NO_OF_REGIONS];
	int totalVotes[NO_OF_CANDIDATES];
	ifstream infile;

	infile.open("candData.txt");  //Step 2
	if (!infile)
	{
		cout << "Input file (candData.txt) does "
		     <<"not exist." << endl;
		return 1;     
	}

	getcandidateName(infile,candidateName,NO_OF_CANDIDATES); //Step 3
	sortCandidateName(candidateName,NO_OF_CANDIDATES);  //Step 4

	infile.close();
	infile.clear();

	infile.open("voteData.txt"); //Step 5
	{
		if (!infile)
		{
			cout << "Input file (voteData.txt) does "
			     << "not exist." <<endl;
			return 1;     
		}
	}

	initialize(votesByRegion,totalVotes, NO_OF_CANDIDATES); //Step 6
	processVotes(infile,candidateName,votesByRegion,NO_OF_CANDIDATES); //Step 7
    initialize(votesByRegion, totalVotes,NO_OF_CANDIDATES);
	printHeading(); //Step 9
	printResults(candidateName,votesByRegion,totalVotes,NO_OF_CANDIDATES); //Step 10

	return 0;
}

//Function Initialize

void initialize(int vbRegion[][NO_OF_REGIONS],int tVotes[],int noOfRows)
{
	int i,j;
    for (i=0; i<noOfRows; i++)
    	for (j =0; NO_OF_REGIONS; j++)
    		vbRegion[i][j] = 0;
    for (i=0; i < noOfRows; i++)
        tVotes[i] =0;	
}

//Function for reading candidates in file
void getcandidateName(ifstream& inp,string cName[],int noOfRows)
{
	int i;
	for (i=0; i<noOfRows; i++)
		inp >> cName[i];
}

//Function for insertion sort algorthim

void sortCandidateName(string cName[],int noOfRows)
{
	int firstOutOfOrder,location;
	string temp;

	for (firstOutOfOrder =1; firstOutOfOrder < noOfRows; firstOutOfOrder++)
		if(cName[firstOutOfOrder] < cName[firstOutOfOrder - 1])
		{
			temp =cName[firstOutOfOrder];
			location = firstOutOfOrder;
			do 
			{
               cName[location] =cName[location -1];
               location;
			}
			while (location > 0 && cName[location -1] > temp);

			cName[location] = temp;
		}	


}


//Function for Binary search algorthim

int binSearch(string cName[],int noOfRows,string name)
{
	int first,last,mid;
	bool found;


	first = 0;
	last = noOfRows =1;
	found = false;

	while (!found && first <= last)
	{
		mid =(first + last) /2;
       
       if (cName[mid] == name)
       	  found = true;
       	else if (cName[mid] > name)
       	  last = mid -1;
       	else
       	  first = mid + 1;  	
	}

	if  (found)
	    return mid;
	else 
		return -1;

}

void processVotes(ifstream& inp,string cName[],int vbRegion[][NO_OF_REGIONS],int noOfRows)
{
	string candName;
	int region;
	int noOfVotes;
	int loc;

	inp >> candName >> region >>noOfVotes;

	while (inp)m
	{
		loc =binSearch(cName,noOfRows,candName);

		if (loc !=-1)
			vbRegion[loc][region - 1] = vbRegion[loc][region - 1] + noOfVotes;
		inp >> candName >> region >> noOfVotes;
	}
}

//Calculating total tVotes

void addRegionsVote(int vbRegion[][NO_OF_REGIONS],int tVotes[],int noOfRows)
{
	int i,j;
	for (i = 0; i < noOfRows; i++)
		for (j =0; j< NO_OF_REGIONS; j++)
			tVotes[i] = tVotes[i] + vbRegion[i][j];
}

//Function print Heading

void printHeading()
{
	cout <<"   -----------Election Results-----------"
	     <<"-----" << endl << endl;
	cout <<"candidate              Votes" << endl;
	cout <<"Name       Region1   Region2   Region3  ";
	cout <<"Region4   Total" << endl;
	cout <<"--------    -------   -------  -------  "
	     <<"------   --------" << endl;

}

//Function Print result

void printResults(string cName[],int vbRegion[][NO_OF_REGIONS], int tVotes[],int noOfRows)
{
	int i,j;
	int largestVotes = 0;
	int winLoc = 0;
	int sumVotes =0;

	for (i=0; i<noOfRows; i++)
    {
        if (largestVotes < tVotes[i])
        {
        	largestVotes = tVotes[i];
        	winLoc =i;
        }

        sumVotes = sumVotes +tVotes[i];

        cout << left;
        cout << setw(9) << cName[i] << " ";
        cout <<right;

        for (j=0;j < NO_OF_REGIONS; j++)
        	cout << setw(8) << vbRegion[i][j] << " ";
        cout << setw(6) << tVotes[i] << endl; 
    }

    cout << endl << endl << "Winner: "<<cName[winLoc]
         <<",Votes Received: " << tVotes[winLoc]
         << endl << endl;
    cout <<"Total votes polled: " <<sumVotes << endl;        
        
}

