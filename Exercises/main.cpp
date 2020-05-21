/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: luca_dillenburg
 *
 * Created on May 11, 2019, 9:42 AM
 */

#include <bits/stdc++.h>
using namespace std;

void rain();
void numberOfStampedCards();
void war();
vector<vector<int>> threeSum(vector<int>& nums);
int auxPeak(const vector<int>& nums);
int semente();
int peakIndex(vector<int> nums);

/*
 * 
 */
int main(int argc, char** argv) {

    rain();

    return 0;
}

void rain()
// https://olimpiada.ic.unicamp.br/pratique/p2/2016/f1/chuva/
{
    int amntSessions;
    cin >> amntSessions;
    
    //precisa ter uma barreira na esquerda e na esquerda
    int amntSessionsWithWater = 0;
    
    struct Partition
    {
        int height, amntSessions;
    } partitions[amntSessions]/*max length*/;
    int iLast=-1;
    
    for (int i=0; i<amntSessions; i++) //O(n)
    {
        int heightCurrSession;
        cin >> heightCurrSession;
        
        bool createPartition = false;
        if (i==0) //first session
            createPartition = true;
        else
        {
            //the current session can be
            //1. in a level below                      => new partition
            //1. in the same level as the last one     => increment number of sessions in the
            //2. higher than the last one              => see there
            
            const int heightLastHighPartition = partitions[iLast].height;

            if (heightCurrSession == heightLastHighPartition) // same level
                partitions[iLast].amntSessions++;
            else if (heightCurrSession > heightLastHighPartition) // level up
            {
                //back n partitions (and add the sessions as with water)
                do
                {
                    //if there is a left barrier to this partition
                    if (iLast>0/*so that there is something before the last*/ && 
                            partitions[iLast-1].height > partitions[iLast].height)
                        amntSessionsWithWater += partitions[iLast].amntSessions;
                    iLast--;
                }while (iLast>=0 && heightCurrSession > partitions[iLast].height);
                
                //if the there is any partition left, see if the current partition is in the same partition than the last or if it will be necessary to create another partition
                if (iLast >= 0)
                {
                    if (heightCurrSession == partitions[iLast].height)
                        partitions[iLast].amntSessions++;
                    else
                        createPartition = true;
                }
                else
                    createPartition = true;
            }else /*if (heightCurrSession < heightLastHighPartition)*/ // level down                
                createPartition = true;
        }
        
        if (createPartition)
        {
            iLast++;
            partitions[iLast].height = heightCurrSession;
            partitions[iLast].amntSessions = 1;
        }
    }
    
    cout << amntSessionsWithWater;
}

/*METODOS:*/

//FREQUENCY ARRAY => O(n)
void numberOfStampedCards() {
    //read inputs (and put in array) - O(n)
    int amntAlbumCards, amntStampedCards, amntBoughtCards;
    cin >> amntAlbumCards >> amntStampedCards >> amntBoughtCards;
    
    int* stampedCards = new int[amntStampedCards]; //O(n)
    for (int i=0; i<amntStampedCards; i++)
        cin >> stampedCards[i];
     
    // populate frequency array
    bool frequencyArray[amntAlbumCards]; //posicoes da memoria estao com lixo - O(n)
    memset(frequencyArray, false, sizeof(frequencyArray)); // setar todas as posicoes do vetor com zero
    for (int i=0; i<amntBoughtCards; i++) //O(n)
    {
        int currBoughtCard;
        cin >> currBoughtCard;
        
        frequencyArray[currBoughtCard] = true;
    }
    
    // resolve
    int amntStampedCardsNotBought = 0;
    for (int i=0; i<amntStampedCards; i++) //O(n)
    {
        if (!frequencyArray[stampedCards[i]])
            amntStampedCardsNotBought++;
    }
    
    cout << amntStampedCardsNotBought;
}

