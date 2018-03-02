//Proyecto: Uso de Tablas Hash con resolucion de colisiones con AVL
//   Curso: Estructura de Datos
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#define thash 77
using namespace std;

int posc,num=0; 
char *Indatos; 
char pt1[5];
char colacaracteres[150];
char line[400];
char divi_token[] = {" \n\t"}; 
char tokenchar;
char* token;   
char *cadena1, *cadena2, *cadena3;
string cadena;
string tokenf;

FILE *ArchivoBinario;
FILE *ArchivoSalidaTransac=fopen("salida.txt", "w");

struct AVL{ 
   char cod[10];       //id
   char nombre[50];   //nombre
   char precio[10];   //cantidad
   char cantidad[50]; //lugar  
   int estado;
   struct AVL *izqda;
   struct AVL *drcha; 
   int altura; 
};

struct AVL *tabla[thash];

int posicion(char cod[10]);
void formarpalabra(string cadena);
void activametodos(string m, string p1, string p2, string p3,  string p4);
void buscar(struct AVL *tabla, int pt, char codx[]);
void eliminar(struct AVL *tabla, int pt, char codx[]);
void modificar(struct AVL *tabla, int pt, char codx[], char modcampo[], char newcampo[]);
int maximo(int a, int b);
int altura(struct AVL *n);
void Simple_derecha(AVL **A);
void Simple_izquierda(AVL **A);
void Doble_izquierda_derecha(AVL **A); 
void Doble_derecha_izquierda(AVL **A); 
void ajusta_AVL(char e[], AVL **A);
void insertarAVL(char codx[], char nombrex[], char preciox[], char cantidadx[], struct AVL **tabla);
void recorreAVL(struct AVL *P);
void recorreAVLaBin(struct AVL *P);
void mostrarCompleto();
void OperarArchivo();

int posicion(char code[10]){
    int r=0;
    int posicion2=0;
    int tamcode=strlen(code);
    for (int i=0;i<tamcode;i++){
        r=r+code[i];
    }
    posicion2=r%thash;
    return(posicion2);
}

void activametodos(string m, string p1, string p2, string p3,  string p4){
    int i=posicion((char*)p1.c_str());
	char *cadena1=(char*)p1.c_str();
	char *cadena2=(char*)p2.c_str();
	char *cadena3=(char*)p3.c_str();
	char *cadena4=(char*)p4.c_str();
	while((m=="insertar")&&(strcmp(cadena1,""))&&(strcmp(cadena2,""))&&(strcmp(cadena3,""))&&(strcmp(cadena4,""))){
		insertarAVL(cadena1, cadena2, cadena3, cadena4, &(tabla[i]));
		break;
	}
	while((m=="modificar")&&(strcmp(cadena1,""))&&(strcmp(cadena2,""))&&(strcmp(cadena3,""))){
		i=posicion((char*)p1.c_str());
		modificar(tabla[i],i,cadena1,cadena2,cadena3);   
		break;
	}
	while((m=="eliminar")&&(strcmp(cadena1,""))){
		i=posicion((char*)p1.c_str());
		eliminar(tabla[i],i,cadena1);
		break;
	}
	while(m=="ver"){
		fputs(" ---- @ ---- Datos recorriendo AVL por posicion ---- @ ----  \n",ArchivoSalidaTransac);
        mostrarCompleto();
		fputs(" ----------------------------------------------------------\n",ArchivoSalidaTransac);
		break;
	}
	while((m=="buscar")&&(strcmp(cadena1,""))){
		i=posicion((char*)p1.c_str());
		buscar(tabla[i],i,cadena1);
		break;
	}
};

