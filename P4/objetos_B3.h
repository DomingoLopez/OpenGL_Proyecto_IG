//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
#include "CImg.h"
using namespace cimg_library;
using namespace std;

const float AXIS_SIZE=5000;
/*AÑADIDOS AL TIPO DE MODO PARA LA ILUMINACIÓN: SOLID_ILUMINATED_FLAT, SOLID_ILUMINATED_GOURAUD*/
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILUMINATED_FLAT,SOLID_ILUMINATED_GOURAUD} _modo;

//Enumerado para cambiar entre materiales
typedef enum{MATERIAL1,MATERIAL2,MATERIAL3} _tipoMaterial;




//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
/*AÑADIDO AL MÉTODO DRAW, float brillo (De cara a la iluminación). Aunque mejor ponerlo en el constructor de cada objeto*/
void 	draw(_modo modo, _tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
/*AÑADIDOS PARA LA ILUMINACIÓN*/
void draw_iluminacion_plana(_tipoMaterial tipoMaterial);
void draw_iluminacion_suave(_tipoMaterial tipoMaterial);

void calcular_normales_caras();
void calcular_normales_vertices();

/*AÑADIDO PARA LA TEXTURA*/




/*Más añadidos para la ILUMINACIÓN*/
bool b_normales_caras;
bool b_normales_vertices;

vector<_vertex3f> normales_caras; //Vector de vectores normales a las caras
vector<_vertex3f> normales_vertices; //vector de vectores normales a los vértices (Entendiendo como vector r->(i,j,k))

_vertex4f ambiente_difusa; //coeficientes ambiente y difuso
_vertex4f especular; //coeficiente especular
float brillo; //exponente del brillo

_tipoMaterial material = MATERIAL1;
void setMaterial(_tipoMaterial material);

vector<_vertex3i> caras;
};




//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:
  
	_cubo(float tam=0.5);

};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

vector<_vertex3f> perfil; 
int num;
};


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
//OJO, EN CADA UNA DE LAS CLASES HAY QUE PONER UN METODO DRAW, OSEA, PARA CADA UNO DE LOS OBJETOS CREADOS
float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D//ESTA CLASE ES EL OBJETO FINAL, SOBRE EL QUE UNIREMOS TODAS LAS PIEZAS
{
public:
       _tanque();
void 	draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

//ESTOS SON LOS GRADOS DE LIBERTAD

float giro_tubo;
float giro_torreta;

//RESTRICCIONES SOBRE LOS GRADOS DE LIBERTAD. OJO.
float giro_tubo_min;
float giro_tubo_max;

protected: //AQUÍ ESTÁN TODAS LAS PIEZAS NECESARIAS
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};


/*
A PARTIR DE AQUÍ SE ESPECIFICAN LAS CLASES NECESARIAS PARA CREAR
EL OBJETO ARTICULADO HORMIGA

*/

class _cono: public _rotacion
{
public: 
	_cono(float altura=1, float radio=0.05);

};


class _cilindro: public _rotacion
{
public: 
	_cilindro(float altura=0.4, float radio=0.1);

};


class _esfera: public _rotacion
{
public: 
	_esfera(float radio=0.5);
       float radio = 0.5;
       void calcular_normales_vertices_exactos();

};

//Clase trapecio para la cabeza de la araña
class _trapecio: public _triangulos3D{

       private:
              float altura;
              float baseInferior;
              float baseSuperior;

       public:
              _trapecio(float baseInferior=1.0, float baseSuperior=0.3, float altura=0.5);

};


class _pinzaSpider: public _triangulos3D{

       public:
              _pinzaSpider(float radio=0.5, float altura=1.4);

       protected:
              float radio;
              float altura;

       

};



/*PARTES DE LA HORMIGA*/

class _cuerpoCentral: public _triangulos3D
{
       public:
       _cuerpoCentral();
       void draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
       
       protected:
       _esfera centro; 

};

class _cuerpoTrasero: public _triangulos3D
{
       public:
       _cuerpoTrasero();
       void draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

       protected:
       _esfera trasero;

};




class _cabezaSpider : public _triangulos3D
{

