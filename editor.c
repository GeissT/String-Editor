/* Basic String Editor written in C, hacks by Geisst
 * Original Source: Page 463, "Program Design and Problem Solving in C"
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define HIGHTH     30000
#define MAX_LEN    300
#define NOT_FOUND -1

char *delete(char *source, int index, int n);
char *do_edit(char *source, char command);
char* get_command(void);
char *insert(char *source, const char *to_insert, int index);
int  pos(const char *source, const char *to_find);

char memory[HIGHTH][MAX_LEN],high=0;

int main(void)
{
	char *command,*source;
	source=memory[high];
	printf("Enter the source string: \n");
	gets(source);
	printf("\nWarning:\nCommand should start with \"^\",or we will use the method \"append\".\n");

	for (command = get_command(); (command[0]=='^' && command[1]!='Q')||(command[0]!='^'); command = get_command()) {
		
		if(command[0]!='^')
			strcat(source,command);
		else
		{
			do_edit(source, command[1]);
			if(command[1]=='N'||command[1]=='L') source=memory[high];
		}
		
		printf("New source: %s\n\n", source);
	}

	{
		int i;
		for(i=0;i<MAX_LEN;i++) printf("%s\n",memory[i]);
	}
	
	return(0);
}

/* Delete function
 * ---------------
 * Delete's parts of the entered string
 */
char *delete(char *source, int index, int n)
{
	char rest_str[MAX_LEN]; // The rest of the string

	// No characters after the deleted portion? Delete ALL!

	if(strlen(source) <= index + n) {
		source[index] = '\0';
	} else {
		strcpy(rest_str, &source[index + n]);
		strcpy(&source[index], rest_str);
	}
	return(source);
}

/* Edit Function
 * -------------
 * Edits the string with what ever modification the user wishes
 */

char *do_edit(char *source, char command)
{
	char str[MAX_LEN]; // String that the editor will work with
	int index;

	switch(command) {
	case 'N':
		high++;
		break;
	case 'L':
		high--;
		break;
	case 'D':
		printf("String to delete: \n");
		gets(str);
		index = pos(source, str);
		if(index == NOT_FOUND)
			printf("'%s' not found!\n", str);
		else
			delete(source, index, strlen(str));
		break;
	case 'B':
		printf("How many backspaces do you want? \n");
		{
			int n,i;
			char *p;
			scanf("%d",&n);
			p=source+strlen(source);
			for(i=0;i<=n;i++)
			{
				*p=(char) 0;
				p--;
			}
		}
		break;
	case 'I':
		printf("String to insert: \n");
		gets(str);
		printf("Position of insertion: \n");
		scanf("%d", &index);
		insert(source, str, index);
		break;
	case 'A':
		printf("String to append: \n");
		gets(str);
		strcat(source,str);
		break;
	case 'F':
		printf("String to find: \n");
		gets(str);
		index = pos(source, str);
		if(index == NOT_FOUND)
			printf("'%s' not found\n", str);
		else
			printf("'%s' found at position: %d\n", str, index);
		break;
	default:
		printf("Invalid command: '%c'\n", command);
	}
	return(source);
}

/* Command Listener
 * ----------------
 * Listens for commands and interprets them
 */
char* get_command(void)
{
	static char command[MAX_LEN];

	printf("Methods:(N)ext, (L)ast, (D)elete, (B)ackspace, (I)nsert, (A)ppend, (F)ind or (Q)uit: ");
	gets(command);
	if (command[0]=='^') command[1]=toupper(command[1]);
	return(command);
}

/* Insert Function
 * ---------------
 * Inserts text into the string
 */
char *insert(char *source, const char *to_insert, int index)
{
	char rest_str[MAX_LEN]; // Rest of the string

	if(strlen(source) <= index) {
		strcat(source, to_insert);
	} else {
		strcpy(rest_str, &source[index]);
		strcpy(&source[index], to_insert);
		strcat(source, rest_str);
	}
	return(source);
}

/* Position function
 * -----------------
 * Returns index of first occurance of to_find in source or
 * value of NOT_FOUND if to_find is not in source.
 */
int pos(const char *source, const char *to_find)
{
	int i = 0, find_len, found = 0, position;
	char substring[MAX_LEN];

	find_len = strlen(to_find);

	while(!found && i <= strlen(source) - find_len) {
		strncpy(substring, &source[i], find_len);
		substring[find_len] = '\0';

		if(strcmp(substring, to_find) == 0)
			found = 1;
		else
			++i;
	}

	if(found)
		position = i;
	else
		position = NOT_FOUND;

	return(position);
}
