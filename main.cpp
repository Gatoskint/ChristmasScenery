#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

GLfloat anguloMuneco = 0.0f;
GLfloat anguloP1 = 0.0;
GLfloat anguloP2 = 0.0;
GLfloat anguloP3 = 0.0;
GLfloat maxAnguloP1 = 15.0;
GLfloat maxAnguloP2 = 30.0;
GLfloat maxAnguloP3 = 100.0;
GLint direccion1 = 1;  
GLint direccion2 = 1;  
GLint direccion3 = 1; 
GLfloat angY = 0.0, mod_angY = 0.0;

int t = 700;
int a = 350;

typedef struct{
	GLubyte *dibujo;
	GLuint bpp;
	GLuint largo;
	GLuint ancho;
	GLuint ID;
}textura;

textura tCasa, tFondo, tNavidad, tNada;

textura tcaraSC, t_caraSC, t_caraDC;

textura t1caraIC, t1caraFC, t1caraDC, t1caraIzC, t1caraDeC, t1_caraFC, t1_caraIzC, t1_caraDeC;
textura t1caraSCu, t1caraICu, t1caraFCu, t1caraDCu, t1caraDeIzCu, t1_caraFCu;
textura t1caraDBD, t1caraDBI, t1caraDeBD, t1caraDeIzB, t1caraFBD, t1caraFBI;
textura t1caraIBD, t1caraIBI, t1caraIzBI, t1caraSBD, t1caraSBI, t1_caraBD, t1_caraBI;
textura t1caraDPD, t1caraDPI, t1caraDePD, t1caraDePI, t1caraFPD, t1caraFPI, t1caraIPD, t1caraIPI, t1caraIzPD, t1caraIzPI;
textura t1caraSPD, t1caraSPI, t1_caraDPD, t1_caraDPI, t1_caraDePD, t1_caraDeIzP, t1_caraFPD, t1_caraFPI, t1_caraIzPI;

textura t2caraDC, t2caraDeC, t2caraFC, t2caraIC, t2caraIzC, t2_caraDeC, t2_caraFC, t2_caraIzC;
textura t2caraDCu, t2caraDeIzCu, t2caraFCu, t2caraICu, t2caraSCu, t2_caraDCu, t2_caraFCu;
textura t2caraDBD, t2caraDBI, t2caraDeBD, t2caraDeIzB, t2caraFBD, t2caraFBI, t2caraIBD;
textura t2caraIBI,t2caraIzBI, t2caraSBD, t2caraSBI, t2_caraDeBD, t2_caraDFB, t2_caraFDB, t2_caraIzBI;
textura t2caraDPD, t2caraDPI, t2caraDePD, t2caraDePI, t2caraFPD, t2caraFPI, t2caraIPD, t2caraIPI, t2caraIzPD;
textura t2caraIzPI, t2caraSPD, t2caraSPI, t2_caraDPD, t2_caraDPI, t2_caraDePD, t2_caraFPD, t2_caraFPI, t2_caraIP;

textura t3C_caraDe, t3C_caraF, t3C_caraI, t3C_caraIz, t3CcaraD, t3CcaraDe, t3CcaraF, t3CcaraI, t3CcaraIz;
textura t3Cu_caraD, t3Cu_caraF, t3CucaraD, t3CucaraDe, t3CucaraF, t3CucaraI, t3CucaraIz, t3CucaraS;
textura t3B_caraDeIz, t3BcaraIzDe, t3BcaraI, t3BD_caraD, t3BD_caraDe, t3BD_caraF, t3BDcaraD, t3BDcaraDe, t3BDcaraF;
textura t3BDcaraS, t3BI_caraD, t3BI_caraF, t3BI_caraIz, t3BIcaraD, t3BIcaraF, t3BIcaraIz, t3BIcaraS;
textura t3P_caraDeIz, t3P_caraDF, t3P_caraFD, t3P_caraIzDe, t3PcaraDeIz, t3PcaraDF;
textura t3PcaraFD, t3PcaraIzDe, t3PDcaraI, t3PDcaraS, t3PIcaraI, t3PIcaraS;

int cargaTGA(char const*nombre,textura *imagen){
	GLubyte cabeceraTGA[12]={0,0,2,0,0,0,0,0,0,0,0,0};
	GLubyte compararTGA[12];//0,0,2,0,0,0,0,0,0,0,0,0
	GLubyte cabecera[6];//244,1,244,1,32,40
	GLuint bytesporpuntos;
	GLuint tamanoimagen;
	GLuint temp, i;
	GLuint tipo=GL_RGBA;
	
	FILE *archivo=fopen(nombre,"rb");
	if(
	 archivo==NULL ||
	 fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA) ||
	 memcmp(cabeceraTGA,compararTGA,sizeof(compararTGA))!= 0 ||
	 fread(cabecera,1,sizeof(cabecera),archivo)!=sizeof(cabecera)
	){
		if(archivo ==NULL){
			printf("NO SE ENCONTRO EL ARCHIVO %\n",nombre);
			return 0;
		}else {
			fclose(archivo);
			return 0;
		}
	}
	
	imagen->largo= 256 * cabecera[1] + cabecera[0];//(256*1)+ 244= 500
	imagen->ancho= 256 * cabecera[3] + cabecera[2];//(256*1)+ 244= 500
	
	if(
	  imagen->largo <=0 ||
	  imagen->ancho <=0 ||
	  (cabecera[4] !=24 && cabecera[4] !=32) //cantidad de bits por punto
	){
		printf("Datos invalidos\n");
		fclose(archivo);
		return 0;
		
	}
	imagen->bpp=cabecera[4];
	bytesporpuntos = cabecera[4] /8; //32   /  8   =4
	tamanoimagen = imagen->largo * imagen->ancho * bytesporpuntos;
	              //  500 * 500 * 4 = 1000000
	              //1000000/1024 = 976,56 = 977 
	imagen->dibujo = (GLubyte *) malloc(tamanoimagen);
	
	 if(
	   imagen->dibujo == NULL ||
	   fread(imagen->dibujo,1, tamanoimagen,archivo) != tamanoimagen
	 ){
	 	 if(imagen->dibujo != NULL){
	 	 	printf(" Error leyendo imagen\n");
	 	 	free(imagen->dibujo);
		  } else {
		  	printf(" Error asignando memoria\n");
		  }
		  fclose(archivo);
		  return 0;
	 }
	 
	 //TGA :BGRA        RGBA 
	 for (i=0;i < (int)tamanoimagen; i+=bytesporpuntos){
	 	 temp = imagen->dibujo[i]; //A-->TEMP
	 	 imagen->dibujo[i]= imagen->dibujo[i+2]; // B--> A
	 	 imagen->dibujo[i+2] =temp;// temp --> B
	 }
	     fclose(archivo);
	     
	     glGenTextures(1,&imagen[0].ID);
	     glBindTexture(GL_TEXTURE_2D, imagen[0].ID);
	     if(imagen->bpp ==24 ) tipo=GL_RGB;
	     glTexImage2D(GL_TEXTURE_2D,0,tipo,imagen[0].ancho,imagen[0].largo,0,tipo,GL_UNSIGNED_BYTE,imagen[0].dibujo);
	     glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	     glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	     
	     return 1;
}

