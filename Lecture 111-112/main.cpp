#include"glframework/shader.h"
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"
#include "glframework/texture.h"
#include "application/camera/perspectiveCamera.h"
#include "application/camera/cameraControl.h"
#include "glframework/geometry.h"
#pragma warning(disable:4244)
Geometry* geometry = nullptr;
GLuint vao, program ,ebo; 
Shader* shader = nullptr;
Texture* texture = nullptr;
Texture* texture2 = nullptr;

glm::mat4 transform(1.0f);
glm::mat4 transform2(2.0f);

glm::mat4 viewMatrix(1.0f);
glm::mat4 orthoMatrix(1.0f);
glm::mat4 perspectiveMatrix(1.0f);
PerspectiveCamera* camera = nullptr;
CameraControl* cameraControl = nullptr;
float angle = 0.0f;
void OnResize(int width, int height) {
	std::cout << "�������´�С" << width << "��" << height << std::endl;
	GL_CALL(glViewport(0, 0, width, height));
}
void OnKey(int key, int action, int mods) {
	std::cout << key << std::endl;
	cameraControl->onKey(key, action, mods);
}

void OnMouse(int button, int action ,int mods) {
	//std::cout << "�����" << button << "," << action << std::endl;
	double x, y;
	app->getCursorPosition(&x, &y);
	cameraControl->onMouse(button, action, x, y);
}
void OnCursor(double xpos, double ypos) {
	//std::cout << "����ƶ�" << xpos << "," << ypos << std::endl;
	cameraControl->onCursor(xpos, ypos);
}
void doRotation() {
	//angle += 2.0f;
	//transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	angle = 1.0f;
	transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}
void doRotationTransform() {
	transform = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}
void doTranslateTransform() {
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
}
void doTranslateTransform2() {
	transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, -1.0f));
}
void doScaleTransform() {
	transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
}
void doTransform() {
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	transform = rotateMat * translateMat;
}
//void prepareInterleavedBuffer() {
//	//float vertices[] = {
//	//	-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,
//	//	0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
//	//	0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,0.5f,1.0f
//	//};
//	//float vertices[] = {
//	//-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,
//	//0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,10.0f,0.0f,
//	//0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,5,10
//	//};
//	float vertices[] = {
//-1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,
//1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
//0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.5f,1.0f
//	};
//	unsigned int indices[] = {
//		0,1,2,
//	};
//	GLuint vbo = 0;
//	glGenBuffers(1, &vbo);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo); //��
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//������
//
//	glGenBuffers(1, &ebo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	//GLuint vao = 0;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	//��̬��ȡλ��
//	GLuint posLocation = glGetAttribLocation(shader->mProgram, "aPos");
//	GLuint colorLocation = glGetAttribLocation(shader->mProgram, "aColor");
//	GLuint uvLocation = glGetAttribLocation(shader->mProgram, "aUV");
//	//��̬��ȡUniform���
//	// GLuint location = glGetUniformLocation(program,"time"); 
//	// ���ñ�����ֵ
//	// glUniform1f(location,0.5f);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//	glEnableVertexAttribArray(posLocation);
//	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
//	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//
//	glEnableVertexAttribArray(colorLocation);//�󶨵�����
//	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
//	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//
//	glEnableVertexAttribArray(uvLocation);//�󶨵�����
//	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
//	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);//��ebo���vao
//
//	glBindVertexArray(0); //���VAO
//}
void prepareVAO() {
	geometry = Geometry::createSphere(5.0f);
}
void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
	texture = new Texture("assets/textures/std-image.jpg", 0);
	texture2 = new Texture("assets/textures/wf.jpg", 0);
}

void prepareCamera() {

	camera = new PerspectiveCamera(60.0f, (float)app->getWidth() / (float)app->getHeight(), 0.1f, 1000.0f);

	cameraControl = new CameraControl();
	cameraControl->setCamera(camera);
	//lookat����viewMatrix��eye��ǰ���������λ�ã�center��ǰ���������ĵ㣬��������Ϸ���
	//viewMatrix = glm::lookAt(glm::vec3(3.0f,0.0f,1.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
	viewMatrix = glm::lookAt(glm::vec3(9.0f, 9.0f, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
void prepareOrtho() {
	orthoMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f);//���� ���� ��Զ
}
void preparePerspective() {
	//FOV �������Žǣ�aspect����ƽ����ݱȣ���ƽ����룬ԭƽ�����
	perspectiveMatrix = glm::perspective(glm::radians(60.0f), (float)app->getWidth()/(float)app->getHeight(), 0.1f, 1000.0f);
}

void prepareState() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_LI);
}
void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));//ִ�л����������, GL_CALL����������ĺ궨��

	//��shader program
	//glUseProgram(program);
	shader->begin();

	//glGetUniformLocation������UseProgram����ʹ�ã�Ҳ����shader->begin��ʹ��
	float color[] = { 0.5f,0.3f,0.4f };
	shader->setVector3("uColor", color);
	shader->setFloat("time", glfwGetTime());//���ı�����VS FS�������󶼿���ʹ�ã���Ϊvs fs�Ѿ��ϳ�Ϊ��program
	shader->setInt("sampler", 0);
	//shader->setInt("sampler", 1);
	shader->setFloat("width", texture->getWidth());
	shader->setFloat("height", texture->getHeight());
	shader->setMatrix4x4("transform", transform);
	shader->setMatrix4x4("viewMatrix", viewMatrix);
	shader->setMatrix4x4("orthoMatrix", orthoMatrix);
	shader->setMatrix4x4("perspectiveMatrix", perspectiveMatrix);
	//glBindVertexArray(vao);
	glBindVertexArray(geometry->getVao());
	//glDrawArrays(GL_TRIANGLES,0,3);//GL_TRIANGLES_STRIP/ FAN
	texture->bind();
	//modes , �����㣬���ͣ�0/ƫ��/��������
	glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);


	//doTranslateTransform();
	//shader->setMatrix4x4("transform", transform2); 
	//texture->bind();
	////modes , �����㣬���ͣ�0/ƫ��/��������
	//glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);

	//glBindVertexArray(0); //���VAO

	//�����Shader����һ��������Ҫ����
	shader->end();
}


int main() {
	if (!app->init(800, 600)) {
		return -1;
	}
	////���ü��������������С�仯����Ϣ
	app->setResizeCallback(OnResize);

	////���ü��������¼�
	app->setKeyBoardCallback(OnKey);

	//��������� �ƶ� �¼�
	app->setMouseCallback(OnMouse);
	app->setCursorCallback(OnCursor);

	//�����ӿڴ�С��������ɫ
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	prepareShader();
	prepareVAO();
	//prepareInterleavedBuffer();
	prepareTexture(); 
	prepareCamera();
	prepareOrtho();
	preparePerspective();
	//prepareState();
	//��Ⱦѭ��
	while (app->update()) {
		cameraControl->update();
		//doRotation();
		render();
	}

	app->destory();
	delete texture;
	return 0;
}