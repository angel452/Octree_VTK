#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkUnsignedCharArray.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkNamedColors.h>

#include <sstream>

#include "Octree.h"
#include <vector>

using namespace std;

// The ordering of the corner points on each face.
std::array<std::array<vtkIdType, 4>, 6> ordering = {{{{0, 3, 2, 1}},
                                                      {{4, 5, 6, 7}},
                                                      {{0, 1, 5, 4}},
                                                      {{1, 2, 6, 5}},
                                                      {{2, 3, 7, 6}},
                                                      {{3, 0, 4, 7}}}};

vtkNew<vtkActor> drawCube( double x, double y, double z, double h){
	std::array<std::array<double, 3>, 8> pts;
	pts[0] = {x,y,z};       //0,0,0
	pts[1] = {x+h, y, z };  //1,0,0
	pts[2] = {x+h, y+h, z}; //1,1,0
	pts[3] = {x, y+h, z};   //0,1,0
  /*
	pts[4] = {x, y, 0};   //0,0,1
	pts[5] = {x+h,y,0};   //1,0,1
	pts[6] = {x+h,y+h,0}; //1,1,1
	pts[7] = {x,y+h,0};   //0,1,1
  */
	pts[4] = {x, y, z+h};   //0,0,1
	pts[5] = {x+h,y,z+h};   //1,0,1
	pts[6] = {x+h,y+h,z+h}; //1,1,1
	pts[7] = {x,y+h,z+h};   //0,1,1
  
	vtkNew<vtkPolyData> cube; // polyData
	vtkNew<vtkPoints> points; // points
	vtkNew<vtkCellArray> polys;
	vtkNew<vtkFloatArray> scalars;

	for (auto i = 0ul; i < pts.size(); ++i) {
		points->InsertPoint(i, pts[i].data());
		scalars->InsertTuple1(i, i);
	}
	for (auto&& i : ordering) {
		polys->InsertNextCell(vtkIdType(i.size()), i.data());
	}

	// We now assign the pieces to the vtkPolyData.
	cube->SetPoints(points);
	cube->SetPolys(polys);
	cube->GetPointData()->SetScalars(scalars);

	// Now we'll look at it.
	vtkNew<vtkPolyDataMapper> cubeMapper;
	cubeMapper->SetInputData(cube);
	cubeMapper->SetScalarRange(cube->GetScalarRange());
	vtkNew<vtkActor> cubeActor;
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetRepresentationToWireframe();

	return cubeActor;
}

int main(int argc, char* argv[])
{  
  // VARIABLES OCTREE
  /*
  int granularidad = 1000;
  
  double x_min = 5.21805; 
  double y_min = -5.21805;
  double z_min = 0.0001;
  double longitudLado = 10.4361;
*/

  int granularidad = 3;
  double x_min = 0; 
  double y_min = 0;
  double z_min = 0;
  double longitudLado = 250;

  //vector< vtkNew<vtkActor> > actoresCube;

  OcTree arbol(x_min, y_min, z_min, longitudLado, granularidad);

  // ######################################################

  vtkNew<vtkNamedColors> namedColors;
  vtkNew<vtkPoints> pointsPuntos;

  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWin;
  renderWin->AddRenderer(renderer);
  renderWin->SetWindowName("Test1");
  
  // ################### TXT ######################
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " Filename(.txt) e.g. TeapotPoints.txt"
              << std::endl;
    return EXIT_FAILURE;
  }
  // Get all data from the file
  std::string filename = argv[1];
  std::ifstream filestream(filename.c_str());

  std::string line;
  // ##############################################
  // Para leer la dama octal

  while (std::getline(filestream, line))
  {
    double x, y, z;
    std::stringstream linestream;
    linestream << line;
    linestream >> x >> y >> z;

    pointsPuntos->InsertNextPoint(x, y, z);
    arbol.insert(x,y,z,arbol);
  }

  cout << "Final de insertar" << endl;
  //arbol.getMinimunSizes(arbol, 0);

  for(int i = 0; i < arbol.allSizes.size(); i++){

    double xMin = arbol.allSizes[i][0];
    double yMin = arbol.allSizes[i][1];
    double zMin = arbol.allSizes[i][2];
    double lenMin = arbol.allSizes[i][3];

    vtkNew<vtkActor> auxActor = drawCube(xMin, yMin, zMin, lenMin);
    renderer->AddActor(auxActor); // cubos

    cout << "x: " << xMin << " y: " << yMin << " z: " << zMin << " len: " << lenMin << endl;
  }

  filestream.close();

  vtkNew<vtkPolyData> polyData;
  polyData->SetPoints(pointsPuntos);

  vtkNew<vtkVertexGlyphFilter> glyphFilter;
  glyphFilter->SetInputData(polyData);
  glyphFilter->Update();

  // Visualization
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(5);
  actor->GetProperty()->SetColor(namedColors->GetColor3d("MidnightBlue").GetData());

  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renderWin);

  renderer->AddActor(actor); // puntos

  renderer->SetBackground(namedColors->GetColor3d("Gainsboro").GetData());
  
  renderWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}