void init(){
	GLfloat light_position[] = {0, 0, 1, 0}; // Define la posición de la fuente de luz (direccional).
	glEnable(GL_LIGHTING); // Habilita la iluminación en la escena.
	glEnable(GL_LIGHT0); // Activa la primera fuente de luz (GL_LIGHT0).
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Establece la posición de GL_LIGHT0.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Rellena las caras de los polígonos (no alambre).
	
	// Propiedades de iluminación para el "muñeco".
	GLfloat light_ambient[] = {0.75, 0.75, 0.75, 1.0}; // Luz ambiental (iluminación global difusa).
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; // Luz difusa (dirección de luz y color).
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0}; // Luz especular (brillos reflectados).
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); // Configura la luz ambiental para GL_LIGHT0.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // Configura la luz difusa para GL_LIGHT0.
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // Configura la luz especular para GL_LIGHT0.
	
	glShadeModel(GL_SMOOTH); // Habilita suavizado de colores y sombras (interpolación).
	glClearDepth(1.0); // Establece la profundidad inicial del búfer Z.
	glEnable(GL_DEPTH_TEST); // Activa la prueba de profundidad para ocultar superficies traseras.
	glDepthFunc(GL_LEQUAL); // Define el criterio para la prueba de profundidad (menor o igual).
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Mejora la calidad de las perspectivas.
	glEnable(GL_TEXTURE_2D); // Habilita las texturas 2D.
	
	glEnable(GL_BLEND); // Activa la mezcla de colores para transparencia.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Configura el modo de mezcla para transparencia.
	glEnable(GL_COLOR_MATERIAL); // Habilita que los colores afecten el material del objeto.
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // Aplica colores a las propiedades ambiente y difusa.
	
	if(!cargaTGA("Casita.tga",&tCasa)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("Navidad.tga",&tNavidad)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("Fondo.tga",&tFondo)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("nada.tga",&tNada)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	
	if(!cargaTGA("caraSC.tga",&tcaraSC)) {
		printf("Error cargando textura \n");
		exit(0);
	}	
	if(!cargaTGA("_caraSC.tga",&t_caraSC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("_caraDC.tga",&t_caraDC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	
	if(!cargaTGA("1caraIC.tga",&t1caraIC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraFC.tga",&t1caraFC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDC.tga",&t1caraDC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIzC.tga",&t1caraIzC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDeC.tga",&t1caraDeC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraFC.tga",&t1_caraFC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraIzC.tga",&t1_caraIzC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraDeC.tga",&t1_caraDeC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	
	if(!cargaTGA("1caraSCu.tga",&t1caraSCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraICu.tga",&t1caraICu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraFCu.tga",&t1caraFCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDCu.tga",&t1caraDCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDeIzCu.tga",&t1caraDeIzCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraFCu.tga",&t1_caraFCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	if(!cargaTGA("1caraDBD.tga",&t1caraDBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDBI.tga",&t1caraDBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDeBD.tga",&t1caraDeBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDeIzB.tga",&t1caraDeIzB)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraFBD.tga",&t1caraFBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraFBI.tga",&t1caraFBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIBD.tga",&t1caraIBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIBI.tga",&t1caraIBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIzBI.tga",&t1caraIzBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraSBD.tga",&t1caraSBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraSBI.tga",&t1caraSBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraBD.tga",&t1_caraBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraBI.tga",&t1_caraBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
		
	if(!cargaTGA("1caraDePD.tga",&t1caraDePD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDePI.tga",&t1caraDePI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDPD.tga",&t1caraDPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraDPI.tga",&t1caraDPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraFPD.tga",&t1caraFPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraFPI.tga",&t1caraFPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIPD.tga",&t1caraIPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIPI.tga",&t1caraIPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIzPD.tga",&t1caraIzPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraIzPI.tga",&t1caraIzPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraSPD.tga",&t1caraSPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1caraSPI.tga",&t1caraSPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraDPD.tga",&t1_caraDPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraDPI.tga",&t1_caraDPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraDePD.tga",&t1_caraDePD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraDeIzP.tga",&t1_caraDeIzP)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraFPD.tga",&t1_caraFPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraFPI.tga",&t1_caraFPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("1_caraIzPI.tga",&t1_caraIzPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}


	if(!cargaTGA("2caraDC.tga",&t2caraDC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDeC.tga",&t2caraDeC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraFC.tga",&t2caraFC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIC.tga",&t2caraIC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIzC.tga",&t2caraIzC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraDeC.tga",&t2_caraDeC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraFC.tga",&t2_caraFC)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraIzC.tga",&t2_caraIzC)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	if(!cargaTGA("2caraDCu.tga",&t2caraDCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDeIzCu.tga",&t2caraDeIzCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraFCu.tga",&t2caraFCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraICu.tga",&t2caraICu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraSCu.tga",&t2caraSCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraDCu.tga",&t2_caraDCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraFCu.tga",&t2_caraFCu)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	if(!cargaTGA("2caraDBD.tga",&t2caraDBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDBI.tga",&t2caraDBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDeBD.tga",&t2caraDeBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDeIzB.tga",&t2caraDeIzB)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraFBD.tga",&t2caraFBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraFBI.tga",&t2caraFBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIBD.tga",&t2caraIBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIBI.tga",&t2caraIBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIzBI.tga",&t2caraIzBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraSBD.tga",&t2caraSBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraSBI.tga",&t2caraSBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraDeBD.tga",&t2_caraDeBD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraDFB.tga",&t2_caraDFB)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraFDB.tga",&t2_caraFDB)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraIzBI.tga",&t2_caraIzBI)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	if(!cargaTGA("2caraDPD.tga",&t2caraDPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDPI.tga",&t2caraDPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDePD.tga",&t2caraDePD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraDePI.tga",&t2caraDePI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraFPD.tga",&t2caraFPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraFPI.tga",&t2caraFPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIPD.tga",&t2caraIPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIPI.tga",&t2caraIPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIzPD.tga",&t2caraIzPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraIzPI.tga",&t2caraIzPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraSPD.tga",&t2caraSPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2caraSPI.tga",&t2caraSPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraDPD.tga",&t2_caraDPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraDPI.tga",&t2_caraDPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraDePD.tga",&t2_caraDePD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraFPD.tga",&t2_caraFPD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraFPI.tga",&t2_caraFPI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("2_caraIP.tga",&t2_caraIP)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	
	if(!cargaTGA("3C_caraDe.tga",&t3C_caraDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3C_caraF.tga",&t3C_caraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3C_caraI.tga",&t3C_caraI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3C_caraIz.tga",&t3C_caraIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CcaraD.tga",&t3CcaraD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CcaraDe.tga",&t3CcaraDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CcaraF.tga",&t3CcaraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CcaraI.tga",&t3CcaraI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CcaraIz.tga",&t3CcaraIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	if(!cargaTGA("3Cu_caraD.tga",&t3Cu_caraD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3Cu_caraF.tga",&t3Cu_caraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CucaraD.tga",&t3CucaraD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CucaraDe.tga",&t3CucaraDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CucaraF.tga",&t3CucaraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CucaraI.tga",&t3CucaraI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CucaraIz.tga",&t3CucaraIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3CucaraS.tga",&t3CucaraS)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	if(!cargaTGA("3B_caraDeIz.tga",&t3B_caraDeIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BcaraIzDe.tga",&t3BcaraIzDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BcaraI.tga",&t3BcaraI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BD_caraD.tga",&t3BD_caraD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BD_caraDe.tga",&t3BD_caraDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BD_caraF.tga",&t3BD_caraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BDcaraD.tga",&t3BDcaraD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BDcaraDe.tga",&t3BDcaraDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BDcaraF.tga",&t3BDcaraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BDcaraS.tga",&t3BDcaraS)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BI_caraD.tga",&t3BI_caraD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BI_caraF.tga",&t3BI_caraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BI_caraIz.tga",&t3BI_caraIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BIcaraD.tga",&t3BIcaraD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BIcaraF.tga",&t3BIcaraF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BIcaraIz.tga",&t3BIcaraIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3BIcaraS.tga",&t3BIcaraS)) {
		printf("Error cargando textura \n");
		exit(0);
	}

	if(!cargaTGA("3P_caraDeIz.tga",&t3P_caraDeIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3P_caraDF.tga",&t3P_caraDF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3P_caraFD.tga",&t3P_caraFD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3P_caraIzDe.tga",&t3P_caraIzDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PcaraDeIz.tga",&t3PcaraDeIz)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PcaraDF.tga",&t3PcaraDF)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PcaraFD.tga",&t3PcaraFD)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PcaraIzDe.tga",&t3PcaraIzDe)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PDcaraI.tga",&t3PDcaraI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PDcaraS.tga",&t3PDcaraS)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PIcaraI.tga",&t3PIcaraI)) {
		printf("Error cargando textura \n");
		exit(0);
	}
	if(!cargaTGA("3PIcaraS.tga",&t3PIcaraS)) {
		printf("Error cargando textura \n");
		exit(0);
	}
}

void Animacion(){
	angY += mod_angY;
    if (angY > 45.0) angY = 45.0;
    if (angY < -45.0) angY = -45.0;
	glRotatef(angY, 0.0, 1.0, 0.0);
}

void pov(){
	gluLookAt(90.0, 45.0, 90.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	Animacion();
}

void estrella(float x, float y, float z, float tamano, float profundidad) {
	glDisable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 0.0);
        glVertex3f(x * tamano, (y + 31.12) * tamano, z); //A
        glVertex3f((x + 10) * tamano, (y + 13.8) * tamano, z); //B
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x + 10) * tamano, (y + 13.8) * tamano, z); //B
        glVertex3f((x + 29.57) * tamano, (y + 9.64) * tamano, z); //D
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x + 29.57) * tamano, (y + 9.64) * tamano, z); //D
        glVertex3f((x + 16.2) * tamano, (y - 5.2) * tamano, z); //E
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x + 16.2) * tamano, (y - 5.2) * tamano, z); //E
        glVertex3f((x + 18.27) * tamano, (y - 25.1) * tamano, z); //F
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x + 18.27) * tamano, (y - 25.1) * tamano, z); //F
        glVertex3f(x * tamano, (y - 17) * tamano, z); //G
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f(x * tamano, (y - 17) * tamano, z); //G
        glVertex3f((x - 18.27) * tamano, (y - 25.1) * tamano, z); //H
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x - 18.27) * tamano, (y - 25.1) * tamano, z); //H
        glVertex3f((x - 16.2) * tamano, (y - 5.2) * tamano, z); //I
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x - 16.2) * tamano, (y - 5.2) * tamano, z); //I
        glVertex3f((x - 29.57) * tamano, (y + 9.64) * tamano, z); //J
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x - 29.57) * tamano, (y + 9.64) * tamano, z); //J
        glVertex3f((x - 10) * tamano, (y + 13.8) * tamano, z); //C
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x - 10) * tamano, (y + 13.8) * tamano, z); //C
        glVertex3f(x * tamano, (y + 31.12) * tamano, z); //A
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
	glColor3f(1.0, 0.90, 0.0);
        glVertex3f(x * tamano, (y + 31.12) * tamano, z); //A
        glVertex3f((x + 10) * tamano, (y + 13.8) * tamano, z); //B
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x + 10) * tamano, (y + 13.8) * tamano, z); //B
        glVertex3f((x + 29.57) * tamano, (y + 9.64) * tamano, z); //D
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x + 29.57) * tamano, (y + 9.64) * tamano, z); //D
        glVertex3f((x + 16.2) * tamano, (y - 5.2) * tamano, z); //E
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x + 16.2) * tamano, (y - 5.2) * tamano, z); //E
        glVertex3f((x + 18.27) * tamano, (y - 25.1) * tamano, z); //F
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x + 18.27) * tamano, (y - 25.1) * tamano, z); //F
        glVertex3f(x * tamano, (y - 17) * tamano, z); //G
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f(x * tamano, (y - 17) * tamano, z); //G
        glVertex3f((x - 18.27) * tamano, (y - 25.1) * tamano, z); //H
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x - 18.27) * tamano, (y - 25.1) * tamano, z); //H
        glVertex3f((x - 16.2) * tamano, (y - 5.2) * tamano, z); //I
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x - 16.2) * tamano, (y - 5.2) * tamano, z); //I
        glVertex3f((x - 29.57) * tamano, (y + 9.64) * tamano, z); //J
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
        
        glVertex3f((x - 29.57) * tamano, (y + 9.64) * tamano, z); //J
        glVertex3f((x - 10) * tamano, (y + 13.8) * tamano, z); //C
        glVertex3f(x * tamano, y * tamano, z-profundidad); //3D
        
        glVertex3f((x - 10) * tamano, (y + 13.8) * tamano, z); //C
        glVertex3f(x * tamano, (y + 31.12) * tamano, z); //A
        glVertex3f(x * tamano, y * tamano, z+profundidad); //3D
    glEnd();
    glEnable(GL_LIGHTING);
    glLoadIdentity();
}

