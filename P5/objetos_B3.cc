//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"
#include <cmath>


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{

}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}


void _triangulos3D::draw_seleccion(float r, float g, float b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3ub(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

void _triangulos3D::draw_seleccion_triangulo(float r, float g, float b, int inc){

int i;
int incre = 0;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);

for (i=0;i<caras.size();i++){

  glColor3ub(r+incre,g+incre,b+incre);

	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

  incre+=inc;

	}
glEnd();

incre = 0;
for(int j=0 ; j<caras.size();j++){
  coloresBack[j].r = r+incre;
  coloresBack[j].g = g+incre;
  coloresBack[j].b = b+incre;

  incre+=inc;
}



}

void _triangulos3D::draw_solido_seleccion(float r, float g, float b){

int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
  glColor3f(coloresFront[i].r,coloresFront[i].g,coloresFront[i].b);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);


  }

glEnd();






}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
  case SELECCION:draw_solido_seleccion(r1,g1,b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  


for(int i =0; i<caras.size(); i++){
  coloresFront.push_back({0.64,0.16,0.16});
  carasPulsadas.push_back({false});
}

coloresBack.resize(caras.size());



}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;


for(int i =0; i<caras.size(); i++){
  coloresFront.push_back({0.64,0.16,0.16});
  carasPulsadas.push_back({false});
}

coloresBack.resize(caras.size());

}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
   
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************


_rotacion::_rotacion()
{

}

/*
void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }
     
 // tapa inferior
if (fabs(perfil[0].x)>0.0 && tapa==1)
  {
  }
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1)
  {
  }
}*/

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)//num es número de lados que se quiren crear
{
int i,j;
_vertex3f vertice_aux;
int num_aux;

//Vértices auxiliares para las tapas inferior y superior
_vertex3f centralTapaInferior;
_vertex3f centralTapaSuperior;
// tratamiento de los vértices


//ESTA COMPROBACIÓN SIRVE PARA EXTRAER LOS VÉRTICES SUPERIOR E INFERIOR DEL PERFIL SI PERTENECEN AL EJE DE ROTACIÓN
if(perfil[0].x==0.0){
   centralTapaInferior = perfil[0];
  perfil.erase(perfil.begin());
}else{
   centralTapaInferior(0.0, perfil[0].y,0.0);
}

if(perfil[perfil.size()-1].x==0.0){
   centralTapaSuperior = perfil[perfil.size()-1];
  perfil.erase(perfil.begin()+perfil.size()-1);
}else{
   centralTapaSuperior(0.0, perfil[perfil.size()-1].y,0.0);
}


num_aux=perfil.size();
vertices.resize(num_aux*num); //Numero de puntos del perfil por el número de lados ó ángulos (rotaciones) que se van a realizar


for (j=0;j<num;j++) //Para cada lado (rotación)
  {for (i=0;i<num_aux;i++) //Para cada vértice del perfil
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+ //OJO, que se ha de usar una variable auxiliar
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y; //Como se ve, se está girando respecto al eje y, ya que este no cambia
      vertices[i+j*num_aux]=vertice_aux; 
     }
  }


/****************************************************************************
// tratamiento de las caras 
//Insertar código de tratamiento de las caras
****************************************************************************/
//Cálculo de numero de caras

int numCaras = ((num_aux*2) -2)*num;
int contador = 0; //Para contabilizar el número de caras

caras.resize(numCaras); //Si analizamos las caras de la revolución, tendremos dos caras más que puntos de perfil -2 (2*2-2 = 2 caras (para dos puntos), (3*2-2 = 4) 4 caras para 3 puntos, etc)
_vertex3i cara_aux; //Creamos una cara auxiliar para almacenar cada una de las caras que vamos a crear
int k = 0; //k es un valor auxiliar que nos ayudará a cambiar entre los vértices 


//PRIMERA FORMA DE TRATAR LAS CARAS. FUNCIONA IGUAL, PERO NO ES TAN ELEGANTE. DESCOMENTAR PARA PROBAR SI SE DESEA
/*

for(int i=0; i< num-1; i++){//Para cada una de las rotaciones realizadas SALVO LA ÚLTIMA. Tendremos que cerrar manualmente la última parte
//Seguro que podríamos cerrar la última usando el ángulo de giro con senos y cosenos, etc. Ver más adelante si da tiempo
  
  for(int j=0; j<num_aux-1;j++){//Para cada vértice del perfil (SALVO EL ÚLTIMO, por eso lo de num_aux-1)


      //Primera cara de las dos que surgen de la revolución
      cara_aux._0=k+j;
      cara_aux._1=k+j+num_aux;
      cara_aux._2=k+j+1;
      caras[contador] = cara_aux;
      contador++;
      //Segunda cara
      cara_aux._0=k+j+num_aux;
      cara_aux._1=k+j+num_aux+1;
      cara_aux._2=k+j+1;
      caras[contador] = cara_aux;
      contador++;

  }

  k+=num_aux; //k + el número de vértices nos lleva al siguiente punto donde se volverá a comenzar a crear las caras (suele ser la base del siguiente perfil generado)

}

/*********************************************************************
//Hacemos el cierre de los últimos vértices con los iniciales
*********************************************************************

for(int j=0; j<num_aux-1;j++){//Para cada vértice del perfil (SALVO EL ÚLTIMO, por eso lo de num_aux-1)


      //Primera cara del cierre
      cara_aux._0=k+j;
      cara_aux._1=j;
      cara_aux._2=k+j+1;
      caras[contador] = cara_aux;
      contador++;
      //Segunda cara del cierre
      cara_aux._0=j;
      cara_aux._1=j+1;
      cara_aux._2=k+j+1;
      caras[contador] = cara_aux;
      contador++;

  }
  TERMINA AQUÍ LA PRIMERA FORMA DE TRATAR LAS CARAS. NO TAN ELEGANTE
  */