void formarpalabra(string cadena){ 
	string palabra, numero; 
    string metodo, palabra1, palabra2, palabra3, palabra4;  
    int j=cadena.size();
    for (int i=0; i<j; i++){ 
       if (cadena[i]!=' '){
          colacaracteres[i]=cadena[i]; 
       }
    }
    int cont=1;
    for(int j=0; j<=150; j++){  
		if (colacaracteres[j]!='('&&colacaracteres[j]!=')'&&colacaracteres[j]!=','&&colacaracteres[j]!=' '){
			palabra=palabra+colacaracteres[j];
		}else{
			// se obtendra cada palabra como metodos y parametros
			if(cont==1){
			   metodo=palabra;
			   palabra="";
			}
			if(cont==2){
			   palabra1=palabra;
			   palabra="";
			}
			if(cont==3){
			   palabra2=palabra;
			   palabra="";
			}
			if(cont==4){
			   palabra3=palabra;
			   palabra="";
			}
			if(cont==5){
			   palabra4=palabra;
			   palabra="";
			}
			cont++;
		}
    }
    activametodos(metodo, palabra1, palabra2, palabra3, palabra4);
}

void mostrarCompleto(){
   for (int i=0; i<=thash; i++ ){
	   if (tabla[i]->cod!=NULL){
	      fputs("        Tabla en posicion -> [",ArchivoSalidaTransac);	
		  char astr[16];
		  int valor = i;
          sprintf(astr, "%d", valor);       
	      fputs(astr,ArchivoSalidaTransac);
          fputs("]\n",ArchivoSalidaTransac);
	      recorreAVL((tabla[i]));  
          fputs("\n",ArchivoSalidaTransac);
       } 
   }	
}

void buscar(struct AVL *tabla, int pt, char codx[10]){
	struct AVL *P=tabla;
	while (P!=NULL){
		int ca=atoi(string(codx).c_str());
		int ca1=atoi(string(P->cod).c_str());
		if (ca1>ca){
			P=P->izqda;
		}else{
			if (ca1<ca){
				P=P->drcha;
			}else{
				if (ca1==ca){
				   sprintf(pt1,"%d", pt);
				   fputs("  --> | ",ArchivoSalidaTransac);
				   fputs(pt1, ArchivoSalidaTransac);
				   fputs(" | ",ArchivoSalidaTransac);
				   fputs("<-- | ",ArchivoSalidaTransac);
				   fputs(P->cod, ArchivoSalidaTransac);
				   fputs(" | ",ArchivoSalidaTransac);
				   fputs(P->nombre, ArchivoSalidaTransac);
				   fputs(" | ",ArchivoSalidaTransac);
				   fputs(P->precio, ArchivoSalidaTransac);
				   fputs(" | ",ArchivoSalidaTransac);
				   fputs(P->cantidad, ArchivoSalidaTransac);
				   fputs(" | ",ArchivoSalidaTransac);
          	       if (P->estado==1) fputs("Activo",ArchivoSalidaTransac); else fputs("In-Activo",ArchivoSalidaTransac);
				   fputs(" | \n",ArchivoSalidaTransac);
				}
				break;
		    }
		}
	}
	if (P==NULL){
	   fputs("   No existe",ArchivoSalidaTransac);
	   fputs("\n",ArchivoSalidaTransac);
	}	
}

void eliminar(struct AVL *tabla, int pt, char codx[10]) {
	struct AVL *P=tabla;
	while (P!=NULL){
		int ca=atoi(string(codx).c_str());
		int ca1=atoi(string(P->cod).c_str());		
		if (ca1>ca){
			P=P->izqda;
		}else{
			if (ca1<ca){
				P=P->drcha;
			}else{
				if (ca1==ca){
                   P->estado=0;
				   fputs("   Paso a estado In-Activo",ArchivoSalidaTransac);
				   fputs("\n",ArchivoSalidaTransac);
				}
				break;
		    }
		}
	}
	if (P==NULL){
	   fputs("   No existe",ArchivoSalidaTransac);
	   fputs("\n",ArchivoSalidaTransac);
	}	
}

