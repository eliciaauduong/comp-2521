/*
Implement your algorithm in C. Your program should accept a single command line 
argument, and check whether it is a palindrome. Examples of the program executing are
./palindrome racecar
yes
./palindrome reviewer
no
Hint: You may use the standard library function strlen(3), which has prototype 
size_t strlen(char *), is defined in <string.h>, and which computes the length 
of a string (without counting its terminating '\0'-character). 
*/

// TIME COMPLEXITY: O(n)

int isPalindrome(char *string) {
	int length = strlen(string);
	for (int i = 0; i < length; i++) {
        if (string[i] != string[length - i - 1]) {
            return 0;
        }
	}

    return 1;
}
