#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include<myShape.h>
#define KEY_ESC 27
#define imageWidth 8
#define imageHeight 8

void polarview( void );
void resetview( void );
void horse(float, float, float);//うまの関数
void hanabi(float, float);
int hanabi_ball[3] = { 1 ,4,8 };//花火の玉を入れる配列※hanabiの関数で使用
float hanabi_time = 0;//花火を飛び散らせるための時間の変数
int judge_space = 0;//space-keyが押されたか判断する為の変数
unsigned char *image;
float theta = 0.0; /*物体の回転角度*/
float uma_theta = 0.0; //馬の上下運動のためのtheta※馬の立つ高さの角度
float uma_theta2 = 0.0;//uma_thetaの上下運動と逆の逆の上下運動をするためのtheta変数
int judge_move = 1; //メリーゴーランドが動いているかを判別するための変数

int xBegin = 0, yBegin = 0;
int mButton;
float distance, twist, elevation, azimuth;
float nearw = 1.0, farw = 100.0, fovy = 60.0;



void display(void)
{
    float diffuse[] = { 0.0, 0.0, 1.0, 1.0 };//青色の馬
	float diffuse2[] = { 1.0, 0.0, 0.0, 1.0 };//土台の赤
	float diffuse3[] = { 0.45, 0.31, 0.19, 1.0 };//茶色の馬
	float diffuse4[] = { 1.0, 1.0, 0.0, 1.0 };//黄色の馬
	float diffuse5[] = { 0.0, 1.0, 0.0, 1.0 };//緑
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
				 
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	polarview();
    glEnable( GL_DEPTH_TEST );
	glEnable(GL_TEXTURE_2D);

	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, 128.0 );
    glEnable( GL_LIGHTING );


	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
		}
		else if (i == 1) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse5);
		}
		else if (i == 2) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		}
		for (int j = 0; j < hanabi_ball[i]; j++) {
			hanabi((i * 2.5)*hanabi_time/200, (360 / hanabi_ball[i])*j);
		}
	}

	glPushMatrix();
	glTranslatef(70, 0, 0);
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
		}
		else if (i == 1) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse5);
		}
		else if (i == 2) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		}
		for (int j = 0; j < hanabi_ball[i]; j++) {
			hanabi((i * 2.5) * hanabi_time / 200, (360 / hanabi_ball[i]) * j);//i*2.5は中心からの距離
		}
	}
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glPushMatrix();//メリーゴーランド本体の動き
	glRotatef(theta, 0, 1, 0);//メリーゴーランドを回す
	glPushMatrix();//メリーゴーランドの上に置く物の動き
		glTranslatef(0, 1.5, 0);//馬を土台の上に配置
		glScalef(1.0, 1.5, 1.0);
		glPopMatrix();
		horse(10, 0, sin((uma_theta2)*3.14/180)*5);
		horse(10, 90, sin((uma_theta2)*3.14 / 180) * 5);
		horse(10, 180, sin((uma_theta2) * 3.14 / 180) * 5);
		horse(10, 270, sin((uma_theta2) * 3.14 / 180) * 5);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse4);//馬を黄色に
		horse(10, 45, sin(uma_theta * 3.14 / 180) * 5);
		horse(10, 135, sin(uma_theta * 3.14 / 180) * 5);
		horse(10, 225, sin(uma_theta * 3.14 / 180) * 5);
		horse(10, 315, sin(uma_theta * 3.14 / 180) * 5);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);//馬を茶色に
		horse(5, 0, 0);
		horse(5, 90, 0);
		horse(5, 180, 0);
		horse(5, 270, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);//メリーゴーランド本体を赤に
	mySolidCylinder(15, 0.8, 32);//（半径、高さ、正何角形か※4の倍数の方が形が綺麗）
		glPushMatrix();//メリーゴーランドの中心の円柱
		glTranslatef(0, 7, 0);
		mySolidCylinder(2, 15, 32);
		glPopMatrix();
		glPushMatrix();//メリーゴーランドの屋根（円錐）
		glTranslatef(0, 14, 0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glutSolidCone(15, 10.0, 12, 8);
		glPopMatrix();
		

	glPopMatrix();
	glPopMatrix();
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
	glutSwapBuffers();
}

