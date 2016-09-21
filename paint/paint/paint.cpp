#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 600;
const int height = 400;

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
	//삼각형
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);


	}
	for (int i = i0; i <= i0 + 140; i++)
	{
		const int j = (j0 - j0)*(i - i0) / (i0 + 140 - i0) + j0;

		drawPixel(i, j, red, green, blue);


	}
	for (int i = i1; i <= i0 + 140; i++)
	{
		const int j = (j0 - j1)*(i - i1) / (i0 + 140 - i1) + j1;

		drawPixel(i, j, red, green, blue);


	}
	//오각형
	for (int i = i0 + 190; i <= i0 + 240; i++)
	{
		const int j = (j0 - j0)*(i - (i0 + 190)) / (i0 + 240 - (i0 + 190)) + j0;

		drawPixel(i, j, red, green, blue);

	}
	for (int i = i0 + 160; i <= i0 + 190; i++)
	{
		const int j = (j0 + 35 - j0)*(i - (i0 + 190)) / (i0 + 160 - (i0 + 190)) + j0;

		drawPixel(i, j, red, green, blue);

	}

	for (int i = i0 + 160; i <= i0 + 215; i++)
	{
		const int j = (j0 + 100 - (j0 + 35))*(i - (i0 + 160)) / (i0 + 215 - (i0 + 160)) + j0 + 35;

		drawPixel(i, j, red, green, blue);

	}
	for (int i = i0 + 215; i <= i0 + 270; i++)
	{
		const int j = (j0 + 100 - (j0 + 35))*(i - (i0 + 215)) / (i0 + 215 - (i0 + 270)) + j0 + 100;

		drawPixel(i, j, red, green, blue);

	}
	for (int i = i0 + 240; i <= i0 + 270; i++)
	{
		const int j = (j0 + 35 - j0)*(i - (i0 + 240)) / (i0 + 270 - (i0 + 240)) + j0;

		drawPixel(i, j, red, green, blue);

	}

	//원 r=50, (380,60)  (i - (i0 + 350))*(i - (i0 + 350)) + (j-(j0+30))* (j-(j0+30)) =2500;

	for (int i = i0 + 300; i <= i0 + 400; i++)
	{
		int j;

		j = sqrt(2500 - (i - (i0 + 350))*(i - (i0 + 350))) + (j0 + 30);


		drawPixel(i, j, red, green, blue);
		int k;

		k= -sqrt(2500 - (i - (i0 + 350))*(i - (i0 + 350))) + (j0 + 30);
		drawPixel(i, k, red, green, blue);
	}

	//기울어진사각형
	
	
	//절편의함수를 만든후 for문으로 반복실행 y = ((j0 + 140) - (j0 + 170)) / (i0 - (i0 - 20)) * (x - i0) + j0 + 140;
	
	for (int i = i0 - 20; i <= i0 + 120; i++)
	{
		for (int x = i0 - 20; x <= i0; x++)
		{
		
		const int	y = ((j0 + 140) - (j0 + 170)) / (i0 - (i0 - 20)) * (x - i0) + j0 + 140;
				const int j = (j0 + 220 - (j0 + 170))*(i - (x)) / (i0 + 120 - (i0 - 20)) + y;

			drawPixel(i, j, red, green, blue);
		}
	}

	

	//사각형
	for (int i = i0 + 190; i <= i0 + 290; i++)
	{
		const int j = (j0 + 240 - (j0 + 240))*(i - (i0 + 190)) / (i0 + 290 - (i0 + 190)) + j0 + 240;

		drawPixel(i, j, red, green, blue);

	}
	for (int i = i0 + 190; i <= i0 + 290; i++)
	{
		const int j = (j0 + 140 - (j0 + 140))*(i - (i0 + 190)) / (i0 + 290 - (i0 + 190)) + j0 + 140;

		drawPixel(i, j, red, green, blue);

	}
	for (int j = j0 + 140; j <= j0 + 240; j++)
	{
		const int i = (i0 + 190 - (i0 + 190)) / (j0 + 240 - (j0 + 140)) * (j - (j0 + 140)) + i0 + 190;

		drawPixel(i, j, red, green, blue);

	}
	for (int j = j0 + 140; j <= j0 + 240; j++)
	{
		const int i = (i0 + 290 - (i0 + 290)) / (j0 + 240 - (j0 + 140)) * (j - (j0 + 140)) + i0 + 290;

		drawPixel(i, j, red, green, blue);

	}

	//색깔있는 사각형
	
	for (int k = 140; k <= 240; k++) //색깔 입히기
	{
		for (int i = i0 + 370; i <= i0 + 470; i++)
		{
			const int j = (j0 + 140 - (j0 + 140))*(i - (i0 + 370)) / (i0 + 470 - (i0 + 370)) + j0 + k;

			drawPixel(i, j, red, green, blue);

		}
	}
	
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	drawLine(30, 30, 100, 100, 1.0f, 0.0f, 0.0f);


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

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

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

