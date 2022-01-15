#include "pch.h"
#include "core.h"

#include "Layers/RenderLayer.h"

class ShaderX : public Application
{
public:
	ShaderX(int argc, char **argv)
	{
		if (argc > 1) {
			setPath(argv[1]);
		}
		push_layer(new RenderLayer());
	}

	~ShaderX()
	{
	}
};

Application *create_application(int argc, char **argv)
{
	return new ShaderX(argc, argv);
}
