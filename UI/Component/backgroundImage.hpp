#ifndef BACKGROUNDIMAGE_HPP
#define BACKGROUNDIMAGE_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
    /// <summary>
    /// A simple static image object.
    /// </summary>
    class backgroundImage : public IObject {
    public:
        bool winflag=false;
        float sx=0;
        float dx=0;
        float scrollSpeed = 1.0f;
        int bgWidth;
        int sy,sw,sh;
        int dy,dw,dh;
        int type;
        // Smart pointer to bitmap.
        std::shared_ptr<ALLEGRO_BITMAP> bmp;
        /// <summary>
        /// Construct a image object.
        /// </summary>
        /// <param name="img">The image path in 'resources/images/'</param>
        /// <param name="x">X-coordinate.</param>
        /// <param name="y">Y-coordinate.</param>
        /// <param name="w">Width of the image, 0 indicates original size.</param>
        /// <param name="h">Height of the image, 0 indicates original size.</param>
        /// <param name="anchorX">The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.</param>
        /// <param name="anchorY">The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.</param>
        explicit backgroundImage(std::string img,int w,int h,int t);
        /// Draw the loaded image.
        /// </summary>
        void Draw() const override;
        /// <summary>
        /// Return bitmap width.
        /// </summary>
        /// <returns>Width of the original or scaled bitmap.</returns>
        int GetBitmapWidth() const;
        /// <summary>
        /// Return bitmap height.
        /// </summary>
        /// <returns>Height of the original or scaled bitmap.</returns>
        int GetBitmapHeight() const;

        void Update(float deltaTime) override;
    };
}
#endif   // backgroundImage_HPP
