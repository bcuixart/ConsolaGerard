#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void usage()
{
	printf("Bro wtf\n");
	printf("Usage: ./bitmap_generator <input_file> <struct_name>\n");
	exit(1);
}

void error(const char* message)
{
	perror(message);
	exit(1);
}

/*
// const struct Bitmap 
{
	uint8_t width;
	uint8_t height;
	uint16_t palette[16];
	uint16_t data_size;
	uint8_t* data;
}
*/

void get_palette(unsigned char* data, int width, int height, uint16_t* palette)
{
	unsigned int cursor = 0;
	for (int i = 0; i < width * height * 3; i += 3)
	{
		uint8_t r = data[i];
		uint8_t g = data[i + 1];
		uint8_t b = data[i + 2];
		uint16_t color = (r >> 3) << 11 | (g >> 2) << 5 | (b >> 3);

		int found = 0;
		for (int j = 0; j < cursor; j++) found |= palette[j] == color;

		if (found) continue;

		palette[cursor] = color;
		cursor++;
		if (cursor > 16) error("Too many colors in the image. Max is 16.");
	}
}

void get_data(unsigned char* data, int width, int height, uint16_t* palette, uint8_t* data_pointer, unsigned int* data_size)
{
	unsigned i = 0;
	while (i < width * height * 3)
	{
		uint8_t r = data[i];
		uint8_t g = data[i + 1];
		uint8_t b = data[i + 2];
		uint16_t color = (r >> 3) << 11 | (g >> 2) << 5 | (b >> 3);

		unsigned int j = 0;
		for (j = 0; j < 16; j++) if (palette[j] == color) break; // trobem j
		if (j == 16) error("Color not found in palette. Si arribem aquí, get_palette ha fallat.");

		uint8_t count = 1;
		while (i + count*3 < width * height * 3 && count < 16)
		{
			unsigned int cursor = i + count * 3;
			uint8_t r2 = data[cursor];
			uint8_t g2 = data[cursor+1];
			uint8_t b2 = data[cursor+2];
			uint16_t color2 = (r2 >> 3) << 11 | (g2 >> 2) << 5 | (b2 >> 3);
			if (color != color2) break;
			count++;
		}
		i += count*3;
		if (count > 16) error("Run length exceeds 16. Si arribem aquí, el for de dalt has bounds incorrectes.");

		*data_pointer++ = (j << 4) | (count - 1);
		(*data_size)++;
	}
}

void generate_bitmap(const char* struct_name, int width, int height, unsigned char* data)
{
	printf("const struct Bitmap PROGMEM %s = \n{\n", struct_name);
	printf("\twidth = %d,\n", width);
	printf("\theight = %d,\n", height);
	printf("\tpalette = { ");

	// Palette
	uint16_t palette[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	get_palette(data, width, height, palette);
	for (int i = 0; i < 16; i++)
	{
		printf("0x%04X%s", palette[i], (i < 15) ? ", " : "");
	}
	printf("},\n");

	// Data
	uint8_t output[width * height];
	unsigned int data_size = 0;
	get_data(data, width, height, palette, output, &data_size);

	printf("\tdata_size = %d,\n", data_size);
	printf("\tdata = {\n");

	for (unsigned int i = 0; i < data_size; i++)
	{
		printf("0x%02X%s", output[i], (i < data_size - 1) ? ", " : "");
		if ((i + 1) % 16 == 0) printf("\n");
	}
	
	printf("\t}\n};\n");
}

int main(int argc, char* argv[]) 
{
	if (argc != 3) usage();
	
	int width, height, channels;
	unsigned char *data = stbi_load(argv[1], &width, &height, &channels, 0);
	if (data) 
	{
		generate_bitmap(argv[2], width, height, data);
		stbi_image_free(data);
	} 
	else 
	{
		error("Womp womp. Failed to load image");
	}
	return 0;
}