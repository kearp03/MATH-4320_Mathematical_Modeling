// gcc HW22tower.c -o tower -lglut -lm -lGLU -lGL
//To stop hit "control c" in the window you launched it from.
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define EDGES 9

#define XWindowSize 2500
#define YWindowSize 2500

#define DRAW 10
#define PRINT 100
#define DAMP 0.5

#define G 1.0

#define DT 0.001

#define EYE 5.0
#define FAR 50.0

#define STOP_TIME 100.0

#define FLOOR_STRENGTH 200.0
#define SHERE_RADIUS 0.2
#define DROP_HIEGHT 5.0

// Define a struct to hold the edge attributes, and name it edge_atributes
typedef struct edge_atributes{
	int to;
	int from;
	float NaturalLength;
	float CompressionStrength;
	float TensionStrength;
	float Red;
	float Green;
	float Blue;
} edge_atributes;

// Globals
float Px[N], Py[N], Pz[N];
float Vx[N], Vy[N], Vz[N];
float Fx[N], Fy[N], Fz[N];
float Mass[N];
edge_atributes Edges[EDGES];

void set_initail_conditions()
{
	int i;
	
	//Setting node masses
	for(i = 0; i < N; i++)
	{	
		Mass[i] = 1.0;
	}
	
	//Setting node velocities
	for(i = 0; i < N; i++)
	{	
		Vx[i] = 0.0;
		Vy[i] = 0.0;
		Vz[i] = 0.0;
	}
	
	//Setting connector attributes
	float compStrength = 100.0;
	float tenStrength = 50.0;

	// Edge from 0 to 1
	Edges[0].from = 0;
	Edges[0].to = 1;

	// Edge from 0 to 2
	Edges[1].from = 0;
	Edges[1].to = 2;

	// Edge from 0 to 3
	Edges[2].from = 0;
	Edges[2].to = 3;
	
	// Edge from 1 to 2
	Edges[3].from = 1;
	Edges[3].to = 2;

	// Edge from 1 to 3
	Edges[4].from = 1;
	Edges[4].to = 3;

	// Edge from 2 to 3
	Edges[5].from = 2;
	Edges[5].to = 3;

	// Edge from 0 to 4
	Edges[6].from = 0;
	Edges[6].to = 4;

	// Edge from 1 to 4
	Edges[7].from = 1;
	Edges[7].to = 4;

	// Edge from 2 to 4
	Edges[8].from = 2;
	Edges[8].to = 4;

	// Setting all edge attributes to the same values
	for(i = 0; i < EDGES; i++)
	{
		Edges[i].CompressionStrength = compStrength;
		Edges[i].TensionStrength = tenStrength;
		Edges[i].NaturalLength = 2.0;
		Edges[i].Red = 0.0;
		Edges[i].Green = 0.0;
		Edges[i].Blue = 0.0;
	}
	
	//Setting node positions
	Px[0] = 0.0;
	Py[0] = 0.0 + DROP_HIEGHT;
	Pz[0] = 1.0;
	
	Px[1] = 1.0;
	Py[1] = 0.0 + DROP_HIEGHT;
	Pz[1] = 0.0;
	
	Px[2] = -1.0;
	Py[2] = 0.0 + DROP_HIEGHT;
	Pz[2] = 0.0;
	
	Px[3] = 0.0;
	Py[3] = 1.0 + DROP_HIEGHT;
	Pz[3] = 0.0;

	Px[4] = 0.0;
	Py[4] = -1.0 + DROP_HIEGHT;
	Pz[4] = 0.0;
}

void draw_picture()
{
	int i;
	
	//Clearing the picture
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	//Drawing the nodes
	for(i = 0; i < N; i++)
	{
		if(i == 0) glColor3d(1.0,1.0,1.0); // white
		if(i == 1) glColor3d(0.0,1.0,0.0); // green
		if(i == 2) glColor3d(1.0,0.0,0.0); // red
		if(i == 3) glColor3d(1.0,0.0,1.0); // purple
		if(i == 4) glColor3d(0.0,1.0,1.0); // cyan
		glPushMatrix();
		glTranslatef(Px[i], Py[i], Pz[i]);
		glutSolidSphere(SHERE_RADIUS,20,20);
		glPopMatrix();
	}
	
	//Drawing the Connectors (red if compressed, blue is stretched)
	glLineWidth(8.0);
	for(int i = 0; i < EDGES; i++)
	{
		glColor3d(Edges[i].Red, Edges[i].Green, Edges[i].Blue);
		glBegin(GL_LINE_STRIP);
			glVertex3f(Px[Edges[i].from], Py[Edges[i].from], Pz[Edges[i].from]);   
			glVertex3f(Px[Edges[i].to], Py[Edges[i].to], Pz[Edges[i].to]); 
		glEnd();
	}
	
	//Drawing the flooor
	glLineWidth(1.0);
	glColor3d(1.0,1.0,1.0);
	int floorSections = 100;
	float floorStartX = -5.0;
	float floorStopX = 5.0;
	float dx = (floorStopX - floorStartX)/floorSections;
	float floorStartZ = -5.0;
	float floorStopZ = 5.0;
	float dz = (floorStopZ - floorStartZ)/floorSections;
	float x;
	float z;
	
	x = floorStartX;
	for(i = 0; i < floorSections; i++)
	{
		glBegin(GL_LINE_STRIP);
			glVertex3f(x, 0.0, floorStartZ);   
			glVertex3f(x, 0.0, floorStopX); 
		glEnd();
		x += dx;
	}
	
	z = floorStartZ;
	for(i = 0; i < floorSections; i++)
	{
		glBegin(GL_LINE_STRIP);
			glVertex3f(floorStartX, 0.0, z);   
			glVertex3f(floorStopX, 0.0, z); 
		glEnd();
		z += dz;
	}
	
	//Pushing picture to the screen
	glutSwapBuffers();
}

