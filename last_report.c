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
void horse(float, float, float);//���܂̊֐�
void hanabi(float, float);
int hanabi_ball[3] = { 1 ,4,8 };//�ԉ΂̋ʂ�����z��hanabi�̊֐��Ŏg�p
float hanabi_time = 0;//�ԉ΂��юU�点�邽�߂̎��Ԃ̕ϐ�
int judge_space = 0;//space-key�������ꂽ�����f����ׂ̕ϐ�
unsigned char *image;
float theta = 0.0; /*���̂̉�]�p�x*/
float uma_theta = 0.0; //�n�̏㉺�^���̂��߂�theta���n�̗������̊p�x
float uma_theta2 = 0.0;//uma_theta�̏㉺�^���Ƌt�̋t�̏㉺�^�������邽�߂�theta�ϐ�
int judge_move = 1; //�����[�S�[�����h�������Ă��邩�𔻕ʂ��邽�߂̕ϐ�

int xBegin = 0, yBegin = 0;
int mButton;
float distance, twist, elevation, azimuth;
float nearw = 1.0, farw = 100.0, fovy = 60.0;



void display(void)
{
    float diffuse[] = { 0.0, 0.0, 1.0, 1.0 };//�F�̔n
	float diffuse2[] = { 1.0, 0.0, 0.0, 1.0 };//�y��̐�
	float diffuse3[] = { 0.45, 0.31, 0.19, 1.0 };//���F�̔n
	float diffuse4[] = { 1.0, 1.0, 0.0, 1.0 };//���F�̔n
	float diffuse5[] = { 0.0, 1.0, 0.0, 1.0 };//��
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
			hanabi((i * 2.5) * hanabi_time / 200, (360 / hanabi_ball[i]) * j);//i*2.5�͒��S����̋���
		}
	}
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glPushMatrix();//�����[�S�[�����h�{�̂̓���
	glRotatef(theta, 0, 1, 0);//�����[�S�[�����h����
	glPushMatrix();//�����[�S�[�����h�̏�ɒu�����̓���
		glTranslatef(0, 1.5, 0);//�n��y��̏�ɔz�u
		glScalef(1.0, 1.5, 1.0);
		glPopMatrix();
		horse(10, 0, sin((uma_theta2)*3.14/180)*5);
		horse(10, 90, sin((uma_theta2)*3.14 / 180) * 5);
		horse(10, 180, sin((uma_theta2) * 3.14 / 180) * 5);
		horse(10, 270, sin((uma_theta2) * 3.14 / 180) * 5);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse4);//�n�����F��
		horse(10, 45, sin(uma_theta * 3.14 / 180) * 5);
		horse(10, 135, sin(uma_theta * 3.14 / 180) * 5);
		horse(10, 225, sin(uma_theta * 3.14 / 180) * 5);
		horse(10, 315, sin(uma_theta * 3.14 / 180) * 5);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);//�n�𒃐F��
		horse(5, 0, 0);
		horse(5, 90, 0);
		horse(5, 180, 0);
		horse(5, 270, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);//�����[�S�[�����h�{�̂�Ԃ�
	mySolidCylinder(15, 0.8, 32);//�i���a�A�����A�����p�`����4�̔{���̕����`���Y��j
		glPushMatrix();//�����[�S�[�����h�̒��S�̉~��
		glTranslatef(0, 7, 0);
		mySolidCylinder(2, 15, 32);
		glPopMatrix();
		glPushMatrix();//�����[�S�[�����h�̉����i�~���j
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
	glRotatef(angle, 0, 1, 0);//�n�����p�x
	glTranslatef(0, 0.3+height, center_distance);//�n�����ʒu
	glRotatef(90, 0, 1, 0);
	glScalef(1.5, 1.5, 1.5);
		glPushMatrix();//�n�̓�
		glTranslatef(0, 2.7, 1.5);
		glRotatef(55, 1, 0, 0);
		glScalef(0.5, 0.5, 1.5);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();//�n�̎�
		glTranslatef(0, 2, 1);
		glRotatef(-65, 1, 0, 0);
		glScalef(0.5, 0.5, 1.5);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();//�n�̓���
		glTranslatef(0, 1.5, 0.0);
		glRotatef(0, 0, 0, 0);
		glScalef(0.8, 0.8, 2.0);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();//�n�̑�(���O)
		glTranslatef(0.25, 0.7, 0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix();
		glPushMatrix();//�n�̑�(�E�O)
		glTranslatef(-0.25, 0.7, 0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix();
		glPushMatrix();//�n�̑�(����)
		glTranslatef(-0.25, 0.7, -0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix();
		glPushMatrix();//�n�̑�(�E��)
		glTranslatef(0.25, 0.7, -0.5);
		glRotatef(0, 0, 0, 0);
		glScalef(1, 1, 1.5);
		mySolidCylinder(0.1, 1.4, 32);
		glPopMatrix(); 
	glPopMatrix();
	//�n�Ɏh�����Ă���_
	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0, 8.5, center_distance);
	mySolidCylinder(0.2, 16, 32);
	glPopMatrix();

}

void hanabi(float hanabi_center_distance, float angle) {//�ԉ΍쐬�̊֐�
	if (hanabi_time != 0){
		glPushMatrix();
		glTranslatef(-35, 20, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(0, hanabi_center_distance, 0);
		glutSolidSphere(1.0, 20, 20); // ���a1.0�̋���`��
		glPopMatrix();
	}
}

void idle(void)/*�C�x���g���Ȃ����idle���˂Ɏ��s�����*/
{
	//dist =fmod(dist+0.05,32.0);
	if (judge_move == 1) {
		theta = fmod(theta + 0.1, 360.0);/*��]�p���O���`�R�U�O���܂�0.1���Â���������j*/
		uma_theta = fmod(uma_theta + 0.1, 180.0);/*��]�p���O���`180���܂�0.1���Â���������j*/

		if ((uma_theta + 90) > 180) {		//uma_theta�Ƌt�̏㉺�^���������邽�߂ɁAuma_theta�̈ʑ���90�x���炵��uma_theta2��0�`180�x�Ɏ��܂�悤�Ɍv�Z
			uma_theta2 = (int)(uma_theta + 90) % 180;//0�`180�x�Ɏ��܂�Ȃ��ꍇ�́A���܂�����Ă����ĉ���
		}
		else {
			uma_theta2 = uma_theta + 90;//180�x�ȓ��Ȃ炻�̂܂�90�x���炵�����̂��g��
		}
	}
	if (judge_space == 1) {
		hanabi_time += 1;
		if (hanabi_time >= 700) {
			judge_space = 0;
			hanabi_time = 0;
		}
	}
	glutPostRedisplay();/*�f�B�X�v���C�R�[���o�b�N�o�b�N�֐�(display)�����s*/
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
	glutIdleFunc(idle);//idle�֐����g�����߂̃R�[�h
	glutReshapeFunc (myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutMotionFunc( myMotion );
	glutMainLoop();
}
