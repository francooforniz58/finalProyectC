#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

#define vaciar system("cls")
// el maximo de pasajeros que entran en el avion
#define MAX 10


//Tipo de dato que uso para los empleados
struct empleados
{
	short legajo;
	char nombre[30];
	char cargo[20];

};

//Tipo de dato que uso para los empleados
struct datos
{
	char nombre[30];
	short edad;
	long dni;
	float peso_equipaje;
	char clase;
};

//Funcion para cargar pasajaros
short cargaPasajero(struct datos **pDatos, short totalP)//paso como puntero a puntero porque asi modifico la direccion que contiene un puntero ya creado
{

    char edad2[25];
    char dni2[30];
    short dniCorrecto;
	short edadCorrecta;
	short ingreso;
	//opcion dinamica de ir ingresando pasajeros a medida que se quiere
	printf("Ingrese un numero para cargar un pasajero o ingrese 0 para salir:");
	scanf("%hd",&ingreso);
	vaciar;

	while(ingreso != 0)
	{
		//agregando pasajeros dinamicamente
        *pDatos = (struct datos *) realloc (*pDatos,(totalP+1) *sizeof(struct datos));

		short nombreCorrecto=1;

		do
		{
			//
			fflush(stdin);
			printf("Nombre y apellido:");
			scanf(" %[^\n]s ",&(*pDatos)[totalP].nombre); //le paso la direccion de memoria de mi puntero *pdatos en el lugar [totalP] para que el contenido sea guardado ahi mismo
			short longitud = strlen((*pDatos)[totalP].nombre);
			nombreCorrecto = 1;

			//validando nombre
			for (short j = 0; j < longitud; j++)
            {
                if (!isalpha((*pDatos)[totalP].nombre[j]) && (*pDatos)[totalP].nombre[j] != ' ')
                {
                    nombreCorrecto = 0;
                    break; // Salir del bucle si no es correcto
                }
            }

			if (nombreCorrecto == 0)
				printf("Ingreso incorrecto. Por favor, ingresa un nombre y apellido validos.\n");

		}while(nombreCorrecto != 1);

		do
		{

            printf("Ingrese la edad del pasajero: ");
            scanf("%s", &edad2);

			if (sscanf(edad2,"%hd", &(*pDatos)[totalP].edad) != 1 ||  (*pDatos)[totalP].edad < 1 || (*pDatos)[totalP].edad > 110)
			{
                printf("Error: La edad debe estar entre 1 y 110. Ingrese la edad nuevamente.\n");
				edadCorrecta = 1;
            }else
            {
                edadCorrecta = 0;
            }

        }while(edadCorrecta == 1);

		do
		{

            printf("Ingrese el dni del pasajero: ");
			scanf("%s", &dni2);

			if (sscanf(dni2,"%ld", &(*pDatos)[totalP].dni) != 1 || (*pDatos)[totalP].dni < 10000000 || (*pDatos)[totalP].dni > 65000000)
			{
            	printf("Error: El dni es invalido. Ingrese el dni nuevamente.\n");
                dniCorrecto = 1;
            }else
            {
                dniCorrecto = 0;
            }

        }while(dniCorrecto == 1);

		do
		{
            printf("Ingrese el peso del equipaje: ");
            scanf("%f", &(*pDatos)[totalP].peso_equipaje);

			if ((*pDatos)[totalP].peso_equipaje < 0 || (*pDatos)[totalP].peso_equipaje > 16)
				printf("PESO PERMITIDO HASTA 16 KILOS! ingrese un peso correcto.\n");

        }while((*pDatos)[totalP].peso_equipaje < 0 || (*pDatos)[totalP].peso_equipaje > 16);

		do
		{
			printf("A para primera clase, B para business, C para turista\nIngrese lugar del asiento:");
			fflush(stdin);
			scanf("%c", &(*pDatos)[totalP].clase);

			if ((*pDatos)[totalP].clase !='A' && (*pDatos)[totalP].clase !='a' && (*pDatos)[totalP].clase !='B' && (*pDatos)[totalP].clase !='b' && (*pDatos)[totalP].clase !='C' && (*pDatos)[totalP].clase !='c')
				printf("ingrese una clase correcta.\n");

		}while((*pDatos)[totalP].clase !='A' && (*pDatos)[totalP].clase !='a' && (*pDatos)[totalP].clase !='B' && (*pDatos)[totalP].clase !='b' && (*pDatos)[totalP].clase !='C' && (*pDatos)[totalP].clase !='c');

		totalP++;

		vaciar;

		printf("Ingrese un numero para cargar un pasajero o ingrese 0 para salir:");
		scanf("%hd",&ingreso);
		vaciar;

	}

	vaciar;
	return totalP;

}

