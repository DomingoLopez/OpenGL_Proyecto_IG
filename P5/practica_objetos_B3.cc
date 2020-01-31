//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, SPIDER} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_tanque tanque;
_spider spider;

// _objeto_ply *ply1;

//VARIABLES PARA EL PICK DE COLOR NECESARIOS

int estadoRaton[3], xc, yc, modos[12], cambio=0;

float incrementoColor = 0; //Pequeño incremento de color para los picks que se vean más marcados

//PEQUEÑO TRUCO PARA QUE NO CORRA MUCHO CUANDO HAY ANIMACIÓN Y TENEMOS QUE HACER PICK. (CAMBIA ENTRE ESTADOS)
bool entrado = false;

//CAMBIOS DE LA PROYECCIÓN Y CÁMARAS
int modo_camara =1;
float factor = 1.0;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

void change_projection_planta(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(Observer_distance*-0.5,Observer_distance*0.5,Observer_distance*-0.5,Observer_distance*0.5,-100.0,100.0);
}

void change_projection_alzado(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(Observer_distance*-0.5,Observer_distance*0.5,Observer_distance*-0.5,Observer_distance*0.5,-100.0,100.0);

}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glViewport(0,0,Window_width,Window_high);
change_projection();
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}



//Cambiar a proyección paralela

