#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std; 
 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
 
// Константы
const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;
 
int main()
{
  //glfw: инициализация и конфигурирование
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  //glfw: creating window
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
    "Ilya Karandeev's computer graphics", NULL, NULL);
  if (window == NULL)
  {
    cout << "Failed to create GLFW window\n" ;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
  // glad: загрузка всех указателей на OpenGL-функции
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    cout << "Failed to initialize GLAD\n";
    return -1;
  }    

 
  //render cicle
  while (!glfwWindowShouldClose(window))
  {
    // Обработка ввода
    processInput(window);
		
    // Выполнение рендеринга
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
 
    // glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
 
  // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
  glfwTerminate();
  return 0;
}
 
// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
 
// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна. 
	// Обратите внимание, что ширина и высота будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}
