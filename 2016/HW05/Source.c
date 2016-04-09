/*
*	Author: Muaz Duran
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8


void getPosition(char *col, int *row);
int isValidCell(char col, int row);
void printBoard(char *board);
int isPieceMovable(char *board);
void initBoard(char *board);
int char_index(char col, int row);

int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isBishopMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow); 
int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);

int isPieceMovable(char *board);


/* Moveable functions */
int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);

void emptyBuffer()
{
	while (getchar() != '\n');
}




/* Girilecek olan rastgele tahta şekli */
void initBoard(char *board) {

	int i;
	char temp[64] = {
		'r','n','b','q','k','b','n','r',
		'p','p','p','p','p','p','p','p',
		' ',' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ',' ',' ',' ',' ',
		'P','P','P','P','P','P','P','P',
		'R','N','B','Q','K','B','N','R'
	};

	for (i = 0; i < 64; i++)
		board[i] = temp[i];

}

/* Oyun tahtasının o anki halini verecek. */
void printBoard(char *board) {

	int i, j;

	printf("  a b c d e f g h\n");
	printf("  - - - - - - - -");
	for (i = 0; i < SIZE; ++i) {
		printf("\n");
		if ((i*SIZE) % 8 == 0) {
			printf("%d", 8 - i);
			printf("|");
		}

		for (j = 0; j < SIZE; j++) {
			if ((i*SIZE + j) % 8 != 0)
				printf(" ");
			printf("%c", board[i*SIZE + j]);

		}
		printf("|");

	}
	printf("\n");
	printf("  - - - - - - - -\n");

}

int isValidCell(char col, int row) {

	if ((((col >= 'a' && col <= 'h') || (col >= 'A' && col <= 'H'))) && (row >= 1 && row <= 8))
		return 1;
	else
		return 0;
}


void getPosition(char *col, int *row) {
	char temp; /* Bosluk okuma icin */

	scanf("%c %d", col, row);
	scanf("%c", &temp);
}

int isPieceMovable(char *board) {

	char sourceCol, targetCol;
	int sourceRow, targetRow;
    int a,b,c;
    a=0;
    b=0;
    c=0;
    
	getPosition(&sourceCol, &sourceRow);
	if (isValidCell(sourceCol, sourceRow) != 1)
	{
		emptyBuffer();
		return 0;
	}

	getPosition(&targetCol, &targetRow);
	if (isValidCell(targetCol, targetRow) != 1)
	{
		emptyBuffer();
		return 0;
	}

	a = char_index(sourceCol ,sourceRow);
	b = board [a];
	
	switch(b){

	case 'r':
	case 'R': c= isRookMovable(board, sourceCol, sourceRow, targetCol, targetRow); break;
	case 'n':
	case 'N': c= isKnightMovable(board, sourceCol, sourceRow, targetCol, targetRow);break;
	case 'b':
	case 'B': c= isBishopMovable(board, sourceCol, sourceRow, targetCol, targetRow);break;
	case 'q':
	case 'Q': c= isQueenMovable(board, sourceCol, sourceRow, targetCol, targetRow);break;
	case 'k':
	case 'K': c= isKingMovable(board, sourceCol, sourceRow, targetCol, targetRow);break;
	case 'p':
	case 'P': c= isPawnMovable(board, sourceCol, sourceRow, targetCol, targetRow);break;

	default: c=1; break;


	 
	}
	return c;
}

/* Column ve Row belli olan taşın
  Dizideki konumunu bulan fonksiyon */
int char_index(char col, int row) {
	return (abs(row - 8) * 8) + ((int)(col - 'a'));
}

