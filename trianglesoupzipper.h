#ifndef TRIANGLESOUPZIPPER_H
#define TRIANGLESOUPZIPPER_H
#include "utils.h"
#include <map>



//la structure Index a ete donnee dans le TP, on a ajoute l'operateur binaire "=="
//Index sert a stocker et tester sur les 3 entiers qui numerotent chaque cellule.
struct Index {
  int idx[ 3 ];
  Index() {}
  Index( int i0, int i1, int i2 )
  {
    idx[ 0 ] = i0;
    idx[ 1 ] = i1;
    idx[ 2 ] = i2;
  }
  Index( int indices[] )
  {
    idx[ 0 ] = indices[ 0 ];
    idx[ 1 ] = indices[ 1 ];
    idx[ 2 ] = indices[ 2 ];
  }
  int  operator[]( int i ) const { return idx[ i ]; }
  int& operator[]( int i )       { return idx[ i ]; }
  bool operator<( const Index& other ) const
  {
    return ( idx[ 0 ] < other.idx[ 0 ] )
      || ( ( idx[ 0 ] == other.idx[ 0 ] )
           && ( ( idx[ 1 ] < other.idx[ 1 ] )
                || ( ( idx[ 1 ] == other.idx[ 1 ] )
                     && ( idx[ 2 ] < other.idx[ 2 ] ) ) ) );
  }

  bool operator==(const Index& other){ return (!(*this<other)&&!(other<*this));  }
};




//La structure CellData a ete donnee dans le TP , on a definit les methodes add et barycentre.
struct CellData {
  Utils::Vecteur acc;
  int nb;
  // Crée un accumulateur vide.
  CellData(): acc(), nb(0) {}
  // Ajoute le point v à l'accumulateur.
  void add( const Utils::Vecteur& v ){ acc+=v ;nb++;}
  // Retourne le barycentre de tous les points ajoutés.
  Utils::Vecteur barycenter() const{
      return Utils::Vecteur(acc[0]/nb,acc[1]/nb,acc[2]/nb);
  }
};


//La classe dans laquelle on va faire la compression d'une soupe via les methodes zip() pour la compression centroide et smartzip() pour la compression barycentre.
class TriangleSoupZipper
{

public:
    Utils::TriangleSoup input;
    Utils::TriangleSoup& output;
    Index size ;
    float celluleSize[3];

    //Dictionnaire dans lequel index sont les cles et CellData sont les valeurs.
    std::map<Index, CellData> index2data;

    
    TriangleSoupZipper(Utils::TriangleSoup& anInput,Utils::TriangleSoup& anOuput,Index size): output(anOuput){
        input=anInput;
        this->size=size;
        calculerTailleCellule();
    }

    // Methode pour calculer la taille reelle de chaque cellule.
    void calculerTailleCellule(){
        Utils::Vecteur v = input.max - input.min ;
        for (int i = 0; i < 3; ++i) celluleSize[i]=  v[i]/size[i];
    }

    // On calcule l'index d'un vecteur c.a.d. les coordonnees de la cellule qui l'englobe.
    Index index(Utils::Vecteur& p) {
        Utils::Vecteur v = p - input.min ;
        return Index( round(v[0]/celluleSize[0]),round(v[1]/celluleSize[1]),round(v[2]/celluleSize[2]));
    }

    // On calcule le vecteur qui correspond au centre de notre cellule.
    Utils::Vecteur centroid(const Index& idx)const {
        return Utils::Vecteur(input.min[0] + idx[0]*celluleSize[0]+0.5*celluleSize[0],
                              input.min[1] + idx[1]*celluleSize[1]+0.5*celluleSize[1],
                              input.min[2] + idx[2]*celluleSize[2]+0.5*celluleSize[2]);
    }


    //On teste si deux sommets au moins d'un traingle sont englobes par la meme cellule afin de jetter les triangles qui ont cette propriete.
    bool hasSameIndex(Utils::Triangle triangle){
        return  ( (index(triangle[0])==index(triangle[1])) ||
                  (index(triangle[0])==index(triangle[2])) ||
                  (index(triangle[1])==index(triangle[2])) );
    }

    //zip() teste si elle va garder un triangle celon le test d'index "hasSameIndex()", si le triangle est garde elle va remplacer chaque sommet par le centre de la 	   cellule qui l'englobe, puis elle l'ajoute dans la soupe de sortie.
    void zip(){
        for (auto it = input.triangles.begin(); it != input.triangles.end(); ++it) {
            if(!hasSameIndex(*it)){
                Utils::Triangle& triangle =*it;
                for (int i = 0; i < 3; ++i) triangle[i] = centroid(index(triangle[i]));
                output.triangles.push_back(*it);
        }
    }
    }

    //zip2() fait le meme travail que zip() mais avec les baryCentres.
    void zip2(){
        for (auto it = input.triangles.begin(); it != input.triangles.end(); ++it) {
            if(!hasSameIndex(*it)){
                Utils::Triangle& triangle =*it;
                for (int i = 0; i < 3; ++i) triangle[i] = index2data[index(triangle[i])].barycenter();
                output.triangles.push_back(triangle);
        }
    }
    }


    //Dans cette methode on parcourt tous les sommets des triangles de la soupe d'entree et on met a jour l'accumulateur de la cellule correspendante.
    void mettreAJourMap(){
        index2data.clear();
        for (auto t : input.triangles )
            for (int i = 0; i < 3; ++i)
                index2data[index(t[i])].add(t[i]);
    }


    //On compresse la soupe en utilisant les baryCentres.
    void smartZip(){
        mettreAJourMap();
        zip2();
    }
};

#endif // TRIANGLESOUPZIPPER_H
