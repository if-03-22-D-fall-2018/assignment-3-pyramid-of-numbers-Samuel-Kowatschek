 /*				HTBLA-Leonding / Class: 2DHIF
 *----------------------------------------------------------
 * ---------------------------------------------------------
 * Exercise Number: 03
 * Title:			Pyramid of Numbers
 * Author:			Kowatschek Samuel
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
	struct BigInt firstNumber;
	struct BigInt result;
	char userInput[5];
	printf("Pyramid of numbers\n\n");
	printf("Please enter a number: " );
	scanf("%s",&userInput[0] );
	int len=strlen(userInput);
	len=strtobig_int(userInput, len, &firstNumber);
	firstNumber.digits_count=len;
	print_big_int(&firstNumber);
	printf("\n%d\n",len);
	multiply(&firstNumber, 5, &result);

	printf("\n\n");
	print_big_int(&result);


	return 0;
}

int strtobig_int(const char *str, int len, struct BigInt *big_int){
	int counter=0;
	for (int i = 0; i < len; i++) {
		if(str[i]>='0'&&str[i]<='9'){
			int temp=str[i]-'0';
			big_int -> the_int[i] = temp;
			counter++;
		}
	}
	return counter;
}


void print_big_int(const struct BigInt *big_int){
for (int i=0; i < big_int->digits_count; i++) {
	printf("%d",big_int->the_int[i] );
}
printf("\n");
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result){
	int overflowNumber=0;
		for (int i = big_int->digits_count-1 ; i >0; i--) {		     //for loop which counts from the end of the integer to the beginning, like we'd do it in reallife
			int tempResult=big_int->the_int[i]*factor;								//tempResult is the temporary Result

			if (tempResult>9) {																		//here we check if the tempResult is bigger than 9, because if it is, we'd have to split the two parts (e.g. 1 and 4 for 14) and put 1 to the next
					int temp=tempResult%10+overflowNumber;
					big_result->the_int[i]=temp;
					overflowNumber=tempResult/10;
				}else{
					int temp=tempResult%10+overflowNumber;
					big_result->the_int[i]=temp;
				}
			}
}
