#include "utility.h"

string gear_str(int gear)
{
    if(gear == 0) return "N";
    else if(gear == -1) return "R";
    else return to_string(gear);
}

string time_str(float time)
{
    string best_lap_r = to_string(time -  floor((time / 60.0)) * 60.0);
    best_lap_r = string(2 - best_lap_r.substr(0, best_lap_r.find(".")).length(), '0') + best_lap_r;
    return to_string((int)floor((time / 60.0))) + ":" + best_lap_r.substr(0, best_lap_r.find(".")+4);
}


void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color,unsigned int VAO,unsigned int VBO,map<GLchar, Character> Characters)
{
    // activate corresponding render state	
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void udp_loop(SOCKET *sock,char *buffer,SOCKADDR_IN *si_other,int *slen,PacketHeader *pHead,PacketCarTelemetryData *telemetry,PacketLapData *lap_data,PacketCarStatusData *status,PacketCarSetupData *setups,PacketEventData *events,PacketFinalClassificationData *final_class,PacketLobbyInfoData *lobby_info,PacketMotionData *motion,PacketParticipantsData *participants,PacketSessionData *session)
{
    int read;
    bool flag = false;
    while(1)
    {
        read = recvfrom(*sock,buffer,BUFFER_SIZE*2,0,(SOCKADDR *)si_other, slen);

        if(!flag)
        {
            system("cls");
            flag = true;
        }

        if(read == SOCKET_ERROR)
            cout << "Recieving data has failed " << WSAGetLastError() << endl;
        else
        {
            parse(buffer,pHead,telemetry,lap_data,status,setups,events,final_class,lobby_info,motion,participants,session);   
        }
    }
}


DWORD FindProcessId(char* processName)
{
    // strip path

    char* p = strrchr(processName, '\\');
    if(p)
        processName = p+1;

    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if ( processesSnapshot == INVALID_HANDLE_VALUE )
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if ( !strcmp(processName, processInfo.szExeFile) )
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while ( Process32Next(processesSnapshot, &processInfo) )
    {
        if ( !strcmp(processName, processInfo.szExeFile) )
        {
          CloseHandle(processesSnapshot);
          return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

ERSMODE ers_mode(uint8_t ersMode)
{
    ERSMODE ers;
    switch (ersMode)
    {
    case 0:ers.mode = "NONE";ers.color = glm::vec3(0.5,0.5,0.5);break;
    case 1:ers.mode = "MEDIUM";ers.color = glm::vec3(0.98,0.84,0.0);break;
    case 2:ers.mode = "OVERTAKE";ers.color = glm::vec3(0.0,1.0,0.0);break;
    case 3:ers.mode = "HOTLAP";ers.color = glm::vec3(0.67,0.15,0.79);break;
    default:break;
    }
    return ers;
}

FUELMODE fuel_mode(uint8_t fuelMode)
{
    FUELMODE fuel;
    switch (fuelMode)
    {
    case 0:fuel.mode = "LEAN";fuel.color = glm::vec3(1.0,1.0,1.0);break;
    case 1:fuel.mode = "STANDARD";fuel.color = glm::vec3(0.98,0.84,0.0);break;
    case 2:fuel.mode = "RICH";fuel.color = glm::vec3(0.0,1.0,0.0);break;
    case 3:fuel.mode = "MAX";fuel.color = glm::vec3(0.67,0.15,0.79);break;
    default:break;
    }
    return fuel;
}



void ClearScreen()
{	
COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(((DWORD)-11)), cursorPosition);
}