float get_force(int i, float separation)
{
	if(separation <= Edges[i].NaturalLength)
	{
		Edges[i].Red = 1.0;
		Edges[i].Green = 0.0;
		Edges[i].Blue = 0.0;
		return(Edges[i].CompressionStrength*(separation - Edges[i].NaturalLength));
	}
	else
	{
		Edges[i].Red = 0.0;
		Edges[i].Green = 0.0;
		Edges[i].Blue = 1.0;
		return(Edges[i].TensionStrength*(separation - Edges[i].NaturalLength));
	}
}

void n_body()
{
	float force_mag; 
	float dx,dy,dz,d, d2, dt;
	int    tdraw = 0; 
	int    tprint = 0;
	float  time = 0.0;
	int i;
	
	dt = DT;

	while(time < STOP_TIME)
	{
		for(i = 0; i < N; i++)
		{
			Fx[i] = 0.0;
			Fy[i] = 0.0;
			Fz[i] = 0.0;
		}
		
		for(i = 0; i < EDGES; i++)
		{
			//Finding the distance between nodes.
			dx = Px[Edges[i].to] - Px[Edges[i].from];
			dy = Py[Edges[i].to] - Py[Edges[i].from];
			dz = Pz[Edges[i].to] - Pz[Edges[i].from];
			d2 = dx*dx + dy*dy + dz*dz;
			d  = sqrt(d2);

			//Getting the magnitude of the force caused by node positions.
			force_mag  =  get_force(i, d);

			//Seperating into x, y, z components
			Fx[Edges[i].from] += force_mag*dx/d;
			Fx[Edges[i].to] -= force_mag*dx/d;
			Fy[Edges[i].from] += force_mag*dy/d;
			Fy[Edges[i].to] -= force_mag*dy/d;
			Fz[Edges[i].from] += force_mag*dz/d;
			Fz[Edges[i].to] -= force_mag*dz/d;
		}
		for(i = 0; i < N; i++)
		{
			//Adding in the force of gravity
			Fy[i] += -G;
			
			//Adding in the push back force from the floor.
			if((Py[i] - SHERE_RADIUS) < 0.0) Fy[i] += FLOOR_STRENGTH*(0.0 - (Py[i] - SHERE_RADIUS)); 
		}

		//Leapfrog formulas to move the nodes forward in time dt.
		for(i = 0; i < N; i++)
		{
			if(time == 0.0)
			{
				Vx[i] += ((Fx[i]-DAMP*Vx[i])/Mass[i])*0.5*dt;
				Vy[i] += ((Fy[i]-DAMP*Vy[i])/Mass[i])*0.5*dt;
				Vz[i] += ((Fz[i]-DAMP*Vz[i])/Mass[i])*0.5*dt;
			}
			else
			{
				Vx[i] += ((Fx[i]-DAMP*Vx[i])/Mass[i])*dt;
				Vy[i] += ((Fy[i]-DAMP*Vy[i])/Mass[i])*dt;
				Vz[i] += ((Fz[i]-DAMP*Vz[i])/Mass[i])*dt;
			}

			Px[i] += Vx[i]*dt;
			Py[i] += Vy[i]*dt;
			Pz[i] += Vz[i]*dt;
		}

		if(tdraw == DRAW) 
		{
			draw_picture();
			tdraw = 0;
		}
		
		time += dt;
		tdraw++;
		tprint++;
	}
}

void control()
{	
	int    tdraw = 0;
	float  time = 0.0;
	set_initail_conditions();
	draw_picture();
    	n_body();
	
	printf("\n DONE \n");
	while(1);
}

void Display(void)
{
	gluLookAt(EYE, EYE, EYE, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	control();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-0.2, 0.2, -0.2, 0.2, 0.2, FAR);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(XWindowSize,YWindowSize);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Tower");
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat light_ambient[]  = {0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat mat_specular[]   = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[]  = {10.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}






