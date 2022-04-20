#include "c2C02.h"

c2C02::c2C02()
{
	palScreen[0x00] = olc::Pixel(84, 84, 84);
	palScreen[0x01] = olc::Pixel(0, 30, 116);
	palScreen[0x02] = olc::Pixel(8, 16, 144);
	palScreen[0x03] = olc::Pixel(48, 0, 136);
	palScreen[0x04] = olc::Pixel(68, 0, 100);
	palScreen[0x05] = olc::Pixel(92, 0, 48);
	palScreen[0x06] = olc::Pixel(84, 4, 0);
	palScreen[0x07] = olc::Pixel(60, 24, 0);
	palScreen[0x08] = olc::Pixel(32, 42, 0);
	palScreen[0x09] = olc::Pixel(8, 58, 0);
	palScreen[0x0A] = olc::Pixel(0, 64, 0);
	palScreen[0x0B] = olc::Pixel(0, 60, 0);
	palScreen[0x0C] = olc::Pixel(0, 50, 60);
	palScreen[0x0D] = olc::Pixel(0, 0, 0);
	palScreen[0x0E] = olc::Pixel(0, 0, 0);
	palScreen[0x0F] = olc::Pixel(0, 0, 0);

	palScreen[0x10] = olc::Pixel(152, 150, 152);
	palScreen[0x11] = olc::Pixel(8, 76, 196);
	palScreen[0x12] = olc::Pixel(48, 50, 236);
	palScreen[0x13] = olc::Pixel(92, 30, 228);
	palScreen[0x14] = olc::Pixel(136, 20, 176);
	palScreen[0x15] = olc::Pixel(160, 20, 100);
	palScreen[0x16] = olc::Pixel(152, 34, 32);
	palScreen[0x17] = olc::Pixel(120, 60, 0);
	palScreen[0x18] = olc::Pixel(84, 90, 0);
	palScreen[0x19] = olc::Pixel(40, 114, 0);
	palScreen[0x1A] = olc::Pixel(8, 124, 0);
	palScreen[0x1B] = olc::Pixel(0, 118, 40);
	palScreen[0x1C] = olc::Pixel(0, 102, 120);
	palScreen[0x1D] = olc::Pixel(0, 0, 0);
	palScreen[0x1E] = olc::Pixel(0, 0, 0);
	palScreen[0x1F] = olc::Pixel(0, 0, 0);

	palScreen[0x20] = olc::Pixel(236, 238, 236);
	palScreen[0x21] = olc::Pixel(76, 154, 236);
	palScreen[0x22] = olc::Pixel(120, 124, 236);
	palScreen[0x23] = olc::Pixel(176, 98, 236);
	palScreen[0x24] = olc::Pixel(228, 84, 236);
	palScreen[0x25] = olc::Pixel(236, 88, 180);
	palScreen[0x26] = olc::Pixel(236, 106, 100);
	palScreen[0x27] = olc::Pixel(212, 136, 32);
	palScreen[0x28] = olc::Pixel(160, 170, 0);
	palScreen[0x29] = olc::Pixel(116, 196, 0);
	palScreen[0x2A] = olc::Pixel(76, 208, 32);
	palScreen[0x2B] = olc::Pixel(56, 204, 108);
	palScreen[0x2C] = olc::Pixel(56, 180, 204);
	palScreen[0x2D] = olc::Pixel(60, 60, 60);
	palScreen[0x2E] = olc::Pixel(0, 0, 0);
	palScreen[0x2F] = olc::Pixel(0, 0, 0);

	palScreen[0x30] = olc::Pixel(236, 238, 236);
	palScreen[0x31] = olc::Pixel(168, 204, 236);
	palScreen[0x32] = olc::Pixel(188, 188, 236);
	palScreen[0x33] = olc::Pixel(212, 178, 236);
	palScreen[0x34] = olc::Pixel(236, 174, 236);
	palScreen[0x35] = olc::Pixel(236, 174, 212);
	palScreen[0x36] = olc::Pixel(236, 180, 176);
	palScreen[0x37] = olc::Pixel(228, 196, 144);
	palScreen[0x38] = olc::Pixel(204, 210, 120);
	palScreen[0x39] = olc::Pixel(180, 222, 120);
	palScreen[0x3A] = olc::Pixel(168, 226, 144);
	palScreen[0x3B] = olc::Pixel(152, 226, 180);
	palScreen[0x3C] = olc::Pixel(160, 214, 228);
	palScreen[0x3D] = olc::Pixel(160, 162, 160);
	palScreen[0x3E] = olc::Pixel(0, 0, 0);
	palScreen[0x3F] = olc::Pixel(0, 0, 0);
}

