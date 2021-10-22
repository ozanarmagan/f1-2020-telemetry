#include "udp_server.h"


unsigned int VAO, VBO;
// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 500;


PacketHeader pHead;
PacketCarTelemetryData telemetry;
PacketLapData lap_data;
PacketCarStatusData status;
PacketCarSetupData setups;
PacketEventData events;
PacketFinalClassificationData final_class;
PacketLobbyInfoData lobby_info;
PacketMotionData motion;
PacketParticipantsData participants;
PacketSessionData session;
std::map<GLchar, Character> Characters;

#define BUFFER_SIZE 2048

using namespace std;
using namespace glm;


std::string operator*(const string& s, unsigned int n) {
    stringstream out;
    while (n--)
        out << s;
    return out.str();
}

std::string operator*(unsigned int n, const string& s) { return s * n; }


void udp_server(unsigned short port)
{
    WSADATA wsa;
    cout << "Initializing WinSock" << endl;

    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cout << "Fail on initialization" << WSAGetLastError();
        exit(EXIT_FAILURE);
    }

    SOCKET sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sock == SOCKET_ERROR)
    {
        cout << "Socket Creation Error" << WSAGetLastError();
        exit(EXIT_FAILURE);
    }

    if(FindProcessId((char*)"F1_2020_dx12.exe") == 0)
        cout << "WARNING: Please start the game first !" << endl;

    cout << "Connection established" <<endl;

    SOCKADDR_IN si_other = {};
    int slen = sizeof(si_other);
    si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	si_other.sin_addr.s_addr = INADDR_ANY;

    int result = bind(sock,(SOCKADDR*)&si_other,sizeof(si_other));
    if (result == SOCKET_ERROR) {
        cout << "Socket bind failed. Error: " << WSAGetLastError() << endl;
        exit(1);
    }

    cout << "Socket binded" << endl << "Waiting for data to receive..." << endl;

    char buffer[BUFFER_SIZE*2];
    int read;

    bool flag = false;

    cout << "Rendering OpenGL window...";

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sim Telemetry", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    
    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // compile and setup the shader
    // ----------------------------
    Shader shader("./shader/text.vs", "./shader/text.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

	// find path to font
    std::string font_name = "C:/Users/Ozan/Desktop/f1/font.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
    }
	
	// load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 200);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    
    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glfwSwapInterval(0);
    thread t1(udp_loop,&sock,buffer,&si_other,&slen,&pHead,&telemetry,&lap_data,&status,&setups,&events,&final_class,&lobby_info,&motion,&participants,&session);
    float speed_offset = 0;
    ERSMODE ers;
    FUELMODE fuel;
    while(1)
    {
        
        if(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_speed < 10)
            speed_offset = 40.0f;
        else if(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_speed < 100)
            speed_offset = 20.0f;
        else
            speed_offset = 0.0f;
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        RenderText(shader, gear_str(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_gear), 365.0f, 260.0f, 1.3f, glm::vec3(1.0, 1.0, 1.0),VAO,VBO,Characters);
        RenderText(shader, to_string(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_speed), 380.0f + speed_offset, 170.0f, 0.35f, glm::vec3(0.3, 0.7f, 0.9f),VAO,VBO,Characters);
        RenderText(shader, time_str(lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_bestLapTime), 307.0f, 100.0f, 0.35f, glm::vec3(0.8, 0.7f, 0.9f),VAO,VBO,Characters);
        RenderText(shader, time_str(lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_lastLapTime), 348.0f, 40.0f, 0.25f, glm::vec3(1.0,1.0,1.0),VAO,VBO,Characters);
        RenderText(shader, "P" + to_string(lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_carPosition), 30.0f, 420.0f, 0.22f, glm::vec3(1.0,1.0,1.0),VAO,VBO,Characters);
        RenderText(shader, time_str(lap_data.m_lapData[lap_data.m_header.m_playerCarIndex].m_currentLapTime), 30.0f, 370.0f, 0.22f, glm::vec3(1.0,1.0,1.0),VAO,VBO,Characters);
        RenderText(shader, "DRS", 30.0f, 280.0f, 0.22f, (telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_drs == 1 ? glm::vec3(0.0,1.0,0.0) : glm::vec3(0.5,0.5,0.5)) ,VAO,VBO,Characters);
        ers = ers_mode(status.m_carStatusData[pHead.m_playerCarIndex].m_ersDeployMode);
        fuel = fuel_mode(status.m_carStatusData[pHead.m_playerCarIndex].m_fuelMix);
        RenderText(shader,ers.mode, 30.0f, 230.0f, 0.22f, ers.color ,VAO,VBO,Characters);
        RenderText(shader,fuel.mode, 30.0f, 180.0f, 0.22f, fuel.color ,VAO,VBO,Characters);
        glDisable(GL_BLEND);
        if(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_revLightsPercent <= 40)
            RenderText(shader,string("I")*((unsigned int)telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_revLightsPercent), 0.0f, 480.0f, 0.2f, glm::vec3(0.0,1.0,0.0),VAO,VBO,Characters);
        else if(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_revLightsPercent <= 80)
            RenderText(shader,string("I")*((unsigned int)telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_revLightsPercent), 0.0f, 480.0f, 0.2f, glm::vec3(1.0,0.0,0.0),VAO,VBO,Characters);
        else
            RenderText(shader,string("I")*((unsigned int)telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_revLightsPercent), 0.0f, 480.0f, 0.2f, glm::vec3(0.0,0.0,1.0),VAO,VBO,Characters);
        RenderText(shader,string("I")*(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_throttle*100), 30.0f, 60.0f, 0.05f, glm::vec3(0.0,1.0,0.0),VAO,VBO,Characters);
        RenderText(shader,string("I")*(telemetry.m_carTelemetryData[telemetry.m_header.m_playerCarIndex].m_brake*100), 30.0f, 40.0f, 0.05f, glm::vec3(1.0,0.0,0.0),VAO,VBO,Characters);
        
        glEnable(GL_BLEND);
        glfwSwapBuffers(window);
        glfwPollEvents();
    



    }

}