void imprimirPasajero(struct datos *pDatos, short pasajerosT)
{
	printf("NOMBRE DEL PASAJERO\t\tEDAD DEL PASAJERO\t\tDNI DEL PASAJERO\t\tPESO DEL EQUIPAJE\tCLASE\n");
	for (short i = 0; i < pasajerosT; i++)
	{
		//imprimiendo los pasajeros
		printf("%s\t\t\t", pDatos[i].nombre);
        printf("%hd\t\t\t\t", pDatos[i].edad );
        printf("%ld\t\t\t\t", pDatos[i].dni );
		printf("%.2f\t\t",pDatos[i].peso_equipaje);
		if (pDatos[i].clase == 'a' || pDatos[i].clase == 'A' )
			printf("Primera clase(%c)\t\t\n",pDatos[i].clase);
		if (pDatos[i].clase == 'b' || pDatos[i].clase == 'B' )
			printf("Business(%c)\t\t\n",pDatos[i].clase);
		if (pDatos[i].clase == 'c' || pDatos[i].clase == 'C' )
			printf("Turista(%c)\t\t\n",pDatos[i].clase);
	}
	//esta accion lo hago mas que nada para limpiar la consola
	printf("Presione enter para continuar...");
	getchar();
	vaciar;

}

void Busqueda (struct datos *pDatos, struct datos aux, short pasajerosT)
{
	short u,r,i;
	short inferior, medio, superior;
	char buscado[30];

	//ordeno los nombres de menor a mayor(a...z) con pivot
	for(u=0;u<pasajerosT-1;u++)
	{
		for(r=u+1;r<pasajerosT;r++)
		{
			if(strcmp(pDatos[u].nombre, pDatos[r].nombre)>0)
			{  //ordenando de menor a mayor(de la A a la Z)
				aux = pDatos[u];
				pDatos[u] = pDatos[r];
				pDatos[r] = aux;
			}
		}
	}

	do
	{
	printf("*******NOMBRES*******\n");
	for(i=0;i<pasajerosT;i++)
		printf("%s\n",pDatos[i].nombre);

	printf("********************* \n");

		inferior=0;
		superior=pasajerosT;
		medio=superior/2;

		printf("ingrese el nombre pasajero para ver los datos: ");

		fflush(stdin);
		fgets(buscado,sizeof(buscado),stdin);
		buscado[strlen(buscado)-1]=0;
		//utilizo busqueda binaria para buscar el nombre de la persona
		while(strcmp(buscado,pDatos[medio].nombre)!=0 && inferior<=superior)
		{
			if(strcmp(buscado,pDatos[medio].nombre)>0)
				inferior=medio+1;
			else
				superior=medio-1;

			medio=(superior+inferior)/2;
		}

		if(strcmp(buscado,pDatos[medio].nombre)==0)
		{

			vaciar;
			printf("NOMBRE DEL PASAJERO\t\tEDAD DEL PASAJERO\t\tDNI DEL PASAJERO\t\tPESO DEL EQUIPAJE\t\tCLASE\n");
			printf("%s\t\t\t", pDatos[medio].nombre);
        	printf("%hd\t\t\t\t", pDatos[medio].edad );
        	printf("%ld\t\t\t\t", pDatos[medio].dni );
			printf("%.2f\t\t\t",pDatos[medio].peso_equipaje);
			printf("%c\t\t\n",pDatos[medio].clase);
			printf("********************************************************************************************************************************** \n");



		}else
			printf("El pasajero no fue registrado\n");

		printf("si quiere realizar otra busqueda presione a, sino cualquier otra tecla: ");

	} while(getchar()=='a');

}


