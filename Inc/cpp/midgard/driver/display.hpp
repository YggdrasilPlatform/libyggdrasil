 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
  *  @file cpp/midgard/driver/display.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Display abstraction implementation for Midgard
  */

#pragma once

#include <cpp/midgard/core/cortex.hpp>
#include <cpp/midgard/driver/gpio.hpp>
#include <cpp/common/frontend/display.hpp>

#include <cpp/midgard/st/otm8009a.h>

#include <cmath>

namespace bsp::mid::drv {

	template<auto Context>
	struct Display {
		Display(const Display&) = delete;

		enum class Orientation {
			Portrait	= 0x00,
			Landscape	= 0x01
		};


		/*
		 * @brief Display initialization
		 *
		 * @param orientation Display orientation
		 * @return True when successful, false when not
		 */
		static bool init(Orientation orientation = Orientation::Portrait) noexcept {
			auto [hltdc, hdsi, hdma2d] = Context;

			DSI_PLLInitTypeDef dsiPllInit;
			static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
			uint32_t LcdClock  = 27429; /*!< LcdClk = 27429 kHz */

			u32 laneByteClk_kHz = 0;
			u32 VSA, VBP, VFP, VACT, HSA, HBP, HFP, HACT;

			Display::reset();

			HAL_NVIC_DisableIRQ(LTDC_IRQn);
			HAL_NVIC_DisableIRQ(DMA2D_IRQn);
			HAL_NVIC_DisableIRQ(DSI_IRQn);

			__HAL_RCC_LTDC_FORCE_RESET();
			__HAL_RCC_DMA2D_FORCE_RESET();
			__HAL_RCC_DSI_FORCE_RESET();

			__HAL_RCC_LTDC_CLK_DISABLE();
			__HAL_RCC_DMA2D_CLK_DISABLE();
			__HAL_RCC_DSI_CLK_DISABLE();

			__HAL_RCC_LTDC_CLK_ENABLE();
			__HAL_RCC_LTDC_FORCE_RESET();
			__HAL_RCC_LTDC_RELEASE_RESET();

			__HAL_RCC_DMA2D_CLK_ENABLE();
			__HAL_RCC_DMA2D_FORCE_RESET();
			__HAL_RCC_DMA2D_RELEASE_RESET();

			__HAL_RCC_DSI_CLK_ENABLE();
			__HAL_RCC_DSI_FORCE_RESET();
			__HAL_RCC_DSI_RELEASE_RESET();

			HAL_NVIC_SetPriority(LTDC_IRQn, 0x0F, 0);
			HAL_NVIC_EnableIRQ(LTDC_IRQn);
			HAL_NVIC_SetPriority(DMA2D_IRQn, 0x0F, 0);
			HAL_NVIC_EnableIRQ(DMA2D_IRQn);
			HAL_NVIC_SetPriority(DSI_IRQn, 0x0F, 0);
			HAL_NVIC_EnableIRQ(DSI_IRQn);

			hdsi->Instance = DSI;

			HAL_DSI_DeInit(hdsi);

			dsiPllInit.PLLNDIV  = 100;
			dsiPllInit.PLLIDF   = DSI_PLL_IN_DIV5;
			dsiPllInit.PLLODF  = DSI_PLL_OUT_DIV1;
			laneByteClk_kHz = 62500;

			hdsi->Init.NumberOfLanes = DSI_TWO_DATA_LANES;

			hdsi->Init.TXEscapeCkdiv = laneByteClk_kHz/15620;

			HAL_DSI_Init(hdsi, &dsiPllInit);

			if(orientation == Orientation::Portrait) {
				Display::s_xSize = OTM8009A_480X800_WIDTH;
				Display::s_ySize = OTM8009A_480X800_HEIGHT;
			}
			else {
				Display::s_xSize = OTM8009A_800X480_WIDTH;
				Display::s_ySize = OTM8009A_800X480_HEIGHT;
			}

			HACT = Display::s_xSize;
			VACT = Display::s_ySize;

			VSA  = OTM8009A_480X800_VSYNC;
			VBP  = OTM8009A_480X800_VBP;
			VFP  = OTM8009A_480X800_VFP;
			HSA  = OTM8009A_480X800_HSYNC;
			HBP  = OTM8009A_480X800_HBP;
			HFP  = OTM8009A_480X800_HFP;

			Display::s_hdsiVideo.VirtualChannelID = 0;
			Display::s_hdsiVideo.ColorCoding = DSI_RGB888;
			Display::s_hdsiVideo.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
			Display::s_hdsiVideo.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
			Display::s_hdsiVideo.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
			Display::s_hdsiVideo.Mode = DSI_VID_MODE_BURST;
			Display::s_hdsiVideo.NullPacketSize = 0xFFF;
			Display::s_hdsiVideo.NumberOfChunks = 0;
			Display::s_hdsiVideo.PacketSize                = HACT;
			Display::s_hdsiVideo.HorizontalSyncActive = (HSA * laneByteClk_kHz)/LcdClock;
			Display::s_hdsiVideo.HorizontalBackPorch = (HBP * laneByteClk_kHz)/LcdClock;
			Display::s_hdsiVideo.HorizontalLine = ((HACT + HSA + HBP + HFP) * laneByteClk_kHz)/LcdClock;
			Display::s_hdsiVideo.VerticalSyncActive        = VSA;
			Display::s_hdsiVideo.VerticalBackPorch         = VBP;
			Display::s_hdsiVideo.VerticalFrontPorch        = VFP;
			Display::s_hdsiVideo.VerticalActive            = VACT;

			Display::s_hdsiVideo.LPCommandEnable = DSI_LP_COMMAND_ENABLE;

			Display::s_hdsiVideo.LPLargestPacketSize = 16;

			Display::s_hdsiVideo.LPVACTLargestPacketSize = 0;

			Display::s_hdsiVideo.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE;
			Display::s_hdsiVideo.LPHorizontalBackPorchEnable  = DSI_LP_HBP_ENABLE;
			Display::s_hdsiVideo.LPVerticalActiveEnable = DSI_LP_VACT_ENABLE;
			Display::s_hdsiVideo.LPVerticalFrontPorchEnable = DSI_LP_VFP_ENABLE;
			Display::s_hdsiVideo.LPVerticalBackPorchEnable = DSI_LP_VBP_ENABLE;
			Display::s_hdsiVideo.LPVerticalSyncActiveEnable = DSI_LP_VSYNC_ENABLE;

			HAL_DSI_ConfigVideoMode(hdsi, &Display::s_hdsiVideo);

			hltdc->Init.HorizontalSync = (HSA - 1);
			hltdc->Init.AccumulatedHBP = (HSA + HBP - 1);
			hltdc->Init.AccumulatedActiveW = (Display::s_xSize + HSA + HBP - 1);
			hltdc->Init.TotalWidth = (Display::s_ySize + HSA + HBP + HFP - 1);

			hltdc->LayerCfg->ImageWidth  = Display::s_xSize;
			hltdc->LayerCfg->ImageHeight = Display::s_ySize;

			PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
			PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
			PeriphClkInitStruct.PLLSAI.PLLSAIR = 7;
			PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
			HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

			hltdc->Init.Backcolor.Blue = 0;
			hltdc->Init.Backcolor.Green = 0;
			hltdc->Init.Backcolor.Red = 0;
			hltdc->Init.PCPolarity = LTDC_PCPOLARITY_IPC;
			hltdc->Instance = LTDC;

			HAL_LTDC_StructInitFromVideoConfig(hltdc, &Display::s_hdsiVideo);
			HAL_LTDC_Init(hltdc);

			HAL_DSI_Start(hdsi);

			OTM8009A_Init(OTM8009A_FORMAT_RGB888, enumValue(orientation));

		    LTDC_LayerCfgTypeDef layerCfg;

		    layerCfg.WindowX0 = 0;
		    layerCfg.WindowX1 = Display::getWidth();
		    layerCfg.WindowY0 = 0;
		    layerCfg.WindowY1 = Display::getHeight();
		    layerCfg.PixelFormat = LTDC_PIXEL_FORMAT_L8;
		    layerCfg.FBStartAdress = Display::FramebufferAddress;
		    layerCfg.Alpha = 255;
		    layerCfg.Alpha0 = 0;
		    layerCfg.Backcolor.Blue = 0;
		    layerCfg.Backcolor.Green = 0;
		    layerCfg.Backcolor.Red = 0;
		    layerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
		    layerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
		    layerCfg.ImageWidth = Display::getWidth();
		    layerCfg.ImageHeight = Display::getHeight();

			HAL_LTDC_ConfigLayer(hltdc, &layerCfg, 0);
			HAL_LTDC_EnableCLUT(hltdc, 0);

			Display::setPalette(Display::getDefaultPalette());

			Display::turnOn();

			return true;
		}

