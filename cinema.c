#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Student 7
#define FullPrice 10
struct hall{
    char *hallname;
    char *movie_name;
    int hallwidth;
    int hallhigh;
    int person1;
    int person2;
    int **cinema_plan;
};
int ticket_type(char x[]){
    if(strcmp(x,"Student")==0){
        return 1;
        }
    else if(strcmp(x,"FullFare")==0){
        return 2;
    }
    else
        return 0;
}

int find_asci(char x[]){
    char first_letter=x[0];
    return (first_letter-64);
}
int find_seat(char x[]){
    int coming_size=strlen(x);
    char remaining[coming_size];
    int remaining_number;
    int i;
    for(i=0;i<coming_size;i++){
        remaining[i]=x[i+1];
    }
    remaining_number=atoi(remaining);
    return  remaining_number;
}

int main(int argc,char *arg[])
{
    struct hall *halls;
    int line_number=0;
    int how_many_hall=0;
    FILE *fp1;
    char words_in_row[100];
    char *c;
    char *word;
    char captured_words[5][30];
    fp1 = fopen("input1.txt","r");
    do {
     c = fgets(words_in_row,100,fp1);
     if (c != NULL){
        word = strtok(c, " ");
        strcpy(captured_words[0],word);
        int i=1;
        if((strcmp(captured_words[0],("CREATEHALL"))==0)){
                if(how_many_hall==0){
                    halls=(struct hall*) calloc(1,sizeof(struct hall));
                    how_many_hall++;
                }
                else{
                    halls=(struct hall*) realloc(halls,sizeof(struct hall)*(how_many_hall+1));
                    how_many_hall++;
                }

            }
        int counter=1;
        while ((word = strtok(NULL, " ")) != NULL){
            strcpy(captured_words[i],word);
            i++;
            counter++;
        }
        line_number++;

        if((strcmp(captured_words[0],("CREATEHALL"))==0)){
            halls[how_many_hall-1].hallname=(char *)malloc(30*sizeof(char));
            halls[how_many_hall-1].movie_name=(char *)malloc(30*sizeof(char));
            strcpy(halls[how_many_hall-1].hallname,captured_words[1]);
            strcpy(halls[how_many_hall-1].movie_name,captured_words[2]);
            halls[how_many_hall-1].hallwidth=atoi(captured_words[3]);
            halls[how_many_hall-1].hallhigh=atoi(captured_words[4]);
             halls[how_many_hall-1].person1=0;
             halls[how_many_hall-1].person2=0;

        }
        else if((strcmp(captured_words[0],("BUYTICKET"))==0)){
                static int create=0;

                int z,w,x;
                if(create==0){
                    for(z=0;z<how_many_hall;z++){
                        halls[z].cinema_plan=(int **) calloc(halls[z].hallhigh*halls[z].hallwidth,sizeof(int));
                        for(w=0;w<halls[z].hallhigh;w++){
                            halls[z].cinema_plan[w]=(int *) calloc(halls[z].hallwidth,sizeof(int));
                        }
                    }
                create++;
                }

                for(z=0;z<how_many_hall;z++){
                    if((strcmp(captured_words[1],(halls[z].movie_name))==0)){
                        for(w=0;w<atoi(captured_words[4]);w++){
                            if(find_seat(captured_words[2])>halls[z].hallhigh || (find_asci(captured_words[2])+w)>halls[z].hallwidth){
                                printf("ERROR: Seat %s is not defined at %s\n",captured_words[2],halls[z].hallname);
                                break;
                            }
                            else if((halls[z].cinema_plan[find_seat(captured_words[2])-1][(find_asci(captured_words[2])+w)-1])!=0){
                                printf("ERROR: Specified seat(s) in %s are not available! They have been already taken.\n",halls[z].hallname);
                                break;
                            }
                            else if((halls[z].cinema_plan[find_seat(captured_words[2])-1][(find_asci(captured_words[2]))+w-1])==0){
                                    if(w==((atoi(captured_words[4]))-1)){
                                    if(((strcmp(captured_words[3],("Student")))==0)){
                                            halls[z].person1+=atoi(captured_words[4]);

                                    }
                                    if(((strcmp(captured_words[3],("FullFare")))==0)){
                                            halls[z].person2+=atoi(captured_words[4]);

                                        }
                                    printf("%s [%s] Seat(s) ",halls[z].hallname,captured_words[1]);
                                    for(x=0;x<atoi(captured_words[4]);x++){
                                    halls[z].cinema_plan[find_seat(captured_words[2])-1][((find_asci(captured_words[2]))+x)-1]=ticket_type(captured_words[3]);

                                    if(x==(atoi(captured_words[4])-1)){
                                               	   	printf("%c%d",find_asci(captured_words[2])+64+x,find_seat(captured_words[2]));
                                    }else{
                                               	   	printf("%c%d,",find_asci(captured_words[2])+64+x,find_seat(captured_words[2]));
                                         }
                                         }
                                    printf(" successfully sold.\n");
                                    }

                                }
                        }


                        }
                    }

        }
        else if((strcmp(captured_words[0],("CANCELTICKET"))==0)){
                int z;
                if((captured_words[1][1])==34){/* " --> 34 (ascii) */
                    printf("ERROR: Movie name cannot be empty\n");
                }
                else{
                for(z=0;z<how_many_hall;z++){
                    if((strcmp(captured_words[1],(halls[z].movie_name))==0)){
                        if((halls[z].cinema_plan[find_seat(captured_words[2])-1][find_asci(captured_words[2])-1])==0){
                            printf("ERROR: Seat %c%d in %s was not sold.\n",captured_words[2][0],find_seat(captured_words[2]),halls[z].hallname);
                        }
						else if((halls[z].cinema_plan[find_seat(captured_words[2])-1][find_asci(captured_words[2])-1])!=0){
                            if(((halls[z].cinema_plan[find_seat(captured_words[2])-1][find_asci(captured_words[2])-1])==1)){
                                            halls[z].person1-=1;

                                    }
                            else if(((halls[z].cinema_plan[find_seat(captured_words[2])-1][find_asci(captured_words[2])-1])==2)){
                                            halls[z].person2-=1;

                                        }
							halls[z].cinema_plan[find_seat(captured_words[2])-1][find_asci(captured_words[2])-1]=0;
                            printf("%s [%s] Purchase cancelled. Seat %c%d is now free.\n",(halls[z].hallname),(captured_words[1]),(captured_words[2][0]),(find_seat(captured_words[2])));

                        }
                        break;
                    }
                }
            }
        }
        else if((strcmp(captured_words[0],("SHOWHALL"))==0)){
            int z,i,j,k;
           char catching[30];
           int l=strlen(captured_words[1]);
           strcpy(catching,captured_words[1]);
           catching[l-1]='\0';
           printf("%s sitting plan\n",catching);
           for(z=0;z<how_many_hall;z++)
		   {
            	if((strcmp(catching,(halls[z].hallname))==0)){
            		printf("  ---------------------------------------------\n");
                	for(i=0;i<halls[z].hallhigh;i++){
                		if((i+1)>=10)
                   			printf("%d",i+1);
                   		else
							printf("%d ",i+1);

                    	for(j=0;j<halls[z].hallwidth;j++){
                            switch(halls[z].cinema_plan[i][j]){
                            case 0:printf("| ");break;
                            case 1:printf("|s");break;
                            case 2:printf("|f");break;
                            ;
                            }
                    	}printf("|\n");
                    	printf("  -------------------------------------------------------\n");

                	}
                	int y=0;
                	printf("   ");
                    	while(y<halls[z].hallwidth)
                    	{
                    		printf("%c ",y+65);
                    		y++;
						}
						printf("\n");
						y=0;
						while(y<halls[z].hallwidth/2+6){

						  printf(" ");
						y++;
						}
						printf("C U R T A I N\n");
           		}
           }
        }
        else if((strcmp(captured_words[0],("STATISTICS"))==0)){
                printf("Statistics\n");
                int x;
                for(x=0;x<how_many_hall;x++){
                	printf("%s %d student(s), %d full fare(s), sum:%d TL\n",halls[x].movie_name,halls[x].person1,halls[x].person2,halls[x].person1*Student+halls[x].person2*FullPrice);
                }
        }
        }
   } while (c != NULL);
    int q,t;
    for(q=0;q<how_many_hall;q++){
        free(halls[q].hallname);
        free(halls[q].movie_name);}
    return 0;
}


