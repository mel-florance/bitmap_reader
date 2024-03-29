#pragma once

#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <filesystem>

#include "buffer.h"

namespace fs = std::filesystem;

class BMP {
public:
	struct Header {
		u16 signature;
		u32 file_size;
		u32 reserved;
		u32 data_offset;

		inline friend std::ostream& operator << (
			std::ostream& stream,
			const Header& header
			) {
			stream <<
				"BMP Header:\n"   <<
				"\tSignature\t"   << header.signature << "\n" <<
				"\tFile size\t"   << human_size(header.file_size) << "\n" <<
				"\tReserved\t"    << header.reserved << "\n" <<
				"\tData offset\t" << header.data_offset << "\n";

			return stream;
		}
	};

	struct Infos {
		u32 size;
		u32 width;
		u32 height;
		u16 planes;
		u16 bit_count;
		u32 compression;
		u32 image_size;
		u32 x_ppm;
		u32 y_ppm;
		u32 colors_used;
		u32 colors_important;

		inline friend std::ostream& operator << (
			std::ostream& stream,
			const Infos& infos
			) {
			stream <<
				"BMP Infos:\n" <<
				"\tSize\t\t" << human_size(infos.size) << "\n" <<
				"\tWidth\t\t" << infos.width << "\n" <<
				"\tHeight\t\t" << infos.height << "\n" <<
				"\tPlanes\t\t" << infos.planes << "\n" <<
				"\tBit count\t" << infos.bit_count << "\n" <<
				"\tCompression\t" << infos.compression << "\n" <<
				"\tImage size\t" << human_size(infos.image_size) << "\n" <<
				"\tX ppm\t\t" << infos.x_ppm << "\n" <<
				"\tY ppm\t\t" << infos.y_ppm << "\n" <<
				"\tCol used\t" << infos.colors_used << "\n" <<
				"\tCol important\t" << infos.colors_important << "\n";

			return stream;
		}
	};

	struct Bitmap {
		Header header;
		Infos infos;
		std::vector<u8> pixels;
	};

	static std::optional<Bitmap> read(const std::string& filename);
	static bool write(const std::string& filename, const Bitmap& bitmap);

	static inline std::string human_size(size_t size) {
		char str[200];
		const char* sizes[5] = { "B", "KB", "MB", "GB", "TB" };

		int i;
		double dblByte = size;
		for (i = 0; i < 5 && size >= 1024; i++, size /= 1024)
			dblByte = size / 1024.0;

		sprintf(str, "%.2f", dblByte);

		return strcat(strcat(str, " "), sizes[i]);
	}
};