#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_class/shader_class.h>
#include <supplemental/supplemental.h>
#include <stb_image/stb_image.h>

#include <iostream>

// settings
static unsigned int SCR_WIDTH = 1920;
static unsigned int SCR_HEIGHT = 1080;

// GLSL source code
// Moved into their own files, accessed by Shader_Class now

int exercises()
{
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
	
	std::cout << "divided by zero I think" << "\n" << std::endl;
	Shader our_shader_01
	(
		"C:\\Users\\benji\\Workspace\\Cpp\\physics_simulations\\src\\shader_source\\vertex_shader_practice.vs", 
		"C:\\Users\\benji\\Workspace\\Cpp\\physics_simulations\\src\\shader_source\\fragment_shader_01_practice.fs"
	);
	std::cout << "made it here in the program :D" << std::endl;

	Shader our_shader_02
	(
		"C:\\Users\\benji\\Workspace\\Cpp\\physics_simulations\\src\\shader_source\\vertex_shader_practice.vs",
		"C:\\Users\\benji\\Workspace\\Cpp\\physics_simulations\\src\\shader_source\\fragment_shader_02_practice.fs"
	);

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

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
	glGenBuffers(2, VBOs);
	// first triangle setup
	// --------------------
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
	// second triangle setup
	// ---------------------
	glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);
	// glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound 
	// (like binding element buffer objects, or enabling/disabling vertex attributes)

	// Texture stuff
	unsigned int texture01, texture02;
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
	unsigned char *data1 = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
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
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
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
	glUniform1i(glGetUniformLocation(our_shader_01.ID, "texture01"), 0); // set it manually
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
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glDeleteProgram(our_shader_01.ID);
	glDeleteVertexArrays(1, &VAOs[0]);
	glDeleteVertexArrays(1, &VAOs[1]);
	glDeleteBuffers(1, &VBOs[0]);
	glDeleteBuffers(1, &VBOs[1]);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}