void Cubo(float x, float y, float z, float tamano, textura tcaraF, textura tcaraDe, textura tcaraD, textura tcaraIz, textura tcaraS, textura tcaraI){
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tcaraF.ID); // Frente
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y+8)*tamano,(z+8)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y+8)*tamano,(z+8)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+8)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z+8)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraDe.ID); // Cara Derecha
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y+8)*tamano,(z+8)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y+8)*tamano,(z-8)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-8)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+8)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraD.ID); // Detras
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y+8)*tamano,(z-8)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x+8)*tamano,(y+8)*tamano,(z-8)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z-8)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-8)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraIz.ID); // Cara Izquierda
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y+8)*tamano,(z-8)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x+8)*tamano,(y+8)*tamano,(z+8)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z+8)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z-8)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraS.ID); // Cara Superior
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y+8)*tamano,(z-8)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y+8)*tamano,(z-8)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y+8)*tamano,(z+8)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y+8)*tamano,(z+8)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraI.ID); // Cara Inferior
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z+8)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+8)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-8)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z-8)*tamano);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLoadIdentity();
}

void Cuerpo(float x, float y, float z, float tamano, textura tcaraF, textura tcaraDe, textura tcaraD, textura tcaraIz, textura tcaraS, textura tcaraI){
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, tcaraF.ID); // Frente
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y-32)*tamano,(z+4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraDe.ID); // Cara Derecha
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z-4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z+4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraD.ID); // Detras
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x+8)*tamano,(y-32)*tamano,(z-4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z-4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraIz.ID); // Cara Izquierda
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x+8)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y-32)*tamano,(z-4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraS.ID); // Cara Superior
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y-8)*tamano,(z+4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraI.ID); // Cara Inferior
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x+8)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z-4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x+8)*tamano,(y-32)*tamano,(z-4)*tamano);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLoadIdentity();
}

