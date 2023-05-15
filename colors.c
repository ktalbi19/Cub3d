unsigned long createRGBA(int r, int g, int b, int a)
{   
    return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8))
}

nt			from_rgb_to_hex(t_rgb color)
{
	int		output;

	output = 256 * 256 * color.r + 256 * color.g + color.b;
	return (output);
}