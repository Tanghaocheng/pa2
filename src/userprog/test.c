#include<string.h>
#include<stdio.h>
#include<stdlib.h>
void
main()
{
	char c[]="abc";
	char *d;
	d=malloc(strlen(c));
	strcpy(d,c);
	printf("%s\n",d);
	printf("%d\n",d[3]);
	/*printf("%s\n",c[3]);
	char s[] = "  String to  tokenize. ";
	char a[] = "  String to  tokenize. ";
   char *token, *save_ptr;
	printf ("'%s'\n", s);
   for (token = strtok_r (s, " ", &save_ptr); token != NULL;
        token = strtok_r (NULL, " ", &save_ptr))
     printf ("'%s'\n", token);
     printf ("'%s'\n", s);
       for (token = strtok_r (a, " ", &save_ptr); token != NULL;
        token = strtok_r (NULL, " ", &save_ptr))
     printf ("'%s'\n", token);*/
	}
