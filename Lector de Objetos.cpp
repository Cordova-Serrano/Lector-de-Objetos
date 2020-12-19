/*
   -> CORDOVA SERRANO EDUARDO JAVIER
   -> NUNEZ VARELA ALBERTO SALVADOR
   -> 09/Octubre/2020
   -> Avance1 - LectorOBJ
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/freeglut.h> 
using namespace std;

//////////Clase V e r t e x ////////////
class Vertex
{
    private:
        float x;
        float y;
        float z;
    public:
        Vertex();
        //Setters
        void setX(float);//Establece el valor de x del vertice
        void setY(float);//Establece el valor de y del vertice
        void setZ(float);//Establece el valor de z del vertice
        //Getters
        float getX();//Regresa el valor de x
        float getY();//Regresa el valor de y
        float getZ();//Regresa el valor de z
};
//Constructor
Vertex::Vertex()
{
}
//Entrega el valor de 'x' del vertice
float Vertex::getX()
{
	return x;
}
//Entrega el valor de 'y' del vertice
float Vertex::getY()
{
	return y;
}
//Entrega el valor de 'z' del vertice
float Vertex::getZ()
{
    return z;
}
//Modifica el valor de x del vertice
void Vertex::setX(float x)
{
	this->x = x;
}
//Modifica el valor de x del vertice
void Vertex::setY(float y)
{
    this->y = y;
}
//Modifica el valor de x del vertice
void Vertex::setZ(float z)
{
    this->z = z;
}
////////////////////////////////////

//////////Clase F a c e ////////////
class Face
{
    public:
        vector<int> refs;//Vector que guarda las referencias de vertices para la cara
    public:
        Face();//Constructor
        void addNexVertex(int);//Metodo para agregar un nuevo vertice
};
Face::Face()
{
  
}
void Face::addNexVertex(int i)//Metodo para agregar vertices
{
    refs.push_back(i);//ingresa el indice de un vertice en un vector
}
////////////////////////////////////

//////////Clase O b j ////////////
class Obj
{
    private:
        string name;//Noombre del objeto
    public:
        Obj(string); //El constructor recibe el nombre del archivo a leer
        vector<Vertex> vertices;//Vector que almacenara los vertices
        vector<Face> faces;//Vector que almacenara las caras

        void newVertex(Vertex);//Metodo para agregar nuevos vertices al vector de vertices
        void newFace(Face);//Metodo para agregar nuevas caras al vector de caras

        void addName(string Name);//Metodo para agregar nombre
        string getName();
        //A R C H I V O S 
		string nameFile;
        void read(); //Funcion para leer el archivo obj
        void print(); //Funcion para imprimir los valores del obj
};
//Constructor
Obj::Obj(string name)
{
	nameFile = name;
}
//Añade una nueva cara al vector de caras
void Obj::newFace(Face f)//agrega una cara
{
    faces.push_back(f);
}
//Añade un nuevo vertice al vector de vertices
void Obj::newVertex(Vertex v)//agrega un vertice
{
    vertices.push_back(v);
}
//Añade un nombre al objeto
void Obj::addName(string Name)//Agrega el nombre el objeto
{
    name = Name;
}
//Regresa el nombre del objeto
string Obj::getName()
{
    return name;
}
//Lee los valores del archivo .obj
void Obj::read()
{
	ifstream myfile(nameFile.c_str()); //Variable para manipular el archivo 
	string lector;
	Vertex v;

	char* read = (char*)malloc(sizeof(char) * 1000); // reservar memoria dinamica para leer una linea del archivo
	char* next = NULL;
	char* temp;

	if (myfile.is_open())
	{
		while (myfile.getline(read, 1000)) // en cada ciclo se actualiza la linea a leer en read
		{
			string line(read); // lo que tenga read se asigna en line
			lector = line.substr(0, 2); // la linea sustrae los primeros dos caracteres y se iguala en lector
			if (lector == "o ")
			{
				addName(line.substr(2)); //quitamos los primeros 2 caracteres y mandamos lo restante a name
			}
			else if (lector == "v ")
			{

				temp = strtok_s(read, " ", &next);
				temp = strtok_s(NULL, " ", &next);
				v.setX(stod(temp)); //stod: sirve para convertir char a int
				temp = strtok_s(NULL, " ", &next);
				v.setY(stod(temp));
				temp = strtok_s(NULL, " ", &next);
				v.setZ(stod(temp));
				newVertex(v);//se agrega un nuevo vertice al modelo

			}
			else if (lector == "f ")
			{
				int vEntero;
				temp = strtok_s(read, " ", &next);// se detiene hasta que read sea igual a espacio
				bool i = true;
				Face f;//Se crea una variable de tipo face para manipular las caras
				while (temp != NULL)//Entra en ciclo hasta llegar al fin de la linea que se esta leyendo
				{
					if (!i)
					{
						f.addNexVertex(atoi(temp) - 1);//Se agrega un vertice a la cara
					}
					else
						i = false;
					temp = strtok_s(NULL, " ", &next);// se detiene hasta que read sea igual a espacio
				}
				newFace(f);//se agrega la cara a model
			}
		}
		myfile.close();//cierra el archivo
	}
	else
	{
		cout << "Error: No se pudo abrir el archivo obj\n"; //Si no se puede abrir el archivo
		exit(1);
	}
}
//Imprime los valores del archivo .ojb
void Obj::print()
{
	int i; //contadores

	cout <<getName() + "\n";
	for (i = 0; i < vertices.size(); i++)
	{
		cout << "v " << vertices[i].getX() << " " << vertices[i].getY() << " " << vertices[i].getZ();
		cout << "\n";
	}
	i = 0;
	for (Face face : faces)
	{
		cout << "f ";
		for (int i = 0; i < face.refs.size(); i++)
		{
			cout << face.refs[i] << " ";
		}
		cout << "\n";
	}
}
////////////////////////////////////
Obj obj("tanque.obj");
//////////D I S P L A Y ////////////
void Draw()
{
	int f, v;

	glClear(GL_COLOR_BUFFER_BIT);

	gluLookAt(1.5, 0.0, 3.0   , 0.0, 1.0, 0.0    , 0.0, 1.0, 0.0);
	//Color de relleno
	// 0 = 0
	// 1 = 255
	//        R     G    B 
	glColor3f(0.4, 0.4, 0.2); //Color verde olivo 

	//C A R A S 
	for (f = 0; f < obj.faces.size(); f++) 
	{

		if (obj.faces[f].refs.size() == 4)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glBegin(GL_TRIANGLES);
		}

		for (v = 0; v < obj.faces[f].refs.size(); v++)
		{
			glVertex3f(obj.vertices[obj.faces[f].refs[v]].getX(),
				obj.vertices[obj.faces[f].refs[v]].getY(),
				obj.vertices[obj.faces[f].refs[v]].getZ());
		}
		glEnd();
	}

	//V E R T I C E S
	//Color de las lineas
	glColor3f(0.0, 0.0, 0.0);// Color negro 
	for (f = 0; f < obj.faces.size(); f++) 
	{
		glBegin(GL_LINE_STRIP);//Se dibujarán Líneas

		for (v = 0; v < obj.faces[f].refs.size(); v++)
		{
			glVertex3f(obj.vertices[obj.faces[f].refs[v]].getX(),
				obj.vertices[obj.faces[f].refs[v]].getY(),
				obj.vertices[obj.faces[f].refs[v]].getZ());
		}
		glEnd();
	}
	glutSwapBuffers();
	glFlush();
}
int main(int argc, char** argv)
{
	int width = 640;//variable de ancho de la ventana
	int height = 480;//variable de altura de la ventana
	//Instancia
	obj.read();
	obj.print();
	//Display
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);

	glutCreateWindow("Modelo 3D");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);

	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);


	glutDisplayFunc(Draw); 
	glutMainLoop();

	return 0;
}
