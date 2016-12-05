#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory_things.h"

#define N 16
typedef struct instruct
{
    char inst[3];
    int hex_code;
    int warguments;
    char format[5];
    char uformat[6];
} instruction;
instruction insn[N];

FILE * archivo;
char datass[10000]="";
int whereAreColons[255][255];
int NumOfdots;
char linebyline[255][200];
char linebyline2[255][200];
char linebyline_alt[255][200];
char data[28];
char data_inHEX[10000];
int NL=0;
int NL2=0;
int nLabelTag=0;
int isok=0;
int Nlines=0;
int howManylinesdel=0;
int lineINLINE[2][0xFF];
/* lINL[0][lINL]=labelLine[i].line;
            lINL[1][lINL]=label1typeline[z];*/ //Remember
int lINL=0;

int replace_REALline(const char *);

int havelabel=0;

typedef struct LabelTag
{
    char name[20];
    int line;
    int type; //0 is individual or 1 is embedded
}LabeltLine;

LabeltLine labelLine[255];
int label1typeline[200]; //for save true lines to jump
int howmany1typel;

int label2typeline[200]; //for save true lines to jump (2nd type)
int howmany2typel;

void view_line_data(const char * stringTs,int y,int mode);
void check_if_has_syntaxe(); //check for error in syntaxis in block wothout colons.
void translate(); //translator::translate()
void put_fileheader(); //Put the ARCH_HEADER (v2.0 raw)
int verificar_dosp(); //Verify is the datass have colons
void where_lines_are_colons();
void replace_labels_for_numbers(); //Replace lines with coincidence

void general_delim(int); //To work with delimiter: ':'
void col_line_ind(int); //To took individual lines.
void col_line_emb(int); //To took embebeds lines.
void col_line_ind2nd(int y); //Delete all labels
void col_line_emb2nd(int y);

void choose_ind_emb(); //Choose between individual or embebed comments.
void ReadLBL(); //Go to text_utils::view_line_data()

void print_buffer_line(); //Print lines in buffer (lineByline array)
void clean_buffer_line(); //Clean buffer for new use
void debug_a_stringTs(const char * stringTs); //For view stringTss in HEX
void print_labelLines(); //print array structure of labelLine[]
int where_is_this_label(const char * stringTs);
int is_only_spaces(const char * stringTs); //1 if only space or 0 if not only space
void fold_void_lines(); //verify with function above and copy the new buffer linebyline
void verify_is_morecol(); //verify more than : colons
void same_label(); //verify have same label
void label_keyword(); //verify label is keyword
void the_labels_appears(); //verify if method appear in jmps or bra

int NLA=0;

void filter_ins(const char * stringTs,char ** getstringTs);

void the_labels_appears()
{
    int i,j,k,m;
    char * whl;
    char * zhl;
    int havejmpbra=0;
    char candidate[20];
    char caracter;
    int inuse=0;
    char ** data=arraystringTs_init(data,1,34);
    for(i=0;i<NL;i++)
    {
        filter_ins(linebyline[i],data);
        for(m=0;m<strlen(*data);m++)
            linebyline[i][m]=data[0][m];
        linebyline[i][m]='\0';
        char jmpbra[2][20]={"JMP","BRA"};
        for(m=0;m<2;m++)
        {
            whl=strstr(linebyline[i],jmpbra[m]);
            //printf("WHLL::: 0x%x with %s in %s\n",whl,jmpbra[m],linebyline[i]);
            if(!(whl==NULL))
            {
                havejmpbra=1;
                break;
            }
        }
        if(havejmpbra==1)
        {

            //printf("Line: %s\n",linebyline[i]);
            for(j=0;j<nLabelTag;j++)
            {

                whl=strstr(linebyline[i],labelLine[j].name);
                //printf("STRSTR: 0x%p\n",whl);

                    //printf("I: %d :: lL: %d\n",i,labelLine[k].line);
                    if(whl != NULL)
                    {

                            printf("SUPLABEL:: %s\n",labelLine[j].name);
                            //printf("POINTER:: 0x%x\n",*(whl+strlen(labelLine[j].name)+1));
                            //////////
                            m=0;
                            for(zhl=whl;*zhl!='\0';zhl++)
                            {
                                candidate[m]=*zhl;
                                m++;
                            }
                            candidate[m]='\0';
                            printf("CANDIDATE: %s\n",candidate);

                            if(strcmp(candidate,labelLine[j].name) == 0)
                            {
                                inuse=1;
                            }
                    }

            }

            if(inuse==0 && havejmpbra==1)
            {
                 printf("Error: Hay una etiqueta que no está en uso en la línea:\n %s \n Abortando...",linebyline[i]);
                 exit(1);
            }

        }
        havejmpbra=0;
        inuse=0;
    }

}

