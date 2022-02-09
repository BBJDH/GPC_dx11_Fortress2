#pragma once

namespace Engine::Rendering::Pipeline
{
    namespace HmemDC
    {
        HDC getdc();
        void Create_hmemdc(HWND const& hWindow);
        void draw_map(HBITMAP const &hbitmap);
        void Render_map(HDC const & hdc_mem, COLORREF const & transparents_color,
            POINT const& dest,  POINT const& bring_start, SIZE const& size);
        void Render_minimap(HDC const & hdc_mem, COLORREF const & transparents_color,
            POINT const& dest, SIZE const& size, unsigned const alpha);

    }
    namespace Effect
    {
        void init_buffer();
        void create_buffer();
        void Update();
        void set_alhpa(float alpha);
        void set_y(float y);
    }

    namespace String
    {
        void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const & size, POINT const & center);
    }

    namespace Texture
    {
        void Create(struct Handle       *       & handle, SIZE const & size, BYTE const * const data);
        void Render(struct Handle const * const & handle, RECT const & area);
        void Delete(struct Handle       * const & handle);
    }

    namespace Transform
    {
        enum class Type
        {
            World,
            View,
            Projection
        };

        using Matrix = float[4][4];

        template<Type type>
        void Update(Matrix const & matrix);
    }
}