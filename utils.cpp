#include "utils.h"
#include <functional>


//Methode qui construit un triangle a partir de chaque ligne lue.
void Utils::TriangleSoup::readLine(std::istream &in){
    Triangle triangle ;
    in>>triangle;
    triangles.push_back(triangle);
}

// Methode pour lire la soupe de triangles a partir du fichier texte.
void Utils::TriangleSoup::read(){
    std::ifstream input(source);
    std::string str ;
    while(std::getline(input,str))
        if(str[0]!='#') {std::istringstream strStream(str); readLine(strStream);};
    boundingBox(min,max);
}

// les predicats binaires utilises pour recuperer le min et le max.
auto min = [](float a,float b) -> bool {return b<a;};
auto max = [](float a,float b) -> bool {return b>a;};
auto C = c<float,std::function<bool(float,float)>>;

// Methode pour recuperer le minimum de chaque composante de deux vecteurs.
Utils::Vecteur Utils::Vecteur::inf(const Vecteur &other) const{
    return Utils::Vecteur(C(xyz[0],other[0],min),
                          C(xyz[1],other[1],min),
                          C(xyz[2],other[2],min));
}

// Methode pour recuperer le maximum de chaque composante de deux vecteurs.
Utils::Vecteur Utils::Vecteur::sup(const Vecteur &other) const{
    return Utils::Vecteur(C(xyz[0],other[0],max),
                          C(xyz[1],other[1],max),
                          C(xyz[2],other[2],max));
}

// Methode pour calculer le produit vectoriel.
Utils::Vecteur Utils::Vecteur::cross(const Vecteur &vec){
    return (     Vecteur( (xyz[1] * vec[2]) - (xyz[2] * vec[1]),
                          (xyz[2] * vec[0]) - (xyz[0] * vec[2]),
                          (xyz[0] * vec[1]) - (xyz[1] * vec[0])));
}

//Methode pour calculer le vecteur normal sur le plan de notre triangle.
Utils::Vecteur Utils::Triangle::normal(){
    Utils::Vecteur v1 = ((*this)[1]-(*this)[0]) , v2 = ((*this)[2]-(*this)[1] );
    return v1.cross(v2).normal();
}

//Methode pour ecrire la soupe de triangles dans un fichier.
void Utils::TriangleSoup::write(std::string path){
    std::ofstream output(path);
    for(auto t : triangles ) output<<t<<std::endl;
}

// Methode pour calculer la boite englobante de l'objet genere par l'emplacement de notre soupe de triangles dans l'espace.
void Utils::TriangleSoup::boundingBox( Vecteur& low, Vecteur& up) {
    low = up = triangles[0][0];
    for(auto it = ++triangles.begin();it!=triangles.end();it++){
        for (int i = 0; i < 3; ++i) {
            low = (*it)[i].inf(low);
            up = (*it)[i].sup(up);
        }
    }
}