//2ª FORMA DE TRATAR LAS CARAS. MÁS ELEGANTE

for(int j=0; j<num; j++){
  for(int i = 0; i<num_aux-1;i++){

    cara_aux._0=i+((j+1)%num)*num_aux;
    cara_aux._1=i+1+((j+1)%num)*num_aux;
    cara_aux._2=i+1+j*num_aux;
    caras.push_back(cara_aux);

    cara_aux._0=i+1+j*num_aux;
    cara_aux._1=i+j*num_aux;
    cara_aux._2=i+((j+1)%num)*num_aux;
    caras.push_back(cara_aux);



  }
}

/*

 // tapa inferior
if (fabs(perfil[0].x)>0.0) //Esta comprobación es porque si tenemos un punto en el eje de giro se repetiría muchas veces.
  { //Por eso hacemos esta comprobación. 
  //La tapa es la parte que hemos de hacer manual para que no se repitan los puntos al hacer la rotación. (Los puntos del eje que rota)
  


  //ESTA COMPROBACIÓN SE HA HECHO ARRIBA DE LA FUNCIÓN DE MANERA PARECIDA
  DADO QUE MI PROGRAMA MANEJA LA GESTIÓN DE LOS VERTICES DENTRO DEL EJE DE ROTACIÓN
    

  }


*/

  //Mi forma de crear las tapas. Añadimos los vértices que hemos extraido al vector de vértices y lo hacemos corresponder con los vértices de cierre de la tapa

if(tapa == 1){
    vertices.push_back(centralTapaInferior);
    k=0; //valor auxiliar

    for(int i=0; i<num-1;i++){
      cara_aux._0=k;cara_aux._1=k+num_aux;cara_aux._2=vertices.size()-1;
      caras.push_back(cara_aux);
      k+=num_aux;
    }

    //Añadimos la cara final 
    cara_aux._0=k;cara_aux._1=0;cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);


}


/*

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
    //ESTA COMPROBACIÓN SE HA HECHO ARRIBA DE LA FUNCIÓN DE MANERA PARECIDA
    DADO QUE MI PROGRAMA MANEJA LA GESTIÓN DE LOS VÉRTICES DENTRO DEL EJE DE ROTACIÓN
    
  }
*/

if(tapa==1){

    	vertices.push_back(centralTapaSuperior);
    	k = num_aux -1;
    
    	for(int i=0; i<num-1;i++){
      	 cara_aux._0=k;cara_aux._1=k+num_aux;cara_aux._2=vertices.size()-1;
      	 caras.push_back(cara_aux);
     	 k+=num_aux;
    	}

    	//Añadimos la cara final (la que une final con principio, dado que se han de unir los vértices finales con los iniciales)

    	cara_aux._0=k;cara_aux._1=num_aux-1;cara_aux._2=vertices.size()-1;
    	caras.push_back(cara_aux);
	}


  for(int i =0; i<caras.size(); i++){
  coloresFront.push_back({0.64,0.16,0.16});
  carasPulsadas.push_back({false});
  }
coloresBack.resize(caras.size());

}

//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12,1);
altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,0); //EL 0 del parametro es para que no tenga tapa. Mirar la funcion parámetros
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.4,0,0); //Recordar que primero se "ejecuta" la rotación y despues la traslación. Esto no es así, es decir, se traslada y se rota, pero como las matrices en openGL son traspuesta, hemos de pensar al reves
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
glPopMatrix();

};



/*
A PARTIR DE AQUÍ SE ESPECIFICAN LAS CLASES NECESARIAS PARA CREAR
EL OBJETO ARTICULADO HORMIGA

Para ello, necesitaremos, conos, cilindros, esferas. 

*/

//CLASE CONO

_cono::_cono(float altura, float radio){

  _vertex3f aux;
  
//Perfil del cono
aux.x=radio; aux.y=-altura/2; aux.z=0.0;
vertices.push_back(aux);
aux.x=0; aux.y=altura/2; aux.z=0.0;
vertices.push_back(aux);

this->parametros(vertices,18,1);

}

//CLASE CILINDRO

_cilindro::_cilindro(float altura, float radio){

  _vertex3f aux;
  
//Perfil del cilindro
aux.x=radio; aux.y=-altura/2; aux.z=0.0;
vertices.push_back(aux);
aux.x=radio; aux.y=altura/2; aux.z=0.0;
vertices.push_back(aux);

this->parametros(vertices,18,1);

}


