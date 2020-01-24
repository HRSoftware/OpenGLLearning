#pragma once

class PickingTexture
{
	public:
		PickingTexture();
		~PickingTexture();
		bool Init(unsigned int windowWidth, unsigned int windowHeight);
		void EnableWriting();
		void DisableWriting();

	struct PixelInfo
	{
		float ObjectID;
		float DrawID;
		float PrimID;

		PixelInfo()
		{
			ObjectID = 0.f;
			DrawID = 0.f;
			PrimID = 0.f;

		}

		
	};

	PixelInfo ReadPixel(unsigned int x, unsigned int y);
	private:
		GLuint m_fbo;
		GLuint m_pickingTexture;
		GLuint m_depthTexture;
};
