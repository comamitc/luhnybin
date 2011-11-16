/*
	optimization needed when allocating the arrays and strings
	'BUFFER' creates a bit of overhead

	some test numbers
	9875610591081018250321
	56613959932535089
	56613959932537
*/

#include <stdio.h>
#include <string.h>

#define MAXSIZE 16
#define MINSIZE 14
#define BUFFER 1024

int matches[BUFFER];

void looney(char cc[], int len);
int isdeca(int d[], int i);
int ctoi(char c);

int main (void)
{
	char str[BUFFER];
	char c;
	int len;
	/*
		Wait for the java code to throw us a bone
		then mask it and give ti back
	*/
	while (1){
		int j = 0;
		while ((c = getchar()) != '\n'){
			str[j++] = c;
		}
		str[j] = '\0';

		len = strlen(str);
		looney(str, len);
		printf("%s\n", str);
		fflush(stdout);
	}
	return 0;
}


void looney(char cc[], int len)
{
	int j = (len - 1), i = 0, max = 0, start_ind = 0, tmax = 0, idx = 0;
	int digits[BUFFER];
	
	//convert all numbers to ints
	while (j >= 0){
		char dchar = cc[j];
		if (dchar <= '9' && dchar >= '0'){		
			matches[i] = j--;
			digits[i++] = ctoi(dchar);
			
			//once we record at least 14 digits we need to mask
			if (i >= 14){
				tmax =  isdeca(digits, i);
				if (tmax >= max){
					max = tmax;
					start_ind = (i - 1);
					idx = start_ind;
					while ((start_ind - idx) < max){
						cc[matches[idx--]] = 'X';
					}
				}
			}
		} else { j--; } //need to index down even if none number
	}
}


int isdeca(int d[], int i)
{
	int depth = MINSIZE,  max_seq = 0;
	while (depth <= MAXSIZE && depth <= i) {
		int sum = 0, iter = i, lower = (i - depth), j = 0;
		while (iter > lower) {	
			int num;
			if ((j % 2) != 0) {
				num = d[lower] << 1;
			} else {
				num = d[lower];
			}
			
			if (num > 9) {
				//double digit num
				int second = num % 10;
				int first = num / 10;
				sum += (first + second);			
			} else {
				//single digit num
				sum += num;
			}
			lower++;
			j++;
		}
		if ((sum % 10) == 0) {
			max_seq = depth;
		}
		depth++;
	}
	return max_seq;
}

int ctoi(char c)
{
	return (c - '0');
}