void change_observer_planta(){
    change_projection_planta();
    glViewport(0,0,Window_width,Window_high);
    glRotatef(90,1,0,0);
    glScalef(factor,factor,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void change_observer_alzado(){
    change_projection_alzado();
    glViewport(0,0,Window_width,Window_high);
    glRotatef(90,0,1,0);
    glScalef(factor,factor,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case ARTICULADO: tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
        //case SPIDER: spider.draw(modo,0.0,0.0,0.0,0.3,0.3,0.3,2);break;
        case SPIDER: spider.draw(modo,0.64,0.16,0.16,0.36,0.25,0.2,2);break; //Colores rojo y marrón
	}

}


void draw_objects_seleccion(){

        if(t_objeto == SPIDER && modo == SOLID){ //Si el objeto es la araña
        //Dado que voy a hacer la selección de color sobre la araña. Ha de respetar y se ha de mover la "capa falsa" igual que la original
        int inc = 10; //Indico el incremento de color que voy a dar a cada componente de la araña.
        spider.draw_seleccion(100,100,100, inc);
        }

}

void draw_objects_seleccion_triangulo(){


        if(t_objeto == SPIDER && modo == SELECCION){


            int inc = 1;
            spider.draw_seleccion_triangulo(10,10,10, inc);

        }

}





//**************************************************************************
//
//***************************************************************************

void draw(void)
{

if(!entrado){
glDrawBuffer(GL_FRONT);
clean_window();
if(modo_camara ==1) change_observer();
if(modo_camara ==2) change_observer_planta();
if(modo_camara ==3) change_observer_alzado();
//change_observer();
draw_axis();
draw_objects();


glDrawBuffer(GL_BACK); //ESTO HACE QUE SE ESCRIBA EN EL BUFFER "TRASERO LOS OBJETOS CON LOS PARÁMETROS DE DRAW_OBJECTS_SELECCION". ASÍ CREAMOS UNA "SOMBRA" DE CADA OBJETO Y DESPUES LEEMOS DEL GL BACK
clean_window();
change_observer();
if(modo != SELECCION){
draw_objects_seleccion();
}else{
    draw_objects_seleccion_triangulo();
}

glFlush();

}else{

clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();


}

}

void animacion(){
        spider.animacion();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
    case '5':modo=SELECCION;break;
    case '6': modo_camara = 2;break;
    case '8': modo_camara = 1;break;
    case '7': modo_camara = 3;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'A':t_objeto=ARTICULADO;break;
        case 'H':t_objeto=SPIDER;break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************
void animacionIDLE(){ //ANIMACIÓN IDDLE PARA LAS PATAS CUANDO SE ACTIVA
        
                       spider.animacion();
                       glutPostRedisplay();
}



void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        case GLUT_KEY_F1:tanque.giro_tubo+=1;
                         if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_max;
                         break;
        case GLUT_KEY_F2:tanque.giro_tubo-=1;
                         if (tanque.giro_tubo<tanque.giro_tubo_min) tanque.giro_tubo=tanque.giro_tubo_min;
                         break;break;
        case GLUT_KEY_F3:tanque.giro_torreta+=5;break;
        case GLUT_KEY_F4:tanque.giro_torreta-=5;break;


        case GLUT_KEY_F5: //MOVIMIENTO DE LAS PATAS MANUALMENTE

                if(t_objeto == SPIDER){ 


                spider.animacion();

                }

        break;

        case GLUT_KEY_F6: //Movimiento del aguijón Hacia arriba

                if(t_objeto==SPIDER){
                        float incremento = 1.0;
                        spider.modificaAnguloAguijon(incremento);
                

                }


        break;

        case GLUT_KEY_F7: //Movimiento del aguijón Hacia arriba

                if(t_objeto==SPIDER){
                        float incremento = -1.0;
                        spider.modificaAnguloAguijon(incremento);
                }


        break;
        

        case GLUT_KEY_F8: //ACTIVAMOS FUNCIÓN IDDLE PARA QUE REALICE LA ANIMACIÓN

                if(t_objeto==SPIDER){
                        entrado = true;
                        glutIdleFunc(animacionIDLE);           
                }


        break;

        case GLUT_KEY_F9: //DESACTIVAMOS FUNCIÓN IDDLE PARA QUE PARE LA ANIMACIÓN

                if(t_objeto==SPIDER){
                        glutIdleFunc(nullptr);
                        entrado = false;
                }


        break;


        case GLUT_KEY_F10: //Abrimos pinzas

                if(t_objeto==SPIDER){
                
                        float incremento = 1.0;
                        spider.modificaAnguloPinzas(incremento);
                }


        break;

        case GLUT_KEY_F11: //Cerramos pinzas

                if(t_objeto==SPIDER){
                        float incremento = -1.0;
                        spider.modificaAnguloPinzas(incremento);
                }


        break;

}

	
glutPostRedisplay();

}//Fin switch
//Fin función



void procesar_color(unsigned char color[3]) //Recibe el color de ese pixel seleccionado
{

 switch (color[0])
      {case 100:  //Se ha pickado Scentro. (Cuerpo central de la araña)
                 if (modos[0]==0) 
                      {modos[0]=1;
                      
                       spider.Scentro.r1 = 0.3+incrementoColor;
                       spider.Scentro.g1 = 0.9+incrementoColor;
                       spider.Scentro.b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[0]=0;
                       spider.Scentro.r1 = 0.64;
                       spider.Scentro.g1 = 0.16;
                       spider.Scentro.b1 = 0.16;
                      }
                  break; 
        case 120: //Se ha pickado Stracero. (Cuerpo trasero)
                 if (modos[1]==0) 
                      {modos[1]=1;
                       spider.Strasero.r1 = 0.3+incrementoColor;
                       spider.Strasero.g1 = 0.9+incrementoColor;
                       spider.Strasero.b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[1]=0;
                       spider.Strasero.r1 = 0.64;
                       spider.Strasero.g1 = 0.16;
                       spider.Strasero.b1 = 0.16;
                      }
                  break;
        case 130:  //Se ha pickado Scabeza. (La cabeza de la araña)
                  if (modos[2]==0) 
                      {modos[2]=1;
                       spider.Scabeza.r1 = 0.3+incrementoColor;
                       spider.Scabeza.g1 = 0.9+incrementoColor;
                       spider.Scabeza.b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[2]=0;
                       spider.Scabeza.r1 = 0.64;
                       spider.Scabeza.g1 = 0.16;
                       spider.Scabeza.b1 = 0.16;
                      }
                  break; 
        case 140: //Se ha pickado Saquijón
                  if (modos[3]==0) 
                      {modos[3]=1;
                       spider.Saguijon.r1 = 0.3+incrementoColor;
                       spider.Saguijon.g1 = 0.9+incrementoColor;
                       spider.Saguijon.b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[3]=0;
                       spider.Saguijon.r1 = 0.64;
                       spider.Saguijon.g1 = 0.16;
                       spider.Saguijon.b1 = 0.16;
                      }
                  break;
        case 150: //Se ha pickado una de las pinzas Spinzas (pinza derecha)
                  if (modos[4]==0) 
                      {modos[4]=1;
                       spider.Spinzas.r1 = 0.3+incrementoColor;
                       spider.Spinzas.g1 = 0.9+incrementoColor;
                       spider.Spinzas.b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[4]=0;
                       spider.Spinzas.r1 = 0.64;
                       spider.Spinzas.g1 = 0.16;
                       spider.Spinzas.b1 = 0.16;
                      }
                  break;

        case 160: //Se ha pickado una de las pinzas Spinzas (pinza izquierda)
                  if (modos[5]==0) 
                      {modos[5]=1;
                       spider.Spinzas.r1 = 0.3+incrementoColor;
                       spider.Spinzas.g1 = 0.9+incrementoColor;
                       spider.Spinzas.b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[5]=0;
                       spider.Spinzas.r1 = 0.64;
                       spider.Spinzas.g1 = 0.16;
                       spider.Spinzas.b1 = 0.16;
                      }
                  break;

        case 170: //Se ha pickado una de las patas (Empezamos por la primera y así)
                  if (modos[6]==0) 
                      {modos[6]=1;
                       spider.patas[0].r1 = 0.3+incrementoColor;
                       spider.patas[0].g1 = 0.9+incrementoColor;
                       spider.patas[0].b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[6]=0;
                       spider.patas[0].r1 = 0.64;
                       spider.patas[0].g1 = 0.16;
                       spider.patas[0].b1 = 0.16;
                      }
                  break;

        case 180: //Se ha pickado una de las patas (Empezamos por la primera y así)
                  if (modos[7]==0) 
                      {modos[7]=1;
                       spider.patas[1].r1 = 0.3+incrementoColor;
                       spider.patas[1].g1 = 0.9+incrementoColor;
                       spider.patas[1].b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[7]=0;
                       spider.patas[1].r1 = 0.64;
                       spider.patas[1].g1 = 0.16;
                       spider.patas[1].b1 = 0.16;
                      }
                  break;

        case 190: //Se ha pickado una de las patas (Empezamos por la primera y así)
                  if (modos[8]==0) 
                      {modos[8]=1;
                       spider.patas[2].r1 = 0.3+incrementoColor;
                       spider.patas[2].g1 = 0.9+incrementoColor;
                       spider.patas[2].b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[8]=0;
                      spider.patas[2].r1 = 0.64;
                       spider.patas[2].g1 = 0.16;
                       spider.patas[2].b1 = 0.16;
                      }
                  break;

        case 200: //Se ha pickado una de las patas (Empezamos por la primera y así)
                  if (modos[9]==0) 
                      {modos[9]=1;
                       spider.patas[3].r1 = 0.3+incrementoColor;
                       spider.patas[3].g1 = 0.9+incrementoColor;
                       spider.patas[3].b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[9]=0;
                       spider.patas[3].r1 = 0.64;
                       spider.patas[3].g1 = 0.16;
                       spider.patas[3].b1 = 0.16;
                      }
                  break;

        case 210: //Se ha pickado una de las patas (Empezamos por la primera y así)
                  if (modos[10]==0) 
                      {modos[10]=1;
                       spider.patas[4].r1 = 0.3+incrementoColor;
                       spider.patas[4].g1 = 0.9+incrementoColor;
                       spider.patas[4].b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[10]=0;
                       spider.patas[4].r1 = 0.64;
                       spider.patas[4].g1 = 0.16;
                       spider.patas[4].b1 = 0.16;
                      }
                  break;

        case 220: //Se ha pickado una de las patas (Empezamos por la primera y así)
                  if (modos[11]==0) 
                      {modos[11]=1;
                       spider.patas[5].r1 = 0.3+incrementoColor;
                       spider.patas[5].g1 = 0.9+incrementoColor;
                       spider.patas[5].b1 = 0.3+incrementoColor;
                      }
                  else 
                      {modos[11]=0;
                       spider.patas[5].r1 = 0.64;
                       spider.patas[5].g1 = 0.16;
                       spider.patas[5].b1 = 0.16;
                      }
                  break;
        
                }         


                //Incrementamos el color
                incrementoColor-=0.05;
                if (incrementoColor < -0.55){
                        incrementoColor = 0;
                }
                
                 
 }


void procesar_color_triangulo(unsigned char color[3]){

    bool encontrado = false;
    int caraPulsada = 0;

    for(int i =0; i<spider.Scentro.centro.coloresBack.size() && !encontrado; i++){
        if(spider.Scentro.centro.coloresBack[i].r == color[0]){
            encontrado = true;
            caraPulsada = i;    
                
        }
    }
    
        
    if(spider.Scentro.centro.carasPulsadas[caraPulsada] && encontrado){
        spider.Scentro.centro.carasPulsadas[caraPulsada] = false;
        spider.Scentro.centro.coloresFront[caraPulsada].r = 0.64;
        spider.Scentro.centro.coloresFront[caraPulsada].g = 0.16;
        spider.Scentro.centro.coloresFront[caraPulsada].b = 0.16;
    }else if(!spider.Scentro.centro.carasPulsadas[caraPulsada] && encontrado){
        spider.Scentro.centro.carasPulsadas[caraPulsada] = true;
        spider.Scentro.centro.coloresFront[caraPulsada].r = 0.3;
        spider.Scentro.centro.coloresFront[caraPulsada].g = 0.9;
        spider.Scentro.centro.coloresFront[caraPulsada].b = 0.3;
    }




}





void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3]; //Captura el pixel

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK); //LEEMOS DE BUFFER BACK, POR ESO SALEN ESOS COLORES DE PÍXELES Y PODEMOS DIFERENCIAR LAS PIRÁMIDES
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]); //Lee el pixel y lo guarda (El color)
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

