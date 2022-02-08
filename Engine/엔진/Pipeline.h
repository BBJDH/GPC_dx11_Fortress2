#pragma once

namespace Engine::Rendering::Pipeline
{
    namespace HmemDC
    {
        HDC getdc();
        void Create_hmemdc(HWND const& hWindow);
        void draw_map(HBITMAP const &hbitmap);
        void Transparents_Color(HDC const & hdc_mem, COLORREF const & transparents_color, SIZE const& size, POINT const& start);
    }
    namespace Effect
    {
        void init_buffer();
        void create_buffer();
        void Update();
        void set_alhpa(float alpha);
    }

    namespace String
    {
        void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const& size, POINT const& center);
    }

    namespace Texture
    {
        void Create(struct Handle*& handle, SIZE const& size, BYTE const* const data);
        void Render(struct Handle const* const& handle, RECT const& area);
        void Delete(struct Handle* const& handle);
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
        void Update(Matrix const& matrix);
    }
}