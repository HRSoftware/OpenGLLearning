#pragma once
class IRenderCallbacks
{
	public:
		virtual void DrawStartCB(unsigned int DrawIndex) = 0;
};