/* Piyonun ilerleyip ilerlemeyeceğini kontrol eder */
int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	/* Board sınırlarını kontrol eder
	   Sınırların dışında bir row değeri var ise 0 döndürür ve işi bitirir */
	if (0 < sourceRow && sourceRow < 9 && 0 < targetRow && targetRow < 9)
	{
		/* Piyonlar hareket etmesi için aynı satırda olmaları gerekir. */
		if (sourceCol == targetCol)
		{
			/* Eğer P ise;
			   Sadece row'da hareket eder
			   Önce girilen koordinatlardaki değerin P olup olmadığına bakılır, değilse 'p' else if a atlar
			   Row değeri 1 arttığında hedefteki row olması gerekir eğer değilse hareket edemez.
			   Sonra hedef row un boşluk olması gerekir yoksa hareket edemez.
			*/
			if (board[char_index(sourceCol, sourceRow)] == 'P')
				if ((sourceRow + 1) == targetRow)
					if (board[char_index(targetCol, targetRow)] == ' ')
						return 1;
					else
						return 0;

				else
					return 0;

			/* Eğer hedef 'p' ise
			   Piyon sadece row'da hareket eder
			   Girilen koordinatlardaki değerin 'p' olup olmadığına bakılır değilse piyon değildir Program devam eder return 0 olur
			   'p' piyonunun hareket etmesi için row değerinin azalması gerekir
			   row değeri azaldığında target row olması gerekir ki hareket etsin
			  Hedef row boş olması gerekiyor ki hareket etsin, yoksa hareket edemez. */
			else if (board[char_index(sourceCol, sourceRow)] == 'p')
				if ((sourceRow - 1) == targetRow)
					if (board[char_index(targetCol, targetRow)] == ' ')
						return 1;
					else 
						return 0;
				else return 0;
			else return 0;
		}

		else if (board[char_index(sourceCol, sourceRow)] == 'p')
			{
				if ((sourceRow - 1) == targetRow)
				{	
					if( (sourceCol +1 ==targetCol) )
					{ 
						if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
							return 1;
						else 
							return 0;
					}
					if( (sourceCol -1 ==targetCol) )
					{
						if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
							return 1;
						else 
							return 0;
					}
				}
			}


			else if (board[char_index(sourceCol, sourceRow)] == 'P')
			{
				if ((sourceRow + 1) == targetRow)
				{	
					if( (sourceCol -1 ==targetCol) )
					{ 
						if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
							return 1;
						else 
							return 0;
					}
					if( (sourceCol +1 ==targetCol) )
					{
						if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
							return 1;
						else 
							return 0;
					}
				}
			}		

	}
return 0;
}