void war() {
    //get input
    int s;
    cin >> s;
    
    int skillsQuadronians[s];
    for (int i=0; i<s; i++)
        cin >> skillsQuadronians[i];
    
    int skillsNlogonians[s];
    for (int i=0; i<s; i++)
        cin >> skillsNlogonians[i];

    //resuolution
    sort(skillsQuadronians, skillsQuadronians+s); //O(n log n)
    sort(skillsNlogonians, skillsNlogonians+s); //O(n log n)
    
    int amntBattlesWin = 0;
    int iNlogonians=s-1, iQuadronians=s-1; //indexes
    while(iQuadronians>=0) //O(n)
    {
        if (skillsNlogonians[iNlogonians] > skillsQuadronians[iQuadronians])
        {
            amntBattlesWin++;
            iNlogonians--;
        }
        iQuadronians--;
    }
    cout << amntBattlesWin;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    //Solution: O(N^2). using sort

    std::sort(nums.begin(), nums.end()); //sort
    vector<vector<int>> res;

    const int length = nums.size(); //length
    for (int i=0; i<length; i++)
    {
        const int sumTarget = -nums[i]; //-a = b+c

        //if the target sum is less than zero, it means that you are already on the positive side of the sequence (and in this side you cannot have 3 values that summed up, results in zero)
        if (sumTarget < 0)
            break;

        int front = i+1;
        int back = length-1;

        //find all pairs that summed up results in sumTarget (set the pointer to the begin and end and moving it depending on the values)
        while (front < back)
        {
            const int sum = nums[front] + nums[back];

            if (sum > sumTarget) //it means the back is too to the right
                back--;
            else if (sum < sumTarget) //it means the front is too to the left
                front++;
            else //the sum is equal to the target
            {
                vector<int> triplet {-sumTarget, nums[front], nums[back]};
                res.push_back(triplet);

                // Processing duplicates of Number 2: Rolling the front pointer to the next different number forwards
                while (front < back && nums[front] == triplet[1])
                    front++;

                // Processing duplicates of Number 3: Rolling the back pointer to the next different number backwards
                while (front < back && nums[back] == triplet[2])
                    back--;
            }
        }

        // Processing duplicates of Number 1
        while (i + 1 < length && nums[i + 1] == nums[i]) 
            i++;
    }

    return res;
}

int peakIndex(int* nums, int size) //index of peak (i): nums[i-1] < nums[i] > nums[i+1]
{
    //a array necessarially has at least one peak. when after many divisions there's only a element left, that's one peak
    //ex: [1]=>i:0, [1,2]=>i:1

    int low = 0;
    int high = size-1;
    while(low < high)
    {
        int mid = (high + low)/2;
        if (nums[mid] > nums[mid+1])
        //if the middle element is higher than the one in the right, the peak is the middle or one element in the left of the middle
        //(nums[mid-1]>nums[mid] => i:mid; else: nums[mid-2]>mid[mid-1] => return mid;... until mid=0)
            high = mid;
        else
        //for the same reason, if the middle element is shorter, the peak element is in the right of the middle
            low = mid + 1;
    }
    return low; //here: low==high => the elements was restricted to one (being certain that the peak is in the side chosen)
}

int dropsOfSeed()
{
    int amntPositions, amntDrops;
    cin >> amntPositions >> amntDrops;
    
    int maxDays = 0;
    int lastDropPos = 0;
    
    for (int i=0; i<amntDrops; i++)
    {
        int currPosition;
        cin >> currPosition;
        
        int days;
        if (i == 0)
            days = currPosition -1;
        else
            days = ceil((currPosition-lastDropPos-1)/2.0f);
        
        if (days > maxDays)
            maxDays = days;
        
        lastDropPos = currPosition;
        
        if (i == amntDrops -1)
        {
            int daysToRibbonEnd = amntPositions - lastDropPos;
            if (daysToRibbonEnd > maxDays)
                return daysToRibbonEnd;
            else
                return maxDays;
        }
    }
}

int myAtoi(string str)
{
    const int imin = numeric_limits<int>::min();
    const int imax = numeric_limits<int>::max();
    
    long int ret = 0;
    bool numericStarted = false;
    bool positive = true;
    for (char &c : str)
    {
        if (c>='0' && c<='9')
        {
            numericStarted = true;
            
            int n;
            switch (c)
            {
                case '0': n = 0; break;
                case '1': n = 1; break;
                case '2': n = 2; break;
                case '3': n = 3; break;
                case '4': n = 4; break;
                case '5': n = 5; break;
                case '6': n = 6; break;
                case '7': n = 7; break;
                case '8': n = 8; break;
                case '9': n = 9; break;
            }
            
            if (positive)
                ret = ret*10 + n;
            else
                ret = ret*10 - n;
            
            if (ret < imin)
                return imin;
            if (ret > imax)
                return imax;
        }else if (c=='+' || c=='-')
        {
            if (numericStarted)
                break; //ignore the characters after the numeric value
            
            numericStarted = true; //its not acceptable for a character different from a number come next
            if (c=='-')
                positive = false;
        }else
        {
            if (c!=' ' || numericStarted)
                break;
        }
    }
    
    return ret;
}
