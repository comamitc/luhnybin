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
#define SMALLBUFFER 25

int matches[SMALLBUFFER];

void build_case(char cc[], int len);
int looney(int d[], int i);
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
		build_case(str, len);
		printf("%s\n", str);
		fflush(stdout);
	}
	return 0;
}

/*
		Iterate through the string detecting digits
		if 14+ digits are found, see if they pass the Luhn Algorithm
		if they do, iterate up to a range of 16 (if possible)
		mask as things are found to match the pattern that way a 1,000 character
		string that matches the alg tests gets masked entirely in 16 character sets
*/
void build_case(char cc[], int len)
{
	int j = (len - 1), i = 0, max = 0, start_ind = 0, temp_max = 0, idx = 0;
	int digits[BUFFER];
	
	//convert all numbers to ints
	while (j >= 0){
		char dchar = cc[j];
		if (dchar <= '9' && dchar >= '0'){		
			matches[i] = j;
			digits[i++] = ctoi(dchar);
			
			// once we record at least 14 digits we need to check luhn alg
			// and mask accordingly and incrementally
			if (i >= 14){
				temp_max =  looney(digits, i);
				if (temp_max >= max){
					max = temp_max;
					idx = start_ind = (i - 1);
					while ((start_ind - idx) < max){
						cc[matches[idx--]] = 'X';
					}
				}
			}
		}
		j--;
	}
}


/*
		Iterate through the string detecting digits
		if 14+ digits are found, see if they pass the Luhn Algorithm
		if they do, iterate up to a range of 16 (if possible)
		mask as things are found to match the pattern that way a 1,000 character
		string that matches the alg tests gets masked entirely in 16 character sets
*/
int looney(int d[], int i)
{
	int depth = MINSIZE,  max_seq = 0;
	while (depth <= MAXSIZE && depth <= i) {
		int sum = 0, upper = i, iter = (i - depth), j = 0;
		while (upper > iter) {	
			int num;			
			
			if ((j % 2) != 0)
				num = d[iter] << 1;
			else
				num = d[iter];
			
			if (num > 9)
				sum += (1 + (num % 10));			
			else 
				sum += num;
				
			iter++;
			j++;
		}
		if ((sum % 10) == 0)
			max_seq = depth;

		depth++;
	}
	return max_seq;
}


/*
	Convert single chars to ints
	-> will work on letters too return thier int equivalent
*/
int ctoi(char c)
{
	return (c - '0');
}
