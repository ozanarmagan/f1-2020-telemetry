
#ifndef _udp_server_h
#define _udp_server_h

#include "../parser/parser.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../utility/utility.h"
#include "../shader/shader.h"




#pragma comment(lib,"ws2_32.lib")




void udp_server(unsigned short port);



#endif