#include <stdio.h>
#include <stdlib.h>

#define size 8


void getPosition(char *col, int *row);
int isValidCell(char col, int row);
void printBoard(char *board);
int isPieceMovable(char *board);
void initBoard(char *board);
int char_index(char col, int row);

// Moveable functions
int isPawnMovable(char *, char, int, char, int);

void emptyBuffer()
{
	while (getchar() != '\n');
}

int main()
{
	char board[64];
	int initComplete = 0;
	char empty;

	int command;
	scanf("%d", &command);

	while (command != 4)
	{
		switch (command)
		{
		case 1: initBoard(board);
			initComplete = 1;
			printf("OK\n");
			break;
		case 2:
			/*Read space character after command number*/
			scanf("%c", &empty);
			if (initComplete)
			{
				if (isPieceMovable(board))
					printf("YES\n");
				else
					printf("NO\n");
			}
			else
			{
				printf("Board is not initialized!\n");
				emptyBuffer();
			}
			break;
		case 3:
			if (initComplete)
				printBoard(board);
			else
				printf("Board is not initialized!\n");
			emptyBuffer();
			break;

		default: printf("Invalid command!\n"); emptyBuffer(); break;

		}

		scanf("%d", &command);

	}
}

// Girilecek olan rastgele tahta şekli
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

// Oyun tahtasının o anki halini verecek.
void printBoard(char *board) {

	int i, j;

	printf("  a b c d e f g h\n");
	printf("  - - - - - - - -");
	for (i = 0; i < size; ++i) {
		printf("\n");
		if ((i*size) % 8 == 0) {
			printf("%d", 8 - i);
			printf("|");
		}

		for (j = 0; j < size; j++) {
			if ((i*size + j) % 8 != 0)
				printf(" ");
			printf("%c", board[i*size + j]);

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
	char temp; // Bosluk okuma icin

	scanf("%c %d", col, row);
	scanf("%c", &temp);
}

int isPieceMovable(char *board) {

	char sourceCol, targetCol;
	int sourceRow, targetRow;
	int Ti, Si;

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

	if (isPawnMovable(board, sourceCol, sourceRow, targetCol, targetRow)) return 1;
	else return 0;
}

// Column ve Row belli olan taşın
// Dizideki konumunu bulan fonksiyon
int char_index(char col, int row) {
	return (abs(row - 8) * 8) + ((int)(col - 'a'));
}

// Piyonun ilerleyip ilerlemeyeceğini kontrol eder
int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	// Board sınırlarını kontrol eder
	// Sınırların dışında bir row değeri var ise 0 döndürür ve işi bitirir
	if (0 < sourceRow && sourceRow < 9 && 0 < targetRow && targetRow < 9)
	{
		// Piyonlar hareket etmesi için aynı satırda olmaları gerekir.
		if (sourceCol == targetCol)
		{
			// Eğer P ise;
			// Sadece row'da hareket eder
			// Önce girilen koordinatlardaki değerin P olup olmadığına bakılır, değilse 'p' else if a atlar
			// Row değeri 1 arttığında hedefteki row olması gerekir eğer değilse hareket edemez.
			// Sonra hedef row un boşluk olması gerekir yoksa hareket edemez.
			//
			if (board[char_index(sourceCol, sourceRow)] == 'P')
				if ((sourceRow + 1) == targetRow)
					if (board[char_index(targetCol, targetRow)] == ' ')
						return 1;
					else
						return 0;
				else
					return 0;
			// Eğer hedef 'p' ise
			// Piyon sadece row'da hareket eder
			// Girilen koordinatlardaki değerin 'p' olup olmadığına bakılır değilse piyon değildir Program devam eder return 0 olur
			// 'p' piyonunun hareket etmesi için row değerinin azalması gerekir
			// row değeri azaldığında target row olması gerekir ki hareket etsin
			// Hedef row boş olması gerekiyor ki hareket etsin, yoksa hareket edemez.
			else if (board[char_index(sourceCol, sourceRow)] == 'p')
				if ((sourceRow - 1) == targetRow)
					if (board[char_index(targetCol, targetRow)] == ' ')
						return 1;
					else
						return 0;
				else
					return 0;
			else
				return 0;
		}
		else
			return 0;
	}
	else
	{
		return 0;
	}

} // end funciton