void print_buffer_line()
{
    int i;
    printf("Buffer Lines::\n");
    for(i=0;i<NL;i++)
	    printf("Line %d: %s\n",i,linebyline[i]);
}

void where_lines_are_colons()
{
    int i,j;
    char * pch;
    for(i=0;i<NL;i++)
    {
        pch=strchr(linebyline[i],0x3a);
        if(pch != NULL)
        {
            whereAreColons[0][NumOfdots]=i;
            whereAreColons[1][NumOfdots]=pch-linebyline[i];
            NumOfdots++;
        }

    }

    //print the list of columns
    for (i=0;i<NumOfdots;i++)
    {
        view_line_data(linebyline[whereAreColons[0][i]],whereAreColons[0][i],1); //filter lines with colons
        /*printf("LINE:: %d have colon in %d and end of stringTs have: %d :: %s\n",whereAreColons[0][i],whereAreColons[1][i],
               strlen(linebyline[whereAreColons[0][i]])-1,linebyline[whereAreColons[0][i]]);
        debug_a_stringTs(linebyline[whereAreColons[0][i]]);*/
    }

}

void read_lineBline()
{
    int i,j;
    j=0;
    char caracter;
    int consider=1;
    char anterior;
    //printf("RBL: %d\n",strlen(datass));
    for(i=0;i<strlen(datass);i++)
    {
        caracter=datass[i];
        if(caracter != '\n')
        {
	    //printf("chart::: %c\n",toupper(caracter));
            if(caracter!=';' && consider==1)
            {
                linebyline[NL][j]=toupper(caracter);
                linebyline2[NL2][j]=toupper(caracter);
            }
            else
                {
                    consider=0;
                }
	    //printf("CHAR:: 0x%X\n",linebyline[NL][j]);
	    j++;
        }
        else
        {
            consider=1;
            NL++;
            NL2++;
            j=0;
        }
    }
    NL+=1;

    fold_void_lines();

    //print_buffer_line();
    if (verificar_dosp())
    {

        printf("Puede que haya una etiqueta\n");
        choose_ind_emb();
        //verify is more than :
        verify_is_morecol();
        //have the same line
        same_label();
        //label is keyword
        label_keyword();
    }


    ReadLBL();

}

void verify_is_morecol()
{
    int colon_num=0;
    int i,j;
    int line;
    char strns[50]="";

    for(i=0;i<NL;i++)
    {
        line=replace_REALline(linebyline[i]);
        for(j=0;j<strlen(linebyline[i]);j++)
        {
            if(linebyline[i][j]== 0x3a)
            {
                printf("Hay más de un caracter \':\'\n... Abortando...");
                printf("Linea: %d\n",line);
                exit(1);
            }

        }
        colon_num=0;
    }
}

void same_label()
{
    int i, j;
    for(i=0;i<nLabelTag;i++)
    {
        for(j=0;j<nLabelTag;j++)
        {
            if((strcmp(labelLine[i].name,labelLine[j].name)==0) && (i != j))
            {
                printf("Error: Hay una etiqueta repetida: %s... Abortando...",labelLine[i].name);
                //printf("Línea: %d\n",line);
                exit(1);
            }
        }
    }
}

void label_keyword()
{
    int i, j;
    for(i=0;i<nLabelTag;i++)
    {
        for(j=0;j<N;j++)
        {
            if(strcmp(labelLine[i].name,insn[j].inst)==0)
            {
                printf("Error: Una etiqueta es un nemónico: %s... Abortando...\n",labelLine[i].name);
               // printf("Línea: %d\n",labelLine[i].line);
                exit(1);
            }
        }
    }
}


int is_only_spaces(const char * stringTs)
{
    int i;
    for(i=0;i<strlen(stringTs);i++)
    {
        if(stringTs[i] != 0x20 && stringTs[i] != '\n' && stringTs[i] != 0x09 )
            return 0;
    }
    return 1;
}