       public:
       _cabezaSpider();
       void draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

       _trapecio cabeza;
};

class _aguijonSpider : public _triangulos3D
{

       public:
       _aguijonSpider();
       void draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

       void modificaAnguloAguijon(float incremento);
       _cono aguijon;

      protected:
      float anguloActualZ;
      float limiteInferiorZ;
      float limiteSuperiorZ;
       
};


class _pinzasSpider : public _triangulos3D
{

       public:
       _pinzasSpider();

       void draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

          

       //getters


       _pinzaSpider pinzaD;
       _pinzaSpider pinzaI;


       float anguloActualPinzaD;
       float anguloActualPinzaI;

       float limiteSuperiorPinzaD;
       float limiteInferiorPinzaD;

       float limiteSuperiorPinzaI;
       float limiteInferiorPinzaI;

       

};


class _pataSpider : public _triangulos3D
{

       protected: 
         //LIMITES DE LOS GRADOS DE LIBERTAD. //Cada pata va a tener sus propios límites de ángulos
         //Para evitar chocarse entre ellas
         int idPata;
         float anguloActualY; //Los sufijos X e Y en todos los atributos indican el eje de rotación
         float anguloActualX;
         float limiteHorizontal1;//Al rotar el eje Y
         float limiteHorizontal2;
         float limiteVertical1;//Al rotar el eje X
         float limiteVertical2;
         float diferenciaLimites;
       

         bool superiorVisitadoX;//Esto es para tener una referencia de si vamos hacia adelante o hacia atrás
         bool inferiorVisitadoX;
          
         bool superiorVisitadoY; //Esto es para tener una referencia de si vamos hacia arriaba o abajo
         bool inferiorVisitadoY;


       public:
       _pataSpider();
       _pataSpider(int idPata);
       void draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
      
       //setters
       void setID(int id);

       void setLimitesHorizontal(float limiteHorizontal1, float limiteHorizontal2);
       void setLimitesVertical(float limiteVertical1, float limiteVertical2);

       void setVisitadosHorizontal(bool superiorVisitadoY, bool inferiorVisitadoY);
       void setVisitadosVertical(bool superiorVisitadoX, bool inferiorVisitadoX);

       void setAnguloX(float angulo);
       void setAnguloY(float angulo);

       void modificaAnguloX(float incremento);
       void modificaAnguloY(float incremento);

       void setDiferenciaLimites(float diferencia);


       //getters
       int getID();
       float getAnguloActualY();
       float getAnguloActualX();

       bool getSuperiorVisitadoY();
       bool getInferiorVisitadoY();

       bool getSuperiorVisitadoX();
       bool getInferiorVisitadoX();

       float getLimiteSuperiorY();
       float getLimiteInferiorY();

       float getDiferenciaLimites();


       _cono salienteCuerpo;
       _esfera articulacion;
       _cilindro intermedia;
       _cono pie;

       



};




//CLASE DEL OBJETO FINAL
//AQUÍ AGRUPAMOS TODO
class _spider : public _triangulos3D
{

       public:
       _spider();

       void draw(_modo modo,_tipoMaterial material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
       
       //animacion de las patas
       void animacion();

       //getters
       _pataSpider getPataIndice(int indice);

       //modificadores para las patas
       void modificaAnguloPataY(int indicePata, float incremento);
       void modificaVisitadosH(int indicePata, bool visitadoSuperior, bool visitadoInferior);
       
       void modificaAnguloPataX(int indicePata, float incremento);
       void modificaVisitadosV(int indicePata, bool visitadoSuperior, bool visitadoInferior);

       //Modificadores para el aguijón y las pinzas
       void modificaAnguloAguijon(float incremento);
       void modificaAnguloPinzas(float incremento);

       protected:
       _pinzasSpider Spinzas;
       _aguijonSpider Saguijon;
       _cuerpoCentral Scentro;
       _cuerpoTrasero Strasero; 
       _cabezaSpider Scabeza;
       vector<_pataSpider> patas;//Vector de patas
       
       //Para simplificar, los límites y ángulos actuales de las patas se han definido en cada pata
       
 


};