_esfera::_esfera(float radio){

//Perfil de la esfera (Lo vamos a generar por ángulos.)

  _vertex3f aux;
  
  int repeticiones = 8;//Estas repeticiones marcan el número de puntos del perfil
  int anguloGiro = 180/repeticiones; //180 es el ángulo máximo de giro que vamos a tener

  int anguloInicial = -90; //Empezamos en -90 grados y vamos hasta los 90


  while(anguloInicial >=-90 && anguloInicial <=90){

  if(anguloInicial==-90){ //Esto hemos de hacerlo, porque cos(90*M_PI/180) no va a dar 0 exacto. Y queremos que sea 0 exacto para la comprobación posterior en el método parámetros
    aux.x=0.0;aux.y=-radio;aux.z=0.0;
    vertices.push_back(aux);
  }else if(anguloInicial==90){
    aux.x=0.0;aux.y=radio;aux.z=0.0;
    vertices.push_back(aux);
  }else{
  aux.x=radio*cos(anguloInicial*M_PI/180);aux.y=radio*sin(anguloInicial*M_PI/180);aux.z=0.0;
  vertices.push_back(aux);
  }

  anguloInicial+=anguloGiro;
  }

  this->parametros(vertices,8, 1);

}


_trapecio::_trapecio(float baseInferior, float baseSuperior, float altura){

  this->baseInferior=baseInferior;
  this->baseSuperior=baseSuperior;
  this->altura=altura;



  vertices.resize(8);
  vertices[0].x=baseInferior/2; vertices[0].y=-altura/2; vertices[0].z=-baseInferior/2;
  vertices[1].x=baseInferior/2; vertices[1].y=-altura/2; vertices[1].z=baseInferior/2;
  vertices[2].x=-baseInferior/2; vertices[2].y=-altura/2; vertices[2].z=baseInferior/2;
  vertices[3].x=-baseInferior/2; vertices[3].y=-altura/2; vertices[3].z=-baseInferior/2;
  vertices[4].x=baseSuperior/2; vertices[4].y=altura/2; vertices[4].z=-baseSuperior/2;
  vertices[5].x=baseSuperior/2; vertices[5].y=altura/2; vertices[5].z=baseSuperior/2;
  vertices[6].x=-baseSuperior/2;vertices[6].y=altura/2; vertices[6].z=baseSuperior/2;
  vertices[7].x=-baseSuperior/2; vertices[7].y=altura/2; vertices[7].z=-baseSuperior/2;

  

caras.resize(12);
caras[0]._0=2;caras[0]._1=1;caras[0]._2=0;
caras[1]._0=3;caras[1]._1=2;caras[1]._2=0;
caras[2]._0=3;caras[2]._1=0;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=4;caras[3]._2=7;
caras[4]._0=0;caras[4]._1=1;caras[4]._2=5;
caras[5]._0=0;caras[5]._1=5;caras[5]._2=4;
caras[6]._0=1;caras[6]._1=2;caras[6]._2=6;
caras[7]._0=1;caras[7]._1=6;caras[7]._2=5;
caras[8]._0=2;caras[8]._1=3;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=7;caras[9]._2=6;
caras[10]._0=7;caras[10]._1=4;caras[10]._2=5;
caras[11]._0=7;caras[11]._1=5;caras[11]._2=6;  



for(int i =0; i<caras.size(); i++){
  coloresFront.push_back({0.64,0.16,0.16});
  carasPulsadas.push_back({false});
}
coloresBack.resize(caras.size());

}


_pinzaSpider::_pinzaSpider(float radio, float altura){

  this->radio=radio;
  this->altura=altura;

  vertices.resize(9);
  vertices[0].x= radio/2;vertices[0].y= 0;vertices[0].z= 0;
  vertices[1].x= radio/2*cos(45*M_PI/180);vertices[1].y=0 ;vertices[1].z= radio/2*sin(45*M_PI/180);
  vertices[2].x= 0;vertices[2].y=0 ;vertices[2].z= radio/2;
  vertices[3].x= -radio/2*cos(45*M_PI/180);vertices[3].y=0 ;vertices[3].z= radio/2*sin(45*M_PI/180);
  vertices[4].x= -radio/2;vertices[4].y=0 ;vertices[4].z= 0;
  vertices[5].x= -radio/2*cos(45*M_PI/180);vertices[5].y=0 ;vertices[5].z= -radio/2*sin(45*M_PI/180);
  vertices[6].x= 0;vertices[6].y=0 ;vertices[6].z= -radio/2;
  vertices[7].x= radio/2*cos(45*M_PI/180);vertices[7].y= 0;vertices[7].z= -radio/2*sin(45*M_PI/180);
  vertices[8].x= -radio/2;vertices[8].y= altura/2;vertices[8].z= 0;


  caras.resize(14);

  //Parte inferior
  caras[0]._0=1;caras[0]._1=0;caras[0]._2=7;
  caras[1]._0=1;caras[1]._1=7;caras[1]._2=6;
  caras[2]._0=2;caras[2]._1=1;caras[2]._2=6;
  caras[3]._0=2;caras[3]._1=6;caras[3]._2=5;
  caras[4]._0=3;caras[4]._1=2;caras[4]._2=5;
  caras[5]._0=3;caras[5]._1=5;caras[5]._2=4;
  //Parte superior
  caras[6]._0=7;caras[6]._1=0;caras[6]._2=8;
  caras[7]._0=6;caras[7]._1=7;caras[7]._2=8;
  caras[8]._0=5;caras[8]._1=6;caras[8]._2=8;
  caras[9]._0=4;caras[9]._1=5;caras[9]._2=8;
  caras[10]._0=3;caras[10]._1=4;caras[10]._2=8;
  caras[11]._0=2;caras[11]._1=3;caras[11]._2=8;
  caras[12]._0=1;caras[12]._1=2;caras[12]._2=8;
  caras[13]._0=0;caras[13]._1=1;caras[13]._2=8;

for(int i =0; i<caras.size(); i++){
  coloresFront.push_back({0.64,0.16,0.16});
  carasPulsadas.push_back({false});
}

coloresBack.resize(caras.size());

}





