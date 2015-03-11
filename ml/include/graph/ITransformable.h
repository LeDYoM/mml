#pragma once

#include "TransformMatrix4.h"
#include "../mlcconfig.h"

namespace ml
{
	namespace graph
	{
		template class ML_API Vector3d<f32>;
		class ML_API ITransformable
		{
		public:

			ITransformable() :transform() {}
			virtual ~ITransformable() {}

			const TransformationMatrix getTransform() const { return transform; }
		protected:
			TransformationMatrix transform;
			Box box;
			Vector3d<f32> position = Vector3d<f32>(0.0f, 1.0f, 0.0f);
			Vector3d<f32> scale = Vector3d<f32>(1.0f, 1.0f, 1.0f);
			Vector3d<f32> rotation = Vector3d<f32>(0.0f, 0.0f, 0.0f);
		public:
			void setPosition(const Vector3d<f32> &np) { position = np; }
			void setPositionXY(const Vector2d<f32> &np) { setPosition(Vector3d<f32>(np.x, np.y, position.z)); }
			void setPositionXY(const f32 x_, const f32 y_) { setPositionXY(Vector2d<f32>(x_, y_)); }

			void setScale(const Vector3d<f32> &scale_) { scale = scale_; }
			void setScaleXY(const Vector2d<f32> &scale_) { setScale(Vector3d<f32>(scale_.x, scale_.y, scale.z)); }
			void setScaleXY(const f32 &scale_) { setScaleXY(Vector2d<f32>(scale_, scale_)); }

		};
	}
}
