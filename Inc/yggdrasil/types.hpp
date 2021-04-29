#pragma once

namespace bsp::ygg {

	union RGBA8 {
		struct {
			u8 r, g, b, a;
		};
		u32 rgba;
	};

	struct RGBA16 {
		struct {
			u16 r, g, b, a;
		};
		u64 rgba;
	};

}
