#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "struct.h"

int main()
{}

void test()
{
	Card c[2], test;
	test.color = COEUR;
	test.val = DEUX;
	c[0] = test;
}

int compare(const void* a, const void* b)
{
	return (*(enum Value*)a - *(enum Value*)b);
}

Card* mergeHand(Card* player_hand, Card* croupier_hand)
{
	Card* cp_hand = malloc(sizeof(Card) * 8); //combination of the player's hand and the croupier's hand
	cp_hand[0] = croupier_hand[0];
	cp_hand[1] = croupier_hand[1];
	cp_hand[2] = croupier_hand[2];
	cp_hand[3] = croupier_hand[3];
	cp_hand[4] = croupier_hand[4];
	cp_hand[5] = player_hand[0];
	cp_hand[6] = player_hand[1];
	return cp_hand;
}

enum Value isPair(Player p, Card* croupier_hand)
{
	int i, j;
	Card* cp_hand = malloc(sizeof(enum Value) * 8);
	cp_hand = mergeHand(p.hand, croupier_hand); //combination of the player's hand and the croupier's hand
	
	for(i=0 ; i<8 ; i++)
	{
		for(j=i+1 ; j<8 ; j++)
		{
			if(cp_hand[i].val == cp_hand[j].val)
			{
				enum Value val = cp_hand[i].val;
				free(cp_hand);
				return val;
			}
		}
	}
	free(cp_hand);
	return 0;
}

enum Value* isDoublePair(Player p, Card* croupier_hand)
{
	int i, j, k;
	Card* cp_hand = malloc(sizeof(Card) * 8);
	cp_hand = mergeHand(p.hand, croupier_hand); //combination of the player's hand and the croupier's hand
	
	enum Value* value = malloc(sizeof(enum Value) * 3);
	value[0] = 0;
	value[1] = 0;
	
	for(i=0 ; i<8 ; i++)
	{
		for(j=i+1 ; j<8 ; j++)
		{
			if(cp_hand[i].val == cp_hand[j].val)
			{
				if(value[0] == 0)
				{
					value[0] = cp_hand[i].val;
				}
				else if(cp_hand[i].val != value[0])
				{
					value[1] = cp_hand[i].val;
				}
			}
		}
	}
	free(cp_hand);
	if(value[0] && value[1])
		return value;
	return NULL;
}


enum Value isFull(Player p, Card* croupier_hand)
{
	int i, j, k;
	Card* cp_hand = malloc(sizeof(Card) * 8);
	cp_hand = mergeHand(p.hand, croupier_hand); //combination of the player's hand and the croupier's hand

	for(i=0 ; i<8 ; i++)
	{
		for(j=i+1 ; j<8 ; j++)
		{
			for(k=j+1 ; k<8 ; k++)
			{
				if(cp_hand[i].val == cp_hand[j].val && cp_hand[j].val == cp_hand[k].val)
				{
					enum Value val = cp_hand[i].val; 
					free(cp_hand);
					return val;
				}
			}
		}
	}
	free(cp_hand);
	return 0;
}

enum Value* isFlush(Player p, Card* croupier_hand)
{
	int i, j, k, l, m;
	Card* cp_hand = malloc(sizeof(Card) * 8);
	cp_hand = mergeHand(p.hand, croupier_hand); //combination of the player's hand and the croupier's hand

	for(i=0 ; i<8 ; i++)
	{
		for(j=i+1 ; j<8 ; j++)
		{
			for(k=j+1 ; k<8 ; k++)
			{
				for(l=k+1 ; k<8 ; k++)
				{
					for(m=l+1 ; k<8 ; k++)
					{
						if(cp_hand[i].color == cp_hand[j].color && cp_hand[i].color == cp_hand[k].color && cp_hand[i].color == cp_hand[l].color && cp_hand[i].color == cp_hand[m].color)
						{
							enum Value* val = malloc(sizeof(enum Value) * 6);
							val[0] = cp_hand[i].val;
							val[1] = cp_hand[j].val;
							val[2] = cp_hand[k].val;
							val[3] = cp_hand[l].val;
							val[4] = cp_hand[m].val;
							qsort(val, 5, sizeof(enum Value), compare);
							free(cp_hand);
							return val;
						}
					}
				}
			}
		}
	}
	free(cp_hand);
	return 0;
}

