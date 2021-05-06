#pragma once

namespace bsp::ygg {

	/**
	 * @brief RGBA8 color type
	 */
	union RGBA8 {
		struct {
			u8 r, g, b, a;
		};
		u32 rgba;
	};

	/**
	 * @brief RGBA16 color type
	 */
	struct RGBA16 {
		struct {
			u16 r, g, b, a;
		};
		u64 rgba;
	};

}