/**********************************************************************/
//Cuerpo Central Araña

_cuerpoCentral::_cuerpoCentral(){

}

void _cuerpoCentral::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){


glPushMatrix();
glScalef(1,0.7,0.7);
glTranslatef(0,1,0);
centro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


}


void _cuerpoCentral::draw_seleccion(float r, float g, float b){

glPushMatrix();
glScalef(1,0.7,0.7);
glTranslatef(0,1,0);
centro.draw_seleccion(r,g,b);
glPopMatrix();

}

void _cuerpoCentral::draw_seleccion_triangulo(float r, float g, float b, int inc){

glPushMatrix();
glScalef(1,0.7,0.7);
glTranslatef(0,1,0);
centro.draw_seleccion_triangulo(r,g,b,inc);
glPopMatrix();

}


/*Cuerpo Trasero Hormiga**********************************************************/

_cuerpoTrasero::_cuerpoTrasero(){

}


void _cuerpoTrasero::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){



glPushMatrix();
glTranslatef(0.9,0.7,0);
glScalef(1.2,1.2,1.2);
trasero.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


}


void _cuerpoTrasero::draw_seleccion(float r, float g, float b){

glPushMatrix();
glTranslatef(0.9,0.7,0);
glScalef(1.2,1.2,1.2);
trasero.draw_seleccion(r,g,b);
glPopMatrix();



}


/*Cuerpo Delantero Araña*****************************************************************/





/*Cabeza Araña*/


_cabezaSpider::_cabezaSpider(){

  

}

void _cabezaSpider::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
 
glPushMatrix();
glTranslatef(-0.55,0.7,0);
glRotatef(90,0,0,1);
glScalef(0.4,0.4,0.4);
cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


}


void _cabezaSpider::draw_seleccion(float r, float g, float b){

glPushMatrix();
glTranslatef(-0.55,0.7,0);
glRotatef(90,0,0,1);
glScalef(0.4,0.4,0.4);
cabeza.draw_seleccion(r,g,b);
glPopMatrix();

}



_aguijonSpider::_aguijonSpider(){
this->anguloActualZ=245;
this->limiteInferiorZ=225;
this->limiteSuperiorZ=270;
}

void _aguijonSpider::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
 
glPushMatrix();
glTranslatef(1.5,0.7,0.0);
glRotatef(anguloActualZ,0,0,1);
glScalef(1.1,0.5,1.1);
aguijon.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

 
}


void _aguijonSpider::draw_seleccion(float r, float g, float b){


glPushMatrix();
glTranslatef(1.5,0.7,0.0);
glRotatef(anguloActualZ,0,0,1);
glScalef(1.1,0.5,1.1);
aguijon.draw_seleccion(r,g,b);
glPopMatrix();


}



void _aguijonSpider::modificaAnguloAguijon(float incremento){
  float anguloAux = this->anguloActualZ+incremento;

  if(anguloAux >= limiteInferiorZ && anguloAux<=limiteSuperiorZ){
    this->anguloActualZ = anguloAux;
  }
}


_pinzasSpider::_pinzasSpider(){
  //HE DE SETEAR LOS ÁNGULOS ACTUALES DE ROTACIÓN RESPECTO A Y
  anguloActualPinzaD = -1;
  anguloActualPinzaI = 1;

  limiteSuperiorPinzaD = -40;
  limiteInferiorPinzaD = 0;

  limiteSuperiorPinzaI = 40;
  limiteInferiorPinzaI = 0;
  
}




void _pinzasSpider::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

  glPushMatrix();
  glTranslatef(-0.55,0.7,-0.06);
  glRotatef(anguloActualPinzaD,0,1,0); //Rotación en el centro
  glRotatef(-90,1,0,0);
  glRotatef(90,0,0,1);
  glScalef(0.2,0.5,0.2);
  pinzaD.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.55,0.7,0.06);
  glRotatef(anguloActualPinzaI,0,1,0); //Rotación en el centro
  glRotatef(90,1,0,0);
  glRotatef(90,0,0,1);
  glScalef(0.2,0.5,0.2);
  pinzaI.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
  glPopMatrix();

}

void _pinzasSpider::draw_seleccion(float r, float g, float b){


  glPushMatrix();
  glTranslatef(-0.55,0.7,-0.06);
  glRotatef(anguloActualPinzaD,0,1,0); //Rotación en el centro
  glRotatef(-90,1,0,0);
  glRotatef(90,0,0,1);
  glScalef(0.2,0.5,0.2);
  pinzaD.draw_seleccion(r,g,b);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.55,0.7,0.06);
  glRotatef(anguloActualPinzaI,0,1,0); //Rotación en el centro
  glRotatef(90,1,0,0);
  glRotatef(90,0,0,1);
  glScalef(0.2,0.5,0.2);
  pinzaI.draw_seleccion(r+10,g+10,b+10);
  glPopMatrix();

}