Winner getWinner(Player* player_list, Card* croupier_hand, int player_number)
{
	Winner w;
	w.comb = INIT;

	int i;
	for (i = 0; i < player_number; ++i)
	{
		enum Combination current = NONE;
		enum Value* val = malloc(sizeof(enum Value));
		

		if((val = isFlush(player_list[i].hand, croupier_hand)) != 0)
			current = FLUSH;
		else
		{
			if((val[0] = isFull(player_list[i].hand, croupier_hand)) != 0)
				current = FULL;
			else
			{
				if((val = isDoublePair(player_list[i].hand, croupier_hand)) != 0)
					current = DOUBLEPAIR;
				else
				{
					if((val[0] = isPair(player_list[i].hand, croupier_hand)) != 0)
						current = PAIR;
					else
						current = NONE;
				}
			}
		}
		
		if(current > w.comb)
		{
			w.player = player_list[i];
			w.comb = current;

			if(w.comb == DOUBLEPAIR)
			{
				w.value[0] = val[0];
				w.value[1] = val[1];

			}
			else if(w.comb == FLUSH)
			{
				w.value[0] = val[0];
				w.value[1] = val[1];
				w.value[2] = val[2];
				w.value[3] = val[3];
				w.value[4] = val[4];
			}
			else
			{
				w.value[0] = val[0];
			}
		}
		else if(current = w.comb)
		{
			switch(w.comb)
			{
				case NONE: 
				if(currentw.value)
				;
				case PAIR:
					if(val[0] > w.value[0])
					{
						w.value[0] = val[0];
						w.comb = current;
						w.player = player_list[i];
					}
					else if(val[0] == w.value[0])
					{
						if(player_list[i].hand[0] < player_list[i].hand[1])
						{
							if(w.player.hand[0] < w.player.hand[1])
							{
								if(player_list[i].hand[1] > w.player.hand[1])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
							else
							{
								if(player_list[i].hand[1] > w.player.hand[0])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];	
								}
							}
						}	
						else
						{
							if(w.player.hand[0] < w.player.hand[1])
							{
								if(player_list[i].hand[0] > w.player.hand[1])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
							else
							{
								if(player_list[i].hand[0] > w.player.hand[0])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
						}
					}
				;
				case DOUBLEPAIR:
					if(val[0] > w.value[0])
					{
						w.value[0] = val[0];
						w.comb = current;
						w.player = player_list[i];
					}
					else if(val[0] == w.value[0])
					{
						if(val[1] > w.value[1])
						{
							w.value[0] = val[0];
							w.comb = current;
							w.player = player_list[i];
						}
						if(player_list[i].hand[0] < player_list[i].hand[1])
						{
							if(w.player.hand[0] < w.player.hand[1])
							{
								if(player_list[i].hand[1] > w.player.hand[1])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
							else
							{
								if(player_list[i].hand[1] > w.player.hand[0])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];	
								}
							}
						}	
						else
						{
							if(w.player.hand[0] < w.player.hand[1])
							{
								if(player_list[i].hand[0] > w.player.hand[1])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
							else
							{
								if(player_list[i].hand[0] > w.player.hand[0])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
						}
					}
				;
				case FULL:
					if(val[0] > w.value[0])
					{
						w.value[0] = val[0];
						w.comb = current;
						w.player = player_list[i];
					}
					else if(val[0] == w.value[0])
					{
						if(player_list[i].hand[0] < player_list[i].hand[1])
						{
							if(w.player.hand[0] < w.player.hand[1])
							{
								if(player_list[i].hand[1] > w.player.hand[1])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
							else
							{
								if(player_list[i].hand[1] > w.player.hand[0])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];	
								}
							}
						}	
						else
						{
							if(w.player.hand[0] < w.player.hand[1])
							{
								if(player_list[i].hand[0] > w.player.hand[1])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
							else
							{
								if(player_list[i].hand[0] > w.player.hand[0])
								{
									w.value[0] = val[0];
									w.comb = current;
									w.player = player_list[i];
								}
							}
						}
				;
				case FLUSH:
				;
				default: break;
			}
		}
	}

	if(w.comb != INIT)
		return w;
	else
	{
		printf("Erreur fonction higherHand");
		exit(EXIT_FAILURE);
	}
}

DeckCard* initDeck()
{
	int i, j, pos = 0;
	DeckCard* deck = malloc(sizeof(DeckCard) * 53);
	for(i=1 ; i<14 ; i++)
	{
		for(j=1 ; j<5 ; j++)
		{
			deck[pos].card.color = j;
			deck[pos].card.val = i;
			deck[pos].AlreadyDrew = false;
			pos++;
		}
	}
	return deck;
}

Card drawCard(DeckCard* deck)
{
	int random;

	do
	{
		random = rand()%52;
	}while(deck[random].AlreadyDrew == true);

	deck[random].AlreadyDrew = false;
	return deck[random].card;
}

void setFalse(DeckCard* deck)
{
	int i;
	for(i=0 ; i<52 ; i++)
	{
		deck[i].AlreadyDrew = false;
	}
}

void dealCards(Player* player_list, Card* croupier_hand, int player_number, DeckCard* deck)
{
	int i;

	//On distribue d'abord une carte à chaque joueur
	for(i=0 ; i<player_number ; i++)
	{
		player_list[i].hand[0] = drawCard(deck);
	}
	//Puis une deuxième
	for(i=0 ; i<player_number ; i++)
	{
		player_list[i].hand[1] = drawCard(deck);
	}
	//On brule une carte
	drawCard(deck);
	//Puis les cartes du croupier
	for(i=0 ; i<5 ; i++)
	{
		if(i == 3 || i == 4)
			drawCard(deck);//On brule une carte
		croupier_hand[i] = drawCard(deck);	
	}
}