void BrazoPierna(float x, float y, float z, float tamano, textura tcaraF, textura tcaraDe, textura tcaraD, textura tcaraIz, textura tcaraS, textura tcaraI){
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tcaraF.ID); // Frente
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-16)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-16)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z+4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraDe.ID); // Cara Derecha
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-16)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-16)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-16)*tamano,(y-32)*tamano,(z-4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-16)*tamano,(y-32)*tamano,(z+4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraD.ID); // Detras
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-16)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z-4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-16)*tamano,(y-32)*tamano,(z-4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraIz.ID); // Cara Izquierda
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z-4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraS.ID); // Cara Superior
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-16)*tamano,(y-8)*tamano,(z-4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-16)*tamano,(y-8)*tamano,(z+4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-8)*tamano,(z+4)*tamano);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tcaraI.ID); // Cara Inferior
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 0.0); glVertex3d((x-16)*tamano,(y-32)*tamano,(z+4)*tamano);
	  glTexCoord2f(1.0, 1.0); glVertex3d((x-16)*tamano,(y-32)*tamano,(z-4)*tamano);
	  glTexCoord2f(0.0, 1.0); glVertex3d((x-8)*tamano,(y-32)*tamano,(z-4)*tamano);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLoadIdentity();
}

void dibujarMunecoDeNieve() {
	glPushMatrix();
    
    // Propiedades de material
	GLfloat mat_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};  // Incrementa la luz ambiente reflejada
	GLfloat mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Difusa más brillante
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Reflejo especular fuerte
	GLfloat mat_shininess[] = {80.0f};                 // Más brillante

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


    // Cuerpo
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75, 20, 20);

    glTranslatef(0.0f, 0.9f, 0.0f);
    glutSolidSphere(0.5, 20, 20);

    glTranslatef(0.0f, 0.7f, 0.0f);
    glutSolidSphere(0.3, 20, 20);

    // Ojos
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.1f, 0.05f, 0.25f);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1f, 0.05f, 0.25f);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();

    // Sonrisa
    glColor3f(0.0f, 0.0f, 0.0f);
	float smilePositions[5][3] = {
        {-0.12f, -0.1f, 0.25f}, {-0.06f, -0.15f, 0.25f}, 
        {0.0f, -0.17f, 0.25f},  {0.06f, -0.15f, 0.25f}, 
        {0.12f, -0.1f, 0.25f}
	};
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(smilePositions[i][0], smilePositions[i][1], smilePositions[i][2]);
        glutSolidSphere(0.03, 10, 10);
        glPopMatrix();
    }

    // Nariz
    glColor3f(1.0f, 0.5f, 0.0f); // Naranja
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.35f); // Frente a la cabeza
    glRotatef(90.0f, 1.0f, 0.0f, 180.0f); // Apunta hacia adelante
    glutSolidCone(0.05f, 0.2f, 20, 20);
    glPopMatrix();

    // Sombrero
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Negro
    glTranslatef(0.0f, 0.65f, 0.0f); // Ajustar posición general del sombrero

    // Base del sombrero (plana)
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f); // Colocar la base más abajo
    glScalef(1.5f, 0.2f, 1.5f); // Aplastar para formar la base
    glutSolidCube(0.5);
    glPopMatrix();

    // Cilindro del sombrero
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f); // Subir el cilindro para que quede encima de la base
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Apuntarlo hacia arriba
    GLUquadric* sombrero = gluNewQuadric();
    gluCylinder(sombrero, 0.25f, 0.25f, 0.5f, 20, 20);
    gluDeleteQuadric(sombrero);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}

