#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char tab_conv[26][5]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
"-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--",
"-..-","-.--","--.."};

char tab_alphabet[27][2]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
"P","Q","R","S","T","U","V","W","X","Y","Z"," " };

int verif_coder(char * source)
{
  int i, len;
  len = strlen(source);

  for (i = 0 ; i < len ; i++)
  {
    if (!isalpha(source[i]) && source[i] != ' ')
      return 0;
    if( islower(source[i]) && source[i] != ' ')
    {
      source[i]-=32; /* passe une minuscule en majuscule */
    }
  }
  return 1;
}

char * coder(char * source)
{
  int i, j, len;

  char * code = malloc(1000 * sizeof(char));
  char * temp;

  if (!verif_coder(source))
  {
    printf("Un caractère n'est pas une lettre ou un espace\n");
    exit(0);
  }

  len = strlen(source);

  for ( i = 0 ; i < len ; i++)
  {
    if(source[i] != ' ')
    {
      temp = malloc( sizeof(char) * strlen(tab_conv[i]) );
      strcat(temp, tab_conv[source[i]-65]);
      strcat(code, temp);
      strcat(code, " ");
      free(temp);
    }
    else
      strcat(code, "---. ");
  }
  code = realloc(code, sizeof(char) * strlen(code));
}

int recherche_sequence(char * sequence)
{
  int i;
  if(!strcmp(sequence, "---."))
  {
    //printf("\ntrouvé espace");
    return 26;}

  for(i = 0 ; i < 26 ; i++)
  {
    if(!strcmp(sequence, tab_conv[i]))
    {
    //  printf("\nrecherche sequence :  i = %i", i);
      return i;
    }
  }
}

char * decoder (char * source)
{
  int i, j, ind, len;
  char * sequence;
  char * decode;

  decode = malloc(sizeof(char) * strlen(source));

  sequence = malloc(5 * sizeof(char));
  i = 0;
  len = strlen(source);

  for(i = 0 ; i < len ; i++)
  {
    //printf("\ni = %i", i);
    strcpy(sequence, "");
    j = 0;
    while(source[i] != ' ')
    {
        sequence[j] = source[i];
        j++;
        i++;
    }
  // printf("\n%s\n", sequence);
    ind = recherche_sequence(sequence);
    //printf("\n%i\n", ind);
    strcat(decode, tab_alphabet[ind]);
  }
  decode = realloc(decode, sizeof(char) * strlen(decode));
  return decode;
}


int main()
{
  char str[] = "A B C ";
  char str2[] = ".- ---. -... ---. -.-. ---. ";
  printf("%s\n", coder(str));
  printf("%s\n", decoder(str2));

}