		/*
		 * @brief Display reset
		 */
		static void reset() noexcept {
			using GPIOPortD = bsp::drv::GPIOPort<0x4002'0C00, bsp::mid::drv::GPIOPort>;
			constexpr auto& DisplayReset = GPIOPortD::Pin<11, bsp::drv::Active::Low>;

			DisplayReset = true;
			core::delay(20);
			DisplayReset = false;
			core::delay(10);
		}

		/*
		 * @brief Enable the display
		 */
		static void turnOn() noexcept {
			const auto [hltdc, hdsi, hdma2d] = Context;

		    HAL_DSI_ShortWrite(hdsi, Display::s_hdsiVideo.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, OTM8009A_CMD_DISPON, 0x00);
		}

		/*
		 * @brief Disable the display
		 */
		static void turnOff() noexcept {
			const auto [hltdc, hdsi, hdma2d] = Context;

		    HAL_DSI_ShortWrite(hdsi, Display::s_hdsiVideo.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, OTM8009A_CMD_DISPOFF, 0x00);
		}

		/*
		 * @brief Get the display width
		 *
		 * @return display width
		 */
		static inline u16 getWidth() {
			return Display::s_xSize;
		}

		/*
		 * @brief Get the display height
		 *
		 * @return display height
		 */
		static inline u16 getHeight() {
			return Display::s_ySize;
		}

