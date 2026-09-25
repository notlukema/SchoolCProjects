#include "ConsoleEngine.h"

namespace Engine
{

	CharCamera::CharCamera(const clfe::Vector3f& position, const clfe::Vector3f& rotation, float fov) : 
		position(position), rotation(rotation), fov(fov),
		near(0.1f), far(100.0f)
	{}

	clfe::Matrix4x4f CharCamera::getCameraMatrix(float width, float height) const
	{
		return getWorldMatrix() * getViewMatrix(width, height);
	}

	clfe::Matrix4x4f CharCamera::getViewMatrix(float width, float height) const
	{
		// World to -1, 1 coords
		return clfe::mfov(fov, width / height, near, far);
	}

	clfe::Matrix4x4f CharCamera::getWorldMatrix() const
	{
		clfe::Matrix4x4f viewMatrix = clfe::Matrix4x4f();
		// Apply translation
		viewMatrix = viewMatrix * clfe::mtranslate(-position.x(), -position.y(), -position.z());
		// Apply rotation
		viewMatrix = viewMatrix * clfe::mrotateY(rotation.y());
		viewMatrix = viewMatrix * clfe::mrotateX(rotation.x());
		viewMatrix = viewMatrix * clfe::mrotateZ(-rotation.z());
		return viewMatrix;
	}

}