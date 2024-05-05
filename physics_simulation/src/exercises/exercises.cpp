#include "exercises/exercises.h"
#include <math.h>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "user_input/user_input.h"
#include "shader_class/shader_class.h"
#include "stb_image/stb_image.h"


// settings
static unsigned int SCR_WIDTH = 192;
static unsigned int SCR_HEIGHT = 108;

// GLSL source code
// Moved into their own files, accessed by Shader_Class now

int exercises()
{
	// glEnable(GL_DEBUG_OUTPUT);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader our_shader_01
	(
		"../src/shader_source/vertex_shader_practice.vs", 
		"../src/shader_source/fragment_shader_01_practice.fs"
	);
	const auto ready_01 = our_shader_01.ready();
	if (!ready_01) {
		std::cout << "ready " << ready_01 << std::endl;
		return -1;
	}
	Shader our_shader_02(
		"../src/shader_source/vertex_shader_practice.vs", 
		"../src/shader_source/fragment_shader_02_practice.fs"
	);
	const auto ready_02 = our_shader_02.ready();
	if (!ready_01) {
		std::cout << "ready " << ready_02 << std::endl;
		return -1;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float vertices1[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	float vertices2[] = {
		 -0.75f, -0.75f, 0.0f,
		 -0.75f, -0.25f, 0.0f,
		 -0.5f, -0.25f, 0.0f,
	};
	unsigned int indices[] = {
	    0, 1, 3,
	    1, 2, 3
	};

	unsigned int VBO[] = {0, 0}, VAO[] = {0, 0};
	gen_gl_objs(VAO, VBO);

	// first triangle setup
	// --------------------
	std::cout << "size of &vertices1: " << sizeof(&vertices1) << std::endl;
	std::cout << "size of vertices1: " << sizeof(vertices1) << std::endl;
	bind_gl_objs(VAO, VBO, vertices1);	
	// glBindVertexArray(VAO[0]);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	vert_attrib_pointer_config();

	// // position attribute
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);
	// // color attribute
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(0);
	// // texture attribute
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// glEnableVertexAttribArray(2);
	
	unsigned int EBO[1] = {0};
	// write_to_element_buffer(EBO, indices);

	glGenBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// second triangle setup
	// ---------------------
	// bind_gl_objs(VAO[1], VBO[1], vertices2);

	// glBindVertexArray(VAO[1]);	// note that we bind to a different VAO now
	// glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);	// and a different VBO
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	// glEnableVertexAttribArray(0);
	// glBindVertexArray(0); 
	// not really necessary as well, but beware of calls that could affect VAOs while this one is bound 
	// (like binding element buffer objects, or enabling/disabling vertex attributes)

	// Texture stuff
	unsigned int texture01 = 0, texture02 = 0;
	// texture 1
	// ---------
	glGenTextures(1, &texture01);
	glBindTexture(GL_TEXTURE_2D, texture01);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char *data1 = stbi_load("../src/container.jpg", &width, &height, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture01);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);

	glGenTextures(1, &texture02);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture02);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("../src/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data2);

	our_shader_01.use(); // don't forget to activate the shader before setting uniforms!  
	glUniform1i(glGetUniformLocation(our_shader_01.id(), "texture01"), 0); // set it manually
	our_shader_01.setInt("texture02", 1); // or with shader class


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture01);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture02);

		our_shader_01.use();
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "out of while loop" << std::endl;
	// glDeleteProgram(our_shader_01.id());
	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteVertexArrays(1, &VAO[1]);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteBuffers(1, &EBO[0]);

	glfwTerminate();
	return 0;
}

void gen_gl_objs(unsigned int *VAO, unsigned int *VBO) {
	// Safe, only throws error if the number of objs to gen is negative.
	glGenVertexArrays(sizeof(VAO)/sizeof(VAO[0]), VAO);
	if (sizeof(VAO)/sizeof(VAO[0]) < 0) {
		std::cout << "ERROR: VAO length is negative" << std::endl;
	}
	glGenBuffers(sizeof(VBO)/sizeof(VBO[0]), VBO);
	if (sizeof(VBO)/sizeof(VBO[0]) < 0) {
		std::cout << "ERROR: VBO length is negative" << std::endl;
	}
}

void bind_gl_objs(unsigned int *VAO, unsigned int *VBO, float (&vertices)[32]) {
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	std::cout << "size of &vertices: " << sizeof(&vertices) << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	std::cout << "size of vertices: " << sizeof(vertices) << std::endl;
}

void vert_attrib_pointer_config() {
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void write_to_element_buffer(unsigned int *EBO, unsigned int *indices) {
	glGenBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}