void dibujarRegaloConCintas(float x, float y, float z, float tamano, float r, float g, float b) {
    glPushMatrix();
    glDisable(GL_LIGHTING);
	glTranslatef(x, y, z);
    glColor3f(r, g, b);
    glutSolidCube(tamano);

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glScalef(1.1f, 0.1f, 1.1f);
    glutSolidCube(tamano);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1f, 1.1f, 1.1f);
    glutSolidCube(tamano);
    glPopMatrix();

    glPopMatrix();
    glLoadIdentity();
}

void Fondo(){
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tCasa.ID);
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d(-t,t*2-t/2-a,t);
	  glTexCoord2f(1.0, 0.0); glVertex3d(-t,t*2-t/2-a,-t);
	  glTexCoord2f(1.0, 1.0); glVertex3d(-t,-t/2-a,-t);
	  glTexCoord2f(0.0, 1.0); glVertex3d(-t,-t/2-a,t);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, tFondo.ID);
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d(-t,t*2-t/2-a,-t);
	  glTexCoord2f(1.0, 0.0); glVertex3d(t,t*2-t/2-a,-t);
	  glTexCoord2f(1.0, 1.0); glVertex3d(t,-t/2-a,-t);
	  glTexCoord2f(0.0, 1.0); glVertex3d(-t,-t/2-a,-t);
	glEnd();
	glDepthMask(GL_TRUE);
	
	glTranslated(100,600,100);
	glRotatef(45,0,1,0);
	glRotatef(40,1,0,0);
	glBindTexture(GL_TEXTURE_2D, tNavidad.ID);
	glBegin(GL_QUADS);
	  glTexCoord2f(0.0, 0.0); glVertex3d(-350,250,-350);
	  glTexCoord2f(1.0, 0.0); glVertex3d(350,250,-350);
	  glTexCoord2f(1.0, 1.0); glVertex3d(350,250,350);
	  glTexCoord2f(0.0, 1.0); glVertex3d(-350,250,350);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLoadIdentity();
	
	pov();
	// Dibuja el muñeco de nieve
    glPushMatrix();
    glTranslatef(-500.0f, -700.0f, 600.0f); // Posición del muñeco
    glRotatef(anguloMuneco, 0.0f, 1.0f, 0.0f); // Rotación en eje Y
    glScalef(150.0f, 150.0f, 150.0f);         // Escala del muñeco
    dibujarMunecoDeNieve();
    glPopMatrix();
    
    //regalos
    dibujarRegaloConCintas(575.0f, -625.0f, -50.0f, 150.0f, 0.7f, 0.0f, 0.0f);
    pov();
    glTranslated(10,10,300);
    glRotatef(45,0,1,0);
	dibujarRegaloConCintas(400.0f, -625.0f, -300.0f, 150.0f, 0.0f, 0.5f, 0.0f);
    pov();
	dibujarRegaloConCintas(-100.0f, -625.0f, -550.0f, 150.0f, 0.0f, 0.0f, 0.5f);
}

