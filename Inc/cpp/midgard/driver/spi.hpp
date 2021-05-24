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
  *  @file cpp/midgard/driver/spi.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief SPI abstraction implementation for Midgard
  */

#pragma once

#include <cpp/common/frontend/spi.hpp>

#include <string>
#include <string_view>
#include <array>
extern SPI_HandleTypeDef hspi2;
namespace bsp::mid::drv {

	/**
	 * @brief SPI implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context SPI context
	 */
	template<addr_t BaseAddress>
	struct SPI {

		static bool init() {
			return true;
		}

		/**
		 * @brief SPI receive
		 *
		 * @tparam N Data size
	     * @param data Array for the read data
		 */
		template<size_t N>
		static void read(std::array<u8, N> &data) {
			u16 bytesToRead = data.size();

			FRXTH = (bytesToRead <= 1);

			if (!SPE)
				SPE = true;

			while (bytesToRead > 0) {
				u16 currOffset = data.size() - bytesToRead;
				while (!TXE);

				if (bytesToRead > 1)
					Data16 = 0x0000;
				else
					Data8 = 0x00;

				while (!RXNE);

				if (bytesToRead > 1) {
					u16 readData = Data16;
					data[currOffset] = readData >> 8;
					data[currOffset + 1] = readData & 0xFF;

					bytesToRead -= 2;

					if (bytesToRead <= 1)
						FRXTH = true;
				}
				else {
					data[currOffset] = Data8;

					bytesToRead -= 1;
				}
			}
		}

		/**
		 * @brief SPI write
		 *
		 * @tparam N Data size
	     * @param data Array to send
		 */
		template<size_t N>
		static void write(const std::array<u8, N> &data) {
			if (!SPE)
				SPE = true;

			u16 bytesToSend = data.size();

			while (bytesToSend > 0) {
				u16 currOffset = data.size() - bytesToSend;
				while (!TXE);

				if (bytesToSend > 1) {
					Data16 = data[currOffset] << 8 | data[currOffset + 1];
					bytesToSend -= 2;
				} else {
					Data8 = data[currOffset];
					bytesToSend -= 1;
				}
			}
		}


		/**
		 * @brief Set the spi mode (CPOL and CPHA)
		 *
		 * @param mode SPI mode
		 * @note This function wait until the SPI is not busy anymore and then the mode change will take place
		 */
		static void setMode(bsp::drv::SPIMode mode) {
			while(BSY);								// Wait until SPI is not busy
			CPOLCPHA = enumValue(mode);				// Set the new mode
		}

	private:

		enum class RegisterMap {
			CR1	 	= 0x00,			///< Control register 1
			CR2   	= 0x04,			///< Control register 2
			SR    	= 0x08,			///< Status register
			DR    	= 0x0C,			///< Data register
			CRCPR  	= 0x10,			///< CRC polynomial register
			RXCRCR 	= 0x14,			///< Rx CRC register
			TXCRCR 	= 0x18,			///< Tx CRC register
			I2SCFGR = 0x1C,			///< I2S configuration register
			I2SPR	= 0x20,			///< I2S prescaler register
		};

		using CR1 = Register<BaseAddress, RegisterMap::CR1, u32>;
		using CR2 = Register<BaseAddress, RegisterMap::CR2, u32>;
		using SR  = Register<BaseAddress, RegisterMap::SR , u32>;
		using DR8  = Register<BaseAddress, RegisterMap::DR , u8>;
		using DR16  = Register<BaseAddress, RegisterMap::DR , u16>;

		static inline auto CPOLCPHA	= typename CR1::template Field<0, 1>();	///< Clock polarity | Clock phase
		static inline auto SPE	= typename CR1::template Field<6, 6>();		///< SPI enable

		static inline auto FRXTH = typename CR2::template Field<12, 12>();	///< FIFO reception threshold

		static inline auto RXNE	= typename SR::template Field<0, 0>();		///< Receive buffer not empty
		static inline auto TXE 	= typename SR::template Field<1, 1>();		///< Transmit buffer empty
		static inline auto BSY 	= typename SR::template Field<7, 7>();		///< Busy flag

		static inline auto Data8 = typename DR8::template Field<0, 7>();	///< Data register
		static inline auto Data16 = typename DR16::template Field<0, 15>();		///< Data register

	};

}