void fold_void_lines()
{
    int i;
    NLA=0;
    for(i=0;i<NL;i++)
    {
        if(is_only_spaces(linebyline[i]) == 0)
        {
            sprintf(linebyline_alt[NLA],"%s",linebyline[i]);
            NLA++;
        }
    }
    for(i=0;i<NL;i++)
        sprintf(linebyline[i],"");
    NL=NLA;
    for(i=0;i<NL;i++)
    {
        sprintf(linebyline[i],"%s",linebyline_alt[i]);
    }
}

void choose_ind_emb()
{
    int i;
    int whCol=0;
    int enLine=0;
    //print_buffer_line();
    where_lines_are_colons();
    for(i=0;i<NumOfdots;i++) //Loop for each dot, save in the structure
    {
        whCol=whereAreColons[1][i];
        enLine=strlen(linebyline[whereAreColons[0][i]])-1;
        //printf("LINE:: %d have colon in %d and end of stringTs have: %d :: %s\n",whereAreColons[0][i],whCol,
        //       enLine,linebyline[whereAreColons[0][i]]);
        //debug_a_stringTs(linebyline[whereAreColons[0][i]]);
        if(whCol == enLine)
            col_line_ind(i);
        else
            col_line_emb(i);
    }
    //print_labelLines();
    for(i=0;i<nLabelTag;i++) //Loop for modify the general structure and delete labels (2nd)
    {
        if(labelLine[i].type == 0)
            col_line_ind2nd(i);
        else
            col_line_emb2nd(i);
    }
    int z=0;
    for(i=0;i<nLabelTag;i++)
    {
        if(labelLine[i].type==0)
        {
            /*lineINLINE[0][lINL]=labelLine[i].line;
            lineINLINE[1][lINL]=label1typeline[z];
            lINL++;*/
            havelabel=1;
            labelLine[i].line=label1typeline[z];
            z++;
        }
    }
    z=0;
    for(i=0;i<nLabelTag;i++)
    {
        if(labelLine[i].type==1)
        {
            labelLine[i].line=label2typeline[z];
            z++;
        }
    }

    //print_labelLines();
    //The label needs to appear in JMPs or BRAs
    the_labels_appears();
    //Replace the found labels into line numbers
    replace_labels_for_numbers();
    //print_buffer_line();
}

void print_labelLines()
{
    int i;
    for(i=0;i<nLabelTag;i++)
        printf("Label: %s in line %d and is type %d\n",labelLine[i].name,labelLine[i].line,labelLine[i].type);
}

void general_delim(int y)
{
    int i;
    char caracter;
    //printf("LINE|| %s\n",linebyline[whereAreColons[0][y]]);

    for(i=0;i<strlen(linebyline[whereAreColons[0][y]]);i++)
    {
        caracter=linebyline[whereAreColons[0][y]][i];
        if(caracter != 0x3a)
            labelLine[nLabelTag].name[i]=caracter;
    }
    labelLine[nLabelTag].name[i]='\0';
}

void replace_labels_for_numbers()
{
    int i,j,k,m;
    char * whl;
    char * zhl;
    char rlabel[20];
    char candidate[20];
    char caracter;
    char ** data=arraystringTs_init(data,1,34);
    for(i=0;i<NL;i++)
    {
        //printf("Line %d: %s\n",i,linebyline[i]);
        filter_ins(linebyline[i],data);
        for(m=0;m<strlen(*data);m++)
            linebyline[i][m]=data[0][m];
        linebyline[i][m]='\0';
        for(j=0;j<nLabelTag;j++)
        {
            sprintf(rlabel,"%d",labelLine[j].line);
            //printf("RLabel: %s\n",rlabel);
            whl=strstr(linebyline[i],labelLine[j].name);
                //printf("I: %d :: lL: %d\n",i,labelLine[k].line);
                if(whl != NULL)
                {
                        //printf("SUPLABEL:: %s\n",labelLine[j].name);
                        //printf("POINTER:: 0x%x\n",*(whl+strlen(labelLine[j].name)+1));
                        //////////
                        m=0;
                        for(zhl=whl;*zhl!='\0';zhl++)
                        {
                            candidate[m]=*zhl;
                            m++;
                        }
                        candidate[m]='\0';
                        //printf("CANDIDATE: %s\n",candidate);

                        if( strcmp(candidate,labelLine[j].name) == 0 )
                        {
                            strncpy(whl,rlabel,strlen(rlabel));
                            linebyline[i][(int)(whl-linebyline[i])+strlen(rlabel)]='\0';
                        }
                }

        }

    }

}

