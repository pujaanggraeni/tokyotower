#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <GL\glut.h>
#include <gl\glu.h>
#include"imageloader.h"

void init(void);
void tampil(void);
void keyboard(unsigned char, int, int);
void ukuran(int, int);
int channel=0;

int is_depth;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
float xtrans = 0.0f;
float ytrans = 0.0f;
float ztrans = 0.0f;

bool mouseDown = false;
bool atap = true;
bool tv = true;

GLuint _textureId1;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;
GLuint _textureId7;



GLuint loadTexture1(Image* image1){
GLuint textureId1;
glGenTextures(1, &textureId1);
glBindTexture(GL_TEXTURE_2D, textureId1);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image1 -> width, image1 -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->pixels);
return textureId1;
}

GLuint loadTexture2(Image* image2){
GLuint textureId2;
glGenTextures(1, &textureId2);
glBindTexture(GL_TEXTURE_2D, textureId2);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image2 -> width, image2 -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->pixels);
return textureId2;
}

GLuint loadTexture3(Image* image3){
GLuint textureId3;
glGenTextures(1, &textureId3);
glBindTexture(GL_TEXTURE_2D, textureId3);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image3 -> width, image3 -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->pixels);
return textureId3;
}

GLuint loadTexture4(Image* image4){
GLuint textureId4;
glGenTextures(1, &textureId4);
glBindTexture(GL_TEXTURE_2D, textureId4);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image4 -> width, image4 -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->pixels);
return textureId4;
}

GLuint loadTexture5(Image* image5){
GLuint textureId5;
glGenTextures(1, &textureId5);
glBindTexture(GL_TEXTURE_2D, textureId5);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image5 -> width, image5 -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, image5->pixels);
return textureId5;
}

GLuint loadTexture6(Image* image6){
GLuint textureId6;
glGenTextures(1, &textureId6);
glBindTexture(GL_TEXTURE_2D, textureId6);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image6 -> width, image6 -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, image6->pixels);
return textureId6;
}

void init(void)
{
	glClearColor(0.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	is_depth = 1;
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	Image* image1 = loadBMP("jalan1.bmp");//ambil gambar bmp
	_textureId1 = loadTexture1(image1);
	delete image1;
	Image* image2 = loadBMP("paving2.bmp");//ambil gambar bmp
	_textureId2 = loadTexture2(image2);
	delete image2;
	Image* image3 = loadBMP("jalan2.bmp");//ambil gambar bmp
	_textureId3 = loadTexture3(image3);
	delete image3;
	Image* image4 = loadBMP("poster.bmp");//ambil gambar bmp
	_textureId4 = loadTexture4(image4);
	delete image4;
	Image* image5 = loadBMP("aspal.bmp");//ambil gambar bmp
	_textureId5 = loadTexture5(image5);
	delete image5;
	Image* image6 = loadBMP("ged1.bmp");//ambil gambar bmp
	_textureId6 = loadTexture6(image6);
	delete image6;

	glPointSize(9.0);
	glLineWidth(2.0f);
}

void ukuran(int lebar, int tinggi)
{
	if (tinggi == 0) tinggi = 1;
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, lebar, tinggi);
	glLoadIdentity();
	gluPerspective(50.0, lebar / tinggi, 5.0, 500.0);
	glTranslatef(0.0, -5.0, -150.0);
	glMatrixMode(GL_MODELVIEW);
}

