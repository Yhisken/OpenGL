#include "geometry.h"

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
	if (mVao != 0) {
		glDeleteVertexArrays(1, &mVao);
	}
	if (mPosVbo != 0) {
		glDeleteBuffers(1, &mPosVbo);
	}
	if (mUvVbo != 0) {
		glDeleteVertexArrays(1, &mUvVbo);
	}
	if (mEbo != 0) {
		glDeleteVertexArrays(1, &mEbo);
	}
	

}

Geometry* Geometry::createBox(float size)
{
	Geometry* geometry = new Geometry();
	geometry->mIndicesCount = 36;
	float halfSize = size / 2.0f;
	float positions[] = {
		// ǰ�� (X+)
		-halfSize, -halfSize,  halfSize,
		 halfSize, -halfSize,  halfSize,
		 halfSize,  halfSize,  halfSize,
		-halfSize,  halfSize,  halfSize,

		// ���� (X-)
		-halfSize, -halfSize, -halfSize,
		-halfSize,  halfSize, -halfSize,
		 halfSize,  halfSize, -halfSize,
		 halfSize, -halfSize, -halfSize,

		 // ���� (Y+)
		 -halfSize,  halfSize, -halfSize,
		 -halfSize,  halfSize,  halfSize,
		 -halfSize, -halfSize,  halfSize,
		 -halfSize, -halfSize, -halfSize,

		 // ���� (Y-)
		  halfSize,  halfSize, -halfSize,
		  halfSize, -halfSize, -halfSize,
		  halfSize, -halfSize,  halfSize,
		  halfSize,  halfSize,  halfSize,

		  // ���� (Z+)
		  -halfSize,  halfSize,  halfSize,
		   halfSize,  halfSize,  halfSize,
		   halfSize,  halfSize, -halfSize,
		  -halfSize,  halfSize, -halfSize,

		  // ���� (Z-)
		  -halfSize, -halfSize, -halfSize,
		  -halfSize, -halfSize,  halfSize,
		   halfSize, -halfSize,  halfSize,
		   halfSize, -halfSize, -halfSize
	};

		float uvs[] = {
		// ǰ�� (X+)
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		// ���� (X-)
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		// ���� (Y+)
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		// ���� (Y-)
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		// ���� (Z+)
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		// ���� (Z-)
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f

		};

		unsigned int indices[]{
			// ǰ��
			0, 1, 2,  0, 2, 3,
			// ����
			4, 5, 6,  4, 6, 7,
			// ����
			8, 9, 10,  8, 10, 11,
			// ����
			12, 13, 14, 12, 14, 15,
			// ����
			16, 17, 18, 16, 18, 19,
			// ����
			20, 21, 22, 20, 22, 23
		};

	GLuint& posVbo = geometry->mPosVbo, uvVbo = geometry->mUvVbo;
	GLuint& Ebo = geometry->mEbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &Ebo);
	glBindBuffer(GL_ARRAY_BUFFER, Ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBindVertexArray(0);
	return geometry;
}

Geometry* Geometry::createSphere(float size)
{
	return nullptr;
}