void personaje1(float x, float y, float z, float tamanoC, float angulo_, float ejex, float ejey, float ejez){
	
	float tamanoD = tamanoC*16/15;
	
	glPushMatrix();
    glTranslatef(x, y, z);
	glRotatef(angulo_,ejex,ejey,ejez);
	
    // Cabeza
    glPushMatrix();
    glRotatef(-20,1,0,0);
    glTranslated(0, 0, -2.5*tamanoC);
    Cubo(0, 0, 0, tamanoC, t1caraFC, t1caraDeC, t1caraDC, t1caraIzC, tcaraSC, t1caraIC);
    glPopMatrix();

    // Cuerpo
    glPushMatrix();
    Cuerpo(0, 0, 0, tamanoC, t1caraFCu, t1caraDeIzCu, t1caraDCu, t1caraDeIzCu, t1caraSCu, t1caraICu);
    glPopMatrix();

    // Brazo Izquierdo
    glPushMatrix();
    BrazoPierna(0, 0, 0, tamanoC, t1caraFBI, t1caraDeIzB, t1caraDBI, t1caraIzBI, t1caraSBI, t1caraIBI);
    glPopMatrix();

    // Brazo Derecho
    glPushMatrix();
    glTranslated(tamanoC*22, -15*tamanoC, -2*tamanoC);
    glRotatef(170,-1,-0.04,0.0);
    glTranslated(-tamanoC*24, tamanoC, 2*tamanoC);
    glRotatef(anguloP1, 0, 0, 1);
    glTranslated(tamanoC*24, -tamanoC, -2*tamanoC);
    BrazoPierna(0, 0, 0,tamanoC,t1caraFBD,t1caraDeBD,t1caraDBD,t1caraDeIzB,t1caraSBD,t1caraIBD);
    glPopMatrix();

    // Pierna Izquierda
    glPushMatrix();
	glTranslated(tamanoC*8, -(tamanoC*24), 0);
    BrazoPierna(0, 0, 0, tamanoC, t1caraFPI, t1caraDePI, t1caraDPI, t1caraIzPI, t1caraSPI, t1caraIPI);
    glPopMatrix();

    // Pierna Derecha
    glPushMatrix();
	glTranslated(tamanoC*16, -(tamanoC*24), 0);
    BrazoPierna(0, 0, 0, tamanoC, t1caraFPD, t1caraDePD, t1caraDPD, t1caraIzPD, t1caraSPD, t1caraIPD);
    glPopMatrix();

    // Detalles de la Cabeza
    glPushMatrix();
    glRotatef(-20,1,0,0);
    glTranslated(0, 0, -2.5*tamanoD);
    glTranslatef(0, tamanoD * 0.5, tamanoD * 0.5);
    Cubo(0, 0, 0, tamanoD, t1_caraFC, t1_caraDeC, t_caraDC, t1_caraIzC, t_caraSC, tNada);
    glPopMatrix();

    // Detalles del Cuerpo
    glPushMatrix();
    glTranslatef(0, tamanoC * 1, 0);
    Cuerpo(0, 0, 0, tamanoD, t1_caraFCu, tNada, tNada, tNada, tNada, tNada);
    glPopMatrix();

    // Detalles del Brazo Izquierdo
    glPushMatrix();
    BrazoPierna(0, 0, 0, tamanoD, t1_caraBI, t1_caraBI, t1_caraBI, tNada, tNada, tNada);
    glPopMatrix();

    // Detalles del Brazo Derecho
    glPushMatrix();
    glTranslated(tamanoD*22, -15*tamanoD, -2*tamanoD);
    glRotatef(170,-1,-0.04,0.0);
    glTranslated(-tamanoD*24, tamanoD, 2*tamanoD);
    glRotatef(anguloP1, 0, 0, 1);
    glTranslated(tamanoD*24, -tamanoD, -2*tamanoD);
    BrazoPierna(0, 0, 0, tamanoD, t1_caraBD, tNada, t1_caraBD, t1_caraBD, tNada, tNada);
    glPopMatrix();

    // Detalles de la Pierna Izquierda
    glPushMatrix();
	glTranslated(tamanoD*8, -(tamanoD*20), 0);
    BrazoPierna(0, 0, 0, tamanoD, t1_caraFPI, t1_caraDeIzP, t1_caraDPI, t1_caraIzPI, tNada, t1caraIPI);
    glPopMatrix();

    // Detalles de la Pierna Derecha
    glPushMatrix();
    glTranslated(tamanoD*16, -(tamanoD*20), 0);
    BrazoPierna(0, 0, 0, tamanoD, t1_caraFPD, t1_caraDePD, t1_caraDPD, t1_caraDeIzP, tNada, t1caraIPD);
    glPopMatrix();

    glPopMatrix();
}

void personaje2(float x, float y, float z, float tamanoC, float angulo_, float ejex, float ejey, float ejez){
	
	float tamanoD = tamanoC*16/15;
	
	glPushMatrix();
    glTranslatef(x, y, z);
	glRotatef(angulo_,ejex,ejey,ejez);
	
    // Cabeza
    glPushMatrix();
    glRotated(15,-1,0,0);
    glTranslatef(0, -1.333*tamanoC, tamanoC);
    glRotated(anguloP2,1,0,0);
    Cubo(0, 0, 0, tamanoC, t2caraFC, t2caraDeC, t2caraDC, t2caraIzC, tcaraSC, t2caraIC);
    glPopMatrix();

    // Cuerpo
    glPushMatrix();
    Cuerpo(0, 0, 0, tamanoC, t2caraFCu, t2caraDeIzCu, t2caraDCu, t2caraDeIzCu, t2caraSCu, t2caraICu);
    glPopMatrix();

    // Brazo Izquierdo
    glPushMatrix();
    glTranslatef(0, -6.667*tamanoC, -8.333*tamanoC);
    glRotated(70,-1,0,0);
    BrazoPierna(0, 0, 0, tamanoC, t2caraFBI, t2caraIzBI, t2caraDBI, t2caraDeIzB, t2caraSBI, t2caraIBI);
    glPopMatrix();

    // Brazo Derecho
    glPushMatrix();
    glTranslated(tamanoC*24, 0, 0);
    glTranslatef(0, -6.667*tamanoC, -8.333*tamanoC);
    glRotated(70,-1,0,0);
    BrazoPierna(0, 0, 0,tamanoC, t2caraFBD, t2caraDeIzB, t2caraDBD, t2caraDeBD, t2caraSBD, t2caraIBD);
    glPopMatrix();

    // Pierna Izquierda
    glPushMatrix();
    glTranslated(tamanoC*8, -(tamanoC*30.4), -(tamanoC*4));
	glRotatef(90,-1,0,0);
	glRotatef(15,0,0,-1);
    BrazoPierna(0, 0, 0, tamanoC, t2caraFPI, t2caraDePI, t2caraDPI, t2caraIzPI, t2caraSPI, t2caraIPI);
    glPopMatrix();

    // Pierna Derecha
    glPushMatrix();
	glTranslated(tamanoC*16, -(tamanoC*30.4), -(tamanoC*9));
	glRotatef(90,-1,0,0);
	glRotatef(15,0,0,1);
    BrazoPierna(0, 0, 0, tamanoC, t2caraFPD, t2caraDePD, t2caraDPD, t2caraIzPD, t2caraSPD, t2caraIPD);
    glPopMatrix();

    // Detalles de la Cabeza
    glPushMatrix();
    glRotated(15,-1,0,0);
    glTranslatef(0, -1.333*tamanoD, tamanoD);
    glRotated(anguloP2,1,0,0);
    Cubo(0, 0, 0, tamanoD, t2_caraFC, t2_caraDeC, t_caraDC, t2_caraIzC, t_caraSC, tNada);
    glPopMatrix();

    // Detalles del Cuerpo
    glPushMatrix();
    glTranslatef(0, tamanoC * 1, 0);
    Cuerpo(0, 0, 0, tamanoD, t2_caraFCu, tNada, t2_caraDCu, tNada, tNada, tNada);
    glPopMatrix();

    // Detalles del Brazo Izquierdo
    glPushMatrix();
    glTranslatef(0, -6.667*tamanoD, -8.333*tamanoD);
    glRotated(70,-1,0,0);
    BrazoPierna(0, 0, 0, tamanoD, t2_caraFDB, t2_caraIzBI, t2_caraDFB, tNada, tNada, tNada);
    glPopMatrix();

    // Detalles del Brazo Derecho
    glPushMatrix();
    glTranslated(tamanoD*24, 0, 0);
    glTranslatef(0, -6.667*tamanoD, -8.333*tamanoD);
    glRotated(70,-1,0,0);
    BrazoPierna(0, 0, 0, tamanoD, t2_caraDFB, tNada, t2_caraFDB, t2_caraDeBD, tNada, tNada);
    glPopMatrix();

    // Detalles de la Pierna Izquierda
    glPushMatrix();
	glTranslated(tamanoD*8.5, -(tamanoD*28.5),  -tamanoD*5);
	glRotatef(90,-1,0,0);
	glRotatef(15,0,0,-1);
    BrazoPierna(0, 0, 0, tamanoD, t2_caraFPI, tNada, t2_caraDPI, tNada, tNada, t2_caraIP);
    glPopMatrix();

    // Detalles de la Pierna Derecha
    glPushMatrix();
    glTranslated(tamanoD*15.5, -(tamanoD*28.5),  -tamanoD*10);
	glRotatef(90,-1,0,0);
	glRotatef(15,0,0,1);
    BrazoPierna(0, 0, 0, tamanoD, t2_caraFPD, tNada, t2_caraDPD, t2_caraDePD, tNada, t2_caraIP);
    glPopMatrix();

    glPopMatrix();
}

