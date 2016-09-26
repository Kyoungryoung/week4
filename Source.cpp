
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 1000;
const int height = 700;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1)
	{
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}

	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void circle(const int& i, const int& j, const int& r, const float& red, const float& green, const float& blue)
{
	double d = 0.0;
	float angle = 360.0;
	int x = 0, y = 0;

	for (angle = 0; angle < 360; angle++)
	{
		d = angle*(3.14 / 180);
		x = i + r*sin(d);
		y = j + r*cos(d);
		drawPixel(x, y, red, green, blue);
		drawPixel(x + 1, y, red, green, blue);
		drawPixel(x, y - 1, red, green, blue);
	}

}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

	for (int i = 0; i<width*height; i++) {
		pixels[i * 3 + 0] = 1.0f; // red 
		pixels[i * 3 + 1] = 1.0f; // green
		pixels[i * 3 + 2] = 1.0f; // blue
	}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		double xpos, ypos;
		double dist;

		// 1_1
		circle(100, 560, 50, 1.0f, 0.0f, 0.0f);
		
		glfwGetCursorPos(window, &xpos, &ypos);
		dist =((xpos - 100)*(xpos - 100) + (ypos - 120)*(ypos - 120));
		if (dist < (50*50)) {
			circle(100, 560, 50, 0.0f, 1.0f, 0.0f);
		}
		for (int i = 0; i<4; i++)
			drawLine(70, 540 + i, 125, 580 + i, 1.0f, 0.0f, 0.0f);

		//1_2
		circle(250, 560, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 250)*(xpos - 250) + (ypos - 120)*(ypos - 120));
		if (dist < (50 * 50)) {
			circle(250, 560, 50, 0.0f, 1.0f, 0.0f);
		}
		for (int i = 0; i < 5; i++)
			circle(250+i, 560, 20, 1.0f, 0.0f, 0.0f);
		

		//1_3
		circle(400, 560, 50, 1.0f, 0.0f, 0.0f);

		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 400)*(xpos - 400) + (ypos - 120)*(ypos - 120));
		if (dist < (50 * 50)) {
			circle(400, 560, 50, 0.0f, 1.0f, 0.0f);
		}
		drawLine(380, 540, 420, 540, 1.0f, 0.0f, 0.0f);
		drawLine(380, 540, 380, 575, 1.0f, 0.0f, 0.0f);
		drawLine(380, 575, 420, 575, 1.0f, 0.0f, 0.0f);
		drawLine(420, 540, 420, 575, 1.0f, 0.0f, 0.0f);
		

		//1_4
		circle(550, 560, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 550)*(xpos - 550) + (ypos - 120)*(ypos - 120));
		if (dist < (50 * 50)) {
			circle(550, 560, 50, 0.0f, 1.0f, 0.0f);
		}
		drawLine(525, 540, 575, 580, 1.0f, 0.0f, 0.0f);
		drawLine(525, 580, 575, 540, 1.0f, 0.0f, 0.0f);
		

		//1_5
		circle(700, 560, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 700)*(xpos - 700) + (ypos - 120)*(ypos - 120));
		if (dist < (50 * 50)) {
			circle(700, 560, 50, 0.0f, 1.0f, 0.0f);
		}

		drawLine(700, 540, 700, 580, 1.0f, 0.0f, 0.0f);
		drawLine(690, 550, 700, 540, 1.0f, 0.0f, 0.0f);
		drawLine(700, 540, 710, 550, 1.0f, 0.0f, 0.0f);
	

		//2_1
		circle(100, 360, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 100)*(xpos - 100) + (ypos - 300)*(ypos - 300));
		if (dist < (50 * 50)) {
			circle(100, 360, 50, 0.0f, 1.0f, 0.0f);
		}

		drawLine(70, 360, 125, 360, 1.0f, 0.0f, 0.0f);
		drawLine(110, 370, 125, 360, 1.0f, 0.0f, 0.0f);
		drawLine(110, 350, 125, 360, 1.0f, 0.0f, 0.0f);

		//2_2
		circle(250, 360, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 250)*(xpos - 250) + (ypos - 300)*(ypos - 300));
		if (dist < (50 * 50)) {
			circle(250, 360, 50, 0.0f, 1.0f, 0.0f);
		}
		drawLine(240, 360, 260, 360, 1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 2; i++) 
			drawLine(230, 340 + i, 250, 380 + i, 1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 2; i++) 
			drawLine(250, 380 + i, 270, 340 + i, 1.0f, 0.0f, 0.0f);

		//2_3
		circle(400, 360, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 400)*(xpos - 400) + (ypos - 300)*(ypos - 300));
		if (dist < (50 * 50)) {
			circle(400, 360, 50, 0.0f, 1.0f, 0.0f);
		}
		drawLine(400, 330, 400, 390, 1.0f, 0.0f, 0.0f);

		//2_4
		circle(550, 360, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 550)*(xpos - 550) + (ypos - 300)*(ypos - 300));
		if (dist < (50 * 50)) {
			circle(550, 360, 50, 0.0f, 1.0f, 0.0f);
		}
		drawLine(525, 360, 575, 360, 1.0f, 0.0f, 0.0f);
		drawLine(525, 360, 540, 370, 1.0f, 0.0f, 0.0f);
		drawLine(525, 360, 540, 350, 1.0f, 0.0f, 0.0f);

		//2_5
		circle(700, 360, 50, 1.0f, 0.0f, 0.0f);
		glfwGetCursorPos(window, &xpos, &ypos);
		dist = ((xpos - 700)*(xpos - 700) + (ypos - 300)*(ypos - 300));
		if (dist < (50 * 50)) {
			circle(700, 360, 50, 0.0f, 1.0f, 0.0f);
		}
		drawLine(700, 340, 700, 380, 1.0f, 0.0f, 0.0f);
		drawLine(690, 370, 700, 380, 1.0f, 0.0f, 0.0f);
		drawLine(700, 380, 710, 370, 1.0f, 0.0f, 0.0f);

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
