#include "Object.hpp"
#include <GL/Glut.h>
#include <FreeImage.h>

// Rotation
static GLfloat yRot = 0.0f;
static GLfloat xRot = 90.0f;
static GLfloat zoom = -5.0f;

static GLfloat posCamera[3] = { 0.0f, 0.0f, 10.0f };
static GLfloat direcaoCamera[3] = { 0.0f, 0.0f, -1.0f };
static GLfloat cameraUp[3] = { 0.0f, 1.0f, 0.0f };
static GLfloat velocCamera = 0.5f;

Object object;
GLuint textureID;

void ChangeSize(int w, int h) {
    GLfloat fAspect;


    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    gluPerspective(35.0f, fAspect, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Setup() {
    GLfloat whiteLight[] = { 0.4, 0.4, 0.4, 1.0f };
    GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glEnable(GL_LIGHTING);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glShadeModel(GL_SMOOTH);

    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
}

void SpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN:
        yRot -= 10.0f;
        break;

    case GLUT_KEY_UP:
        yRot += 10.0f;
        break;

    case GLUT_KEY_LEFT:
        xRot += 10.0f;
        break;

    case GLUT_KEY_RIGHT:
        xRot -= 10.0f;
        break;
    }

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);


    glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {

    case 'w':
    case 'W':
        posCamera[1] += velocCamera;
        break;


    case 's':
    case 'S':
        posCamera[1] -= velocCamera;
        break;


    case 'a':
    case 'A':
        posCamera[0] -= velocCamera;
        break;


    case 'D':
    case 'd':
        posCamera[0] += velocCamera;
        break;


    case 'z':
        zoom -= velocCamera * 2;
        break;


    case 'Z':
        zoom += velocCamera * 2;
        break;


    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void loadTexture(const char* fileName, GLuint textureID) {
    // Carregando a imagem usando FreeImage
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName, 0);
    FIBITMAP* image = FreeImage_Load(format, fileName);
    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);
    int width = FreeImage_GetWidth(image32bits);
    int height = FreeImage_GetHeight(image32bits);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configurando os parâmetros da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carregando os dados da imagem na textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));

    // Liberando a memória utilizada pelas imagens
    FreeImage_Unload(image);
    FreeImage_Unload(image32bits);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(posCamera[0], posCamera[1], posCamera[2],
        posCamera[0] + direcaoCamera[0], posCamera[1] + direcaoCamera[1], posCamera[2] + direcaoCamera[2],
        cameraUp[0], cameraUp[1], cameraUp[2]);

    glTranslatef(0.0f, -1.0f, zoom);
    glRotatef(yRot, 1.0f, 0.0f, 0.0f);
    glRotatef(xRot, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    for (const auto& face : object.getFaces()) {
        long unsigned int materialIndex = face.materialIndex;

        if (materialIndex < object.getMaterials().size()) {
            const Material material = object.getMaterials()[materialIndex];
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.emission);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
            glMaterialf(GL_FRONT_AND_BACK, GL_ALPHA, material.dissolve);

        }

        glBegin(GL_POLYGON);
        for (size_t i = 0; i < face.vertexIndices.size(); ++i) {
            int vertexIndex = face.vertexIndices[i];
            int texCoordIndex = face.textureIndices[i];
            int normalIndex = face.normalIndices[i];
            const Vertex vertex = object.getVertices()[vertexIndex];
            const Texture texCoord = object.getTextures()[texCoordIndex];
            const Normal normal = object.getNormals()[normalIndex];
            glTexCoord2f(texCoord.x, texCoord.y);
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    glGenTextures(1, &textureID);
    if (!object.loadOBJ("C:\\Users\\halat\\source\\repos\\TC4\\Data\\perfume.obj")) return 0;
    if (!object.loadMTL("C:\\Users\\halat\\source\\repos\\TC4\\Data\\perfume.mtl")) return 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OBJ viewer");
    loadTexture("C:\\Users\\halat\\source\\repos\\TC4\\Data\\perfume.jpeg", textureID);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(drawScene);
    Setup();
    glutMainLoop();

    return 0;
}