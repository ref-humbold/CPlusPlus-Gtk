#version 330 core

in vec4 fragmentColor;
in vec4 normVecCamera;
in vec4 eyeDirCamera;
in vec4 lightDirCamera;

out vec4 outColor;

void main()
{
    float distance = length(eyeDirCamera);
    vec4 lightColorSource = vec4(1, 1, 1, 1)*8*exp(-distance);
    vec4 lightColorObserve = vec4(1, 1, 1, 1);
    vec4 ambientCoeff = vec4(0.2, 0.2, 0.2, 1.0);
    vec4 specularCoeff = vec4(0.3, 0.3, 0.3, 1.0);

    vec4 eyeVector = normalize(eyeDirCamera);
    vec4 normalVector = normalize(normVecCamera);
    vec4 lightDirSource = normalize(lightDirCamera);
    vec4 lightDirObserve = normalize(-eyeDirCamera);

    vec4 reflDirSource = normalize( reflect(-lightDirSource, normalVector) );
    vec4 reflDirObserve = normalize( reflect(-lightDirObserve, normalVector) );

    float cosineLightSource = max(dot(normalVector, lightDirSource), 0);
    float cosineReflSource = max(dot(eyeVector, reflDirSource), 0);
    float cosineLightObserve = max(dot(normalVector, lightDirObserve), 0);
    float cosineReflObserve = max(dot(eyeVector, reflDirObserve), 0);

    vec4 ambient = ambientCoeff*fragmentColor;
    vec4 diffuseSource = fragmentColor*lightColorSource*cosineLightSource;
    vec4 specularSource = specularCoeff*lightColorSource*pow(cosineReflSource, 32);
    vec4 diffuseObserve = fragmentColor*lightColorObserve*cosineLightObserve;
    vec4 specularObserve = specularCoeff*lightColorObserve*pow(cosineReflObserve, 6);

    outColor = ambient+diffuseSource+specularSource+diffuseObserve+specularObserve;
}

