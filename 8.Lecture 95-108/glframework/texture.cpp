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
	//一旦MipLevel非-时，就默认开启了Mipmap功能，要一路生成到最后
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//为当前纹理插槽自动生成Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//手动生成Mipmap层级
	//for (int level = 0; true; ++level) {
	//	glTexImage2D(GL_TEXTURE_2D,level, GL_RGBA, mWidth, mWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	if (mWidth == 1 && mHeight == 1) {
	//		break;
	//	}
	//	mWidth = mWidth > 1 ? mWidth / 2 : 1;
	//	mHeight = mHeight > 1 ? mHeight / 2 : 1;
	//}
	
	//释放
	stbi_image_free(data);

	//设置过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// GL_LINEAR/NEAREST_MIPMAP_LINEAR/NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //变小时候使用MipMap

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