/* Queen'un ilerleyip ilerlemeyeceğini kontrol eder */
int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
int cikis;
cikis=0;
	/* Board sınırlarını kontrol eder
	   Sınırların dışında bir row değeri var ise 0 döndürür ve işi bitirir */
	if ((0 < sourceRow) && (sourceRow < 9) && (0 < targetRow) && (targetRow < 9))
	{	
		/* Asagi ve Yukari icin */
		if (sourceCol == targetCol)
		{	/* Yukari gidebilme*/
			if(sourceRow<targetRow)
			{
				/* Büyük R Yukarı giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'Q')
				{

					while (sourceRow != targetRow && cikis!=1)
					{
						sourceRow++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceRow==targetRow))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük Yukarı giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'q')
				{

					while (sourceRow != targetRow && cikis!=1)
					{
						sourceRow++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceRow==targetRow))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

			}
			/*Asagi gidebilme*/
			if(sourceRow>targetRow)
			{
				/* Büyük R asagi giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'Q')
				{
					while (sourceRow != targetRow)
					{
						sourceRow--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceRow==targetRow))						
								return 1;
							else 
								break;	
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük r asagi giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'q')
				{
					while (sourceRow != targetRow)
					{
						sourceRow--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceRow==targetRow))						
								return 1;
							else 
								break;	
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

			}	


		}

		/* Sol ve Sag icin */
		if (sourceRow == targetRow)
		{	/* Saga gidebilme*/
			if(sourceCol<targetCol)
			{
				/* Büyük R saga giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'Q')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük r saga giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'q')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

			}

			/* Sol gidebilme*/
			if(sourceCol>targetCol)
			{
				/* Büyük R sola giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'Q')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük r sola giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'q')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

			}
		}

		 
			/* Büyük B Yukarı saga  giderken yeme ve gidebilme */
		else if (board[char_index(sourceCol, sourceRow)] == 'Q')
			{
				if(targetRow>sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') && 
								(sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else {
								cikis=1; /* break kullanmamak icin bunu yaptim */}
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								printf("1\n");
								return 1;
							}
						}			
					}
				}
				/* Büyük B Yukarı sola giderken yeme ve gidebilme */
				else if(targetRow>sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* Büyük B Asagi sol giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') && (sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* Büyük B Asagi saga  giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

			}
			
			/* kücük b icin islemler */
			/* kücük Yukarı saga  giderken yeme ve gidebilme */
			if (board[char_index(sourceCol, sourceRow)] == 'q')
			{
				if(targetRow>sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') && 
								(sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else {
								cikis=1; /* break kullanmamak icin bunu yaptim */}
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* kücük Yukarı sol giderken yeme ve gidebilme */
				else if(targetRow>sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* kücük asagi sol giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* kücük asagi sag giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
			}	

	}	
return 0;	
}

/* Sahin ilerleyip ilerlemeyeceğini kontrol eder */
int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	/* Board sınırlarını kontrol eder
	   Sınırların dışında bir row değeri var ise 0 döndürür ve işi bitirir */
	if (0 < sourceRow && sourceRow < 9 && 0 < targetRow && targetRow < 9)
	{
		/*

		  Asagida if - elseif - else olacak :
		  If 	  => Sahin asagi yukari kontrolunu yapacak
		  Else if => Sahin sol sag kontrolunu yapacak
		  Else 	  => Else icinde 4 tane daha if olacak 
		  		  	 bu if'ler sirasiyla sol ust-
		  		  	 sag ust - sag alt - sol alt 
		  		  	 kontrolu yapacak 
		*/
		
		
		/************** Hem buyuk 'K' hem kucuk 'k' icin Asagi-Yukari kontrolu baslangici ***************/

		if (sourceCol == targetCol)
		{	
			/* Büyük K Yukarı giderken yeme ve gidebilme */
			if (board[char_index(sourceCol, sourceRow)] == 'K')
			{
				if ((sourceRow + 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
			}

			/* Kucuk k yukari giderken yiyebilme ve gidebilme kontrolu */
			if (board[char_index(sourceCol, sourceRow)] == 'k')
			{
				
				if ((sourceRow + 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') /* Bos bir yer varsa oraya gidebilir 
																		   ve if ile return sonucu 1 olur.Boylece 
																		   else if'e girmez ve cikar */
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
																		/* Ama eger if'e girmezse gidecegi yer bos degildir 
																		ve yeme hamlesi yapmalidir. If'i atlayıp if else geldi
																		bunu kontrol edecek ve dogru ise 1 degeri dondurecek. 
																		Yanlis ise else'e atlayacak*/
						return 1;
					else	
						return 0;
				}
			}
			else
				return 0;

			/* Büyük K Aşağı giderken yeme + gidebilme*/
			if (board[char_index(sourceCol, sourceRow)] == 'K')
			{
				if ((sourceRow - 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
			}
			/*Kucuk k asagi giderken yeme + gidebilme */
			if (board[char_index(sourceCol, sourceRow)] == 'k')
			{
				if ((sourceRow - 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else
						return 0;
				}
			}
			else
				return 0;
		}				
		/*********************************************ASAGI-YUKARI FONKSYIONLARININ BITISI*********************************/



		/*******************************************SOL VE SAG ICIN ******************************************************/
		else if (sourceRow == targetRow)
		{
			/*Buyuk İcin */
			if (board[char_index(sourceCol, sourceRow)] == 'K')
			{
				/*Sola gitmesi*/
				if ((sourceCol - 1) == targetCol)
				{	
					if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else if ((board[char_index(targetCol, targetRow)])== ' ')
						return 1;
					else 
						return 0;
				}

				/*Saga gitmesi*/
				if( (sourceCol +1 ==targetCol) )
				{
					if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else if ((board[char_index(targetCol, targetRow)])== ' ')
						return 1;
					else 
						return 0;	
				}
			}
			/*Kucuk k icin*/	
			if (board[char_index(sourceCol, sourceRow)] == 'k')
			{
				/*Sola gitmesi*/
				if ((sourceCol - 1) == targetCol)
				{	
					if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else if ((board[char_index(targetCol, targetRow)])== ' ')
						return 1;
					else 
						return 0;
				}

				/*Saga gitmesi*/
				if( (sourceCol +1 ==targetCol) )
				{
					if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else if ((board[char_index(targetCol, targetRow)])== ' ')
						return 1;
					else 
						return 0;	
				}
			}			

				
		}
			
		/**************************Sol sag kontrolu bitisi*******************************************************************/


		/************************Caprazlarin kontrolu************************************************************************/
		else 
		{
				/*Sol Ust  */
				if ((sourceCol - 1) == targetCol)
				{
					/*Buyuk K icin*/
					if (board[char_index(sourceCol, sourceRow)] == 'K')
					{
						if ((sourceRow + 1) == targetRow)
						{
							if (board[char_index(targetCol, targetRow)] == ' ') 
								return 1;
							else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
								return 1;
							else
								return 0;
						}
					}
					/*Kucuk K icin*/			
					if (board[char_index(sourceCol, sourceRow)] == 'k')
					{
						if ((sourceRow + 1) == targetRow)
						{
							if (board[char_index(targetCol, targetRow)] == ' ') 
								return 1;
							else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
								return 1;
							else
								return 0;
						}	
						
					}	
				else
					return 0;
				}
			/* Sağ alt */
			if ((sourceCol + 1) == targetCol)
			{	
				/*Buyuk K icin*/
				if (board[char_index(sourceCol, sourceRow)] == 'K')
				{
					if ((sourceRow - 1) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
							return 1;
						else
							return 0;
					}
				}
				/*Kucuk k icin*/
				if (board[char_index(sourceCol, sourceRow)] == 'k')
				{
					if ((sourceRow - 1) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
							return 1;
						else
							return 0;
					}
				}
			else 
				return 0;	
			}		
			/* Sag ust*/
			if ((sourceCol + 1) == targetCol)
			{
				/*Buyuk K icin*/
				if (board[char_index(sourceCol, sourceRow)] == 'K')
				{
					if ((sourceRow + 1) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
							return 1;
						else
							return 0;
					}
				}
				/*Kucuk k icin*/
				if (board[char_index(sourceCol, sourceRow)] == 'k')
				{
					if ((sourceRow + 1) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
							return 1;
						else
							return 0;
					}			
				}
			else
				return 0;	
			}
			/*Sol alt*/
			if ((sourceCol - 1) == targetCol)
			{
				/*Buyuk K icin*/
				if (board[char_index(sourceCol, sourceRow)] == 'K')
				{
					if ((sourceRow - 1) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
							return 1;
						else
							return 0;
					}
				}
				/*Kucuk k icin*/
				if (board[char_index(sourceCol, sourceRow)] == 'k')
				{
					if ((sourceRow - 1) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
							return 1;
						else
							return 0;
					}
				}	
				
			}
			else
				return 0;
			/**************************Caprazlarin kontrolu bitisi********************************************************************/
		}
	}
return 0;	
}






/* Atin ilerleyip ilerlemeyeceğini kontrol eder */
int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	/* Board sınırlarını kontrol eder
	   Sınırların dışında bir row değeri var ise 0 döndürür ve işi bitirir */
	if (0 < sourceRow && sourceRow < 9 && 0 < targetRow && targetRow < 9)
	{	
		/*4 durumdan birini hem kucuk n hem Buyuk N icin yapma*/
		if ((sourceCol+1) == targetCol)
		{	
			if (board[char_index(sourceCol, sourceRow)] == 'N')
			{	/* Büyük N ust sag uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow + 2) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
				/* Büyük N alt sag uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow - 2) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
			}

			else if (board[char_index(sourceCol, sourceRow)] == 'n')
				{	/* kücük n ust sag uzaga L seklinde giderken yeme ve gidebilme */
					if ((sourceRow + 2) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
							return 1;
						else
							return 0;
					}
					/* kücük n alt sag uzaga L seklinde giderken yeme ve gidebilme */
					if ((sourceRow - 2) == targetRow)
					{
						if (board[char_index(targetCol, targetRow)] == ' ') 
							return 1;
						else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
							return 1;
						else
							return 0;
					}
				}
			
		}

		/*4in 2si*/
		if ((sourceCol-1) == targetCol)
		{	
			if (board[char_index(sourceCol, sourceRow)] == 'N')
			{	/* Büyük N ust sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow + 2) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
				/* Büyük N alt sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow - 2) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
			}

			else if (board[char_index(sourceCol, sourceRow)] == 'n')
			{	/* kücük n ust sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow + 2) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else
						return 0;
				}
				/* kücük n alt sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow - 2) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else
						return 0;
				}
			}

		}
		/*4in 3ü*/
		if ((sourceCol+2) == targetCol)
		{	
			if (board[char_index(sourceCol, sourceRow)] == 'N')
			{	/* Büyük N ust sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow + 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
				/* Büyük N alt sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow - 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
			}

			else if (board[char_index(sourceCol, sourceRow)] == 'n')
			{	/* kücük n ust sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow + 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else
						return 0;
				}
				/* kücük n alt sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow - 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else
						return 0;
				}
			}

		}

		/*4ün 4ü*/
		if ((sourceCol-2) == targetCol)
		{	
			if (board[char_index(sourceCol, sourceRow)] == 'N')
			{	/* Büyük N ust sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow + 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
				/* Büyük N alt sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow - 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'a' && (board[char_index(targetCol, targetRow)]) <= 'z' )						
						return 1;
					else
						return 0;
				}
			}

			else if (board[char_index(sourceCol, sourceRow)] == 'n')
			{	/* kücük n ust sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow + 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else
						return 0;
				}
				/* kücük n alt sol uzaga L seklinde giderken yeme ve gidebilme */
				if ((sourceRow - 1) == targetRow)
				{
					if (board[char_index(targetCol, targetRow)] == ' ') 
						return 1;
					else if ((board[char_index(targetCol, targetRow)]) >= 'A' && (board[char_index(targetCol, targetRow)]) <= 'Z' )						
						return 1;
					else
						return 0;
				}
			}

		}
	}
return 0;	
}	


/* Rook'un ilerleyip ilerlemeyeceğini kontrol eder */
int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
int cikis;
cikis=0;
	/* Board sınırlarını kontrol eder
	   Sınırların dışında bir row değeri var ise 0 döndürür ve işi bitirir */
	if ((0 < sourceRow) && (sourceRow < 9) && (0 < targetRow) && (targetRow < 9))
	{	
		/* Asagi ve Yukari icin */
		if (sourceCol == targetCol)
		{	/* Yukari gidebilme*/
			if(sourceRow<targetRow)
			{
				/* Büyük R Yukarı giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'R')
				{

					while (sourceRow != targetRow && cikis!=1)
					{
						sourceRow++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceRow==targetRow))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük Yukarı giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'r')
				{

					while (sourceRow != targetRow && cikis!=1)
					{
						sourceRow++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceRow==targetRow))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

			}
			/*Asagi gidebilme*/
			if(sourceRow>targetRow)
			{
				/* Büyük R asagi giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'R')
				{
					while (sourceRow != targetRow)
					{
						sourceRow--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceRow==targetRow))						
								return 1;
							else 
								break;	
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük r asagi giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'r')
				{
					while (sourceRow != targetRow)
					{
						sourceRow--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceRow==targetRow))						
								return 1;
							else 
								break;	
						}
						else
						{
							if(sourceRow==targetRow)
							{
								return 1;
							}
						}			
					}
				}

			}	


		}

		/* Sol ve Sag icin */
		if (sourceRow == targetRow)
		{	/* Saga gidebilme*/
			if(sourceCol<targetCol)
			{
				/* Büyük R saga giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'R')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük r saga giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'r')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

			}

			/* Sol gidebilme*/
			if(sourceCol>targetCol)
			{
				/* Büyük R sola giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'R')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'a') && (board[char_index(sourceCol, sourceRow)] <= 'z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

				/* kücük r sola giderken yeme ve gidebilme */
				if (board[char_index(sourceCol, sourceRow)] == 'r')
				{

					while (sourceCol != targetCol && cikis!=1)
					{
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(sourceCol, sourceRow)] >= 'A') && (board[char_index(sourceCol, sourceRow)] <= 'Z') && (sourceCol==targetCol))						
								return 1;
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

			}
		}	

	}	
return 0;	
}



/* Bishop'un ilerleyip ilerlemeyeceğini kontrol eder */
int isBishopMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
int cikis;
cikis=0;
	/* Board sınırlarını kontrol eder
	   Sınırların dışında bir row değeri var ise 0 döndürür ve işi bitirir */
	if ((0 < sourceRow) && (sourceRow < 9) && (0 < targetRow) && (targetRow < 9))
	{	
			/* Büyük B Yukarı saga  giderken yeme ve gidebilme */
			if (board[char_index(sourceCol, sourceRow)] == 'B')
			{
				if(targetRow>sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') && 
								(sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else {
								cikis=1; /* break kullanmamak icin bunu yaptim */}
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								printf("1\n");
								return 1;
							}
						}			
					}
				}
				/* Büyük B Yukarı sola giderken yeme ve gidebilme */
				else if(targetRow>sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* Büyük B Asagi sol giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') && (sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* Büyük B Asagi saga  giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'a') && (board[char_index(targetCol, targetRow)] <= 'z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}

			}
			
			/* kücük b icin islemler */
			/* kücük Yukarı saga  giderken yeme ve gidebilme */
			if (board[char_index(sourceCol, sourceRow)] == 'b')
			{
				if(targetRow>sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') && 
								(sourceRow==targetRow && sourceCol==targetCol)){					
								return 1;}
							else {
								cikis=1; /* break kullanmamak icin bunu yaptim */}
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* kücük Yukarı sol giderken yeme ve gidebilme */
				else if(targetRow>sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow++;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* kücük asagi sol giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol < sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol--;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
				/* kücük asagi sag giderken yeme ve gidebilme */
				else if(targetRow<sourceRow && targetCol > sourceCol)
				{
					while ((sourceRow != targetRow) && (sourceCol !=targetCol) && cikis!=1)
					{
						sourceRow--;
						sourceCol++;
						if (board[char_index(sourceCol, sourceRow)] != ' ')
						{
							if ((board[char_index(targetCol, targetRow)] >= 'A') && (board[char_index(targetCol, targetRow)] <= 'Z') 
								&& (sourceRow==targetRow && sourceCol==targetCol)){
								return 1;}
							else 
								cikis=1; /* break kullanmamak icin bunu yaptim */
						}
						else
						{
							if(sourceRow==targetRow && sourceCol==targetCol)
							{
								return 1;
							}
						}			
					}
				}
			}		
	}					
return 0;	
}
