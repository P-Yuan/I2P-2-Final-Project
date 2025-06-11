#include <allegro5/allegro.h>
#include <memory>

#include "Scene/PlayScene.hpp"
#include "Engine/IObject.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "backgroundImage.hpp"

namespace Engine {
   backgroundImage::backgroundImage(std::string img,int w,int h,int t)
   :type(t)
   {
        
        bmp = Resources::GetInstance().GetBitmap(img); 
        if(type==1)
        {
            bgWidth=GetBitmapWidth();
            sx=0;sy=0;sw=bgWidth/2,sh=GetBitmapHeight();
            dx=0;dy=0;dw=w,dh=h;
        }
        else if(type==2)
        {
            bgWidth=h;
            sx=0;sy=0;sw=GetBitmapWidth(),sh=0;
            dx=0;dy=0;dw=w,dh=0;
        }
        
    }

    void backgroundImage::Draw() const 
    {
        al_draw_scaled_bitmap(bmp.get(), 
                            sx, sy, sw, sh,
                            dx, dy, dw, dh, 0);
    }


    int backgroundImage::GetBitmapWidth() const {
        return al_get_bitmap_width(bmp.get());
    }
    int backgroundImage::GetBitmapHeight() const {
        return al_get_bitmap_height(bmp.get());
    }

    void backgroundImage::Update(float deltaTime) 
    {
        if(type==1)
        {
            if (bgWidth - sx < sw || sx >= bgWidth ) 
            {
                sx = 0;
            }
            else if(winflag && bgWidth - sx < sw || sx >= bgWidth)
            {
                return;
            }
            else
            {
                sx += scrollSpeed;
            }
        }
        else if(type==2)
        {
            if(sh>bgWidth)
            {
                return;
            }
            else
            {
                sh+=scrollSpeed*4;
                dh+=scrollSpeed*4;
            }
        }
       
    };
}