void personaje3(float x, float y, float z, float tamanoC, float angulo_, float ejex, float ejey, float ejez){
	
	float tamanoD = tamanoC*16/15;
	
	glPushMatrix();
    glTranslatef(x, y, z);
	glRotatef(angulo_,ejex,ejey,ejez);
	
	// Cabeza
    glPushMatrix();
    glTranslatef(0, -6.667*tamanoC, 13.333*tamanoC);
    Cubo(0, 0, 0, tamanoC, t3CcaraF, t3CcaraIz, t3CcaraD, t3CcaraDe, tcaraSC, t3CcaraI);
    glPopMatrix();

    // Cuerpo
    glPushMatrix();
    glRotatef(30,1,0,0);
    glTranslatef(0, 0, 16.667*tamanoC);
    Cuerpo(0, 0, 0, tamanoC, t3CucaraF, t3CucaraDe, t3CucaraD, t3CucaraIz, t3CucaraS, t3CucaraI);
    glPopMatrix();

    // Brazo Izquierdo
    glPushMatrix();
    glRotatef(30,1,0,0);
    glTranslatef(0, 0, 16.667*tamanoC);
    glTranslatef(0, -50, -8);
    glRotatef(anguloP3,-1,0,0);
    glTranslatef(0, 50, 10);
    BrazoPierna(0, 0, 0, tamanoC, t3BIcaraF, t3BIcaraIz, t3BIcaraD, t3BcaraIzDe, t3BIcaraS, t3BcaraI);
    glPopMatrix();

    // Brazo Derecho
    glPushMatrix();
    glTranslated(tamanoC*24, 0, 0);
    glRotatef(30,1,0,0);
    glTranslatef(0, 0, 16.667*tamanoC);
    BrazoPierna(0, 0, 0,tamanoC, t3BDcaraF, t3BcaraIzDe, t3BDcaraD, t3BDcaraDe, t3BDcaraS, t3BcaraI);
    glPopMatrix();

    // Pierna Izquierda
    glPushMatrix();
    glTranslated(tamanoC*8, -(tamanoC*24), 0);
    BrazoPierna(0, 0, 0, tamanoC, t3PcaraDF, t3PcaraDeIz, t3PcaraFD, t3PcaraIzDe, t3PIcaraS, t3PIcaraI);
    glPopMatrix();

    // Pierna Derecha
    glPushMatrix();
	glTranslated(tamanoC*16, -(tamanoC*24), 0);
    BrazoPierna(0, 0, 0, tamanoC, t3PcaraFD, t3PcaraIzDe, t3PcaraDF, t3PcaraDeIz, t3PDcaraS, t3PDcaraI);
    glPopMatrix();

	// Detalles de la Cabeza
    glPushMatrix();
    glTranslatef(0, -6.667*tamanoD, 13.333*tamanoD);
    Cubo(0, 0, 0, tamanoD, t3C_caraF, t3C_caraIz, t_caraDC, t3C_caraDe, t_caraSC, t3C_caraI);
    glPopMatrix();

    // Detalles del Cuerpo
    glPushMatrix();
    glRotatef(30,1,0,0);
    glTranslatef(0, 0, 16.667*tamanoD);
    Cuerpo(0, 0, 0, tamanoD, t3Cu_caraF, tNada, t3Cu_caraD, tNada, tNada, tNada);
    glPopMatrix();

    // Detalles del Brazo Izquierdo
    glPushMatrix();
    glRotatef(30,1,0,0);
    glTranslatef(0, 0, 16.667*tamanoD);
    glTranslatef(0, -50, -8);
    glRotatef(anguloP3,-1,0,0);
    glTranslatef(0, 50, 10);
    BrazoPierna(0, 0, 0, tamanoD, t3BI_caraF, t3BI_caraIz, t3BI_caraD, t3B_caraDeIz, tNada, tNada);
    glPopMatrix();

    // Detalles del Brazo Derecho
    glPushMatrix();
    glTranslated(tamanoD*24, 0, 0);
    glRotatef(30,1,0,0);
    glTranslatef(0, tamanoD, 16.667*tamanoD);
    BrazoPierna(0, 0, 0, tamanoD, t3BD_caraF, t3B_caraDeIz, t3BD_caraD, t3BD_caraDe, tNada, tNada);
    glPopMatrix();
    
    // Detalles de la Pierna Izquierda
    glPushMatrix();
	glTranslated(tamanoD*8, -(tamanoD*20), 0);
    BrazoPierna(0, 0, 0, tamanoD, t3P_caraFD, t3P_caraIzDe, t3P_caraDF, t3P_caraDeIz, tNada, tNada);
    glPopMatrix();

    // Detalles de la Pierna Derecha
    glPushMatrix();
    glTranslated(tamanoD*16, -(tamanoD*20), 0);
    BrazoPierna(0, 0, 0, tamanoD, t3P_caraDF, t3P_caraDeIz, t3P_caraFD, t3P_caraIzDe, tNada, tNada);
    glPopMatrix();

    glPopMatrix();
}

