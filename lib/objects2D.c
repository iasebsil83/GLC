//images
void GLC_image(unit x, unit y, unit width, unit height, color* data){
	glRasterPos2i(x,y);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);
}
