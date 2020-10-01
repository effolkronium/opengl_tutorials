#include "IRenderCreator.h"

class Scene
{
public:
	Scene(IRenderCreator& renderCreator);

	virtual void run() = 0;
private:
	IRenderCreator& m_renderCreator;
};