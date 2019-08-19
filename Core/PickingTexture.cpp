#include "PickingTextures.h"
#include <cstdio>

bool PickingTexture::Init(unsigned windowWidth, unsigned windowHeight)
{
	// Create the FBO
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// Create the texture object for the primitive information buffer
	glGenTextures(1, &m_pickingTexture);
	glBindTexture(GL_TEXTURE_2D, m_pickingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowWidth, windowHeight,
		0, GL_RGB, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		m_pickingTexture, 0);

	// Create the texture object for the depth buffer
	glGenTextures(1, &m_depthTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, windowWidth, windowHeight,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
		m_depthTexture, 0);

	// Disable reading to avoid problems with older GPUs
	glReadBuffer(GL_NONE);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	// Verify that the FBO is correct
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}

	// Restore the default framebuffer
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return glGetError();
}

void PickingTexture::EnableWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
} 

void PickingTexture::DisableWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

PickingTexture::PixelInfo PickingTexture::ReadPixel(unsigned int x, unsigned int y)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	PixelInfo Pixel;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &Pixel);

	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	return Pixel;
}
