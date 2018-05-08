#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "utils.h"
#include "trianglesoupzipper.h"



using namespace std;
int main(int argc, char** argv)
{
  // Read command lines arguments.

  // Instantiate the viewer.
  //freopen( "error.txt", "w", stderr );
  if(argc==2){
      QApplication application(argc,argv);
      Utils::TriangleSoup soup( argv[1] ) ;
      soup.read();
      cout<< "nombre de triangles en entree : " << soup.triangles.size()<< endl ;
      Viewer viewer(&soup);
      // Give a name
      viewer.setWindowTitle("Viewer triangle soup");
      // Make the viewer window visible on screen.
      viewer.show();
      // Run main loop.
      application.exec();
      return 0;
  }

  else if(argc==6) {
      Utils::TriangleSoup soup( argv[1] ) ;
      Utils::TriangleSoup soupSortie;
      //On lit la soupe d'entree puis on recupere les entiers pour la subdivison, ensuite on cree un objet "TriangleSousZipper" qui va appele la methode "smartZip()"
      soup.read();
      Index size(std::stoi(argv[3]),std::stoi(argv[4]),std::stoi(argv[5]));
      TriangleSoupZipper zipper(soup,soupSortie,size);
      zipper.smartZip();
      //Question 4.3 sans remplacement des sommets
      //zipper.zip();
      soupSortie.write(argv[2]);
      cout<< "nombre de triangles en entree : " << soup.triangles.size()<< endl ;
      cout<< "nombre de triangles en sortie : " << soupSortie.triangles.size()<< endl ;
      cout<< "taux de compression : " << soup.triangles.size() / soupSortie.triangles.size() << " fois" <<endl ;
      return 0;
  }
  else {
      cerr<< "nombre d'arguments invalide !!!" <<endl;
      exit(0);
  }
  }