void modificar(struct AVL *tabla, int pt, char codx[10], char modcampo[], char newcampo[]) {
    char modnombrex[10], modpreciox[10], modcantidadx[10];
    strcpy(modnombrex,"nombre");strcpy(modpreciox,"precio");strcpy(modcantidadx,"cantidad");	
	struct AVL *P=tabla;
	while (P!=NULL){
		int ca=atoi(string(codx).c_str());
		int ca1=atoi(string(P->cod).c_str());
		if (ca1>ca){
			P=P->izqda;
		}else{
			if (ca1<ca){
				P=P->drcha;
			}else{
				if (ca1==ca){
					if (strcmp(modnombrex,modcampo) == 0)
					   strcpy(P->nombre,newcampo);
					else
					   if (strcmp(modpreciox,modcampo) == 0)
						  strcpy(P->precio,newcampo);
					   else
						  if (strcmp(modcantidadx,modcampo) == 0)
							 strcpy(P->cantidad,newcampo);
				   fputs("   Update realizado con exito",ArchivoSalidaTransac);
				   fputs("\n",ArchivoSalidaTransac);
				}
				break;
		    }
		}
	}
	if (P==NULL){
	   fputs("   No existe",ArchivoSalidaTransac);
	   fputs("\n",ArchivoSalidaTransac);
	}	
}

int maximo(int a, int b){
   if (a>b)
      return (a);
   else
      return (b);
}

int altura(struct AVL * n){
   if(n!=NULL)
      return(n->altura);
   else
      return(-1);
}

void Simple_derecha(AVL **A){ 
   AVL *p; 
   p=*A;
   p = (*A)->izqda; 
   (*A)->izqda = p->drcha; 
   p->drcha = (*A); 
   (*A) = p; 
   p = (*A)->drcha; 
   p->altura = maximo(altura(p->izqda),altura(p->drcha))+1; 
   (*A)->altura = maximo(altura((*A)->izqda),altura((*A)->drcha))+1;
}

void Simple_izquierda(AVL **A){ 
    AVL *p; 
    p = (*A)->drcha; 
    (*A)->drcha = p->izqda; 
    p->izqda = (*A); 
    (*A) = p; 
    p = (*A)->izqda; 
    p->altura = maximo(altura(p->izqda),altura(p->drcha))+1; 
    (*A)->altura = maximo(altura((*A)->izqda),altura((*A)->drcha))+1;
 } 

void Doble_izquierda_derecha(AVL **A){ 
    Simple_izquierda(&((*A)->izqda));       	
    Simple_derecha(&((*A)->drcha)); 
} 

void Doble_derecha_izquierda(AVL **A){ 
    Simple_derecha(&((*A)->drcha)); 
    Simple_izquierda(&((*A)->izqda)); 
}

void ajusta_AVL(char e[], AVL **A){
   if ((*A)!=NULL){
      if (e > (*A)->cod){
         ajusta_AVL(e,&((*A)->drcha));
      }else 
         if (e < (*A)->cod){
            ajusta_AVL(e,&((*A)->izqda));
         }
      switch (altura((*A)->izqda)-altura((*A)->drcha)){
         case 2:
            if (altura((*A)->izqda->izqda) > altura((*A)->izqda->drcha)){
               Simple_derecha(&((*A)->drcha));
            }else{
               Doble_izquierda_derecha(&(*A));
            }
         break;
         case -2:
            if (altura((*A)->drcha->drcha) > altura((*A)->drcha->izqda)){
               Simple_izquierda(&((*A)->izqda));
            }else{
               Doble_derecha_izquierda(&(*A));
            }
         break;
         default:
            (*A)->altura = maximo(altura((*A)->izqda),altura((*A)->drcha))+1;
      }
   }
}