if(modo !=SELECCION)
procesar_color(pixel);
else
procesar_color_triangulo(pixel);

glutPostRedisplay();
}




//FUNCIÓN QUE SE EJECUTA EL HACER CLICK CON EL RATÓN

void clickRaton( int boton, int estado, int x, int y )
{

if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x; //Setea los parámetros globales de la posición relativa de la ventana
      yc=y;
     } 
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      if(modo_camara ==1)
      pick_color(xc, yc); //Si pica con el botón izquierdo llama a pick_color con esas coordenadas relativas de x e y
    } 
  }

  //ESTO ES EL ZOOM POR RUEDA DE RATÓN
if(boton == 3){

     if(estado == 1){
          
          Observer_distance/=1.2;
          glutPostRedisplay();
    }
}
if(boton == 4){
     if(estado == 1){
          
          Observer_distance*=1.2;
          glutPostRedisplay();
    }
}


}

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_y;
*y=Observer_angle_x;

/*
*x=Observer_angle_x; //Así estaba. Hay que hacerlo al reveés para que funcione bien
*y=Observer_angle_y;
*/
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y) //Para setear la cámara
{
Observer_angle_x=y; 
Observer_angle_y=x;

/*
Observer_angle_x=y; //Así estaba. Hay que hacerlo al revés para que funcione bien
Observer_angle_y=x;

*/

}



/*************************************************************************/

void RatonMovido( int x, int y ) //x e y del ratón en ese momento
{
float x0, y0, xn, yn; 
if(estadoRaton[2]==1) //Si el botón derecho está pulsado
    {getCamara(&x0,&y0); //Obtenemos los valores x e y del observador
     yn=y0+(y-yc); //El observador ahora será donde esté en ese momento (y0) + (y del ratón - y de la posición relativa de la camara)
     xn=x0-(x-xc);
     setCamara(xn,yn); //Seteamos los nuevos valores del observador
     xc=x; 
     yc=y;
     glutPostRedisplay();
    }
}






//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);

//12 porque tengo 12 objetos en la araña
for (int i=0;i<12;i++) modos[i]=0; //Seteamos los modos para la selección

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv)
{
 

// creación del objeto ply

ply.parametros(argv[1]);


// perfil 

vector<_vertex3f> perfil2;
_vertex3f aux;
aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=0.5;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.8;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.55;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=1.4;aux.z=0.0;
perfil2.push_back(aux);
rotacion.parametros(perfil2,6,1);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// eventos ratón
glutMouseFunc( clickRaton );
glutMotionFunc( RatonMovido );


// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