void horse(float center_distance, float angle, float height){
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);//馬が立つ角度
	glTranslatef(0, 0.3+height, center_distance);//馬が立つ位置
	glRotatef(90, 0, 1, 0);
	glScalef(1.5, 1.5, 1.5);
		glPushMatrix();//馬の頭
		glTranslatef(0, 2.7, 1.5);
		glRotatef(55, 1, 0, 0);
		glScalef(0.5, 0.5, 1.5);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();//馬の首
		glTranslatef(0, 2, 1);
		glRotatef(-65, 1, 0, 0);
		glScalef(0.5, 0.5, 1.5);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();//馬の胴体
		glTranslatef(0, 1.5, 0.0);
		glRotatef(0, 0, 0, 0);
		glScalef(0.8, 0.8, 2.0);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();//馬の足(左前)
		glTranslatef(0.25, 0.7, 0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix();
		glPushMatrix();//馬の足(右前)
		glTranslatef(-0.25, 0.7, 0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix();
		glPushMatrix();//馬の足(左後)
		glTranslatef(-0.25, 0.7, -0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix();
		glPushMatrix();//馬の足(右後)
		glTranslatef(0.25, 0.7, -0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix(); 
	glPopMatrix();
	//馬に刺さっている棒
	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0, 8.5, center_distance);
	mySolidCylinder(0.2, 16, 32);
	glPopMatrix();

}

void hanabi(float hanabi_center_distance, float angle) {//花火作成の関数
	if (hanabi_time != 0){
		glPushMatrix();
		glTranslatef(-35, 20, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(0, hanabi_center_distance, 0);
		glutSolidSphere(1.0, 20, 20); // 半径1.0の球を描画
		glPopMatrix();
	}
}

void idle(void)/*イベントがなければidleがつねに実行される*/
{
	//dist =fmod(dist+0.05,32.0);
	if (judge_move == 1) {
		theta = fmod(theta + 0.1, 360.0);/*回転角を０°～３６０°まで0.1°づつ増加させる）*/
		uma_theta = fmod(uma_theta + 0.1, 180.0);/*回転角を０°～180°まで0.1°づつ増加させる）*/

		if ((uma_theta + 90) > 180) {		//uma_thetaと逆の上下運動をさせるために、uma_thetaの位相を90度ずらしたuma_theta2を0～180度に収まるように計算
			uma_theta2 = (int)(uma_theta + 90) % 180;//0～180度に収まらない場合は、あまりを入れてあげて解決
		}
		else {
			uma_theta2 = uma_theta + 90;//180度以内ならそのまま90度ずらしたものを使う
		}
	}
	if (judge_space == 1) {
		hanabi_time += 1;
		if (hanabi_time >= 700) {
			judge_space = 0;
			hanabi_time = 0;
		}
	}
	glutPostRedisplay();/*ディスプレイコールバックバック関数(display)を実行*/
}


void myKbd(unsigned char key, int x, int y)
{
	switch(key) {
    case KEY_ESC:
        exit( 0 );
	case 13:
		if (judge_move == 0) {
			judge_move = 1;
		}
		else if (judge_move == 1) {
			judge_move = 0;
		}
		break;
	case 32:
		if (judge_space == 0) {
			judge_space = 1;
			hanabi_time = 0;
		}
		else if (judge_space == 1) {
			judge_space = 0;
		}
  	default:
   		break;
	}
}


void myInit (char *progname)
{
    glutInitWindowPosition(0, 0);
	glutInitWindowSize( 800, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (1.0, 1.0, 0.0, 1.0);
    glutKeyboardFunc(myKbd);
		
	resetview();
	glShadeModel( GL_SMOOTH );
	glEnable( GL_LIGHT0 );
}

void myReshape(int width, int height)
{
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, nearw, farw);
    glMatrixMode(GL_MODELVIEW);
}


void polarview( void )
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}


void resetview( void )
{
	distance = 70.0;
    twist = 0.0;
    elevation = -13.0;
    azimuth = 0.0;
}

void myMouse( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN) {
		mButton = button;
        xBegin = x;
        yBegin = y;
	}
}


void myMotion(int x, int y)
{
    int xDisp, yDisp;

    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch(mButton){
    case GLUT_LEFT_BUTTON:
        azimuth += (float) xDisp/2.0;
        elevation -= (float) yDisp/2.0;
        break;
    case GLUT_MIDDLE_BUTTON:
        elevation -= (float) yDisp/2.0;
//        twist = fmod (twist + xDisp, 360.0);
        break;
    case GLUT_RIGHT_BUTTON:
        distance -= (float) yDisp/40.0;
        break;
    }
    xBegin = x;
    yBegin = y;
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	myInit(argv[0]);
	glutIdleFunc(idle);//idle関数を使うためのコード
	glutReshapeFunc (myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutMotionFunc( myMotion );
	glutMainLoop();
}
