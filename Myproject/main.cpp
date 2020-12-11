#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

//starting window size values
const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;

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
 
  //render cicle
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);
		
    //changing color
    glClearColor(0.2f, 0.7f, 0.5f, 0.5f);   //context change function
    glClear(GL_COLOR_BUFFER_BIT);           //the function that applies changes
 
    //glfw: обмен содержимым front- и back- буферов. Отслеживание событий
    //ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
 
  //glfw: terminating, freeing all allocated resources
  glfwTerminate();
  return 0;
}