int where_is_this_label(const char * stringTs) //TODO: delete this function??
{
    int i;
    for(i=0;i<nLabelTag;i++)
    {
        if (strcmp(stringTs,labelLine[i].name) == 0)
            return i;
    }
    return -1;
}

void col_line_ind(int y)
{
    int i;
    general_delim(y);
    labelLine[nLabelTag].line=whereAreColons[0][y];
    labelLine[nLabelTag].type=0;
    nLabelTag++;
    //printf("Took individual Line.\n");
}

void col_line_emb(int y)
{
    general_delim(y);
    labelLine[nLabelTag].line=whereAreColons[0][y];
    labelLine[nLabelTag].type=1;
    nLabelTag++;
    //printf("Took embedded Line.\n");
}

void col_line_ind2nd(int y)
{
    int i;
    //printf("Took 2nd ind.\n");
    sprintf(linebyline[labelLine[y].line],"");
    for(i=labelLine[y].line;i<NL-1;i++)
    {
        sprintf(linebyline[i],"%s",linebyline[i+1]);
    }
    //printf("I:::: %d\n",labelLine[y].line);
    lineINLINE[0][lINL]=whereAreColons[0][y];
    lineINLINE[1][lINL]=labelLine[y].line;
    lINL++;
    label1typeline[howmany1typel]=labelLine[y].line;
    howmany1typel++;
    for(i=0;i<nLabelTag;i++)
    {
        labelLine[i].line--;
    }
    NL--;
}

void col_line_emb2nd(int y)
{
    //printf("I:::: %d\n",labelLine[y].line);
    int h,i,SA;
    char backup[200];
    char caracter;
    char * whR;
    SA=1;
    h=labelLine[y].line;
    lineINLINE[0][lINL]=whereAreColons[0][y];
    lineINLINE[1][lINL]=labelLine[y].line;
    lINL++;
    backup[strlen(linebyline[h])]=0x20;
    char ** data=arraystringTs_init(data,1,34);
    for(i=0;i<strlen(linebyline[h]);i++)
    {
        caracter=linebyline[h][i];
        linebyline[h][i]=0x20;
        if(caracter==0x3a)
            break;
    }
    filter_ins(linebyline[h],data);
    for(i=0;i<strlen(*data);i++)
    {
        linebyline[h][i]=data[0][i];
    }
    linebyline[h][i]='\0';
    //debug_a_stringTs(linebyline[h]);
    /*printf("Backup:: \n");
    debug_a_stringTs(backup);*/

    label2typeline[howmany2typel]=h;
    howmany2typel++;
    //printf("Took 2nd emb.\n");
}

void ReadLBL()
{
    int i;
    //printf("NL:: %d\n",NL);
    	for(i=0;i<NL;i++)
    	{
            view_line_data(linebyline[i],i,0);
    	}
    	Nlines=NL-1;
}


void read_archivo(const char data[])
{
    int ch;
    int i=0;
    //char anterior;
    archivo=fopen(data,"r");

    while(1)
    {
    	ch=fgetc(archivo);
        if(ch!=EOF)
        {
                datass[i]=ch;
                i++;
            //printf("%c",ch);
        }
        else
            break;
    }
    fclose(archivo);
    //printf("Datos\n %s\n",datass);
    read_lineBline();
}


int verificar_dosp()
{
    int i;
    char caracter;
    for(i=0;i<strlen(datass);i++)
    {
	caracter=datass[i];
	if(caracter == 0x3a)
		return 1;
    }
    return 0;
}

void create__write_archivo(const char arch[])
{
    //archivo=fopen(arch,"r");
    /*if(archivo!=NULL)
    {
    	archivo=fopen(arch,"a");
   	printf("%s\n",data_inHEX);
	//sprintf(datass,data_inHEX);
	fprintf(archivo,"%s",data_inHEX);
    }
    else
    {*/
    printf("where save:: %s\n",arch);
    archivo=fopen(arch,"w+");
	fprintf(archivo,"%s","");
	fprintf(archivo,"%s",data_inHEX);
	//printf("NULL\n");
    //}
    fclose(archivo);

}

