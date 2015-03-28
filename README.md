# ObjModelLoader

Loads model from Wavefront Obj file (*.obj). Using triangles and normals
as static object. No texture mapping.

Warning: OBJ files must be triangulated. Non triangulated objects wont
		 work! You can use Blender to triangulate.

Exporting as Obj File on Blender:
		(a) Open Blender program. Create your model.
		(b) File -> Export -> Wavefront (.obj)
		(c) Now at the left side panel on "Export Obj" section check on
			"Triangulate Faces".
		(d) Click on "Export OBJ" button. It produce two files. For
			example: cube.obj and cube.mtl. We will only need the *.obj
			file only.

Sample Usage:

		ObjModelLoader *mesh = NULL;
		mesh = new ObjModelLoader("C:\\data\\filename.obj");

		mesh->Draw();