void kubus(float ex, float ey, float ez, float p, float l, float t) {
	glBegin(GL_QUADS);
	//Depan
	glVertex3d(ex, ey, ez);  //TITIK KIRI BAWAH
	glVertex3d(ex, ey + t, ez);  //TITIK KIRI ATAS
	glVertex3d(ex + p, ey + t, ez);  //TITIK KANAN ATAS
	glVertex3d(ex + p, ey, ez);  //TITIK KANAN BAWAH

	//Belakang
	glVertex3d(ex, ey, ez + l);  //TITIK KIRI BAWAH
	glVertex3d(ex, ey + t, ez + l);  //TITIK KIRI ATAS
	glVertex3d(ex + p, ey + t, ez + l);  //TITIK KANAN ATAS
	glVertex3d(ex + p, ey, ez + l);  //TITIK KANAN BAWAH

	//Kiri
	glVertex3d(ex, ey, ez);  //TITIK DEPAN BAWAH
	glVertex3d(ex, ey + t, ez);  //TITIK DEPAN ATAS
	glVertex3d(ex, ey + t, ez + l);  //TITIK BELAKANG ATAS
	glVertex3d(ex, ey, ez + l);  //TITIK BELAKANG BAWAH

	//Kanan
	glVertex3d(ex + p, ey, ez);  //TITIK DEPAN BAWAH
	glVertex3d(ex + p, ey + t, ez);  //TITIK DEPAN ATAS
	glVertex3d(ex + p, ey + t, ez + l);  //TITIK BELAKANG ATAS
	glVertex3d(ex + p, ey, ez + l);  //TITIK BELAKANG BAWAH

	//Atas
	glVertex3d(ex, ey + t, ez);  //TITIK DEPAN KIRI
	glVertex3d(ex + p, ey + t, ez);  //TITIK DEPAN KANAN
	glVertex3d(ex + p, ey + t, ez + l);  //TITIK BELAKANG KANAN
	glVertex3d(ex, ey + t, ez + l);  //TITIK BELAKANG KIRI

	//Bawah
	glVertex3d(ex, ey, ez);  //TITIK DEPAN KIRI
	glVertex3d(ex + p, ey, ez);  //TITIK DEPAN KANAN
	glVertex3d(ex + p, ey, ez + l);  //TITIK BELAKANG KANAN
	glVertex3d(ex, ey, ez + l);  //TITIK BELAKANG KIRI
	glEnd();
}

void tanggatidur(int exs, int yee, int pan, int ting) {
	int wrn5 = 0;
	int warnat = 162;
	for (int a = 0; a < 4; a++) {
		if (wrn5 == 1) {
			glColor3f(0.72, 0.52, 0.04);
			kubus(exs, yee, warnat, pan, 5, ting);
			warnat += 5;
			wrn5 = 0;
		}
		else if (wrn5 == 0) {
			glColor3f(0.80, 0.62, 0.34);
			kubus(exs, yee, warnat, pan, 5, ting);
			warnat += 5;
			wrn5 = 1;
		}
	}
}

void tanggatidur2(int exs, int yee, int pan, int ting) {
	int wrn5 = 0;
	int warnat = 182;
	for (int a = 0; a < 2; a++) {
		if (wrn5 == 1) {
			glColor3f(1, 0, 0);
			kubus(exs, yee, warnat, pan, 5, ting);
			warnat += 5;
			wrn5 = 0;
		}
		else if (wrn5 == 0) {
			glColor3f(1, 0, 0);
			kubus(exs, yee, warnat, pan, 5, ting);
			warnat += 5;
			wrn5 = 1;
		}
	}
}

