#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
	//read inputs (and put in array) - O(n)
	int amntAlbumCards, amntStampedCards, amntBoughtCards;
	cin >> amntAlbumCards >> amntStampedCards >> amntBoughtCards;

	int *stampedCards = new int[amntStampedCards]; //O(n)
	for (int i = 0; i < amntStampedCards; i++)
		cin >> stampedCards[i];

	// populate frequency array
	bool frequencyArray[amntAlbumCards];				   //posicoes da memoria estao com lixo - O(n)
	memset(frequencyArray, false, sizeof(frequencyArray)); // setar todas as posicoes do vetor com zero
	for (int i = 0; i < amntBoughtCards; i++)			   //O(n)
	{
		int currBoughtCard;
		cin >> currBoughtCard;

		frequencyArray[currBoughtCard] = true;
	}

	// resolve
	int amntStampedCardsNotBought = 0;
	for (int i = 0; i < amntStampedCards; i++) //O(n)
	{
		if (!frequencyArray[stampedCards[i]])
			amntStampedCardsNotBought++;
	}

	cout << amntStampedCardsNotBought;
}