_pataSpider::_pataSpider(){}

_pataSpider::_pataSpider(int id){
  this->idPata=id;
}

int _pataSpider::getID(){
  return idPata;
}

void _pataSpider::setID(int id){
  idPata=id;
}


void _pataSpider::setAnguloY(float angulo){
  anguloActualY =  angulo;
}

void _pataSpider::setAnguloX(float angulo){
  anguloActualX =  angulo;
}

void _pataSpider::setLimitesHorizontal(float limiteHorizontal1, float limiteHorizontal2){

this->limiteHorizontal1=limiteHorizontal1;
this->limiteHorizontal2=limiteHorizontal2;

}

void _pataSpider::setLimitesVertical(float limiteVertical1, float limiteVertical2){

this->limiteVertical1=limiteVertical1;
this->limiteVertical2=limiteVertical2;

}


void _pataSpider::setVisitadosHorizontal(bool superiorVisitadoY, bool inferiorVisitadoY){
  this->superiorVisitadoY = superiorVisitadoY;
  this->inferiorVisitadoY = inferiorVisitadoY;
}

void _pataSpider::setVisitadosVertical(bool superiorVisitadoX, bool inferiorVisitadoX){
  this->superiorVisitadoX = superiorVisitadoX;
  this->inferiorVisitadoX = inferiorVisitadoX;
}


void _pataSpider::modificaAnguloX(float incremento){

  this->anguloActualX+=incremento;
}

void _pataSpider::modificaAnguloY(float incremento){
  this->anguloActualY+=incremento;
}


bool _pataSpider::getSuperiorVisitadoY(){

  return this->superiorVisitadoY;
}


bool _pataSpider::getInferiorVisitadoY(){

  return this->inferiorVisitadoY;

}

       
bool _pataSpider::getSuperiorVisitadoX(){

  return this->superiorVisitadoX;
}
       
       
bool _pataSpider::getInferiorVisitadoX(){

  return this->inferiorVisitadoX;
}


 float _pataSpider::getLimiteSuperiorY(){

   return this->limiteHorizontal1;
 }
 float _pataSpider::getLimiteInferiorY(){

   return this->limiteHorizontal2;
 }


float _pataSpider::getAnguloActualY(){
  return this->anguloActualY;
}


float _pataSpider::getAnguloActualX(){

  return this->anguloActualX;
}


void _pataSpider::setDiferenciaLimites(float diferencia){
  this->diferenciaLimites=diferencia;
}

float _pataSpider::getDiferenciaLimites(){
  return this->diferenciaLimites;
}


void _pataSpider::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){



glPushMatrix();

glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.35,0);
glRotatef(-134,1,0,0);
glTranslatef(0,0,-0.5);
salienteCuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();





glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.35,0.75);
glScalef(0.15,0.15,0.15);
articulacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();




glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.20,0.93);
glRotatef(-45,1,0,0);
glScalef(0.5,1,0.5);
intermedia.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();



glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.02,1.1);
glScalef(0.15,0.15,0.15);
articulacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();



glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,0,1.2);
glRotatef(-185,1,0,0);
glTranslatef(0,-0.5,0);
salienteCuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();




}

void _pataSpider::draw_seleccion(float r, float g, float b){


glPushMatrix();

glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.35,0);
glRotatef(-134,1,0,0);
glTranslatef(0,0,-0.5);
salienteCuerpo.draw_seleccion(r,g,b);
glPopMatrix();





glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.35,0.75);
glScalef(0.15,0.15,0.15);
articulacion.draw_seleccion(r,g,b);
glPopMatrix();




glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.20,0.93);
glRotatef(-45,1,0,0);
glScalef(0.5,1,0.5);
intermedia.draw_seleccion(r,g,b);
glPopMatrix();



glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,1.02,1.1);
glScalef(0.15,0.15,0.15);
articulacion.draw_seleccion(r,g,b);
glPopMatrix();



glPushMatrix();
glRotatef(anguloActualX,1,0,0);
glRotatef(anguloActualY,0,1,0);

glTranslatef(0,0,1.2);
glRotatef(-185,1,0,0);
glTranslatef(0,-0.5,0);
salienteCuerpo.draw_seleccion(r,g,b);
glPopMatrix();

}

 

/************************************************************************/
//Araña completa


_pataSpider _spider::getPataIndice(int indice){
  return this->patas[indice];
}


void _spider::modificaAnguloPataY(int indicePata, float incremento){

  this->patas[indicePata].modificaAnguloY(incremento);

}

void _spider::modificaVisitadosH(int indicePata, bool visitadoSuperior, bool visitadoInferior){

  this->patas[indicePata].setVisitadosHorizontal(visitadoSuperior,visitadoInferior);
}

 void _spider::modificaAnguloPataX(int indicePata, float incremento){
   
   if(incremento == -1000)
   this->patas[indicePata].setAnguloX(0);
   else
   this->patas[indicePata].modificaAnguloX(incremento);
 }


void _spider::modificaVisitadosV(int indicePata, bool visitadoSuperior, bool visitadoInferior){

  this->patas[indicePata].setVisitadosVertical(visitadoSuperior, visitadoInferior);
}

