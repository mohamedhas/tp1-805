/// \file Viewer.h
#include <vector>
#include <QGLViewer/qglviewer.h>
#include "utils.h"
#include <fstream>
#include <iostream>
#include <istream>
#include <functional>

class Viewer : public QGLViewer
{
 public:
    float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
    float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
    float colorNull      [4] = { 0.0, 0.0, 0.0, 1.0 };
  //Viewer() : QGLViewer() {}
    const Utils::TriangleSoup* ptrSoup;
    Viewer( const Utils::TriangleSoup* aSoup = 0 ) : QGLViewer(), ptrSoup( aSoup ) {}
  //Methode qui recupere la partie decimal d'un float.
    float d(float x){return x - round(x);}


    // methode qui trace un seul triangle.
    void drawTriangle(Utils::Triangle triangle){
        // si vous voulez tracer avec des couleurs "question 3.5 " decommentez les deux lignes suivantes et commentez celle d'apres.
        //float color[4] = {d(triangle[0][0]),d(triangle[0][1]),d(triangle[0][2]),1.0};
        //glColor4fv(color);
        glColor4fv(colorBronzeDiff);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNull);
        glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
        glMaterialf(GL_FRONT, GL_SHININESS, 20.0f );
        Utils::Vecteur n = triangle.normal();
        glNormal3f( n[ 0 ], n[ 1 ], n[ 2   ] );
        for (int i = 0; i < 3; ++i) {
            glVertex3f(triangle[i][0],triangle[i][1],triangle[i][2]);
        }
  }
    // methode qui trace tous les triangles de notre soupe.
    void drawImage(){
        for(auto it = ptrSoup->triangles.begin();it!=ptrSoup->triangles.end();it++)drawTriangle(*it);
    }

 protected :
  /// Called at each draw of the window
  virtual void draw();
  /// Called before the first draw
  virtual void init();
  /// Called when pressing help.
  virtual QString helpString() const;
};

