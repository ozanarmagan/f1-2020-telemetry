#ifndef __utility_h
#define __utility_h

#include "../templates/handler.h"
#include "../parser/parser.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <WinSock2.h>
#include <iomanip>
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
#include "../shader/shader.h"
#include <tlhelp32.h>
using namespace std;
#define BUFFER_SIZE 2048
/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

struct ERSMODE {
    std::string mode;
    glm::vec3 color;
};

struct FUELMODE {
    std::string mode;
    glm::vec3 color;
};



std::string gear_str(int gear);
std::string time_str(float time);
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color,unsigned int VAO,unsigned int VBO,std::map<GLchar, Character> Characters);
void udp_loop(SOCKET *sock,char *buffer,SOCKADDR_IN *si_other,int *slen,PacketHeader *pHead,PacketCarTelemetryData *telemetry,PacketLapData *lap_data,PacketCarStatusData *status,PacketCarSetupData *setups,PacketEventData *events,PacketFinalClassificationData *final_class,PacketLobbyInfoData *lobby_info,PacketMotionData *motion,PacketParticipantsData *participants,PacketSessionData *session);
DWORD FindProcessId(char* processName);
ERSMODE ers_mode(uint8_t ersMode);
FUELMODE fuel_mode(uint8_t fuelMode);
void ClearScreen();

#endif