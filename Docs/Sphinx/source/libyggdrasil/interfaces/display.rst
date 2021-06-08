.. _DisplayInterface:

Display Interface
=================

.. note::
    The 800x480 Touch LCD Display, controlled though MIPI/DSI, in the center of the board can be used to display images, draw geometric shapes or output text. 


Simple Usage
------------

The display driver includes many functions to draw text and geometric forms onto the display. However, it's also backed by a in-memory framebuffer that can be written to directly if more complex operations are needed.

.. important::

    Due to memory constraints it's not possible to use a full RGBA8 framebuffer. Instead so called indirect colors are used. A color lookup table (palette) with 256 RGBA8 entries is loaded into hardware on initialization.
    The framebuffer then only contains single byte indexes into that LUT then. By default, a LUT is used that interprets the index as a RGB332 color. However it's possible to overwrite it with a custom one.

The following code will initialize the display and clear the screen to white.

.. tabs::

    .. code-tab:: c

        yggdrasil_Display_Init(DisplayOrientation_Portrait);
        yggdrasil_Display_Clear(Color_White);

    .. code-tab:: cpp

        using Color = bsp::drv::Color;

        bsp::Display::init();
        bsp::Display::clear(Color::White);

The following drawing functions are available:

.. tabs::

    .. code-tab:: c

        // Draw a blue rectangular frame from [100, 100] to [300, 400]
        yggdrasil_Display_DrawRectangle(100, 100, 300, 400, Color_Blue);

        // Draw a blue filled rectangle from [150, 150] to [250, 350]
        yggdrasil_Display_FillRectangle(150, 150, 250, 350, Color_Blue);

        // Draw a single yellow pixel at [50, 50]
        yggdrasil_Display_DrawPixel(50, 50, Color_Yellow);

        // Draw a maroon line from [10, 20] to [300, 60]
        yggdrasil_Display_DrawLine(10, 20, 300, 60, Color_Maroon);

        // Draw a navy circle outline at [150, 150] with radius 50
        yggdrasil_Display_DrawCircle(150, 150, 50, Color_Navy);

        // Draw a lime filled circle at [150, 150] with radius 30
        yggdrasil_Display_FillCircle(150, 150, 30, Color_Lime);

        // Draw a red "Hello World" at [200, 300] with size 16
        yggdrasil_Display_DrawString(200, 300, "Hello World", Color_Red, Font16);

    .. code-tab:: cpp

        // Draw a blue rectangular frame from [100, 100] to [300, 400]
        bsp::Display::drawRectangle(100, 100, 300, 400, Color::Blue);

        // Draw a blue filled rectangle from [150, 150] to [250, 350]
        bsp::Display::fillRectangle(150, 150, 250, 350, Color::Green);

        // Draw a single yellow pixel at [50, 50]
        bsp::Display::drawPixel(50, 50, Color::Yellow);

        // Draw a maroon line from [10, 20] to [300, 60]
        bsp::Display::drawLine(10, 20, 300, 60, Color::Maroon);

        // Draw a navy circle outline at [150, 150] with radius 50
        bsp::Display::drawCircle(150, 150, 50, Color::Navy);

        // Draw a lime filled circle at [150, 150] with radius 30
        bsp::Display::fillCircle(150, 150, 30, Color::Lime);

        // Draw a red "Hello World" at [200, 300] with size 16
        bsp::Display::drawString(200, 300, "Hello World", 0b111'000'00, Font16);


Custom Color Palette
--------------------

For some applications it's necessary to use different colors than the standard ones. For this, it's possible to change the used color lookup table.
To do this, a u32 array with 256 entries needs to be created and filled with colors. The color at array index 0 will correspond with the color drawn
when a value of 0 is written to the framebuffer.

.. tabs::

    .. code-tab:: c

        palette_t customPalette = { {
            0xFFAABBCC, 0xFFDDEEFF, /* ... */
        } };

        yggdrasil_Display_SetPalette(&customPalette);

    .. code-tab:: cpp

        constexpr bsp::drv::Palette CustomPalette = {
            0xFFAABBCC, 0xFFDDEEFF, /* ... */
        };

        bsp::Display::setPalette(CustomPalette);


Framebuffer
-----------

It's possible to implement custom drawing algorithms or draw pixels to the screen by accessing the framebuffer region in memory directly.
This is often desired when drawing computer generated images or animations where using basic geometric forms are not helpful.

.. tabs::

    .. code-tab:: c

        u8 *framebuffer = (u8*)(yggdrasil_Display_GetFrameBufferAddress());

        const auto width = yggdrasil_Display_getWidth();

        // Draw blue Pixel at [100, 200]
        framebuffer[100 + width * 200] = 0x03;

    .. code-tab:: cpp

        u8 *Framebuffer = static_cast<u8*>(bsp::Display::getFramebufferAddress());

        const auto Width = bsp::Display::getWidth();

        // Draw blue Pixel at [100, 200]
        Framebuffer[100 + Width * 200] = 0b000'000'11;