void bangunan(void) {

	//================================ KAKI =================================== 
float x=30,y=-20,z=50; //belakang kiri
	glColor3f(1.0, 0.0, 0.0);
	for(int nil=1;nil<=20;nil++){
		kubus(x, y, z, 3, 4, 3);
		x-=0.5;
		y-=1;
		z-=0.5;
	}

float i=60,j=-20,k=50; //belakang kanan
	glColor3f(1.0, 0.0, 0.0);
	for(int nil=1;nil<=20;nil++){
		kubus(i, j, k, 3, 4, 3);
		i+=0.5;
		j-=1;
		k-=0.5;
	}	
float a=60,b=-20,c=80; //depan kanan
	glColor3f(1.0, 0.0, 0.0);
	for(int nil=1;nil<=20;nil++){
		kubus(a, b, c, 3, 4, 3);
		a+=0.5;
		b-=1;
		c+=0.5;
	}	
float d=30,e=-20,f=80; //depan kiri
	glColor3f(1.0, 0.0, 0.0);
	for(int nil=1;nil<=20;nil++){
		kubus(d, e, f, 3, 4, 3);
		d-=0.5;
		e-=1;
		f+=0.5;
	}
	glColor3f(1.0, 0.0, 0.0);
	kubus(30, -20, 50, 30, 4, 3);
	kubus(30, -20, 50, 4, 30, 3);
	kubus(60, -20, 50, 4, 32, 3);
	kubus(30, -20, 80, 30, 4, 3);


	  glColor3f( 1, 0, 0 );
	  glBegin(GL_QUADS);//
      glVertex3f(40,50,72);//left of window ------------- bawah kotak putih
      glVertex3f(50,50,72);//bottom of window
      glVertex3f(63,-20,82);//right of window
      glVertex3f(30,-20,82);//top of window

	  glVertex3f(40,50,60);//left of window
      glVertex3f(50,50,60);//bottom of window
      glVertex3f(63,-20,50);//right of window
      glVertex3f(30,-20,50);//top of window

	  glVertex3f(40,50,60);//left of window
      glVertex3f(40,50,72);//bottom of window
      glVertex3f(30,-20,83);//right of window
      glVertex3f(30,-20,50);//top of window

	  glVertex3f(50,50,60);//left of window
      glVertex3f(50,50,72);//bottom of window
      glVertex3f(60,-20,83);//right of window
      glVertex3f(60,-20,50);//top of window

	  glVertex3f(43,128,70);//left of window ------------- atas kotak putih
      glVertex3f(48,128,70);//bottom of window
      glVertex3f(50,58,72);//right of window
      glVertex3f(40,58,72);//top of window

	  glVertex3f(43,128,62);//left of window
      glVertex3f(48,128,62);//bottom of window
      glVertex3f(50,58,60);//right of window
      glVertex3f(40,58,60);//top of window

	  glVertex3f(43,128,62);//left of window
      glVertex3f(43,128,70);//bottom of window
      glVertex3f(40,58,72);//right of window
      glVertex3f(40,58,60);//top of window

	  glVertex3f(48,128,62);//left of window
      glVertex3f(48,128,70);//bottom of window
      glVertex3f(50,58,72);//right of window
      glVertex3f(50,58,60);//top of window


	  glVertex3f(44,145,67);//left of window ------------- atas kotak putih atas
      glVertex3f(46,145,67);//bottom of window
      glVertex3f(48,130,69);//right of window
      glVertex3f(43,130,69);//top of window

	  glVertex3f(44,145,65);//left of window
      glVertex3f(46,145,65);//bottom of window
      glVertex3f(48,130,63);//right of window
      glVertex3f(43,130,63);//top of window

	  glVertex3f(44,145,65);//left of window
      glVertex3f(44,145,67);//bottom of window
      glVertex3f(43,130,69);//right of window
      glVertex3f(43,130,63);//top of window

	  glVertex3f(46,145,65);//left of window
      glVertex3f(46,145,67);//bottom of window
      glVertex3f(48,130,69);//right of window
      glVertex3f(48,130,63);//top of window
    glEnd();//end drawing of line loop

	glColor3f(1.0, 1.0, 1.0); //putih tengah
	kubus(38, 50, 58, 14, 17,8);

	glColor3f(1.0, 1.0, 1.0);// putih atas
	kubus(43, 128, 62, 5, 8,2);

	glColor3f(1.0, 1.0, 1.0);// putih merah atas banget
	kubus(44, 145, 65, 2, 2,2);
	glColor3f(1.0, 0.0, 0.0);
	kubus(44, 147, 65, 2, 2,2);

	glColor3f(1.0, 1.0, 1.0);// pucuk
	kubus(44.5, 149, 65.5, 1, 1,10);

	//glColor3f(0.0, 1.0, 0.0);//alas
	//kubus(-6, -40, -20, 99, 230, 2);
	
	

	glPopMatrix();
}