void _spider::modificaAnguloAguijon(float incremento){
  this->Saguijon.modificaAnguloAguijon(incremento);
}

void _spider::modificaAnguloPinzas(float incremento){
  if(incremento < 0){ //Cerrar las pinzas
    
    if(Spinzas.anguloActualPinzaI+incremento >= Spinzas.limiteInferiorPinzaI ){
        Spinzas.anguloActualPinzaI+=incremento;
        incremento = abs(incremento);
        Spinzas.anguloActualPinzaD+=incremento;
    }

  }else{
    if((Spinzas.anguloActualPinzaI+incremento) <= Spinzas.limiteSuperiorPinzaI){
        
        Spinzas.anguloActualPinzaI+=incremento;
        Spinzas.anguloActualPinzaD-=incremento;
    }
  }
  
  
}



void _spider::animacion(){
  //Definimos el incremento de las patas Rotación EjeY
                        float incremento = 1.0;//El incremento que le queramos poner al avanzar
                        float incrementoPatasMedias = incremento*2; //Las patas de en medio han de avanzar más rápido
                        float incrementoFinal = incremento;
                        
                        //Definimos el incremento de las patas Rotación EjeX
                        float incrementoV =incremento/2;
                        float incrementoFinalX = incremento;

                        //Para cada una de las patas
                        
                        for(int i=0; i<6;i++){

                                _pataSpider aux = getPataIndice(i);
                                
                                float limiteSuperior = aux.getLimiteSuperiorY();
                                float limiteInferior = aux.getLimiteInferiorY();
                                float anguloActual = aux.getAnguloActualY();
                                float anguloActualX = aux.getAnguloActualX();
                                bool visitadoSuperiorH = aux.getSuperiorVisitadoY();
                                bool visitadoInferiorH = aux.getInferiorVisitadoY();

                                bool visitadoSuperiorV = aux.getSuperiorVisitadoX();
                                bool visitadoInferiorV = aux.getInferiorVisitadoX();
                                
                                float diferenciaLimites = aux.getDiferenciaLimites();
                                
                                if(i%2==0){//Patas pares

                                        if(i==2){ //Para la segunda pata ha de avanzar más rápido
                                                incrementoFinal = incremento*2;
                                                incrementoFinalX = incremento;
                                                diferenciaLimites/=2;
                                        }else{
                                                incrementoFinal = incremento;
                                                incrementoFinalX = incremento;
                                        }

                                        if(!visitadoInferiorH && visitadoSuperiorH){ //Voy hacia abajo
                                            
                                           if(anguloActual < limiteInferior){
                                                modificaAnguloPataY(i,incrementoFinal);
                                                
                                           }else{
                                                modificaAnguloPataY(i,-incrementoFinal);
                                                //PREPARATIVOS MOVIENTO EJE X
                                                modificaAnguloPataX(i,-incrementoFinalX);
                                                modificaVisitadosV(i, false,true);
                                                //FIN PREPARATIVOS MOVIMIENTO EJE X
                                                modificaVisitadosH(i,false,true); //(superior,inferior)
                                           }
                                           
                                        }else if (visitadoInferiorH && !visitadoSuperiorH){ //Voy hacia arriba
                                        
                                           if(anguloActual > limiteSuperior){
                                                modificaAnguloPataY(i,-incrementoFinal);
                                                
                                                //PREPARATIVOS DE MOVIMIENTO ROTANCO EL EJE X
                                                if(!visitadoSuperiorV && visitadoInferiorV && abs(anguloActualX) < diferenciaLimites/2)
                                                        modificaAnguloPataX(i,-incrementoFinalX);
                                                else if(!visitadoSuperiorV && abs(anguloActualX) >= diferenciaLimites/2){
                                                        modificaVisitadosV(i,true, false);
                                                        modificaAnguloPataX(i,incrementoFinalX);
                                                }else if(visitadoSuperiorV && abs(anguloActualX) < diferenciaLimites/2  && abs(anguloActualX) !=0)
                                                        modificaAnguloPataX(i, incrementoFinalX);
                                                else if(!visitadoInferiorV && abs(anguloActualX) == 0){
                                                        modificaAnguloPataX(i, -incrementoFinalX);
                                                        modificaVisitadosV(i,false, true);
                                                }

                                                //FIN DE PREPARATIVOS DE MOVIMIENTO DEL EJE X
                                                
                                           }else{
                                                
                                                modificaAnguloPataY(i,incrementoFinal);
                                                //PREPARATIVOS MOVIENTO EJE X
                                                modificaAnguloPataX(i,-1000); //El -1000 es para resetear el ángulo a 0. Mirar la función
                                                //FIN PREPARATIVOS MOVIMIENTO EJE X
                                                modificaVisitadosH(i,true,false); //(superior,inferior)
                                           }
                                        }

                                }else{

                                        
                                        if(i==3){ //Para la cuarta pata ha de avanzar más rápido (Las patas del medio de la arña son las 2 y 3)
                                                incrementoFinal = incremento*2;
                                                diferenciaLimites/=2;
                                                incrementoFinalX = incremento;
                                        }else{
                                                incrementoFinal = incremento;
                                        }

                                        if(!visitadoInferiorH && visitadoSuperiorH){ //Voy hacia abajo
                                            
                                           if(anguloActual > limiteInferior){
                                                modificaAnguloPataY(i,-incrementoFinal);
                                                
                                           }else{
                                                modificaAnguloPataY(i,+incrementoFinal);
                                                modificaVisitadosH(i,false,true); //(superior,inferior)
                                                //PREPARATIVOS MOVIENTO EJE X
                                                modificaAnguloPataX(i,+incrementoFinalX);
                                                modificaVisitadosV(i, false,true);
                                                //FIN PREPARATIVOS MOVIMIENTO EJE X

                                           }
                                           
                                        }else if (visitadoInferiorH && !visitadoSuperiorH){ //Voy hacia arriba
                                        
                                           if(anguloActual < limiteSuperior){
                                                modificaAnguloPataY(i,incrementoFinal);
                                                //PREPARATIVOS DE MOVIMIENTO ROTANCO EL EJE X
                                                if(!visitadoSuperiorV && visitadoInferiorV && abs(anguloActualX) < diferenciaLimites/2)
                                                        modificaAnguloPataX(i,incrementoFinalX);
                                                else if(!visitadoSuperiorV && abs(anguloActualX) >= diferenciaLimites/2){
                                                        modificaVisitadosV(i,true, false);
                                                        modificaAnguloPataX(i,-incrementoFinalX);
                                                }else if(visitadoSuperiorV && abs(anguloActualX) < diferenciaLimites/2  && abs(anguloActualX) !=0)
                                                        modificaAnguloPataX(i, -incrementoFinalX);
                                                else if(!visitadoInferiorV && abs(anguloActualX) == 0){
                                                        modificaAnguloPataX(i, incrementoFinalX);
                                                        modificaVisitadosV(i,false, true);
                                                }
                                                // FIN PREPARATIVOS DE MOVIMIENTO ROTANCO EL EJE X

                                           }else{
                                                modificaAnguloPataY(i,-incrementoFinal);
                                                modificaVisitadosH(i,true,false); //(superior,inferior)
                                                //PREPARATIVOS MOVIENTO EJE X
                                                modificaAnguloPataX(i,-1000); //El -1000 es para resetear el ángulo a 0. Mirar la función
                                                //FIN PREPARATIVOS MOVIMIENTO EJE X
                                           }
                                        }





                                      }
                                        
                                        

                              



                        }



}