		/*
		 * @brief Set the color palette
		 *
		 * @param palettet Color palette
		 */
		static inline void setPalette(const std::array<u32, 256> &palette) {
			const auto [hltdc, hdsi, hdma2d] = Context;

			HAL_LTDC_ConfigCLUT(hltdc, const_cast<u32*>(palette.data()), palette.size(), 0);
		}

		/*
		 * @brief Get the default color palette
		 *
		 * @return Default color palette
		 */
		static std::array<u32, 256> getDefaultPalette() {
			return std::array<u32, 256> {
				0xFF000000, 0xFF00004E, 0xFF00009C, 0xFF0000EA, 0xFF002400, 0xFF00244E, 0xFF00249C, 0xFF0024EA, 0xFF004800, 0xFF00484E, 0xFF00489C, 0xFF0048EA, 0xFF006C00, 0xFF006C4E, 0xFF006C9C, 0xFF006CEA, 0xFF009000, 0xFF00904E, 0xFF00909C, 0xFF0090EA, 0xFF00B400, 0xFF00B44E, 0xFF00B49C, 0xFF00B4EA, 0xFF00D800, 0xFF00D84E, 0xFF00D89C, 0xFF00D8EA, 0xFF00FC00, 0xFF00FC4E, 0xFF00FC9C, 0xFF00FCEA, 0xFF240000, 0xFF24004E, 0xFF24009C, 0xFF2400EA, 0xFF242400, 0xFF24244E, 0xFF24249C, 0xFF2424EA, 0xFF244800, 0xFF24484E, 0xFF24489C, 0xFF2448EA, 0xFF246C00, 0xFF246C4E, 0xFF246C9C, 0xFF246CEA, 0xFF249000, 0xFF24904E, 0xFF24909C, 0xFF2490EA, 0xFF24B400, 0xFF24B44E, 0xFF24B49C, 0xFF24B4EA, 0xFF24D800, 0xFF24D84E, 0xFF24D89C, 0xFF24D8EA, 0xFF24FC00, 0xFF24FC4E, 0xFF24FC9C, 0xFF24FCEA, 0xFF480000, 0xFF48004E, 0xFF48009C, 0xFF4800EA, 0xFF482400, 0xFF48244E, 0xFF48249C, 0xFF4824EA, 0xFF484800, 0xFF48484E, 0xFF48489C, 0xFF4848EA, 0xFF486C00, 0xFF486C4E, 0xFF486C9C, 0xFF486CEA, 0xFF489000, 0xFF48904E, 0xFF48909C, 0xFF4890EA, 0xFF48B400, 0xFF48B44E, 0xFF48B49C, 0xFF48B4EA, 0xFF48D800, 0xFF48D84E, 0xFF48D89C, 0xFF48D8EA, 0xFF48FC00, 0xFF48FC4E, 0xFF48FC9C, 0xFF48FCEA, 0xFF6C0000, 0xFF6C004E, 0xFF6C009C, 0xFF6C00EA, 0xFF6C2400, 0xFF6C244E, 0xFF6C249C, 0xFF6C24EA, 0xFF6C4800, 0xFF6C484E, 0xFF6C489C, 0xFF6C48EA, 0xFF6C6C00, 0xFF6C6C4E, 0xFF6C6C9C, 0xFF6C6CEA, 0xFF6C9000, 0xFF6C904E, 0xFF6C909C, 0xFF6C90EA, 0xFF6CB400, 0xFF6CB44E, 0xFF6CB49C, 0xFF6CB4EA, 0xFF6CD800, 0xFF6CD84E, 0xFF6CD89C, 0xFF6CD8EA, 0xFF6CFC00, 0xFF6CFC4E, 0xFF6CFC9C, 0xFF6CFCEA, 0xFF900000, 0xFF90004E, 0xFF90009C, 0xFF9000EA, 0xFF902400, 0xFF90244E, 0xFF90249C, 0xFF9024EA, 0xFF904800, 0xFF90484E, 0xFF90489C, 0xFF9048EA, 0xFF906C00, 0xFF906C4E, 0xFF906C9C, 0xFF906CEA, 0xFF909000, 0xFF90904E, 0xFF90909C, 0xFF9090EA, 0xFF90B400, 0xFF90B44E, 0xFF90B49C, 0xFF90B4EA, 0xFF90D800, 0xFF90D84E, 0xFF90D89C, 0xFF90D8EA, 0xFF90FC00, 0xFF90FC4E, 0xFF90FC9C, 0xFF90FCEA, 0xFFB40000, 0xFFB4004E, 0xFFB4009C, 0xFFB400EA, 0xFFB42400, 0xFFB4244E, 0xFFB4249C, 0xFFB424EA, 0xFFB44800, 0xFFB4484E, 0xFFB4489C, 0xFFB448EA, 0xFFB46C00, 0xFFB46C4E, 0xFFB46C9C, 0xFFB46CEA, 0xFFB49000, 0xFFB4904E, 0xFFB4909C, 0xFFB490EA, 0xFFB4B400, 0xFFB4B44E, 0xFFB4B49C, 0xFFB4B4EA, 0xFFB4D800, 0xFFB4D84E, 0xFFB4D89C, 0xFFB4D8EA, 0xFFB4FC00, 0xFFB4FC4E, 0xFFB4FC9C, 0xFFB4FCEA, 0xFFD80000, 0xFFD8004E, 0xFFD8009C, 0xFFD800EA, 0xFFD82400, 0xFFD8244E, 0xFFD8249C, 0xFFD824EA, 0xFFD84800, 0xFFD8484E, 0xFFD8489C, 0xFFD848EA, 0xFFD86C00, 0xFFD86C4E, 0xFFD86C9C, 0xFFD86CEA, 0xFFD89000, 0xFFD8904E, 0xFFD8909C, 0xFFD890EA, 0xFFD8B400, 0xFFD8B44E, 0xFFD8B49C, 0xFFD8B4EA, 0xFFD8D800, 0xFFD8D84E, 0xFFD8D89C, 0xFFD8D8EA, 0xFFD8FC00, 0xFFD8FC4E, 0xFFD8FC9C, 0xFFD8FCEA, 0xFFFC0000, 0xFFFC004E, 0xFFFC009C, 0xFFFC00EA, 0xFFFC2400, 0xFFFC244E, 0xFFFC249C, 0xFFFC24EA, 0xFFFC4800, 0xFFFC484E, 0xFFFC489C, 0xFFFC48EA, 0xFFFC6C00, 0xFFFC6C4E, 0xFFFC6C9C, 0xFFFC6CEA, 0xFFFC9000, 0xFFFC904E, 0xFFFC909C, 0xFFFC90EA, 0xFFFCB400, 0xFFFCB44E, 0xFFFCB49C, 0xFFFCB4EA, 0xFFFCD800, 0xFFFCD84E, 0xFFFCD89C, 0xFFFCD8EA, 0xFFFCFC00, 0xFFFCFC4E, 0xFFFCFC9C, 0xFFFCFCEA,
			};
		}