void paving(void){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);//alas
	float x1=-6.0,y1=-40.0,z1=-20.0;
	for(int a=1;a<=30;a++){
		for(int b=1;b<=20;b++){
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0f);
			glVertex3f(x1, y1, z1 ); // Depan Kiri
			glTexCoord2f(1.0, 0.0f);
			glVertex3f(x1+5, y1, z1 ); // Depan Kanan
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(x1+5, y1, z1+5 ); // BELAKANG Kanan
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(x1, y1, z1+5 ); // BELAKANG Kiri
			glEnd();
			x1+=5;
			//z1+=5;
		}
		x1=-6.0;
		z1+=5;
	}
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void jalan(void){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//foto
	glPushMatrix();
	//glTranslated(20,-5,0);
	glColor3f(1.0,1.0,1.0);
	float x1=-6.0,y1=-40.0,z1=-25.0;
	for(int a=1;a<=20;a++){
			glBegin(GL_QUADS);
			glTexCoord2f(1.0, 0.0f);
			glVertex3f(x1+5, y1, z1 ); // Depan Kanan
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(x1+5, y1, z1+5 ); // BELAKANG Kanan
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(x1, y1, z1+5 ); // BELAKANG Kiri
			glTexCoord2f(0.0, 0.0f);
			glVertex3f(x1, y1, z1 ); // Depan Kiri
			glEnd();
			x1+=5;
	}
	float x2=-6.0,y2=-40.0,z2=130.0;
	for(int a=1;a<=20;a++){
			glBegin(GL_QUADS);
			glTexCoord2f(1.0, 0.0f);
			glVertex3f(x2+5, y2, z2 ); // Depan Kanan
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(x2+5, y2, z2+5 ); // BELAKANG Kanan
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(x2, y2, z2+5 ); // BELAKANG Kiri
			glTexCoord2f(0.0, 0.0f);
			glVertex3f(x2, y2, z2 ); // Depan Kiri
			glEnd();
			x2+=5;
	}
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void jalan2(void){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId3);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//foto
	glPushMatrix();
	//glTranslated(20,-5,0);
	glColor3f(1.0,1.0,1.0);
	float x3=94.0,y3=-40.0,z3=-25.0;
	for(int a=1;a<=32;a++){
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0f);
			glVertex3f(x3, y3, z3 ); // Depan Kiri
			glTexCoord2f(1.0, 0.0f);
			glVertex3f(x3+5, y3, z3 ); // Depan Kanan
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(x3+5, y3, z3+5 ); // BELAKANG Kanan
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(x3, y3, z3+5 ); // BELAKANG Kiri
			glEnd();
			z3+=5;
	}
	float x4=-11.0,y4=-40.0,z4=-25.0;
	for(int a=1;a<=32;a++){
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0f);
			glVertex3f(x4, y4, z4 ); // Depan Kiri
			glTexCoord2f(1.0, 0.0f);
			glVertex3f(x4+5, y4, z4 ); // Depan Kanan
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(x4+5, y4, z4+5 ); // BELAKANG Kanan
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(x4, y4, z4+5 ); // BELAKANG Kiri
			glEnd();
			z4+=5;
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void gedung1(void){
	//Aspal
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//foto
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	float x3=99.0,y3=-40.0,z3=-20.0;
	for(int a=1;a<=20;a++){
		for(int b=1;b<=10;b++){
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0f);
			glVertex3f(x3, y3, z3 ); // Depan Kiri
			glTexCoord2f(1.0, 0.0f);
			glVertex3f(x3+5, y3, z3 ); // Depan Kanan
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(x3+5, y3, z3+5 ); // BELAKANG Kanan
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(x3, y3, z3+5 ); // BELAKANG Kiri
			glEnd();
			x3+=5;
		}
		x3=99;
		z3+=5;
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void gedung2(void){
	//Bangunan
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId6);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//foto
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	float x3=109.0,y3=-40.0,z3=-15.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0f);
	glVertex3f(x3, y3, z3 ); // Depan Kiri
	glTexCoord2f(1.0, 0.0f);
	glVertex3f(x3+40, y3, z3 ); // Depan Kanan
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(x3+40, y3+30, z3 ); // BELAKANG Kanan
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(x3, y3+30, z3 ); // BELAKANG Kiri
	glEnd();
	float x4=109.0,y4=-40.0,z4=40.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0f);
	glVertex3f(x4, y4, z4 ); // Depan Kiri
	glTexCoord2f(1.0, 0.0f);
	glVertex3f(x4+40, y4, z4 ); // Depan Kanan
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(x4+40, y4+30, z4 ); // BELAKANG Kanan
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(x4, y4+30, z4 ); // BELAKANG Kiri
	glEnd();
	float x5=109.0,y5=-40.0,z5=-15.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0f);
	glVertex3f(x5, y5, z5+55 ); // BELAKANG Kiri
	glTexCoord2f(1.0, 0.0f);
	glVertex3f(x5, y5, z5 ); // Depan Kiri
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(x5, y5+30, z5 ); // Depan Kanan
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(x5, y5+30, z5+55 ); // BELAKANG Kanan
	glEnd();
	float x6=149.0,y6=-40.0,z6=-15.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0f);
	glVertex3f(x6, y6, z6+55 ); // BELAKANG Kiri
	glTexCoord2f(1.0, 0.0f);
	glVertex3f(x6, y6, z6 ); // Depan Kiri
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(x6, y6+30, z6 ); // Depan Kanan
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(x6, y6+30, z6+55 ); // BELAKANG Kanan
	glEnd();
			
	kubus(109,-40,-15,40,55,30);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void setViewport()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt = 1.0;//half height of the window
	glOrtho(-winHt * 64 / 48, winHt * 64 / 48, -winHt, winHt, 0.1, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	//ganti channel
	case 'c':
	case 'C':
		if(channel<3){
		channel++;
		}
		else if(channel==3){
		channel=0;
		}
		break;
		//gerak ke kiri 
	case 'd':
	case 'D':
		xtrans -= 10.0;
		break;
		//gerak ke kanan
	case 'a':
	case 'A':
		xtrans += 10.0;
		glTranslatef(1.0, 0.0, 0.0);
		break;
		//gerak ke depan
	case 'w':
	case 'W':
		ztrans += 10.0;
		glTranslatef(0.0, 0.0, 1.0);
		break;
		//gerak ke belakang
	case 's':
	case 'S':
		ztrans -= 10.00;
		glTranslatef(0.0, 0.0, -1.0);
		break;
		//gerak ke atas
	case 'q':
	case 'Q':
		ytrans += 10.0;
		glTranslatef(0.0, 1.0, 0.0);
		break;
		//gerak ke bawah
	case 'e':
	case 'E':
		ytrans -= 10.0;
		glTranslatef(0.0, -1.0, 0.0);
		break;
		//rotate ke kiri
	case 'b':
	case 'B':
		atap = true;
		break;
		//rotate ke kanan
	case 'v':
	case 'V':
		atap = false;
		break;
		//rotate ke samping kanan
	case 'i':
	case 'I':
		glRotatef(1.0, 0.0, 0.0, -1.0);
		break;
		//rotate ke samping kiri
	case 'k':
	case 'K':
		glRotatef(1.0, 0.0, 0.0, 5.0);
		break;
		//rotate ke atas
	case 'o':
	case 'O':
		glRotatef(1.0, -5.0, 0.0, 0.0);
		break;
		//rotate ke bawah
	case 'u':
	case 'U':
		glRotatef(1.0, 5.0, 0.0, 0.0);
		break;
	case '5':
		if (is_depth)
		{
			is_depth = 0;
			glDisable(GL_DEPTH_TEST);
		}
		else
		{
			is_depth = 1;
			glEnable(GL_DEPTH_TEST);
		}
		break;
	case 'm':
		exit(1);
		break;

	}
	glutPostRedisplay();
}

void idle()
{
	if (!mouseDown)
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
	glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;
		glutPostRedisplay();
	}
}

void tampil(void)
{

	if (is_depth)

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glViewport(0, 0, 1366, 768);
	glTranslatef(xtrans, ytrans, ztrans);
	glPushMatrix();
	jalan();
	jalan2();
	bangunan();
	gedung1();
	gedung2();
	paving();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(250, 50);
	glutCreateWindow("672018406 - 62018436");
	init();
	glutDisplayFunc(tampil);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(ukuran);
	glutMainLoop();
	return 0;
}