_spider::_spider(){

//Seteo los IDS de las patas
for(int i=0;i<6;i++){
  _pataSpider pata;
  pata.setID(i);
  patas.push_back(pata);
}
/*Spata0.setID(0);
Spata1.setID(1);
Spata2.setID(2);
Spata3.setID(3);
Spata4.setID(4);
Spata5.setID(5);*/

//Seteo los ángulos iniciales de cada pata. Así aparecerán al dibujarlas por primera vez

/*switch(id){
  case 0: ang = -45; break;
  case 1: anguloInicial = 225 - 22.5 + margen; break;
  case 2: anguloInicial = 0.0; break;
  case 3: anguloInicial = 180 +22.5 -margen; break;
  case 4: anguloInicial = 45; break;
  case 5: anguloInicial = 135; break; 
  
}*/

int margen = 5; //Margen de 5 grados entre cada pata al andar


/*
Spata0.setAnguloY(315);
Spata1.setAnguloY(180 +22.5 + margen);
Spata2.setAnguloY(22.5 - margen);
Spata3.setAnguloY(180 +22.5 -margen);
Spata4.setAnguloY(22.5 +margen);
Spata5.setAnguloY(135);*/

/*patas[0].setAnguloY(315);
patas[1].setAnguloY(180 +22.5 + margen);
patas[2].setAnguloY(22.5 - margen);
patas[3].setAnguloY(180 +22.5 -margen);
patas[4].setAnguloY(22.5 +margen);
patas[5].setAnguloY(135);*/

//Lo mismo pero con un grado más en los ángulos extremos
patas[0].setAnguloY(316);
patas[1].setAnguloY(180 +23 + margen);
patas[2].setAnguloY(23 - margen);
patas[3].setAnguloY(180 +23 -margen);
patas[4].setAnguloY(23 +margen);
patas[5].setAnguloY(136);

//Seteamos ángulo de rotación en el eje X
patas[0].setAnguloX(0);
patas[1].setAnguloX(0);
patas[2].setAnguloX(0);
patas[3].setAnguloX(0);
patas[4].setAnguloX(0);
patas[5].setAnguloX(0);




//Seteo los límites superior e inferior Y, que son los que salen de girar en el eje Y

/*Spata0.setLimitesHorizontal(315,315 +22.5 -margen);
Spata1.setLimitesHorizontal(225,225 -22.5 + margen);
Spata2.setLimitesHorizontal(0 -22.5 +margen,22.5 - margen);
Spata3.setLimitesHorizontal(180 +22.5 -margen,180 - 22.5 + margen);
Spata4.setLimitesHorizontal(22.5 +margen,45);
Spata5.setLimitesHorizontal(135 +22.5 -margen,135);*/

//Lo mismo pero con un grado más en los ángulos extremos
patas[0].setLimitesHorizontal(316,316 +23 -margen);
patas[1].setLimitesHorizontal(226,226 -23 + margen);
patas[2].setLimitesHorizontal(0 -23 +margen,23 - margen);
patas[3].setLimitesHorizontal(180 +23 -margen,180 - 23 + margen);
patas[4].setLimitesHorizontal(23 +margen,46);
patas[5].setLimitesHorizontal(136 +23 -margen,136);


//Seteo la diferencia entre los límites que nos servirá más adelante en el movimiento

patas[0].setDiferenciaLimites(abs(patas[0].getLimiteSuperiorY() - patas[0].getLimiteInferiorY()));
patas[1].setDiferenciaLimites(abs(patas[1].getLimiteSuperiorY() - patas[1].getLimiteInferiorY()));
patas[2].setDiferenciaLimites(abs(patas[2].getLimiteSuperiorY() - patas[2].getLimiteInferiorY()));
patas[3].setDiferenciaLimites(abs(patas[3].getLimiteSuperiorY() - patas[3].getLimiteInferiorY()));
patas[4].setDiferenciaLimites(abs(patas[4].getLimiteSuperiorY() - patas[4].getLimiteInferiorY()));
patas[5].setDiferenciaLimites(abs(patas[5].getLimiteSuperiorY() - patas[5].getLimiteInferiorY()));

//Seteo límites visitados iniciales para cada pata
/*
Spata0.setVisitadosHorizontal(true,false);
Spata1.setVisitadosHorizontal(false,true);
Spata2.setVisitadosHorizontal(false,true);
Spata3.setVisitadosHorizontal(true,false);
Spata4.setVisitadosHorizontal(true,false);
Spata5.setVisitadosHorizontal(false,true);*/

patas[0].setVisitadosHorizontal(true,false);
patas[1].setVisitadosHorizontal(false,true);
patas[2].setVisitadosHorizontal(false,true);
patas[3].setVisitadosHorizontal(true,false);
patas[4].setVisitadosHorizontal(true,false);
patas[5].setVisitadosHorizontal(false,true);

//Al inicio acaba de visitar los límites inferiores. Está parada con todas las patas en el suelo
patas[0].setVisitadosVertical(false,true);
patas[1].setVisitadosVertical(false,true);
patas[2].setVisitadosVertical(false,true);
patas[3].setVisitadosVertical(false,true);
patas[4].setVisitadosVertical(false,true);
patas[5].setVisitadosVertical(false,true);




}

