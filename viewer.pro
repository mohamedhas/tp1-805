# Ceci est un fichier de configuration pour une application Qt
# Il faut peut-etre legerement l adapter pour votre ordinateur.

# nom de votre executable
TARGET  = viewer
# config de l executable
CONFIG += c++11
CONFIG *= qt opengl release

# config de Qt
QT     *= opengl xml

# Noms de vos fichiers entete
HEADERS = Viewer.h \
    utils.h \
    trianglesoupzipper.h
# Noms de vos fichiers source
SOURCES = Viewer.cpp main.cpp \
    utils.cpp

###########################################################
# Commentez/decommentez selon votre config/systeme
# (Une config windows est possible)
###########################################################

# Exemple de configuration Linux de Qt et libQGLViewer
INCLUDEPATH *= /home/moh/tmp/libQGLViewer-2.6.4
LIBS *= -L/home/moh/tmp/libQGLViewer-2.6.4/QGLViewer -lQGLViewer-qt5

# Exemple de configuration MacOSX avec macports
##INCLUDEPATH *= /opt/local/include
##LIBS *= -L/opt/local/lib -lQGLViewer 

# Exemple de configuration MacOSX avec frameworks
##  INCLUDEPATH *= /Users/login/libQGLViewer-2.6.4
##  LIBS *= -F/Users/login/Library/Frameworks -framework QGLViewer
