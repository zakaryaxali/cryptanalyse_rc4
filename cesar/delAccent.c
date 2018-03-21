#include<stdio.h>
#include<stdlib.h>

#include<string.h>
#include"delAccent.h"


// supprimer dans un fichier texte les accents mais aussi la ponctuation et les majuscules 
// et pour les chiffres ???

void delAccent(char* fichier, char* new_file){
        // liste les caractères à supprimer ou remplacer
        // c'est un TABLEAU de tableau. Pour les tableaux de voyelles le premier caractère est celui que l'on souhaite voir apparaître à 
        // la place de ceux qui suivent.
        // 0 : A ; 1 : E ; 2 : I ; 3 : O ; 4 : U ; 5 : Ponctuation
        // déclaration des tableaux : 
        char voyelleA[10]; //={'a','à','â','\0'};
        char voyelleE[5];
        char voyelleI[4];
        char voyelleO[4];
        char voyelleU[5];              
        char **caracteres;
        caracteres = malloc(5*sizeof(unsigned char *)); 
        caracteres[0] = voyelleA;    
        caracteres[1] = voyelleE;
        caracteres[2] = voyelleI;
        caracteres[3] = voyelleO;
        caracteres[4] = voyelleU; 
        int c1;
        for(c1=0;c1<4;c1++){
                printf("%d\n",voyelleA[c1]);
        }
        // ouverture des fichiers      
        FILE* f;
        FILE* new_f;
        f= fopen(fichier,"r");
        new_f = fopen(new_file,"w");
        // on parcoure le fichier "fichier" char par char puis on le recopie correctement dans le fichier "new_file"
        unsigned char c;
        c = fgetc(f);
        /*            
        while(c!=255){
                // printf("%d\n",c);
                // on s'occupe des voyelles
                
                int i = 0;
                int bool1=0;              
                while (i<5 && bool1==0){
                        int j = 1;
                        int bool2 = 0;
                        while (caracteres[i][j]!='\0' && bool2 ==0){
                                if (caracteres[i][j]==c){
                                        printf("%d %d\n",caracteres[i][j],c);
                                        // printf("%d %d\n",i,j);
                                        // fputc(caracteres[i][0],new_f);
                                        bool1=1;
                                        bool2=1;                                                
                                } else {
                                        j = j +2;
                                }
                        } 
                        i++;                                              
                } 
                if (bool1==1){
                        bool1=0;
                } else {
                        fputc(c,new_f);
                        // printf("%d",c);
                } 
                c = fgetc(f);               
                                        
        }
         */                          
        fclose(f);
        fclose(new_f);
        
        
        
        
}