void _spider::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

//Les pinto líneas por encima para darle un toque más interersante. Así ahora se vé qué parte se selecciona

if(modo == SOLID || modo == SELECCION){

Scentro.draw(EDGES,0.1,0.1,0.1,0.1,0.1,0.1,grosor);
Strasero.draw(EDGES,0.1,0.1,0.1,0.1,0.1,0.1,grosor);
Scabeza.draw(EDGES,0.1,0.1,0.1,0.1,0.1,0.1,grosor);
Saguijon.draw(EDGES,0.1,0.1,0.1,0.1,0.1,0.1,grosor);
Spinzas.draw(EDGES,0.1,0.1,0.1,0.1,0.1,0.1,grosor);

for(int i=0; i<patas.size();i++){
  patas[i].draw(EDGES,0.1,0.1,0.1,0.1,0.1,0.1,grosor);
}

}

Scentro.draw(modo,Scentro.r1, Scentro.g1, Scentro.b1, Scentro.r2, Scentro.g2, Scentro.b2,grosor);
Strasero.draw(modo,Strasero.r1, Strasero.g1, Strasero.b1, Strasero.r2, Strasero.g2, Strasero.b2,grosor);
Scabeza.draw(modo,Scabeza.r1, Scabeza.g1, Scabeza.b1, Scabeza.r2, Scabeza.g2, Scabeza.b2,grosor);
Saguijon.draw(modo,Saguijon.r1, Saguijon.g1, Saguijon.b1, Saguijon.r2, Saguijon.g2, Saguijon.b2,grosor);
Spinzas.draw(modo,Spinzas.r1, Spinzas.g1, Spinzas.b1, Spinzas.r2, Spinzas.g2, Spinzas.b2,grosor);
for(int i=0; i<patas.size();i++){
  //patas[i].draw(EDGES,0.1,0.1,0.1,0.1,0.1,0.1,grosor);
  patas[i].draw(modo,patas[i].r1, patas[i].g1, patas[i].b1, patas[i].r2, patas[i].g2, patas[i].b2,grosor);
}

}

void _spider::draw_seleccion(float r, float g, float b,int inc){

Scentro.draw_seleccion(r,g,b); //modos[0]
inc+=10;
Strasero.draw_seleccion(r+inc,g+inc,b+inc);//modos[1]
inc+=10;
Scabeza.draw_seleccion(r+inc,g+inc,b+inc);//modos[2]
inc+=10;
Saguijon.draw_seleccion(r+inc,g+inc,b+inc);//modos[3]
inc+=10;
Spinzas.draw_seleccion(r+inc,g+inc,b+inc);//modos[4] y modos[5]
inc+=20;
for(int i=0; i<patas.size();i++){
  patas[i].draw_seleccion(r+inc,g+inc,b+inc); //modos[6,7,8,9,10,11]
  inc+=10;
}

}

void _spider::draw_seleccion_triangulo(float r, float g, float b, int inc){

Scentro.draw_seleccion_triangulo(r,g,b,inc);


}