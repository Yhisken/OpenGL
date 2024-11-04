#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"
Texture::Texture(const std::string& path, unsigned int unit) {
	//读取图片
	int channels;
	mUnit = unit;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);

	//生成纹理 
	glGenTextures(1, &mTexture);
	//激活
	glActiveTexture(GL_TEXTURE0+mUnit);
	//绑定
	glBindTexture(GL_TEXTURE_2D, mTexture);
	//传数据，开辟显存：插槽类型，MipLevel，存储在显存中的格式，宽高，0，传进来的格式，每个通道的数据格式
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//释放
	stbi_image_free(data);

	//设置过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//设置WrapMode：Repeat，Mirror，Clamp
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
	//先切换纹理单元，然后绑定texture对象
	glActiveTexture(GL_TEXTURE0 + mUnit);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}