int main(void)
{

	//INCLUYENDO CARACTERES EN ESPAÑOL
	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	printf("BIENVENIDO AL VUELO!!!!");
	Sleep(2000);


	struct datos *datosP = NULL,auxiliar;
	short totalPasajeros= 0 ;
	//short pasajerosTotal;

	short menu;

	//precargo los datos de los empleados
	struct empleados informacion[]=
    {
        {458,"Ariel Perez","Piloto"}, {234,"Pedro Gonzalez","Copiloto"}, {912,"Carlos Fontana","Azafato"},
        {747,"Lautaro Cox","Azafato"}, {299,"Maria Ramirez","Azafata"}, {117,"Luciana Cali","Azafata"},
		{550,"Federico Cristam","seguridad"}, {876,"Damian Gimenez","seguridad"},
    };

	FILE *archivoB; //puntero a una estrucutra file
	FILE *archivoT;
	long ubicacion;
	short indice;
	short cantidad = sizeof(informacion) / sizeof(informacion[0]);
	short reemplazo = 0;
	//short bandera = 1;


	do
	{
		vaciar;
		//ingresando al menu de opciones
		printf("1.Ingresar pasajeros\n");
		printf("2.Listar pasajeros\n");
		printf("3.Buscar pasajero por nombre\n");
		printf("4.Empleados del vuelo\n");
		printf("5.Salir\n\n");
		printf("Ingrese una opcion para continuar:");
		scanf("%hd",&menu);
		getchar();
		vaciar;

		switch (menu)
		{
			case 1:
				//llamando a la funcion de carga
				totalPasajeros = cargaPasajero(&datosP, totalPasajeros);
				//totalPasajeros = pasajerosTotal; // Actualizar totalPasajeros para despues poder agregar mas datos si es necesario

				break;

			case 2:
				//llamando a la funcion de imprimir
				imprimirPasajero(datosP, totalPasajeros);
				break;

			case 3:
				//buscando pasajeros por nombre
				Busqueda(datosP,auxiliar,totalPasajeros);
				break;

			case 4:

				//creando la estructura file, asignandole un nombre(path) y el modo que va a ser utilzado, el +(permite lectura)
				archivoB = fopen("vuelosEmpleados.bin","wb+");
				//comprobando que mi archivo existe
				if(archivoB!=NULL)
				{
					//fwrite(informacion,sizeof(informacion),1,archivoB);
					for(indice=0; indice < cantidad; indice++)
            		{
               			fwrite(&informacion[indice], sizeof(informacion[0]),1, archivoB);
            		}
					//escribo el bloque de memoria entero a un archivo
					//desde donde lo escribo, el tamanio del bloque,de un solo paso, a donde lo escribo
					rewind(archivoB);
					for(indice=0; indice < cantidad; indice++)
            		{
               			fread(&informacion[indice], sizeof(informacion[0]),1, archivoB);
            		}
				}
				//vuelvo al principio del archivo
				//ubicacion = ftell(archivoB);/* Obtengo la actual direccion antes de leer porque sino me tomaria la siguiente direccion */
				//con fread leo el archivo, paso los mismos datos que para la escritura
				fclose(archivoB);
				//salvamos la informacion a un archivo de texto
				//verificamos que exista el archivo
				printf("LEGAJO\t\tNOMBRE\t\t\tCARGO\n");
				for(indice=0; indice<cantidad; indice++)
       	 		{
					printf("%hd\t\t%s\t\t%s\n",informacion[indice].legajo, informacion[indice].nombre, informacion[indice].cargo);
				}

				printf("********************************************************************************\n");
				printf("Presione a para cambiar un empleado, sino cualquier otra tecla: ");

				if(getchar()=='a')
				{
                    vaciar;
					//vuelvo a abrir el archivo binario para modificarlo
					archivoB = fopen("vuelosEmpleados.bin","wb+");
					rewind(archivoB);
					//ubicacion = ftell(archivoB);

					//leo y escribo nuevos datos
					printf("LEGAJOS:\n");
					for(indice=0; indice<cantidad; indice++)
       	 			{
						printf("%hd\n",informacion[indice].legajo);
					}

					printf("Ingrese un numero el numero de legajo del archivo para continuar: ");
					scanf("%hd",&reemplazo);

					fread(&informacion, sizeof(informacion),1, archivoB);

					short encontrado = 0;
                    for(indice=0;indice<cantidad && encontrado == 0;indice++)
                    {
                        if(informacion[indice].legajo == reemplazo)
                        {
							ubicacion = ftell(archivoB);
                            printf("Ingrese el nuevo numero de legajo: ");
						    scanf("%hd", &informacion[indice].legajo);
						    short nombreCorrecto=1;

                            do
                            {
                                fflush(stdin);
                                printf("Nombre y apellido:");
                                scanf(" %[^\n]s ",informacion[indice].nombre); //le paso la direccion de memoria de mi puntero *pdatos en el lugar [totalP] para que el contenido sea guardado ahi mismo
                                short longitud = strlen(informacion[indice].nombre);
                                nombreCorrecto = 1;
                                //validando nombre

                                for (short j = 0; j < longitud; j++)
                                {
                                    if (!isalpha(informacion[indice].nombre[j]) && informacion[indice].nombre[j] != ' ')
                                    {
                                        nombreCorrecto = 0;
                                        break; // Salir del bucle si no es correcto
                                    }
                                }
                                if (nombreCorrecto == 0)
                                    printf("Ingreso incorrecto. Por favor, ingresa un nombre y apellido validos.\n");

                            }while(nombreCorrecto != 1);

                            printf("Presione enter para continuar...");
                            getchar();
                            vaciar;

                            fseek(archivoB, ubicacion, SEEK_SET);
                            fwrite(&informacion[indice], sizeof(struct empleados), 1, archivoB);
                            encontrado = 1;
                            printf("Empleado reemplazado exitosamente!\n");
                            printf("Presione enter para continuar...");
                            getchar();
                            vaciar;

                        }

                    }

					rewind(archivoB);
					fclose(archivoB);
				}

				archivoT = fopen("EmpleadosVuelos.txt","wt+");

				if(archivoT != NULL)
				{

					for(indice=0; indice<cantidad; indice++)
       	 			{
						fprintf(archivoT,"%5hd ",indice+1);
						fprintf(archivoT,"%10hd  ",informacion[indice].legajo);
						fprintf(archivoT,"%30s",informacion[indice].nombre);
						fprintf(archivoT,"%30s\n",informacion[indice].cargo);

					}
					fclose(archivoT);
				}else
                {
                    printf("Error! No existe el arhivo\n");
                    Sleep(2000);
					vaciar;
                }


			default:

				break;
		}

	}while( menu==1 || menu==2 || menu==3 || menu==4 );

	//libero el espacio del vector de pasajeros
    free(datosP);
	datosP=NULL;
	//aca ya lo puedo volver a usar

	printf("--------------------\n");
	system("cls");
	printf("Adios!");

	return 0;

}