void insertarAVL(char codx[], char nombrex[], char preciox[], char cantidad[], AVL **T){	
	struct AVL *P, *N;
	if ((*T)==NULL) {
		N=(AVL*)malloc(sizeof(AVL));
	    strcpy(N->cod,codx);
	    strcpy(N->nombre,nombrex);
	    strcpy(N->precio,preciox);
	    strcpy(N->cantidad,cantidad);
		N->estado = 1;
		N->altura = 0;
		N->drcha=NULL;
		N->izqda=NULL;
	   if ((*T)==NULL){
		  (*T)=N;
	   }
  	   ajusta_AVL(codx,&(*T)); 
    }else{
		P=(*T);
		if (codx<P->cod){
			insertarAVL(codx,nombrex,preciox,cantidad,&P->izqda);
		}else{
			if (codx>P->cod){
				insertarAVL(codx,nombrex,preciox,cantidad,&P->drcha);
			}
		}
	}
}

void recorreAVL(struct AVL *P){
	if (P!=NULL){
	   recorreAVL(P->izqda);
	   recorreAVL(P->drcha);
	   fputs("            ",ArchivoSalidaTransac);
	   fputs(P->cod,ArchivoSalidaTransac);
	   fputs(" | ",ArchivoSalidaTransac);
	   fputs(P->nombre,ArchivoSalidaTransac);
	   fputs(" | ",ArchivoSalidaTransac);
	   fputs(P->precio,ArchivoSalidaTransac);
	   fputs(" | ",ArchivoSalidaTransac);
	   fputs(P->cantidad,ArchivoSalidaTransac);
	   fputs(" | ",ArchivoSalidaTransac);
	   if (P->estado==1) fputs("Activo",ArchivoSalidaTransac); else fputs("In-Activo",ArchivoSalidaTransac);
	   fputs("\n",ArchivoSalidaTransac);
    }
}

void recorreAVLaBin(struct AVL *P){
	if (P!=NULL){
	   recorreAVL(P->izqda);
	   recorreAVL(P->drcha);
          fwrite(P->cod, sizeof(string), 1, ArchivoBinario);
          fwrite("|", sizeof(string), 1, ArchivoBinario);
          fwrite(P->nombre, sizeof(string), 1, ArchivoBinario);
          fwrite("|", sizeof(string), 1, ArchivoBinario);
          fwrite(P->precio, sizeof(string), 1, ArchivoBinario);
          fwrite("|", sizeof(string), 1, ArchivoBinario);
          fwrite(P->cantidad, sizeof(string), 1, ArchivoBinario);
	   
//	   fputs("            ",ArchivoSalidaTransac);
//	   fputs(P->cod,ArchivoSalidaTransac);
//	   fputs(" | ",ArchivoSalidaTransac);
//	   fputs(P->nombre,ArchivoSalidaTransac);
//	   fputs(" | ",ArchivoSalidaTransac);
//	   fputs(P->precio,ArchivoSalidaTransac);
//	   fputs(" | ",ArchivoSalidaTransac);
//	   fputs(P->cantidad,ArchivoSalidaTransac);
//	   fputs(" | ",ArchivoSalidaTransac);

//	   if (P->estado==1) fputs("Activo",ArchivoSalidaTransac); else fputs("In-Activo",ArchivoSalidaTransac);
//	   fputs("\n",ArchivoSalidaTransac);
    }
}

void OperarArchivo(){
    FILE *Archivo;
    Archivo=fopen("entrada.txt","r+");
    if(!Archivo){
        cout<<"El archivo No se encuentra..."<<endl;
        cout<<"Por favor verificar su ubicacion!"<<endl;
        cout<<endl;
    }else{
        while ( (fgets(line,256,Archivo)) != NULL){ 
         fputs("\n",ArchivoSalidaTransac);
         fputs(line, ArchivoSalidaTransac);
         token = strtok(line, divi_token); 
         cadena = (string)token;
         formarpalabra(cadena);
      }
     fputs("\n                         ** FIN ** \n",ArchivoSalidaTransac);
    }
    cout<<"Archivo procesado con exito";
}

int main(){
   OperarArchivo();
}