		/*
		 * @brief Get the framebuffer address
		 *
		 * @return framebuffer address
		 */
		ALWAYS_INLINE static void* getFramebufferAddress() {
			return reinterpret_cast<void*>(FramebufferAddress);
		}

		/*
		 * @brief Set a Pixel
		 *
		 * @param x X coordinate
		 * @param y Y coordinate
		 * @param paletteIndex Index for the color
		 */
		ALWAYS_INLINE static void setPixel(u16 x, u16 y, u8 paletteIndex) {
			reinterpret_cast<u8*>(FramebufferAddress)[y * Display::s_xSize + x] = paletteIndex;
		}

		/**
		 * @brief Clear the display to a color
		 *
		 * @param paletteIndex Index for the color
		 */
		ALWAYS_INLINE static void clear(u8 paletteIndex) {
			const auto [hltdc, hdsi, hdma2d] = Context;

			hdma2d->Init.Mode         = DMA2D_R2M;
			hdma2d->Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
			hdma2d->Init.OutputOffset = 0;
			hdma2d->Instance = DMA2D;

			if(HAL_DMA2D_Init(hdma2d) == HAL_OK) {
				if(HAL_DMA2D_ConfigLayer(hdma2d, 0) == HAL_OK) {
					if (HAL_DMA2D_Start(hdma2d, paletteIndex << 24 | paletteIndex << 16 | paletteIndex << 8 | paletteIndex, FramebufferAddress, Display::s_xSize / 4, Display::s_ySize) == HAL_OK) {

						HAL_DMA2D_PollForTransfer(hdma2d, 10);
					}
			    }
			}
		}

	private:
		Display() = default;

		constexpr static u32 FramebufferAddress = 0x2002'0000;

		static inline u16 s_xSize, s_ySize;
		static inline DSI_VidCfgTypeDef s_hdsiVideo;

		/**
		 * @brief Declare Display frontend as friend
		 */
		template<auto, template<auto> typename>
		friend struct bsp::drv::Display;
	};

}