c2C02::~c2C02()
{

}


olc::Sprite& c2C02::GetScreen()
{
	return sprScreen;
}

olc::Sprite& c2C02::GetNameTable(uint8_t i)
{
	return sprNameTable[i];
}

olc::Sprite& c2C02::GetPatternTable(uint8_t i, uint8_t palette)
{
	for (uint16_t nTileY = 0; nTileY < 16; nTileY++)
	{
		for (uint16_t nTileX = 0; nTileX < 16; nTileX++)
		{
			uint16_t nOffset = nTileY * 256 + nTileX * 16;

			for (uint16_t row = 0; row < 8; row++)
			{
				uint8_t tile_lsb = ppuRead(i * 0x1000 + nOffset + row + 0x0000);
				uint8_t tile_msb = ppuRead(i * 0x1000 + nOffset + row + 0x0008);
				for (uint16_t col = 0; col < 8; col++)
				{
					uint8_t pixel = (tile_lsb & 0x01) + (tile_msb & 0x01);
					tile_lsb >>= 1;
					tile_msb >>= 1;

					sprPatternTable[i].SetPixel(nTileX * 8 + (7 - col), nTileY * 8 + row, GetColorFromPallete(palette, pixel));
				}
			}
		}

	}
	return sprPatternTable[i];
}

olc::Pixel& c2C02::GetColorFromPallete(uint8_t palette, uint8_t pixel)
{
	return palScreen[ppuRead(0x3F00 + (palette << 2) + pixel)];
}

uint8_t c2C02::cpuRead(uint16_t address, bool readonly)
{
	uint8_t data = 0x00;
	
	switch (address)
	{
	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);
		status.vertical_blank = 0;
		address_latch = 0x00;
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		data = ppu_data_buffer;
		ppu_data_buffer = ppuRead(ppu_address);

		if (ppu_address > 0x3F00) data = ppu_data_buffer;
		ppu_address++;
		break;
	}

	return data;
}

void c2C02::cpuWrite(uint16_t address, uint8_t data)
{
	switch (address)
	{
	case 0x0000: // Control
		control.reg = data;
		break;
	case 0x0001: // Mask
		mask.reg = data;
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		if (address_latch == 0x00)
		{
			ppu_address = (ppu_address & 0x00FF) | (data << 8);
			address_latch = 0x01;
		}
		else
		{
			ppu_address = (ppu_address & 0xFF00) | data;
			address_latch = 0x00;
		}
		break;
	case 0x0007: // PPU Data
		ppuWrite(ppu_address, data);
		ppu_address++;
		break;
	}

}

