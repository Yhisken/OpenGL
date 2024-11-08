#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"
Texture::Texture(const std::string& path, unsigned int unit) {
	//��ȡͼƬ
	int channels;
	mUnit = unit;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);

	//�������� 
	glGenTextures(1, &mTexture);
	//����
	glActiveTexture(GL_TEXTURE0+mUnit);
	//��
	glBindTexture(GL_TEXTURE_2D, mTexture);
	//�����ݣ������Դ棺������ͣ�MipLevel���洢���Դ��еĸ�ʽ����ߣ�0���������ĸ�ʽ��ÿ��ͨ�������ݸ�ʽ
	//һ��MipLevel��-ʱ����Ĭ�Ͽ�����Mipmap���ܣ�Ҫһ·���ɵ����
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//Ϊ��ǰ�������Զ�����Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//�ֶ�����Mipmap�㼶
	//for (int level = 0; true; ++level) {
	//	glTexImage2D(GL_TEXTURE_2D,level, GL_RGBA, mWidth, mWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	if (mWidth == 1 && mHeight == 1) {
	//		break;
	//	}
	//	mWidth = mWidth > 1 ? mWidth / 2 : 1;
	//	mHeight = mHeight > 1 ? mHeight / 2 : 1;
	//}
	
	//�ͷ�
	stbi_image_free(data);

	//���ù��˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// GL_LINEAR/NEAREST_MIPMAP_LINEAR/NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //��Сʱ��ʹ��MipMap

	//����WrapMode��Repeat��Mirror��Clamp
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //U
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //V
}
Texture::~Texture() {
	if (mTexture != 0) {
		glDeleteTextures(1, &mTexture);
	}
}

void Texture::bind()
{
	//���л�����Ԫ��Ȼ���texture����
	glActiveTexture(GL_TEXTURE0 + mUnit);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}
