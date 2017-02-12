#include "Camera.hpp"

using namespace glm;

int Camera::getDims()
{
    return dims;
}

void Camera::changeDims()
{
    dims = 5-dims;
    cameraCoeffs = vec2(0.0f, 0.0f);

    if(dims == 2)
    {
        view = lookAt( vec3(cameraMapPos[0], cameraMapPos[1], 0.0f),
                       vec3(cameraMapPos[0], cameraMapPos[1], -1.0f),
                       vec3(0.0f, 1.0f, 0.0f) );
        sc = mat4( vec4(1.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f),
                   vec4(0.0f, 0.0f, 1.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) );
        cameraCoeffs[0] = degrees(cameraMapPos[0]/MERCATOR);
        cameraCoeffs[1] = degrees(2.0f*atan( exp(cameraMapPos[1]/MERCATOR) )-PI_CONST/2);
    }
    else
    {
        view = lookAt(cameraEarthPos, cameraDir3D(), vec3(0.0f, 1.0f, 0.0f) );
        fov = PI_CONST/3;
        proj = perspective(fov, (1.0f*windowW)/windowH, persBegin, persLength);
    }
}

void Camera::drawEarth(GLuint pID, Earth * earth)
{
    mat4 cameraMat = proj*view;

    earth->draw(pID, cameraMat);
}

void Camera::drawTerrain(GLuint pID, const std::vector<Area *> & areas, Detailing * details)
{
    mat4 cameraMat = dims == 2 ? sc*view : proj*view;

    for(auto ar : areas)
        if( areaInside(ar, cameraMat) )
            ar->draw(pID, cameraMat, details, dims);
}

long long int Camera::getTriangles(const std::vector<Area *> & areas, Detailing * details)
{
    long long int totalTriangles = 0LL;
    mat4 cameraMat = dims == 2 ? sc*view : proj*view;

    for(auto ar : areas)
        if( areaInside(ar, cameraMat) )
            totalTriangles += details->getTriangles();

    return totalTriangles;
}

vec2 Camera::getGeoCenter()
{
    return cameraCoeffs;
}

GLfloat Camera::getZoom()
{
    return dims == 2 ? log( sc[0][0] ) : -9.6f/PI_CONST*fov+3.2;
}

void Camera::viewScale(GLfloat zoom)
{
    if(dims == 2)
    {
        for(int i = 0; i < 3; ++i)
            sc[i][i] *= zoom;
    }
    else
    {
        fov *= zoom;
        fov = std::min(fov, PI_CONST/2);
        fov = std::max(fov, PI_CONST/6);
        proj = perspective(fov, (1.0f*windowW)/windowH, persBegin, persLength);
    }
}

void Camera::resetScale()
{
    fov = PI_CONST/3;
    proj = perspective(fov, (1.0f*windowW)/windowH, persBegin, persLength);

    for(int i = 0; i < 3; ++i)
            sc[i][i] = 1.0f;
}

void Camera::viewRotate(GLfloat angleDeg, bool latitudeAlong)
{
    if(dims == 3 && latitudeAlong)
    {
        view = rotate( view, -angleDeg, vec3(0.0f, 1.0f, 0.0f) );
        cameraCoeffs[0] += angleDeg;

        if(cameraCoeffs[0] > 180.0f)
            cameraCoeffs[0] -= 360.0f;

        if(cameraCoeffs[0] <= -180.0f)
            cameraCoeffs[0] += 360.0f;
    }
    else if(dims == 3 && !latitudeAlong)
    {
        if(abs(cameraCoeffs[1]+angleDeg) <= 80.0f)
        {
            GLfloat lng = radians(cameraCoeffs[0]);

            cameraCoeffs[1] += angleDeg;
            view = rotate( view, angleDeg, vec3( cos(lng), 0.0f, -sin(lng) ) );
        }
    }
}

void Camera::cameraRotate(GLfloat angleDeg)
{
    if(dims == 3)
    {
        GLfloat camPosX = distance*cos( radians(cameraCoeffs[1]) )*sin( radians(cameraCoeffs[0]) );
        GLfloat camPosY = distance*sin( radians(cameraCoeffs[1]) );
        GLfloat camPosZ = distance*cos( radians(cameraCoeffs[1]) )*cos( radians(cameraCoeffs[0]) );

        view = rotate( view, -angleDeg, vec3(camPosX, camPosY, camPosZ) );
    }
}

void Camera::viewTranslate(vec3 trans)
{
    if(dims == 2)
    {
        trans /= sc[0][0];
        cameraMapPos[0] += trans[0];
        cameraMapPos[1] += trans[1];
        cameraCoeffs[0] = degrees(cameraMapPos[0]/MERCATOR);
        cameraCoeffs[1] = degrees(2.0f*atan( exp(cameraMapPos[1]/MERCATOR) )-PI_CONST/2);
        view = translate(view, -trans);
    }
}

std::vector <bool> Camera::checkKeyPress(GLFWwindow * window, std::vector <int> & keys)
{
    std::vector <bool> result(keys.size());

    auto pressed = [=](int k) -> bool
        {
            return glfwGetKey(window, k) == GLFW_PRESS;
        };

    std::transform(keys.begin(), keys.end(), result.begin(), pressed);

    return result;
}

vec3 Camera::cameraDir3D()
{
    return vec3(0.0f, distance, 0.0f);
}

bool Camera::areaInside(Area * area, mat4 cameraMat)
{
    std::pair<vec4, vec4> corners = area->getCorners(dims);
    vec4 leftdown = cameraMat*corners.first;
    vec4 rightup = cameraMat*corners.second;

    if(dims == 2)
        return std::min(rightup[0], rightup[3]) >= std::max(leftdown[0], -leftdown[3])
               && std::min(rightup[1], rightup[3]) >= std::max(leftdown[1], -leftdown[3])
               && std::min(rightup[2], rightup[3]) >= std::max(leftdown[2], -leftdown[3]);
    else
        return true;
}
