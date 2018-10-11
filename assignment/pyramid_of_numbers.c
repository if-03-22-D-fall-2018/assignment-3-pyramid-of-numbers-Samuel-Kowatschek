

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193


/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2DHIF
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
#include <math.h>

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

void put_digits_to_the_right(struct BigInt *big_int);

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
	char userInput[80];
	printf("Pyramid of numbers\n\n");
	printf("Please enter a number: " );
	scanf("%s",userInput );
	int len=strlen(userInput);
	len=strtobig_int(userInput, len, &firstNumber);
	firstNumber.digits_count=len;
	print_big_int(&firstNumber);
	printf("\n%d\n",len);

	multiply(&firstNumber, 9, &result);
	printf("\n\n");
	print_big_int(&result);

	divide(&firstNumber, 9, &result);
	print_big_int(&result);
	printf("\n");

	print_big_int(&firstNumber);
	print_big_int(&result);
	printf("\n\n");

	copy_big_int(&firstNumber, &result);
	print_big_int(&firstNumber);
	print_big_int(&result);

	printf("end");



	return 0;
}

int strtobig_int(const char *str, int len, struct BigInt *big_int){
	int counter=0;
	for (size_t i = 0; i < len; i++) {
		if(str[i]>='0'&&str[i]<='9'){
			int temp=str[i]-'0';
			big_int->the_int[counter] = temp;
			counter++;
		}else{
            return -1;
		}
	}
    return counter;
}

void print_big_int(const struct BigInt *big_int){
    for (int i=0; i < big_int->digits_count; i++) {
        printf("%d",big_int->the_int[i] );
    }
 }
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result){
	int overflowNumber=0;
	int newOverflowNumber=0;
	int tempResult;
	big_result->digits_count=big_int->digits_count;
	for (size_t i = big_int->digits_count-1; i >= 0 && i<big_result->digits_count; i--) {
		tempResult=big_int->the_int[i]*factor+overflowNumber;
		if(tempResult>9){
			newOverflowNumber=tempResult/10;
			if(i==0){
				big_result->the_int[i]=tempResult%10;
				big_result->digits_count++;
				put_digits_to_the_right(big_result);
				big_result->the_int[i]=newOverflowNumber;
			}else{
				big_result->the_int[i]=tempResult%10;
			}
			overflowNumber=newOverflowNumber;
		}else{
				big_result->the_int[i]=tempResult%10;
		}
	}
}

void put_digits_to_the_right(struct BigInt *big_int){
	for (int i= big_int->digits_count-1 ; i >0; i--) {
		big_int->the_int[i]=big_int->the_int[i-1];
	}
}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result){
    int overflowNumber=0;
    int temp;
    int counter=0;
    bool alreadyNumberSetted=false;
    for(int i=0;i<big_int->digits_count;i++){
        temp=(big_int->the_int[i]+overflowNumber)/divisor;
        if(temp==0&&alreadyNumberSetted){

            big_result->the_int[counter]=(big_int->the_int[i]+overflowNumber)/divisor;
            counter++;
        }else if(temp!=0){
         alreadyNumberSetted=true;
         big_result->the_int[counter]=(big_int->the_int[i]+overflowNumber)/divisor;
         counter++;
        }
        overflowNumber=big_int->the_int[i]%divisor;
        overflowNumber*=10;
    }
    big_result->digits_count=counter;
}

void copy_big_int(const struct BigInt *from, struct BigInt *to){
    *to=*from;
}