uint8_t c2C02::ppuRead(uint16_t address, bool readonly)
{
	uint8_t data = 0x00;
	address &= 0x3FFF;

	if (cartridge->ppuRead(address, data))
	{

	}
	else if (address >= 0x0000 && address <= 0x1FFF)
	{
		data = PatternTable[(address & 0x1000) >> 12][address & 0x0FFF];
	}
	else if (address >= 0x2000 && address <= 0x3EFF)
	{
		if (cartridge->mirror == Cartridge::MIRROR::VERTICAL)
		{
			if (address >= 0x0000 && address <= 0x03FF)
				data = NameTable[0][address & 0x03FF];
			if (address >= 0x0400 && address <= 0x07FF)
				data = NameTable[1][address & 0x03FF];
			if (address >= 0x0800 && address <= 0x0BFF)
				data = NameTable[0][address & 0x03FF];
			if (address >= 0x0C00 && address <= 0x0FFF)
				data = NameTable[1][address & 0x03FF];
		}
		else if (cartridge->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal
			if (address >= 0x0000 && address <= 0x03FF)
				data = NameTable[0][address & 0x03FF];
			if (address >= 0x0400 && address <= 0x07FF)
				data = NameTable[0][address & 0x03FF];
			if (address >= 0x0800 && address <= 0x0BFF)
				data = NameTable[1][address & 0x03FF];
			if (address >= 0x0C00 && address <= 0x0FFF)
				data = NameTable[1][address & 0x03FF];
		}
	}
	else if (address >= 0x3F00 && address <= 0x3FFF)
	{
		address &= 0x001F;
		if (address == 0x0010)
		{
			address = 0x0000;
		}
		if (address == 0x0014)
		{
			address = 0x0004;
		}
		if (address == 0x0018)
		{
			address = 0x0008;
		}
		if (address == 0x001C)
		{
			address = 0x000C;
		}

		data = PaletteTable[address];
	}

	return data;
}

void c2C02::ppuWrite(uint16_t address, uint8_t data)
{
	address &= 0x3FFF;
	if (cartridge->ppuWrite(address, data))
	{

	}
	else if (address >= 0x0000 && address <= 0x1FFF)
	{
		PatternTable[(address & 0x1000) >> 12][address & 0x0FFF] = data;
	}
	else if (address >= 0x2000 && address <= 0x3EFF)
	{
		if (cartridge->mirror == Cartridge::MIRROR::VERTICAL)
		{
			if (address >= 0x0000 && address <= 0x03FF)
				NameTable[0][address & 0x03FF] = data;
			if (address >= 0x0400 && address <= 0x07FF)
				NameTable[1][address & 0x03FF] = data;
			if (address >= 0x0800 && address <= 0x0BFF)
				NameTable[0][address & 0x03FF] = data;
			if (address >= 0x0C00 && address <= 0x0FFF)
				NameTable[1][address & 0x03FF] = data;
		}
		else if (cartridge->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal
			if (address >= 0x0000 && address <= 0x03FF)
				NameTable[0][address & 0x03FF] = data;
			if (address >= 0x0400 && address <= 0x07FF)
				NameTable[0][address & 0x03FF] = data;
			if (address >= 0x0800 && address <= 0x0BFF)
				NameTable[1][address & 0x03FF] = data;
			if (address >= 0x0C00 && address <= 0x0FFF)
				NameTable[1][address & 0x03FF] = data;
		}
	}
	else if (address >= 0x3F00 && address <= 0x3FFF)
	{
		address &= 0x001F;
		if (address == 0x0010)
		{
			address = 0x0000;
		}
		if (address == 0x0014)
		{
			address = 0x0004;
		}
		if (address == 0x0018)
		{
			address = 0x0008;
		}
		if (address == 0x001C)
		{
			address = 0x000C;
		}

		PaletteTable[address] = data;
	}
}

void c2C02::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cartridge = cartridge;
}
void c2C02::clock()
{
	if (scanline == -1 && cycle == 1)
	{
		status.vertical_blank = 0;
	}

	if (scanline == 241 && cycle == 1)
	{
		status.vertical_blank = 1;
		if (control.enable_nmi)
			nmi = true;
	}
	//sprScreen.SetPixel(cycle - 1, scanline, palScreen[(rand() % 2) ? 0x3F: 0x30]);
	cycle++;

	if (cycle >= 341)
	{
		cycle = 0;
		scanline++;

		if (scanline >= 261)
		{
			scanline = -1;
			frame_complete = true;
		}
	}
}