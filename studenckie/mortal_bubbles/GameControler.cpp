#include "GameControler.hpp"

using namespace glm;

void GameControler::drawGame(GLuint pID)
{
    player->drawPlayer(pID, view, proj, lightSource);
    bubble->drawAllBubbles(pID, view, proj, lightSource);
    aqua->drawCube(pID, view, proj, lightSource);
}

void GameControler::restart()
{
    player->restart( 0.9f*aqua->getSide() );
    bubble->elements.clear();
    setCamera();
}

void GameControler::restartMoves()
{
    playerMoves.clear();
    playerMoves.push_back( vec4(0.0f, 0.0f, -1.0f, 1.0f) ); //W
    playerMoves.push_back( vec4(0.0f, 0.0f, 1.0f, 1.0f) );  //X
    playerMoves.push_back( vec4(0.0f, 1.0f, 0.0f, 1.0f) );  //E
    playerMoves.push_back( vec4(0.0f, -1.0f, 0.0f, 1.0f) ); //Z
    playerMoves.push_back( vec4(-1.0f, 0.0f, 0.0f, 1.0f) ); //A
    playerMoves.push_back( vec4(1.0f, 0.0f, 0.0f, 1.0f) );  //D
}

void GameControler::setCamera()
{
    if(viewInside)
    {
        vec3 p = player->getRadPos().second;

        cameraPos = vec3( p[0], p[1], p[2]+0.1f );
        cameraDir = vec3( p[0], p[1], p[2] );
        persBegin = 0.05f;
        persStep = 2.0f;
    }
    else
    {
        cameraPos = vec3(0.0f, 0.0f, 3.0f);
        cameraDir = vec3(0.0f, 0.0f, 0.0f);
        persBegin = 1.0f;
        persStep = 4.0f;
    }

    fov = PI_CONST/4;
    view = lookAt( cameraPos, cameraDir, vec3(0.0f, 1.0f, 0.0f) );
    proj = perspective(fov, (1.0f*windowW)/windowH, persBegin, persBegin+persStep);
    restartMoves();
}

void GameControler::changeCamera()
{
    viewInside = !viewInside;
    setCamera();
}

void GameControler::viewScale(GLfloat zoom)
{
    fov *= zoom;
    fov = min(fov, PI_CONST/2);
    fov = max(fov, PI_CONST/6);
    proj = perspective(fov, (1.0f*windowW)/windowH, persBegin, persBegin+persStep);
}

void GameControler::viewRotate(GLfloat angleRad, vec3 axis)
{
    if(viewInside)
    {
        mat4 tr1 = mat4( vec4(1.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f),
            vec4(0.0f, 0.0f, 1.0f, 0.0f), vec4(0.0f, 0.0f, 0.1f, 1.0f) );
        mat4 rt = toMat4( angleAxis(angleRad, axis) );
        mat4 rtMv = toMat4( angleAxis(-angleRad, axis) );
        mat4 tr2 = mat4( vec4(1.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f),
            vec4(0.0f, 0.0f, 1.0f, 0.0f), vec4(0.0f, 0.0f, -0.1f, 1.0f) );

        auto rtMove = [=](vec4 v)
            {
                return rtMv*v;
            };

        std::transform(playerMoves.begin(), playerMoves.end(), playerMoves.begin(), rtMove);
        view = tr2*rt*tr1*view;
    }
    else
        view = rotate(view, angleRad, axis);
}

int GameControler::checkCollisionBubble()
{
    std::pair <GLfloat, vec3> ply = player->getRadPos();

    for(auto it = bubble->elements.begin(); it != bubble->elements.end(); ++it)
    {
        if(distance(std::get<1>(*it), ply.second) <= std::get<0>(*it)+ply.first)
            return std::get<3>(*it);
    }

    return 0;
}

bool GameControler::checkEndRound()
{
    std::pair <GLfloat, vec3> ply = player->getRadPos();
    std::tuple <GLfloat, vec3, vec3> egb = bubble->endGameBubble;

    return distance(std::get<1>(egb), ply.second) <= std::get<0>(egb)+ply.first;
}

void GameControler::deletePointedBubble(int ix)
{
    auto indexing = [=](std::tuple <GLfloat, vec3, vec3, int> b)
        {
            return std::get<3>(b) == ix;
        };

    bubble->elements.remove_if(indexing);
}

GLfloat GameControler::moveBubbles(GLfloat delta, GLfloat counter, int freq)
{
    bubble->move(delta, aqua->getSide());

    if(counter >= 0.2f/freq)
    {
        bubble->showUp(aqua->getSide());
        counter = 0.0f;
    }

    return counter;
}

void GameControler::movePlayer(GLfloat delta, std::vector <bool> movesMask)
{
    GLfloat side = aqua->getSide();
    std::pair <GLfloat, vec3> ply = player->getRadPos();
    vec3 mvPlayer = vec3(0.0f, 0.0f, 0.0f);

    for(unsigned int i = 0; i < movesMask.size(); ++i)
        if( movesMask[i] )
        {
            mvPlayer[0] += playerMoves[i][0];
            mvPlayer[1] += playerMoves[i][1];
            mvPlayer[2] += playerMoves[i][2];
        }

    vec3 moveVector = mvPlayer*delta;
    vec3 nextPos = ply.second+moveVector;

    if(nextPos[0] > side-ply.first || nextPos[0] < -side+ply.first
        || nextPos[1] > side-ply.first || nextPos[1] < -side+ply.first
        || nextPos[2] > side-ply.first || nextPos[2] < -side+ply.first)
        moveVector = vec3(0.0f, 0.0f, 0.0f);

    if(viewInside)
    {
        player->move(moveVector);
        view = translate(view, -moveVector);
    }

    player->move(moveVector);
}

vec3 GameControler::getMousePos(GLFWwindow * window)
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    vec3 res = vec3( 2.0f*x/windowW-1.0f, -(2.0f*y/windowH-1.0f), 0.0f );
    GLfloat ln = res[0]*res[0]+res[1]*res[1];

    if(ln <= 1.0f)
        res[2] = sqrt(1.0f-ln);

    return res;
}

std::vector <bool> GameControler::checkKeyPress(GLFWwindow * window, std::vector <int> & keys)
{
    std::vector <bool> result(keys.size());

    auto pressed = [=](int k) -> bool
        {
            return glfwGetKey(window, k) == GLFW_PRESS;
        };

    std::transform(keys.begin(), keys.end(), result.begin(), pressed);

    return result;
}

bool GameControler::checkMouseAction(GLFWwindow * window, int action)
{
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == action;
}

void GameControler::checkTabReleased(GLFWwindow * window)
{
    while(glfwGetKey(window, GLFW_KEY_TAB) != GLFW_RELEASE)
        glfwPollEvents();
}
