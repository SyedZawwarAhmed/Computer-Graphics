#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <cmath>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{
	// First Triangle
	-1.0f, -0.25f * float(sqrt(3)), 0.0f, // Lower left corner
	-0.8f, 0.25f * float(sqrt(3)), 0.0f, // Upper corner
	-0.6f, -0.25f * float(sqrt(3)), 0.0f, // Lower right corner

	// Second Triangle
	-0.6f, -0.25f * float(sqrt(3)), 0.0f, // Lower left corner
	-0.4f, 0.25f * float(sqrt(3)), 0.0f, // Upper corner
	-0.2f, -0.25f * float(sqrt(3)), 0.0f, // Lower right corner

	// Fifth Triangle
	-0.2f, -0.25f * float(sqrt(3)), 0.0f, // Lower left corner
	0.0f, 0.25f * float(sqrt(3)), 0.0f, // Upper corner
	0.2f, -0.25f * float(sqrt(3)), 0.0f, // Lower right corner

	// Fourth Triangle
	0.2f, -0.25f * float(sqrt(3)), 0.0f, // Lower left corner
	0.4f, 0.25f * float(sqrt(3)), 0.0f, // Upper corner
	0.6f, -0.25f * float(sqrt(3)), 0.0f, // Lower right corner

	// Fourth Triangle
	0.6f, -0.25f * float(sqrt(3)), 0.0f, // Lower left corner
	0.8f, 0.25f * float(sqrt(3)), 0.0f, // Upper corner
	1.0f, -0.25f * float(sqrt(3)), 0.0f, // Lower right corner
};

GLuint indices[] =
{
	0, 1, 2, // First Triangle
	3, 4, 5, // Second Triangle
	6, 7, 8, // Third Triangle
	9, 10, 11, // Fourth Triangle
	12, 13, 14 // Fifth Triangle
};

GLuint circleIndices[] =
{
	0, 1, 2
};

const int windowWidth = 1600;
const int windowHeight = 900;

const float PI = 3.14159265359f;
const int circlePoints = 100;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 1600 by 900 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Mountains", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 1600, y = 900
	glViewport(0, 0, windowWidth, windowHeight);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Calculate the points of the circle
	GLfloat circleVertices[circlePoints * 3]; // 3 coordinates (x, y, z) per point
	float radius = 0.1f; // Circle radius
	float x, y;
	const float circleXOffset = 0.8f, circleYOffset = 0.7f;
	for (int i = 0; i < circlePoints; ++i)
	{
		x = circleXOffset + radius * cos(2 * PI * i / circlePoints);
		y = circleYOffset + radius * sin(2 * PI * i / circlePoints) * static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
		circleVertices[i * 3] = x;
		circleVertices[i * 3 + 1] = y;
		circleVertices[i * 3 + 2] = 0.0f;
	}

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Generates Vertex Array Object and binds it
	VAO VAO2;
	VAO2.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO2(circleVertices, sizeof(circleVertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO2(circleIndices, sizeof(circleIndices));

	// Links VBO to VAO
	VAO2.LinkVBO(VBO2, 0);
	// Unbind all to prevent accidentally modifying them
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	// Use shaderProgram's ID to get the location of the uniform variable
	GLint circleColorLocation = glGetUniformLocation(shaderProgram.ID, "circleColor");

	// Set the color you want for the circle (e.g., yellow)
	glUniform3f(circleColorLocation, 1.0f, 1.0f, 0.0f);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0); // First Triangle
		//glDrawElements(GL_ROUND)
		VAO2.Bind();
		glDrawArrays(GL_LINE_LOOP, 0, circlePoints);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}