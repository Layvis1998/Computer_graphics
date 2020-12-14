#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

//starting window size values
const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;

//vertex and fragment shaders written in glsl (gl shader language)
const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char* fragmentShaderSource = 
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);\n"
  "}\n\0";




void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
 
//each time the window size is changed, this function is being called
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

 
int main()
{
  //initializing glfw
  glfwInit();                                      
  //choosing glfw version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);    
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  
  //choosing OpenGL mod
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfw: creating window
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
    "Ilya Karandeev's computer graphics", NULL, NULL);

  //Processing a situation in which a window has failed to being created
  if (window == NULL)
  {
    cout << "Failed to create GLFW window\n" ;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
  //Loading pointers on OpenGl functions, processing error of this operation
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    cout << "Failed to initialize GLAD\n";
    return -1;
  }    
 
  //Compiling shader program
 
  //Vertex shader
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
 
  //Checking successfull compiling
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    cout << "ERROR: vertex shader not compiled\n" << infoLog << "\n";
  }
 
  //Fragment shader
  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
 
  //checking compilation correctness
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    cout << "ERROR: fragment shader not compiled\n" << infoLog << "\n";
  }
 
  //binding shaders into a shader program
  int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
 
  //Checking linking correctness
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      cout << "ERROR: shader program not linked\n" << infoLog << "\n";
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader); 
 
 
  float vertices[] =
  {
    -0.5f, -0.5f, 0.0f,  
    0.5f, -0.5f, 0.0f,  
    0.0f,  0.5f, 0.0f      
  };
 
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
 

  glBindVertexArray(VAO); 
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
 
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
   
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
   

  //render cicle
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);
		
    //changing color
    glClearColor(0.2f, 0.7f, 0.5f, 0.5f);   //context change function
    glClear(GL_COLOR_BUFFER_BIT);           //the function that applies changes
 


    //drawing triangle    
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); 
    glDrawArrays(GL_TRIANGLES, 0, 3);

    
    //front & back buffer contents interchange
    glfwSwapBuffers(window);
    
    //This function processes only those events that are already in the event
    //queue and then returns immediately. Processing events will cause the
    //window and input callbacks associated with those events to be called.
    glfwPollEvents();
  }
 
  //glfw: terminating, freeing all allocated resources
  glfwTerminate();
  return 0;
}