// Función para dibujar bombillas alrededor del cono
void dibujarBombillas(float baseCono, float alturaCono, int numNiveles, int bombillasPorNivel) {
    float anguloPaso = 360.0f / bombillasPorNivel; // El ángulo entre cada bombilla en un nivel
    float alturaPaso = alturaCono / numNiveles; // Altura entre cada nivel de bombillas

    glPushMatrix();
    glTranslatef(400.0f, -650.0f + alturaCono / 2, -400.0f); // Ajustar la altura inicial para posicionar el cono correctamente

    for (int nivel = 0; nivel < numNiveles; ++nivel) {
        float alturaActual = alturaCono / 2 - nivel * alturaPaso; // Empezar desde la punta hacia la base
        float radioNivel = baseCono * (nivel / (float)numNiveles); // Radio creciente para que las esferas giren alrededor del cono de manera correcta

        for (int i = 0; i < bombillasPorNivel; ++i) {
            float angulo = i * anguloPaso * (M_PI / 180.0f); // Convertir a radianes
            float x = radioNivel * cos(angulo);
            float z = radioNivel * sin(angulo);

            glPushMatrix();
            glTranslatef(x, alturaActual, z); // Colocar cada bombilla
            glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX); // Colores aleatorios
            glutSolidSphere(10.0f, 20, 20); // Dibujar la bombilla como una esfera
            glPopMatrix();
        }
    }

    glPopMatrix();
}

// Agregar función para dibujar un árbol con forma de cono usando glutSolidCone
void arbolCono(float base, float altura) {
    glPushMatrix();
    glTranslatef(400.0f, -650.0f, -400.0f); // Usar las coordenadas especificadas
    glRotatef(-90, 1.0, 0.0, 0.0); // Rotar el cono para que apunte hacia arriba (en la dirección Y)
    glColor3f(0.0, 1.0, 0.0); // Color verde para el árbol

    // Dibujar el cono utilizando glutSolidCone
    glutSolidCone(base, altura, 40, 40);

    glPopMatrix();
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_LIGHTING); // Deshabilita la luz
	
	int x = 1000;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	  glVertex3d(-x,x,-x*2);
	  glVertex3d(x,x,-x*2);
	  glVertex3d(x,-x,-x*2);
	  glVertex3d(-x,-x,-x*2);
	glEnd();
	
	pov();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_QUADS);
	  glVertex3d(-t,-t/2-a,t); //A - vertice izquierdo
	  glVertex3d(t,-t/2-a,t); //B - Frente
	  glVertex3d(t,-t/2-a,-t); //C - vertice derecho
	  glVertex3d(-t,-t/2-a,-t); //D - Atras
	glEnd();
	
	Fondo();
	pov();
	estrella(135,60,-400,3,25);
	glColor3f(1.0, 1.0, 1.0);
	pov();
	personaje1(500, -260, 500, 8, 45, 0, 1, 0);
	personaje2(-200, -425, -550, 8, 90, 0, 1, 0);
	personaje3(-400, -260, 250, 8, 20, 0, -1, 0);
	
    arbolCono(200.0f, 800.0f);
    dibujarBombillas(200.0f, 800.0f, 20, 12); // 20 niveles, 12 bombillas por nivel
	
	glLoadIdentity();
	glutSwapBuffers();
}

void reshape(int largo, int ancho){
	glViewport(0, 0, (GLsizei)largo, (GLsizei)ancho);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int t = 1000;
	glOrtho(-t, t, -t, t, -t*2, t*2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        mod_angY = 0;
    }
}

void keyboard_s(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (angY > -45.0) {
                mod_angY -= 0.005; // Reduce angY
            } else {
                mod_angY = 0; // Evita exceder -90 grados
            }
            break;
        case GLUT_KEY_RIGHT:
            if (angY < 45.0) {
                mod_angY += 0.005; // Incrementa angY
            } else {
                mod_angY = 0; // Evita exceder 90 grados
            }
            break;
    }
}

void idle(){
	anguloMuneco += 0.09;
	
	anguloP1 += 0.09 * direccion1;
    
    if (anguloP1 >= maxAnguloP1) {
        direccion1 = -1;
    } else if (anguloP1 <= 0.0) {
        direccion1 = 1;
    }
    
    anguloP2 += 0.2 * direccion2;
    
    if (anguloP2 >= maxAnguloP2) {
        direccion2 = -1;
    } else if (anguloP2 <= 0.0) {
        direccion2 = 1;
    }
    
    anguloP3 += 0.3 * direccion3;
    
    if (anguloP3 >= maxAnguloP3) {
        direccion3 = -1;
    } else if (anguloP3 <= 0.0) {
        direccion3 = 1;
    }
	display();
}

int main(int argc, char** argv) {
	char soundFile[] = "Luces.wav";
	PlaySound(soundFile, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(400, 50);
	glutCreateWindow("Proyecto_Final");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_s);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
