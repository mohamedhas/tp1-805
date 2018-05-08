#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <sstream>
#include <functional>
#include <math.h>

//fonction generique qui compare deux objets de type quelconque "T" et retourner le premier s'ils ne satisfaissent pas le predicat binaire "f" et le dieuxieme sinon.
template <class T,typename Func> const T& c (const T& a, const T& b,Func f) {
  return !(f(a,b))?a:b;
}


class Utils
{
public:
    Utils();
// Structure pour definir les vecteurs, avec les vecteurs on peut reperer les sommets des triangles ce qui permet de les placer dans l'espace.
    struct Vecteur {
      float xyz[ 3 ]; // les composantesns
      // Dans le constructeur par defaut on met tous les trois composantes de notre vecteur a zero pour des soucis de calcul.
      Vecteur(){xyz[0]=0.0;xyz[1]=0.0;xyz[2]=0.0;}
      Vecteur( float x, float y, float z ) {xyz[0]=x;xyz[1]=y;xyz[2]=z;}
      float  operator[]( int i ) const { return xyz[i] ; }
      float& operator[]( int i ){return xyz[i];}           // accesseur en ecriture
      Vecteur inf( const Vecteur& other ) const;
      Vecteur sup( const Vecteur& other ) const;
      // On surcharge les operateurs suivants : l'affectation, la soustraction et le plus egal.
      Vecteur& operator=(const Vecteur& v){for (int i = 0; i < 3; ++i)xyz[i]=v.xyz[i];return *this ;}
      Vecteur operator-(const Vecteur& v){return  Vecteur(xyz[0]-v[0],xyz[1]-v[1],xyz[2]-v[2]);}
      Vecteur& operator+=(const Vecteur& v){xyz[0]+=v[0];xyz[1]+=v[1];xyz[2]+=v[2];return *this;}

      // Methode pour calculer le produit vectoriel.
      Vecteur cross(const Vecteur& vec);
      // Methode pour calculer la norme de notre vecteur
      float norme(){float s(0);for (int i = 0; i < 3; ++i) s+= (xyz[i]*xyz[i]); return sqrt(s) ;}
      // Methode pour normaliser notre vecteur en divisant chaque composante par la norme.
      Vecteur normal(){float norm=this->norme();return Vecteur(xyz[0]/norm,xyz[1]/norm,xyz[2]/norm);}
    };

  //Structure pour definir les triangles ( un triangle a 3 sommets donc 3 vecteurs).
    struct Triangle {
        Vecteur tabVecteurs [3] ;
        Triangle(){}
        Vecteur  operator[]( int i ) const { return tabVecteurs[i] ; }
        Vecteur& operator[]( int i ){return tabVecteurs[i];}
        // le vecteur normal sur le plan de notre triangle
        Vecteur normal();
    };
    /*
    * Structure qui contient une soupe de triangles et les methodes necessaires pour les recuperer d'un fichier d'entree,
     * les ecrire dans un fichier de sortie ainsi que le calcul de la boite englobante de l'objet genere par l'emplacement
     * de ces triangles dans l'espace.
    */
    struct TriangleSoup {
      Vecteur min,max ;
      std::string source ;
      std::vector<Triangle> triangles; // les triangles
      TriangleSoup() {}
      TriangleSoup(std::string src) : source(src) {}
      void read();
      void write(std::string path);
      void readLine( std::istream& in );      
      void boundingBox( Vecteur& low, Vecteur& up);
    };


};

//Surcharge des opératuers, des flux d'entrée et de sortie, fournie par le prof.
 inline std::ostream& operator<<( std::ostream& out,  Utils::Vecteur v )
{ out << v[ 0 ] << " " << v[ 1 ] << " " << v[ 2 ]; return out ; }
 inline std::istream& operator>>(  std::istream& in, Utils::Vecteur& v )
{ in >> v[ 0 ] >> v[ 1 ] >> v[ 2 ]; return in; }
 inline std::ostream& operator<<(  std::ostream& out, Utils::Triangle v )
{ out << v[ 0 ] << " " << v[ 1 ] << " " << v[ 2 ]; return out ; }
 inline std::istream& operator>>(  std::istream& in , Utils::Triangle& v )
{ in >> v[ 0 ] >> v[ 1 ] >> v[ 2 ]; return in; }
#endif // UTILS_H
